//
// AsyncFunction.h
//
// Library: JS/Core
// Package: Execution
// Module:  AsyncFunction
//
// Definition of the AsyncFunction class tempalte and friends.
//
// Copyright (c) 2021, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_AsyncFunction_INCLUDED
#define JS_Core_AsyncFunction_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/Runnable.h"
#include "Poco/Exception.h"
#include "v8.h"
#include <memory>
#include <functional>


namespace Poco {
namespace JS {
namespace Core {


template <typename TParameterType, typename TResultType>
class AsyncFunctionRunner: public Poco::Runnable
	/// A utility class template for implementing asynchronous JavaScript
	/// functions in C++. Asynchronous functions implemented with this
	/// template take an argument, perform their job in a separate thread
	/// taken from the default Poco::ThreadPool, and return a Promise.
	///
	/// When implementing an asynchronous function with AsyncFunctionRunner,
	/// two functions need to be provided. One (evaluateFunc) to do the actual work,
	/// taking the parameter (converted to a C++ type) as argument, and
	/// returning a C++ type, and a second one (convertResultFunc) that converts 
	/// the returned C++ value to a v8::Local<v8::Value> that is used to resolve the
	/// Promise. In case evaluateFunc throws, the Promise will be automatically
	/// rejected.
{
public:
	using ParameterType = TParameterType;
	using ResultType = TResultType;
	using EvaluateFunc = std::function<ResultType (const ParameterType&)>;
	using ConvertResultFunc = std::function<v8::Local<v8::Value> (v8::Local<v8::Context>&, const ResultType&)>;

	static void start(const v8::FunctionCallbackInfo<v8::Value>& args, v8::Local<v8::Context>& context, EvaluateFunc&& evaluateFunc, ConvertResultFunc&& convertResultFunc, const ParameterType& parameter)
		/// Creates a AsyncFunctionRunner with the given parameters and functions, starts
		/// the evaluation thread in the default Poco::ThreadPool, and sets the return
		/// value to a newly created Promise.
	{
		try
		{
			Poco::JS::Core::JSExecutor::Ptr pExecutor = Poco::JS::Core::JSExecutor::current();
			Poco::JS::Core::TimedJSExecutor::Ptr pTimedJSExecutor = pExecutor.cast<Poco::JS::Core::TimedJSExecutor>();
			if (pTimedJSExecutor)
			{
				v8::MaybeLocal<v8::Promise::Resolver> maybeResolver = v8::Promise::Resolver::New(context);
				v8::Local<v8::Promise::Resolver> resolver;
				if (maybeResolver.ToLocal(&resolver))
				{
					AsyncFunctionRunner* pAsyncFunctionRunner = new AsyncFunctionRunner(args.GetIsolate(), pTimedJSExecutor, resolver, std::move(evaluateFunc), std::move(convertResultFunc), parameter);
					try
					{
						Poco::ThreadPool::defaultPool().start(*pAsyncFunctionRunner);
						args.GetReturnValue().Set(resolver->GetPromise());
					}
					catch (...)
					{
						delete pAsyncFunctionRunner;
					}
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			Wrapper::returnException(args, exc);
		}
		catch (std::exception& exc)
		{
			Wrapper::returnException(args, std::string(exc.what()));
		}
	}

	AsyncFunctionRunner(v8::Isolate* pIsolate, Poco::JS::Core::TimedJSExecutor::Ptr pExecutor, v8::Handle<v8::Promise::Resolver> resolver, EvaluateFunc&& evaluateFunc, ConvertResultFunc&& convertResultFunc, const ParameterType& parameter):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor),
		_resolver(pIsolate, resolver),
		_evaluateFunc(std::move(evaluateFunc)),
		_convertResultFunc(std::move(convertResultFunc)),
		_parameter(parameter)
	{
	}

	v8::Isolate* isolate()
	{
		return _pIsolate;
	}

	Poco::JS::Core::TimedJSExecutor::Ptr& executor()
	{
		return _pExecutor;
	}

	v8::Persistent<v8::Promise::Resolver>& resolver()
	{
		return _resolver;
	}

	const ResultType& result() const
	{
		return _result;
	}

	Poco::Exception* exception() const
	{
		return _pException.get();
	}

	// Runnable
	void run();

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::TimedJSExecutor::Ptr _pExecutor;
	v8::Persistent<v8::Promise::Resolver> _resolver;
	EvaluateFunc _evaluateFunc;
	ConvertResultFunc _convertResultFunc;
	ParameterType _parameter;
	ResultType _result;
	std::unique_ptr<Poco::Exception> _pException;
};


template <typename TParameterType, typename TResultType>
class AsyncFunctionCompletedTask: public Poco::Util::TimerTask
	/// This is executed in the JavaScript timer queue
	/// when an asynchronous function implemented with
	/// AsyncFunctionRunner completes successfully.
	/// It will resolve the Promise with the result
	/// of the asynchronous function.
{
public:
	using ParameterType = TParameterType;
	using ResultType = TResultType;
	using AsyncFunctionRunnerType = AsyncFunctionRunner<ParameterType, ResultType>;
	using ConvertResultFunc = std::function<v8::Local<v8::Value> (v8::Local<v8::Context>&, const ResultType&)>;

	AsyncFunctionCompletedTask(AsyncFunctionRunnerType* pAsyncFunctionRunner, ConvertResultFunc&& convertResultFunc):
		_pAsyncFunctionRunner(pAsyncFunctionRunner),
		_convertResultFunc(std::move(convertResultFunc))
	{
	}

	// TimerTask
	void run()
	{
		v8::Isolate* pIsolate = _pAsyncFunctionRunner->isolate();
		v8::Locker locker(pIsolate);
		v8::Isolate::Scope isoScope(pIsolate);
		v8::HandleScope handleScope(pIsolate);

		v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _pAsyncFunctionRunner->executor()->scriptContext()));
		v8::Context::Scope contextScope(context);

		v8::Local<v8::Promise::Resolver> resolver(v8::Local<v8::Promise::Resolver>::New(pIsolate, _pAsyncFunctionRunner->resolver()));
		_pAsyncFunctionRunner->resolver().Reset();

		v8::Local<v8::Value> result = this->_convertResultFunc(context, this->_pAsyncFunctionRunner->result());
		V8_CHECK_SET_RESULT(resolver->Resolve(context, result));
	}

private:
	std::unique_ptr<AsyncFunctionRunnerType> _pAsyncFunctionRunner;
	ConvertResultFunc _convertResultFunc;
};


template <typename TParameterType, typename TResultType>
class AsyncFunctionFailedTask: public Poco::Util::TimerTask
	/// This is executed in the JavaScript timer queue
	/// when an asynchronous function implemented with
	/// AsyncFunctionRunner fails by throwing an exception.
	/// It will reject the Promise with the thrown exception
	/// wrapped in an Error object.
{
public:	
	using ParameterType = TParameterType;
	using ResultType = TResultType;
	using AsyncFunctionRunnerType = AsyncFunctionRunner<ParameterType, ResultType>;

	AsyncFunctionFailedTask(AsyncFunctionRunnerType* pAsyncFunctionRunner):
		_pAsyncFunctionRunner(pAsyncFunctionRunner)
	{
	}

	// TimerTask
	void run()
	{
		v8::Isolate* pIsolate = _pAsyncFunctionRunner->isolate();
		v8::Locker locker(pIsolate);
		v8::Isolate::Scope isoScope(pIsolate);
		v8::HandleScope handleScope(pIsolate);

		v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _pAsyncFunctionRunner->executor()->scriptContext()));
		v8::Context::Scope contextScope(context);

		v8::Local<v8::Promise::Resolver> resolver(v8::Local<v8::Promise::Resolver>::New(pIsolate, _pAsyncFunctionRunner->resolver()));
		_pAsyncFunctionRunner->resolver().Reset();

		v8::Local<v8::Value> exception = v8::Exception::Error(Wrapper::toV8String(pIsolate, _pAsyncFunctionRunner->exception()->displayText()));
		V8_CHECK_SET_RESULT(resolver->Reject(context, exception));
	}

private:
	std::unique_ptr<AsyncFunctionRunnerType> _pAsyncFunctionRunner;
};


template <typename TParameterType, typename TResultType>
void AsyncFunctionRunner<TParameterType, TResultType>::run()
{
	try
	{
		this->_result = this->_evaluateFunc(_parameter);
		this->_pExecutor->schedule(new AsyncFunctionCompletedTask<ParameterType, ResultType>(this, std::move(_convertResultFunc)));
	}
	catch (Poco::Exception& exc)
	{
		this->_pException.reset(exc.clone());
		this->_pExecutor->schedule(new AsyncFunctionFailedTask<ParameterType, ResultType>(this));
	}
	catch (std::exception& exc)
	{
		this->_pException.reset(new Poco::Exception(exc.what()));
		this->_pExecutor->schedule(new AsyncFunctionFailedTask<ParameterType, ResultType>(this));
	}
}


} } } // namespace Poco::JS::Core


#endif // JS_Core_AsyncFunction_INCLUDED

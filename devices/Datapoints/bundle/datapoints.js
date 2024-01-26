//
// datapoints.js
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH
//

const dpfRef = serviceRegistry.findByName('io.macchina.datapoint-factory');
const dpf = dpfRef.instance();
const dtRef = serviceRegistry.findByName('io.macchina.deviceTree');
const dt = dtRef.instance();

var datapoints = {
	_factory: dpf,
	_deviceTree: dt,
	
	_ref: function(id) {
		return serviceRegistry.findByName(id);
	},
	
	createBoolean: function(params) {
		const id = this._factory.createBoolean(params);
		return this._ref(id);
	},

	createCounter: function(params) {
		const id = this._factory.createCounter(params);
		return this._ref(id);
	},

	createEnum: function(params) {
		const id = this._factory.createEnum(params);
		return this._ref(id);
	},

	createFlags: function(params) {
		const id = this._factory.createFlags(params);
		return this._ref(id);
	},

	createMovingAverage: function(params) {
		const id = this._factory.createMovingAverage(params);
		return this._ref(id);
	},

	createScalar: function(params) {
		const id = this._factory.createScalar(params);
		return this._ref(id);
	},

	createString: function(params) {
		const id = this._factory.createString(params);
		return this._ref(id);
	},

	createVector: function(params) {
		const id = this._factory.createVector(params);
		return this._ref(id);
	},

	createComposite: function(params) {
		const id = this._factory.createComposite(params);
		return this._ref(id);
	},

	createDatapoint: function(config) {
		if ('tags' in config && typeof config.tags === 'object')
		{
			let tagsArray = [];
			for (const tag in config.tags)
			{
				tagsArray.push({
					name: tag,
					value: config.tags[tag]
				});
			}
			config.params.tags = tagsArray;
		}
		const type = config.type;
		if (type === 'bool')
		{
			return this.createBoolean(config.params);
		}
		else if (type === 'counter')
		{
			return this.createCounter(config.params);
		}
		else if (type === 'enum')
		{
			return this.createEnum(config.params);
		}
		else if (type === 'flags')
		{
			return this.createFlags(config.params);
		}
		else if (type === 'movingAverage')
		{
			return this.createMovingAverage(config.params);
		}
		else if (type === 'scalar')
		{
			return this.createScalar(config.params);
		}
		else if (type === 'string')
		{
			return this.createString(config.params);
		}
		else if (type === 'vector')
		{
			return this.createVector(config.params);
		}
		else if (type === 'composite')
		{
			const composite = this.createComposite(config.params);
			if (config.fragments)
			{
				for (const frag of config.fragments)
				{
					frag.params.composite = composite.name;
					this.createDatapoint(frag);
				}
			}
			return composite;
		}
		else throw new Error('invalid datapoint type: ' + type);
	},

	createDatapoints: function(config)
	{
		for (const item of config)
		{
			this.createDatapoint(item);
		}
	},

	remove: function(ref) {
		if (typeof ref === 'string' || ref instanceof String)
		{
			this._factory.remove(ref);
		}
		else if (typeof ref.name === 'string')
		{
			this._factory.remove(ref.name);
		}
	},

	byPath: function(path) {
		const node = dt.deviceByPath(path);
		return serviceRegistry.findByName(node.id);
	},

	findByPath: function(path) {
		const node = dt.findDeviceByPath(path);
		if (node)
			return serviceRegistry.findByName(node.id);
		else
			return null;
	},
	
	physicalUnits: {
		DEGREES_CELSIUS: 'Cel',
		DEGREES_FAHRENHEIT: '[degF]',
		KELVIN: 'K',
		METER: 'm',
		KILOGRAM: 'kg',
		SECOND: 's',
		VOLT: 'V',
		AMPERE: 'A',
		MOL: 'mol',
		CANDELA: 'cd',
		LUX: 'lx',
		MBAR: 'mbar'	
	},

	ACCESS_NONE: 0x00,
	ACCESS_READ: 0x01,
	ACCESS_WRITE: 0x02,
	ACCESS_ALL: 0x03
};

module.exports = datapoints;

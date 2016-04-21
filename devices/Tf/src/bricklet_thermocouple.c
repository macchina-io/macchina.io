/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_thermocouple.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*TemperatureCallbackFunction)(int32_t, void *);

typedef void (*TemperatureReachedCallbackFunction)(int32_t, void *);

typedef void (*ErrorStateCallbackFunction)(bool, bool, void *);

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(push)
	#pragma pack(1)
	#define ATTRIBUTE_PACKED
#elif defined __GNUC__
	#ifdef _WIN32
		// workaround struct packing bug in GCC 4.7 on Windows
		// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=52991
		#define ATTRIBUTE_PACKED __attribute__((gcc_struct, packed))
	#else
		#define ATTRIBUTE_PACKED __attribute__((packed))
	#endif
#else
	#error unknown compiler, do not know how to enable struct packing
#endif

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperature_;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED GetTemperatureResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetTemperatureCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetTemperatureCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetTemperatureCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetTemperatureCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED SetDebouncePeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDebouncePeriod_;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED GetDebouncePeriodResponse_;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED TemperatureCallback_;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED TemperatureReachedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t averaging;
	uint8_t thermocouple_type;
	uint8_t filter;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t averaging;
	uint8_t thermocouple_type;
	uint8_t filter;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorState_;

typedef struct {
	PacketHeader header;
	bool over_under;
	bool open_circuit;
} ATTRIBUTE_PACKED GetErrorStateResponse_;

typedef struct {
	PacketHeader header;
	bool over_under;
	bool open_circuit;
} ATTRIBUTE_PACKED ErrorStateCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIdentity_;

typedef struct {
	PacketHeader header;
	char uid[8];
	char connected_uid[8];
	char position;
	uint8_t hardware_version[3];
	uint8_t firmware_version[3];
	uint16_t device_identifier;
} ATTRIBUTE_PACKED GetIdentityResponse_;

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(pop)
#endif
#undef ATTRIBUTE_PACKED

static void thermocouple_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	TemperatureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[THERMOCOUPLE_CALLBACK_TEMPERATURE];
	TemperatureCallback_ *callback = (TemperatureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[THERMOCOUPLE_CALLBACK_TEMPERATURE];

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void thermocouple_callback_wrapper_temperature_reached(DevicePrivate *device_p, Packet *packet) {
	TemperatureReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED];
	TemperatureReachedCallback_ *callback = (TemperatureReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void thermocouple_callback_wrapper_error_state(DevicePrivate *device_p, Packet *packet) {
	ErrorStateCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[THERMOCOUPLE_CALLBACK_ERROR_STATE];
	ErrorStateCallback_ *callback = (ErrorStateCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[THERMOCOUPLE_CALLBACK_ERROR_STATE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->over_under, callback->open_circuit, user_data);
}

void thermocouple_create(Thermocouple *thermocouple, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(thermocouple, uid, ipcon->p, 2, 0, 0);

	device_p = thermocouple->p;

	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMOCOUPLE_CALLBACK_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_ERROR_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMOCOUPLE_CALLBACK_ERROR_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[THERMOCOUPLE_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[THERMOCOUPLE_CALLBACK_TEMPERATURE] = thermocouple_callback_wrapper_temperature;
	device_p->callback_wrappers[THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED] = thermocouple_callback_wrapper_temperature_reached;
	device_p->callback_wrappers[THERMOCOUPLE_CALLBACK_ERROR_STATE] = thermocouple_callback_wrapper_error_state;
}

void thermocouple_destroy(Thermocouple *thermocouple) {
	device_release(thermocouple->p);
}

int thermocouple_get_response_expected(Thermocouple *thermocouple, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(thermocouple->p, function_id, ret_response_expected);
}

int thermocouple_set_response_expected(Thermocouple *thermocouple, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(thermocouple->p, function_id, response_expected);
}

int thermocouple_set_response_expected_all(Thermocouple *thermocouple, bool response_expected) {
	return device_set_response_expected_all(thermocouple->p, response_expected);
}

void thermocouple_register_callback(Thermocouple *thermocouple, uint8_t id, void *callback, void *user_data) {
	device_register_callback(thermocouple->p, id, callback, user_data);
}

int thermocouple_get_api_version(Thermocouple *thermocouple, uint8_t ret_api_version[3]) {
	return device_get_api_version(thermocouple->p, ret_api_version);
}

int thermocouple_get_temperature(Thermocouple *thermocouple, int32_t *ret_temperature) {
	DevicePrivate *device_p = thermocouple->p;
	GetTemperature_ request;
	GetTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_temperature = leconvert_int32_from(response.temperature);



	return ret;
}

int thermocouple_set_temperature_callback_period(Thermocouple *thermocouple, uint32_t period) {
	DevicePrivate *device_p = thermocouple->p;
	SetTemperatureCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int thermocouple_get_temperature_callback_period(Thermocouple *thermocouple, uint32_t *ret_period) {
	DevicePrivate *device_p = thermocouple->p;
	GetTemperatureCallbackPeriod_ request;
	GetTemperatureCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int thermocouple_set_temperature_callback_threshold(Thermocouple *thermocouple, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = thermocouple->p;
	SetTemperatureCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int thermocouple_get_temperature_callback_threshold(Thermocouple *thermocouple, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = thermocouple->p;
	GetTemperatureCallbackThreshold_ request;
	GetTemperatureCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);



	return ret;
}

int thermocouple_set_debounce_period(Thermocouple *thermocouple, uint32_t debounce) {
	DevicePrivate *device_p = thermocouple->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int thermocouple_get_debounce_period(Thermocouple *thermocouple, uint32_t *ret_debounce) {
	DevicePrivate *device_p = thermocouple->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_debounce = leconvert_uint32_from(response.debounce);



	return ret;
}

int thermocouple_set_configuration(Thermocouple *thermocouple, uint8_t averaging, uint8_t thermocouple_type, uint8_t filter) {
	DevicePrivate *device_p = thermocouple->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.averaging = averaging;
	request.thermocouple_type = thermocouple_type;
	request.filter = filter;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int thermocouple_get_configuration(Thermocouple *thermocouple, uint8_t *ret_averaging, uint8_t *ret_thermocouple_type, uint8_t *ret_filter) {
	DevicePrivate *device_p = thermocouple->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_averaging = response.averaging;
	*ret_thermocouple_type = response.thermocouple_type;
	*ret_filter = response.filter;



	return ret;
}

int thermocouple_get_error_state(Thermocouple *thermocouple, bool *ret_over_under, bool *ret_open_circuit) {
	DevicePrivate *device_p = thermocouple->p;
	GetErrorState_ request;
	GetErrorStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_ERROR_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_over_under = response.over_under;
	*ret_open_circuit = response.open_circuit;



	return ret;
}

int thermocouple_get_identity(Thermocouple *thermocouple, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = thermocouple->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMOCOUPLE_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	strncpy(ret_uid, response.uid, 8);
	strncpy(ret_connected_uid, response.connected_uid, 8);
	*ret_position = response.position;
	memcpy(ret_hardware_version, response.hardware_version, 3 * sizeof(uint8_t));
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	*ret_device_identifier = leconvert_uint16_from(response.device_identifier);



	return ret;
}

#ifdef __cplusplus
}
#endif

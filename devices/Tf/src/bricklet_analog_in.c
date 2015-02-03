/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_analog_in.h"

#include <string.h>



typedef void (*VoltageCallbackFunction)(uint16_t, void *);

typedef void (*AnalogValueCallbackFunction)(uint16_t, void *);

typedef void (*VoltageReachedCallbackFunction)(uint16_t, void *);

typedef void (*AnalogValueReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetVoltageResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValue_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED GetAnalogValueResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAnalogValueCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAnalogValueCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetVoltageCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetAnalogValueCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThresholdResponse_;

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
	uint16_t voltage;
} ATTRIBUTE_PACKED VoltageCallback_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueCallback_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED VoltageReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueReachedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t range;
} ATTRIBUTE_PACKED SetRange_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRange_;

typedef struct {
	PacketHeader header;
	uint8_t range;
} ATTRIBUTE_PACKED GetRangeResponse_;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED SetAveraging_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAveraging_;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED GetAveragingResponse_;

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

static void analog_in_callback_wrapper_voltage(DevicePrivate *device_p, Packet *packet) {
	VoltageCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ANALOG_IN_CALLBACK_VOLTAGE];
	VoltageCallback_ *callback = (VoltageCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ANALOG_IN_CALLBACK_VOLTAGE];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void analog_in_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValueCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ANALOG_IN_CALLBACK_ANALOG_VALUE];
	AnalogValueCallback_ *callback = (AnalogValueCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ANALOG_IN_CALLBACK_ANALOG_VALUE];

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void analog_in_callback_wrapper_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	VoltageReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ANALOG_IN_CALLBACK_VOLTAGE_REACHED];
	VoltageReachedCallback_ *callback = (VoltageReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ANALOG_IN_CALLBACK_VOLTAGE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void analog_in_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED];
	AnalogValueReachedCallback_ *callback = (AnalogValueReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

void analog_in_create(AnalogIn *analog_in, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(analog_in, uid, ipcon->p, 2, 0, 2);

	device_p = analog_in->p;

	device_p->response_expected[ANALOG_IN_FUNCTION_GET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_CALLBACK_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ANALOG_IN_CALLBACK_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ANALOG_IN_CALLBACK_VOLTAGE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_RANGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_RANGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_SET_AVERAGING] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_AVERAGING] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ANALOG_IN_CALLBACK_VOLTAGE] = analog_in_callback_wrapper_voltage;
	device_p->callback_wrappers[ANALOG_IN_CALLBACK_ANALOG_VALUE] = analog_in_callback_wrapper_analog_value;
	device_p->callback_wrappers[ANALOG_IN_CALLBACK_VOLTAGE_REACHED] = analog_in_callback_wrapper_voltage_reached;
	device_p->callback_wrappers[ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED] = analog_in_callback_wrapper_analog_value_reached;
}

void analog_in_destroy(AnalogIn *analog_in) {
	device_destroy(analog_in);
}

int analog_in_get_response_expected(AnalogIn *analog_in, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(analog_in->p, function_id, ret_response_expected);
}

int analog_in_set_response_expected(AnalogIn *analog_in, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(analog_in->p, function_id, response_expected);
}

int analog_in_set_response_expected_all(AnalogIn *analog_in, bool response_expected) {
	return device_set_response_expected_all(analog_in->p, response_expected);
}

void analog_in_register_callback(AnalogIn *analog_in, uint8_t id, void *callback, void *user_data) {
	device_register_callback(analog_in->p, id, callback, user_data);
}

int analog_in_get_api_version(AnalogIn *analog_in, uint8_t ret_api_version[3]) {
	return device_get_api_version(analog_in->p, ret_api_version);
}

int analog_in_get_voltage(AnalogIn *analog_in, uint16_t *ret_voltage) {
	DevicePrivate *device_p = analog_in->p;
	GetVoltage_ request;
	GetVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_voltage = leconvert_uint16_from(response.voltage);



	return ret;
}

int analog_in_get_analog_value(AnalogIn *analog_in, uint16_t *ret_value) {
	DevicePrivate *device_p = analog_in->p;
	GetAnalogValue_ request;
	GetAnalogValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value = leconvert_uint16_from(response.value);



	return ret;
}

int analog_in_set_voltage_callback_period(AnalogIn *analog_in, uint32_t period) {
	DevicePrivate *device_p = analog_in->p;
	SetVoltageCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_voltage_callback_period(AnalogIn *analog_in, uint32_t *ret_period) {
	DevicePrivate *device_p = analog_in->p;
	GetVoltageCallbackPeriod_ request;
	GetVoltageCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int analog_in_set_analog_value_callback_period(AnalogIn *analog_in, uint32_t period) {
	DevicePrivate *device_p = analog_in->p;
	SetAnalogValueCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_analog_value_callback_period(AnalogIn *analog_in, uint32_t *ret_period) {
	DevicePrivate *device_p = analog_in->p;
	GetAnalogValueCallbackPeriod_ request;
	GetAnalogValueCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int analog_in_set_voltage_callback_threshold(AnalogIn *analog_in, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = analog_in->p;
	SetVoltageCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_voltage_callback_threshold(AnalogIn *analog_in, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = analog_in->p;
	GetVoltageCallbackThreshold_ request;
	GetVoltageCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_int16_from(response.min);
	*ret_max = leconvert_int16_from(response.max);



	return ret;
}

int analog_in_set_analog_value_callback_threshold(AnalogIn *analog_in, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = analog_in->p;
	SetAnalogValueCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_analog_value_callback_threshold(AnalogIn *analog_in, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = analog_in->p;
	GetAnalogValueCallbackThreshold_ request;
	GetAnalogValueCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);



	return ret;
}

int analog_in_set_debounce_period(AnalogIn *analog_in, uint32_t debounce) {
	DevicePrivate *device_p = analog_in->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_debounce_period(AnalogIn *analog_in, uint32_t *ret_debounce) {
	DevicePrivate *device_p = analog_in->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int analog_in_set_range(AnalogIn *analog_in, uint8_t range) {
	DevicePrivate *device_p = analog_in->p;
	SetRange_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_RANGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.range = range;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_range(AnalogIn *analog_in, uint8_t *ret_range) {
	DevicePrivate *device_p = analog_in->p;
	GetRange_ request;
	GetRangeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_RANGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_range = response.range;



	return ret;
}

int analog_in_set_averaging(AnalogIn *analog_in, uint8_t average) {
	DevicePrivate *device_p = analog_in->p;
	SetAveraging_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_SET_AVERAGING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.average = average;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_in_get_averaging(AnalogIn *analog_in, uint8_t *ret_average) {
	DevicePrivate *device_p = analog_in->p;
	GetAveraging_ request;
	GetAveragingResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_AVERAGING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_average = response.average;



	return ret;
}

int analog_in_get_identity(AnalogIn *analog_in, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = analog_in->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

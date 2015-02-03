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

#include "bricklet_linear_poti.h"

#include <string.h>



typedef void (*PositionCallbackFunction)(uint16_t, void *);

typedef void (*AnalogValueCallbackFunction)(uint16_t, void *);

typedef void (*PositionReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetPosition_;

typedef struct {
	PacketHeader header;
	uint16_t position;
} ATTRIBUTE_PACKED GetPositionResponse_;

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
} ATTRIBUTE_PACKED SetPositionCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetPositionCallbackPeriodResponse_;

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
} ATTRIBUTE_PACKED SetPositionCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetPositionCallbackThresholdResponse_;

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
	uint16_t position;
} ATTRIBUTE_PACKED PositionCallback_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueCallback_;

typedef struct {
	PacketHeader header;
	uint16_t position;
} ATTRIBUTE_PACKED PositionReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueReachedCallback_;

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

static void linear_poti_callback_wrapper_position(DevicePrivate *device_p, Packet *packet) {
	PositionCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LINEAR_POTI_CALLBACK_POSITION];
	PositionCallback_ *callback = (PositionCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LINEAR_POTI_CALLBACK_POSITION];

	if (callback_function == NULL) {
		return;
	}

	callback->position = leconvert_uint16_from(callback->position);

	callback_function(callback->position, user_data);
}

static void linear_poti_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValueCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LINEAR_POTI_CALLBACK_ANALOG_VALUE];
	AnalogValueCallback_ *callback = (AnalogValueCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LINEAR_POTI_CALLBACK_ANALOG_VALUE];

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void linear_poti_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LINEAR_POTI_CALLBACK_POSITION_REACHED];
	PositionReachedCallback_ *callback = (PositionReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LINEAR_POTI_CALLBACK_POSITION_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->position = leconvert_uint16_from(callback->position);

	callback_function(callback->position, user_data);
}

static void linear_poti_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED];
	AnalogValueReachedCallback_ *callback = (AnalogValueReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

void linear_poti_create(LinearPoti *linear_poti, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(linear_poti, uid, ipcon->p, 2, 0, 0);

	device_p = linear_poti->p;

	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINEAR_POTI_CALLBACK_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LINEAR_POTI_CALLBACK_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LINEAR_POTI_CALLBACK_POSITION_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LINEAR_POTI_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LINEAR_POTI_CALLBACK_POSITION] = linear_poti_callback_wrapper_position;
	device_p->callback_wrappers[LINEAR_POTI_CALLBACK_ANALOG_VALUE] = linear_poti_callback_wrapper_analog_value;
	device_p->callback_wrappers[LINEAR_POTI_CALLBACK_POSITION_REACHED] = linear_poti_callback_wrapper_position_reached;
	device_p->callback_wrappers[LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED] = linear_poti_callback_wrapper_analog_value_reached;
}

void linear_poti_destroy(LinearPoti *linear_poti) {
	device_destroy(linear_poti);
}

int linear_poti_get_response_expected(LinearPoti *linear_poti, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(linear_poti->p, function_id, ret_response_expected);
}

int linear_poti_set_response_expected(LinearPoti *linear_poti, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(linear_poti->p, function_id, response_expected);
}

int linear_poti_set_response_expected_all(LinearPoti *linear_poti, bool response_expected) {
	return device_set_response_expected_all(linear_poti->p, response_expected);
}

void linear_poti_register_callback(LinearPoti *linear_poti, uint8_t id, void *callback, void *user_data) {
	device_register_callback(linear_poti->p, id, callback, user_data);
}

int linear_poti_get_api_version(LinearPoti *linear_poti, uint8_t ret_api_version[3]) {
	return device_get_api_version(linear_poti->p, ret_api_version);
}

int linear_poti_get_position(LinearPoti *linear_poti, uint16_t *ret_position) {
	DevicePrivate *device_p = linear_poti->p;
	GetPosition_ request;
	GetPositionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_position = leconvert_uint16_from(response.position);



	return ret;
}

int linear_poti_get_analog_value(LinearPoti *linear_poti, uint16_t *ret_value) {
	DevicePrivate *device_p = linear_poti->p;
	GetAnalogValue_ request;
	GetAnalogValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

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

int linear_poti_set_position_callback_period(LinearPoti *linear_poti, uint32_t period) {
	DevicePrivate *device_p = linear_poti->p;
	SetPositionCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int linear_poti_get_position_callback_period(LinearPoti *linear_poti, uint32_t *ret_period) {
	DevicePrivate *device_p = linear_poti->p;
	GetPositionCallbackPeriod_ request;
	GetPositionCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int linear_poti_set_analog_value_callback_period(LinearPoti *linear_poti, uint32_t period) {
	DevicePrivate *device_p = linear_poti->p;
	SetAnalogValueCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int linear_poti_get_analog_value_callback_period(LinearPoti *linear_poti, uint32_t *ret_period) {
	DevicePrivate *device_p = linear_poti->p;
	GetAnalogValueCallbackPeriod_ request;
	GetAnalogValueCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int linear_poti_set_position_callback_threshold(LinearPoti *linear_poti, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = linear_poti->p;
	SetPositionCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int linear_poti_get_position_callback_threshold(LinearPoti *linear_poti, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = linear_poti->p;
	GetPositionCallbackThreshold_ request;
	GetPositionCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int linear_poti_set_analog_value_callback_threshold(LinearPoti *linear_poti, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = linear_poti->p;
	SetAnalogValueCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int linear_poti_get_analog_value_callback_threshold(LinearPoti *linear_poti, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = linear_poti->p;
	GetAnalogValueCallbackThreshold_ request;
	GetAnalogValueCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int linear_poti_set_debounce_period(LinearPoti *linear_poti, uint32_t debounce) {
	DevicePrivate *device_p = linear_poti->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int linear_poti_get_debounce_period(LinearPoti *linear_poti, uint32_t *ret_debounce) {
	DevicePrivate *device_p = linear_poti->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int linear_poti_get_identity(LinearPoti *linear_poti, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = linear_poti->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINEAR_POTI_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

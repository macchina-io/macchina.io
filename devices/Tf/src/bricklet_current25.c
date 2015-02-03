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

#include "bricklet_current25.h"

#include <string.h>



typedef void (*CurrentCallbackFunction)(int16_t, void *);

typedef void (*AnalogValueCallbackFunction)(uint16_t, void *);

typedef void (*CurrentReachedCallbackFunction)(int16_t, void *);

typedef void (*AnalogValueReachedCallbackFunction)(uint16_t, void *);

typedef void (*OverCurrentCallbackFunction)(void *);

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
} ATTRIBUTE_PACKED GetCurrent_;

typedef struct {
	PacketHeader header;
	int16_t current;
} ATTRIBUTE_PACKED GetCurrentResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Calibrate_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsOverCurrent_;

typedef struct {
	PacketHeader header;
	bool over;
} ATTRIBUTE_PACKED IsOverCurrentResponse_;

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
} ATTRIBUTE_PACKED SetCurrentCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCurrentCallbackPeriodResponse_;

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
} ATTRIBUTE_PACKED SetCurrentCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetCurrentCallbackThresholdResponse_;

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
	int16_t current;
} ATTRIBUTE_PACKED CurrentCallback_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueCallback_;

typedef struct {
	PacketHeader header;
	int16_t current;
} ATTRIBUTE_PACKED CurrentReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueReachedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED OverCurrentCallback_;

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

static void current25_callback_wrapper_current(DevicePrivate *device_p, Packet *packet) {
	CurrentCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CURRENT25_CALLBACK_CURRENT];
	CurrentCallback_ *callback = (CurrentCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CURRENT25_CALLBACK_CURRENT];

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void current25_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValueCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CURRENT25_CALLBACK_ANALOG_VALUE];
	AnalogValueCallback_ *callback = (AnalogValueCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CURRENT25_CALLBACK_ANALOG_VALUE];

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void current25_callback_wrapper_current_reached(DevicePrivate *device_p, Packet *packet) {
	CurrentReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CURRENT25_CALLBACK_CURRENT_REACHED];
	CurrentReachedCallback_ *callback = (CurrentReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CURRENT25_CALLBACK_CURRENT_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void current25_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CURRENT25_CALLBACK_ANALOG_VALUE_REACHED];
	AnalogValueReachedCallback_ *callback = (AnalogValueReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CURRENT25_CALLBACK_ANALOG_VALUE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void current25_callback_wrapper_over_current(DevicePrivate *device_p, Packet *packet) {
	OverCurrentCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CURRENT25_CALLBACK_OVER_CURRENT];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CURRENT25_CALLBACK_OVER_CURRENT];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void current25_create(Current25 *current25, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(current25, uid, ipcon->p, 2, 0, 0);

	device_p = current25->p;

	device_p->response_expected[CURRENT25_FUNCTION_GET_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_CALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CURRENT25_FUNCTION_IS_OVER_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_SET_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT25_CALLBACK_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CURRENT25_CALLBACK_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CURRENT25_CALLBACK_CURRENT_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CURRENT25_CALLBACK_ANALOG_VALUE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CURRENT25_CALLBACK_OVER_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CURRENT25_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CURRENT25_CALLBACK_CURRENT] = current25_callback_wrapper_current;
	device_p->callback_wrappers[CURRENT25_CALLBACK_ANALOG_VALUE] = current25_callback_wrapper_analog_value;
	device_p->callback_wrappers[CURRENT25_CALLBACK_CURRENT_REACHED] = current25_callback_wrapper_current_reached;
	device_p->callback_wrappers[CURRENT25_CALLBACK_ANALOG_VALUE_REACHED] = current25_callback_wrapper_analog_value_reached;
	device_p->callback_wrappers[CURRENT25_CALLBACK_OVER_CURRENT] = current25_callback_wrapper_over_current;
}

void current25_destroy(Current25 *current25) {
	device_destroy(current25);
}

int current25_get_response_expected(Current25 *current25, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(current25->p, function_id, ret_response_expected);
}

int current25_set_response_expected(Current25 *current25, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(current25->p, function_id, response_expected);
}

int current25_set_response_expected_all(Current25 *current25, bool response_expected) {
	return device_set_response_expected_all(current25->p, response_expected);
}

void current25_register_callback(Current25 *current25, uint8_t id, void *callback, void *user_data) {
	device_register_callback(current25->p, id, callback, user_data);
}

int current25_get_api_version(Current25 *current25, uint8_t ret_api_version[3]) {
	return device_get_api_version(current25->p, ret_api_version);
}

int current25_get_current(Current25 *current25, int16_t *ret_current) {
	DevicePrivate *device_p = current25->p;
	GetCurrent_ request;
	GetCurrentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_current = leconvert_int16_from(response.current);



	return ret;
}

int current25_calibrate(Current25 *current25) {
	DevicePrivate *device_p = current25->p;
	Calibrate_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_CALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int current25_is_over_current(Current25 *current25, bool *ret_over) {
	DevicePrivate *device_p = current25->p;
	IsOverCurrent_ request;
	IsOverCurrentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_IS_OVER_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_over = response.over;



	return ret;
}

int current25_get_analog_value(Current25 *current25, uint16_t *ret_value) {
	DevicePrivate *device_p = current25->p;
	GetAnalogValue_ request;
	GetAnalogValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

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

int current25_set_current_callback_period(Current25 *current25, uint32_t period) {
	DevicePrivate *device_p = current25->p;
	SetCurrentCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_SET_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int current25_get_current_callback_period(Current25 *current25, uint32_t *ret_period) {
	DevicePrivate *device_p = current25->p;
	GetCurrentCallbackPeriod_ request;
	GetCurrentCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int current25_set_analog_value_callback_period(Current25 *current25, uint32_t period) {
	DevicePrivate *device_p = current25->p;
	SetAnalogValueCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int current25_get_analog_value_callback_period(Current25 *current25, uint32_t *ret_period) {
	DevicePrivate *device_p = current25->p;
	GetAnalogValueCallbackPeriod_ request;
	GetAnalogValueCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int current25_set_current_callback_threshold(Current25 *current25, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = current25->p;
	SetCurrentCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int current25_get_current_callback_threshold(Current25 *current25, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = current25->p;
	GetCurrentCallbackThreshold_ request;
	GetCurrentCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int current25_set_analog_value_callback_threshold(Current25 *current25, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = current25->p;
	SetAnalogValueCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int current25_get_analog_value_callback_threshold(Current25 *current25, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = current25->p;
	GetAnalogValueCallbackThreshold_ request;
	GetAnalogValueCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int current25_set_debounce_period(Current25 *current25, uint32_t debounce) {
	DevicePrivate *device_p = current25->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int current25_get_debounce_period(Current25 *current25, uint32_t *ret_debounce) {
	DevicePrivate *device_p = current25->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int current25_get_identity(Current25 *current25, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = current25->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT25_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_joystick.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*PositionCallbackFunction)(int16_t, int16_t, void *);

typedef void (*AnalogValueCallbackFunction)(uint16_t, uint16_t, void *);

typedef void (*PositionReachedCallbackFunction)(int16_t, int16_t, void *);

typedef void (*AnalogValueReachedCallbackFunction)(uint16_t, uint16_t, void *);

typedef void (*PressedCallbackFunction)(void *);

typedef void (*ReleasedCallbackFunction)(void *);

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
	int16_t x;
	int16_t y;
} ATTRIBUTE_PACKED GetPositionResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsPressed_;

typedef struct {
	PacketHeader header;
	bool pressed;
} ATTRIBUTE_PACKED IsPressedResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValue_;

typedef struct {
	PacketHeader header;
	uint16_t x;
	uint16_t y;
} ATTRIBUTE_PACKED GetAnalogValueResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Calibrate_;

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
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
} ATTRIBUTE_PACKED SetPositionCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
} ATTRIBUTE_PACKED GetPositionCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min_x;
	uint16_t max_x;
	uint16_t min_y;
	uint16_t max_y;
} ATTRIBUTE_PACKED SetAnalogValueCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min_x;
	uint16_t max_x;
	uint16_t min_y;
	uint16_t max_y;
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
	int16_t x;
	int16_t y;
} ATTRIBUTE_PACKED PositionCallback_;

typedef struct {
	PacketHeader header;
	uint16_t x;
	uint16_t y;
} ATTRIBUTE_PACKED AnalogValueCallback_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
} ATTRIBUTE_PACKED PositionReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t x;
	uint16_t y;
} ATTRIBUTE_PACKED AnalogValueReachedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED PressedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReleasedCallback_;

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

static void joystick_callback_wrapper_position(DevicePrivate *device_p, Packet *packet) {
	PositionCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[JOYSTICK_CALLBACK_POSITION];
	PositionCallback_ *callback = (PositionCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[JOYSTICK_CALLBACK_POSITION];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValueCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[JOYSTICK_CALLBACK_ANALOG_VALUE];
	AnalogValueCallback_ *callback = (AnalogValueCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[JOYSTICK_CALLBACK_ANALOG_VALUE];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_uint16_from(callback->x);
	callback->y = leconvert_uint16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[JOYSTICK_CALLBACK_POSITION_REACHED];
	PositionReachedCallback_ *callback = (PositionReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[JOYSTICK_CALLBACK_POSITION_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED];
	AnalogValueReachedCallback_ *callback = (AnalogValueReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_uint16_from(callback->x);
	callback->y = leconvert_uint16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_pressed(DevicePrivate *device_p, Packet *packet) {
	PressedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[JOYSTICK_CALLBACK_PRESSED];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[JOYSTICK_CALLBACK_PRESSED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void joystick_callback_wrapper_released(DevicePrivate *device_p, Packet *packet) {
	ReleasedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[JOYSTICK_CALLBACK_RELEASED];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[JOYSTICK_CALLBACK_RELEASED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void joystick_create(Joystick *joystick, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(joystick, uid, ipcon->p, 2, 0, 0);

	device_p = joystick->p;

	device_p->response_expected[JOYSTICK_FUNCTION_GET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_IS_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_CALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_CALLBACK_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[JOYSTICK_CALLBACK_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[JOYSTICK_CALLBACK_POSITION_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[JOYSTICK_CALLBACK_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[JOYSTICK_CALLBACK_RELEASED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[JOYSTICK_CALLBACK_POSITION] = joystick_callback_wrapper_position;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_ANALOG_VALUE] = joystick_callback_wrapper_analog_value;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_POSITION_REACHED] = joystick_callback_wrapper_position_reached;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED] = joystick_callback_wrapper_analog_value_reached;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_PRESSED] = joystick_callback_wrapper_pressed;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_RELEASED] = joystick_callback_wrapper_released;
}

void joystick_destroy(Joystick *joystick) {
	device_release(joystick->p);
}

int joystick_get_response_expected(Joystick *joystick, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(joystick->p, function_id, ret_response_expected);
}

int joystick_set_response_expected(Joystick *joystick, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(joystick->p, function_id, response_expected);
}

int joystick_set_response_expected_all(Joystick *joystick, bool response_expected) {
	return device_set_response_expected_all(joystick->p, response_expected);
}

void joystick_register_callback(Joystick *joystick, uint8_t id, void *callback, void *user_data) {
	device_register_callback(joystick->p, id, callback, user_data);
}

int joystick_get_api_version(Joystick *joystick, uint8_t ret_api_version[3]) {
	return device_get_api_version(joystick->p, ret_api_version);
}

int joystick_get_position(Joystick *joystick, int16_t *ret_x, int16_t *ret_y) {
	DevicePrivate *device_p = joystick->p;
	GetPosition_ request;
	GetPositionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);



	return ret;
}

int joystick_is_pressed(Joystick *joystick, bool *ret_pressed) {
	DevicePrivate *device_p = joystick->p;
	IsPressed_ request;
	IsPressedResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_IS_PRESSED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_pressed = response.pressed;



	return ret;
}

int joystick_get_analog_value(Joystick *joystick, uint16_t *ret_x, uint16_t *ret_y) {
	DevicePrivate *device_p = joystick->p;
	GetAnalogValue_ request;
	GetAnalogValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_uint16_from(response.x);
	*ret_y = leconvert_uint16_from(response.y);



	return ret;
}

int joystick_calibrate(Joystick *joystick) {
	DevicePrivate *device_p = joystick->p;
	Calibrate_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_CALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int joystick_set_position_callback_period(Joystick *joystick, uint32_t period) {
	DevicePrivate *device_p = joystick->p;
	SetPositionCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int joystick_get_position_callback_period(Joystick *joystick, uint32_t *ret_period) {
	DevicePrivate *device_p = joystick->p;
	GetPositionCallbackPeriod_ request;
	GetPositionCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int joystick_set_analog_value_callback_period(Joystick *joystick, uint32_t period) {
	DevicePrivate *device_p = joystick->p;
	SetAnalogValueCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int joystick_get_analog_value_callback_period(Joystick *joystick, uint32_t *ret_period) {
	DevicePrivate *device_p = joystick->p;
	GetAnalogValueCallbackPeriod_ request;
	GetAnalogValueCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int joystick_set_position_callback_threshold(Joystick *joystick, char option, int16_t min_x, int16_t max_x, int16_t min_y, int16_t max_y) {
	DevicePrivate *device_p = joystick->p;
	SetPositionCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_x = leconvert_int16_to(min_x);
	request.max_x = leconvert_int16_to(max_x);
	request.min_y = leconvert_int16_to(min_y);
	request.max_y = leconvert_int16_to(max_y);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int joystick_get_position_callback_threshold(Joystick *joystick, char *ret_option, int16_t *ret_min_x, int16_t *ret_max_x, int16_t *ret_min_y, int16_t *ret_max_y) {
	DevicePrivate *device_p = joystick->p;
	GetPositionCallbackThreshold_ request;
	GetPositionCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min_x = leconvert_int16_from(response.min_x);
	*ret_max_x = leconvert_int16_from(response.max_x);
	*ret_min_y = leconvert_int16_from(response.min_y);
	*ret_max_y = leconvert_int16_from(response.max_y);



	return ret;
}

int joystick_set_analog_value_callback_threshold(Joystick *joystick, char option, uint16_t min_x, uint16_t max_x, uint16_t min_y, uint16_t max_y) {
	DevicePrivate *device_p = joystick->p;
	SetAnalogValueCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_x = leconvert_uint16_to(min_x);
	request.max_x = leconvert_uint16_to(max_x);
	request.min_y = leconvert_uint16_to(min_y);
	request.max_y = leconvert_uint16_to(max_y);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int joystick_get_analog_value_callback_threshold(Joystick *joystick, char *ret_option, uint16_t *ret_min_x, uint16_t *ret_max_x, uint16_t *ret_min_y, uint16_t *ret_max_y) {
	DevicePrivate *device_p = joystick->p;
	GetAnalogValueCallbackThreshold_ request;
	GetAnalogValueCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min_x = leconvert_uint16_from(response.min_x);
	*ret_max_x = leconvert_uint16_from(response.max_x);
	*ret_min_y = leconvert_uint16_from(response.min_y);
	*ret_max_y = leconvert_uint16_from(response.max_y);



	return ret;
}

int joystick_set_debounce_period(Joystick *joystick, uint32_t debounce) {
	DevicePrivate *device_p = joystick->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int joystick_get_debounce_period(Joystick *joystick, uint32_t *ret_debounce) {
	DevicePrivate *device_p = joystick->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int joystick_get_identity(Joystick *joystick, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = joystick->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

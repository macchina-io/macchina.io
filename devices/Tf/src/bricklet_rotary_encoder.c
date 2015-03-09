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

#include "bricklet_rotary_encoder.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*CountCallbackFunction)(int32_t, void *);

typedef void (*CountReachedCallbackFunction)(int32_t, void *);

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
	bool reset;
} ATTRIBUTE_PACKED GetCount_;

typedef struct {
	PacketHeader header;
	int32_t count;
} ATTRIBUTE_PACKED GetCountResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetCountCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCountCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCountCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetCountCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCountCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetCountCallbackThresholdResponse_;

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
	int32_t count;
} ATTRIBUTE_PACKED CountCallback_;

typedef struct {
	PacketHeader header;
	int32_t count;
} ATTRIBUTE_PACKED CountReachedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsPressed_;

typedef struct {
	PacketHeader header;
	bool pressed;
} ATTRIBUTE_PACKED IsPressedResponse_;

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

static void rotary_encoder_callback_wrapper_count(DevicePrivate *device_p, Packet *packet) {
	CountCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ROTARY_ENCODER_CALLBACK_COUNT];
	CountCallback_ *callback = (CountCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ROTARY_ENCODER_CALLBACK_COUNT];

	if (callback_function == NULL) {
		return;
	}

	callback->count = leconvert_int32_from(callback->count);

	callback_function(callback->count, user_data);
}

static void rotary_encoder_callback_wrapper_count_reached(DevicePrivate *device_p, Packet *packet) {
	CountReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ROTARY_ENCODER_CALLBACK_COUNT_REACHED];
	CountReachedCallback_ *callback = (CountReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ROTARY_ENCODER_CALLBACK_COUNT_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->count = leconvert_int32_from(callback->count);

	callback_function(callback->count, user_data);
}

static void rotary_encoder_callback_wrapper_pressed(DevicePrivate *device_p, Packet *packet) {
	PressedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ROTARY_ENCODER_CALLBACK_PRESSED];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ROTARY_ENCODER_CALLBACK_PRESSED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void rotary_encoder_callback_wrapper_released(DevicePrivate *device_p, Packet *packet) {
	ReleasedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ROTARY_ENCODER_CALLBACK_RELEASED];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ROTARY_ENCODER_CALLBACK_RELEASED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void rotary_encoder_create(RotaryEncoder *rotary_encoder, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(rotary_encoder, uid, ipcon->p, 2, 0, 0);

	device_p = rotary_encoder->p;

	device_p->response_expected[ROTARY_ENCODER_FUNCTION_GET_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_SET_COUNT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_GET_COUNT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_SET_COUNT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_GET_COUNT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ROTARY_ENCODER_CALLBACK_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ROTARY_ENCODER_CALLBACK_COUNT_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_IS_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ROTARY_ENCODER_CALLBACK_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ROTARY_ENCODER_CALLBACK_RELEASED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ROTARY_ENCODER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ROTARY_ENCODER_CALLBACK_COUNT] = rotary_encoder_callback_wrapper_count;
	device_p->callback_wrappers[ROTARY_ENCODER_CALLBACK_COUNT_REACHED] = rotary_encoder_callback_wrapper_count_reached;
	device_p->callback_wrappers[ROTARY_ENCODER_CALLBACK_PRESSED] = rotary_encoder_callback_wrapper_pressed;
	device_p->callback_wrappers[ROTARY_ENCODER_CALLBACK_RELEASED] = rotary_encoder_callback_wrapper_released;
}

void rotary_encoder_destroy(RotaryEncoder *rotary_encoder) {
	device_release(rotary_encoder->p);
}

int rotary_encoder_get_response_expected(RotaryEncoder *rotary_encoder, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rotary_encoder->p, function_id, ret_response_expected);
}

int rotary_encoder_set_response_expected(RotaryEncoder *rotary_encoder, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rotary_encoder->p, function_id, response_expected);
}

int rotary_encoder_set_response_expected_all(RotaryEncoder *rotary_encoder, bool response_expected) {
	return device_set_response_expected_all(rotary_encoder->p, response_expected);
}

void rotary_encoder_register_callback(RotaryEncoder *rotary_encoder, uint8_t id, void *callback, void *user_data) {
	device_register_callback(rotary_encoder->p, id, callback, user_data);
}

int rotary_encoder_get_api_version(RotaryEncoder *rotary_encoder, uint8_t ret_api_version[3]) {
	return device_get_api_version(rotary_encoder->p, ret_api_version);
}

int rotary_encoder_get_count(RotaryEncoder *rotary_encoder, bool reset, int32_t *ret_count) {
	DevicePrivate *device_p = rotary_encoder->p;
	GetCount_ request;
	GetCountResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_GET_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.reset = reset;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_count = leconvert_int32_from(response.count);



	return ret;
}

int rotary_encoder_set_count_callback_period(RotaryEncoder *rotary_encoder, uint32_t period) {
	DevicePrivate *device_p = rotary_encoder->p;
	SetCountCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_SET_COUNT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rotary_encoder_get_count_callback_period(RotaryEncoder *rotary_encoder, uint32_t *ret_period) {
	DevicePrivate *device_p = rotary_encoder->p;
	GetCountCallbackPeriod_ request;
	GetCountCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_GET_COUNT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int rotary_encoder_set_count_callback_threshold(RotaryEncoder *rotary_encoder, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = rotary_encoder->p;
	SetCountCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_SET_COUNT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rotary_encoder_get_count_callback_threshold(RotaryEncoder *rotary_encoder, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = rotary_encoder->p;
	GetCountCallbackThreshold_ request;
	GetCountCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_GET_COUNT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int rotary_encoder_set_debounce_period(RotaryEncoder *rotary_encoder, uint32_t debounce) {
	DevicePrivate *device_p = rotary_encoder->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rotary_encoder_get_debounce_period(RotaryEncoder *rotary_encoder, uint32_t *ret_debounce) {
	DevicePrivate *device_p = rotary_encoder->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int rotary_encoder_is_pressed(RotaryEncoder *rotary_encoder, bool *ret_pressed) {
	DevicePrivate *device_p = rotary_encoder->p;
	IsPressed_ request;
	IsPressedResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_IS_PRESSED, device_p->ipcon_p, device_p);

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

int rotary_encoder_get_identity(RotaryEncoder *rotary_encoder, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rotary_encoder->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ROTARY_ENCODER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

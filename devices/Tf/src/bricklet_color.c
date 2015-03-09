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

#include "bricklet_color.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ColorCallbackFunction)(uint16_t, uint16_t, uint16_t, uint16_t, void *);

typedef void (*ColorReachedCallbackFunction)(uint16_t, uint16_t, uint16_t, uint16_t, void *);

typedef void (*IlluminanceCallbackFunction)(uint32_t, void *);

typedef void (*ColorTemperatureCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetColor_;

typedef struct {
	PacketHeader header;
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t c;
} ATTRIBUTE_PACKED GetColorResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetColorCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetColorCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetColorCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min_r;
	uint16_t max_r;
	uint16_t min_g;
	uint16_t max_g;
	uint16_t min_b;
	uint16_t max_b;
	uint16_t min_c;
	uint16_t max_c;
} ATTRIBUTE_PACKED SetColorCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetColorCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min_r;
	uint16_t max_r;
	uint16_t min_g;
	uint16_t max_g;
	uint16_t min_b;
	uint16_t max_b;
	uint16_t min_c;
	uint16_t max_c;
} ATTRIBUTE_PACKED GetColorCallbackThresholdResponse_;

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
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t c;
} ATTRIBUTE_PACKED ColorCallback_;

typedef struct {
	PacketHeader header;
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t c;
} ATTRIBUTE_PACKED ColorReachedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LightOn_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LightOff_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsLightOn_;

typedef struct {
	PacketHeader header;
	uint8_t light;
} ATTRIBUTE_PACKED IsLightOnResponse_;

typedef struct {
	PacketHeader header;
	uint8_t gain;
	uint8_t integration_time;
} ATTRIBUTE_PACKED SetConfig_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfig_;

typedef struct {
	PacketHeader header;
	uint8_t gain;
	uint8_t integration_time;
} ATTRIBUTE_PACKED GetConfigResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIlluminance_;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED GetIlluminanceResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetColorTemperature_;

typedef struct {
	PacketHeader header;
	uint16_t color_temperature;
} ATTRIBUTE_PACKED GetColorTemperatureResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetIlluminanceCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIlluminanceCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetIlluminanceCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetColorTemperatureCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetColorTemperatureCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetColorTemperatureCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED IlluminanceCallback_;

typedef struct {
	PacketHeader header;
	uint16_t color_temperature;
} ATTRIBUTE_PACKED ColorTemperatureCallback_;

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

static void color_callback_wrapper_color(DevicePrivate *device_p, Packet *packet) {
	ColorCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[COLOR_CALLBACK_COLOR];
	ColorCallback_ *callback = (ColorCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[COLOR_CALLBACK_COLOR];

	if (callback_function == NULL) {
		return;
	}

	callback->r = leconvert_uint16_from(callback->r);
	callback->g = leconvert_uint16_from(callback->g);
	callback->b = leconvert_uint16_from(callback->b);
	callback->c = leconvert_uint16_from(callback->c);

	callback_function(callback->r, callback->g, callback->b, callback->c, user_data);
}

static void color_callback_wrapper_color_reached(DevicePrivate *device_p, Packet *packet) {
	ColorReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[COLOR_CALLBACK_COLOR_REACHED];
	ColorReachedCallback_ *callback = (ColorReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[COLOR_CALLBACK_COLOR_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->r = leconvert_uint16_from(callback->r);
	callback->g = leconvert_uint16_from(callback->g);
	callback->b = leconvert_uint16_from(callback->b);
	callback->c = leconvert_uint16_from(callback->c);

	callback_function(callback->r, callback->g, callback->b, callback->c, user_data);
}

static void color_callback_wrapper_illuminance(DevicePrivate *device_p, Packet *packet) {
	IlluminanceCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[COLOR_CALLBACK_ILLUMINANCE];
	IlluminanceCallback_ *callback = (IlluminanceCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[COLOR_CALLBACK_ILLUMINANCE];

	if (callback_function == NULL) {
		return;
	}

	callback->illuminance = leconvert_uint32_from(callback->illuminance);

	callback_function(callback->illuminance, user_data);
}

static void color_callback_wrapper_color_temperature(DevicePrivate *device_p, Packet *packet) {
	ColorTemperatureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[COLOR_CALLBACK_COLOR_TEMPERATURE];
	ColorTemperatureCallback_ *callback = (ColorTemperatureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[COLOR_CALLBACK_COLOR_TEMPERATURE];

	if (callback_function == NULL) {
		return;
	}

	callback->color_temperature = leconvert_uint16_from(callback->color_temperature);

	callback_function(callback->color_temperature, user_data);
}

void color_create(Color *color, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(color, uid, ipcon->p, 2, 0, 0);

	device_p = color->p;

	device_p->response_expected[COLOR_FUNCTION_GET_COLOR] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_SET_COLOR_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_COLOR_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_SET_COLOR_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_COLOR_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_CALLBACK_COLOR] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[COLOR_CALLBACK_COLOR_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[COLOR_FUNCTION_LIGHT_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[COLOR_FUNCTION_LIGHT_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[COLOR_FUNCTION_IS_LIGHT_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_SET_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[COLOR_FUNCTION_GET_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_ILLUMINANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_COLOR_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_FUNCTION_SET_COLOR_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[COLOR_FUNCTION_GET_COLOR_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[COLOR_CALLBACK_ILLUMINANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[COLOR_CALLBACK_COLOR_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[COLOR_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[COLOR_CALLBACK_COLOR] = color_callback_wrapper_color;
	device_p->callback_wrappers[COLOR_CALLBACK_COLOR_REACHED] = color_callback_wrapper_color_reached;
	device_p->callback_wrappers[COLOR_CALLBACK_ILLUMINANCE] = color_callback_wrapper_illuminance;
	device_p->callback_wrappers[COLOR_CALLBACK_COLOR_TEMPERATURE] = color_callback_wrapper_color_temperature;
}

void color_destroy(Color *color) {
	device_release(color->p);
}

int color_get_response_expected(Color *color, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(color->p, function_id, ret_response_expected);
}

int color_set_response_expected(Color *color, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(color->p, function_id, response_expected);
}

int color_set_response_expected_all(Color *color, bool response_expected) {
	return device_set_response_expected_all(color->p, response_expected);
}

void color_register_callback(Color *color, uint8_t id, void *callback, void *user_data) {
	device_register_callback(color->p, id, callback, user_data);
}

int color_get_api_version(Color *color, uint8_t ret_api_version[3]) {
	return device_get_api_version(color->p, ret_api_version);
}

int color_get_color(Color *color, uint16_t *ret_r, uint16_t *ret_g, uint16_t *ret_b, uint16_t *ret_c) {
	DevicePrivate *device_p = color->p;
	GetColor_ request;
	GetColorResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_COLOR, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_r = leconvert_uint16_from(response.r);
	*ret_g = leconvert_uint16_from(response.g);
	*ret_b = leconvert_uint16_from(response.b);
	*ret_c = leconvert_uint16_from(response.c);



	return ret;
}

int color_set_color_callback_period(Color *color, uint32_t period) {
	DevicePrivate *device_p = color->p;
	SetColorCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_SET_COLOR_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_get_color_callback_period(Color *color, uint32_t *ret_period) {
	DevicePrivate *device_p = color->p;
	GetColorCallbackPeriod_ request;
	GetColorCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_COLOR_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int color_set_color_callback_threshold(Color *color, char option, uint16_t min_r, uint16_t max_r, uint16_t min_g, uint16_t max_g, uint16_t min_b, uint16_t max_b, uint16_t min_c, uint16_t max_c) {
	DevicePrivate *device_p = color->p;
	SetColorCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_SET_COLOR_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_r = leconvert_uint16_to(min_r);
	request.max_r = leconvert_uint16_to(max_r);
	request.min_g = leconvert_uint16_to(min_g);
	request.max_g = leconvert_uint16_to(max_g);
	request.min_b = leconvert_uint16_to(min_b);
	request.max_b = leconvert_uint16_to(max_b);
	request.min_c = leconvert_uint16_to(min_c);
	request.max_c = leconvert_uint16_to(max_c);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_get_color_callback_threshold(Color *color, char *ret_option, uint16_t *ret_min_r, uint16_t *ret_max_r, uint16_t *ret_min_g, uint16_t *ret_max_g, uint16_t *ret_min_b, uint16_t *ret_max_b, uint16_t *ret_min_c, uint16_t *ret_max_c) {
	DevicePrivate *device_p = color->p;
	GetColorCallbackThreshold_ request;
	GetColorCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_COLOR_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min_r = leconvert_uint16_from(response.min_r);
	*ret_max_r = leconvert_uint16_from(response.max_r);
	*ret_min_g = leconvert_uint16_from(response.min_g);
	*ret_max_g = leconvert_uint16_from(response.max_g);
	*ret_min_b = leconvert_uint16_from(response.min_b);
	*ret_max_b = leconvert_uint16_from(response.max_b);
	*ret_min_c = leconvert_uint16_from(response.min_c);
	*ret_max_c = leconvert_uint16_from(response.max_c);



	return ret;
}

int color_set_debounce_period(Color *color, uint32_t debounce) {
	DevicePrivate *device_p = color->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_get_debounce_period(Color *color, uint32_t *ret_debounce) {
	DevicePrivate *device_p = color->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int color_light_on(Color *color) {
	DevicePrivate *device_p = color->p;
	LightOn_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_LIGHT_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_light_off(Color *color) {
	DevicePrivate *device_p = color->p;
	LightOff_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_LIGHT_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_is_light_on(Color *color, uint8_t *ret_light) {
	DevicePrivate *device_p = color->p;
	IsLightOn_ request;
	IsLightOnResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_IS_LIGHT_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_light = response.light;



	return ret;
}

int color_set_config(Color *color, uint8_t gain, uint8_t integration_time) {
	DevicePrivate *device_p = color->p;
	SetConfig_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_SET_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.gain = gain;
	request.integration_time = integration_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_get_config(Color *color, uint8_t *ret_gain, uint8_t *ret_integration_time) {
	DevicePrivate *device_p = color->p;
	GetConfig_ request;
	GetConfigResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_gain = response.gain;
	*ret_integration_time = response.integration_time;



	return ret;
}

int color_get_illuminance(Color *color, uint32_t *ret_illuminance) {
	DevicePrivate *device_p = color->p;
	GetIlluminance_ request;
	GetIlluminanceResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_ILLUMINANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_illuminance = leconvert_uint32_from(response.illuminance);



	return ret;
}

int color_get_color_temperature(Color *color, uint16_t *ret_color_temperature) {
	DevicePrivate *device_p = color->p;
	GetColorTemperature_ request;
	GetColorTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_COLOR_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_color_temperature = leconvert_uint16_from(response.color_temperature);



	return ret;
}

int color_set_illuminance_callback_period(Color *color, uint32_t period) {
	DevicePrivate *device_p = color->p;
	SetIlluminanceCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_get_illuminance_callback_period(Color *color, uint32_t *ret_period) {
	DevicePrivate *device_p = color->p;
	GetIlluminanceCallbackPeriod_ request;
	GetIlluminanceCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int color_set_color_temperature_callback_period(Color *color, uint32_t period) {
	DevicePrivate *device_p = color->p;
	SetColorTemperatureCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_SET_COLOR_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int color_get_color_temperature_callback_period(Color *color, uint32_t *ret_period) {
	DevicePrivate *device_p = color->p;
	GetColorTemperatureCallbackPeriod_ request;
	GetColorTemperatureCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_COLOR_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int color_get_identity(Color *color, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = color->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), COLOR_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

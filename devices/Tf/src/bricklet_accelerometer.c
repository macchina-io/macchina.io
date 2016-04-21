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

#include "bricklet_accelerometer.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AccelerationCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*AccelerationReachedCallbackFunction)(int16_t, int16_t, int16_t, void *);

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
} ATTRIBUTE_PACKED GetAcceleration_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetAccelerationResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAccelerationCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAccelerationCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
	int16_t min_z;
	int16_t max_z;
} ATTRIBUTE_PACKED SetAccelerationCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
	int16_t min_z;
	int16_t max_z;
} ATTRIBUTE_PACKED GetAccelerationCallbackThresholdResponse_;

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
} ATTRIBUTE_PACKED GetTemperature_;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetTemperatureResponse_;

typedef struct {
	PacketHeader header;
	uint8_t data_rate;
	uint8_t full_scale;
	uint8_t filter_bandwidth;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t data_rate;
	uint8_t full_scale;
	uint8_t filter_bandwidth;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LEDOn_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LEDOff_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsLEDOn_;

typedef struct {
	PacketHeader header;
	bool on;
} ATTRIBUTE_PACKED IsLEDOnResponse_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED AccelerationCallback_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED AccelerationReachedCallback_;

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

static void accelerometer_callback_wrapper_acceleration(DevicePrivate *device_p, Packet *packet) {
	AccelerationCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ACCELEROMETER_CALLBACK_ACCELERATION];
	AccelerationCallback_ *callback = (AccelerationCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ACCELEROMETER_CALLBACK_ACCELERATION];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void accelerometer_callback_wrapper_acceleration_reached(DevicePrivate *device_p, Packet *packet) {
	AccelerationReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[ACCELEROMETER_CALLBACK_ACCELERATION_REACHED];
	AccelerationReachedCallback_ *callback = (AccelerationReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[ACCELEROMETER_CALLBACK_ACCELERATION_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

void accelerometer_create(Accelerometer *accelerometer, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(accelerometer, uid, ipcon->p, 2, 0, 1);

	device_p = accelerometer->p;

	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_LED_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_LED_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_IS_LED_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_CALLBACK_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ACCELEROMETER_CALLBACK_ACCELERATION_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ACCELEROMETER_CALLBACK_ACCELERATION] = accelerometer_callback_wrapper_acceleration;
	device_p->callback_wrappers[ACCELEROMETER_CALLBACK_ACCELERATION_REACHED] = accelerometer_callback_wrapper_acceleration_reached;
}

void accelerometer_destroy(Accelerometer *accelerometer) {
	device_release(accelerometer->p);
}

int accelerometer_get_response_expected(Accelerometer *accelerometer, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(accelerometer->p, function_id, ret_response_expected);
}

int accelerometer_set_response_expected(Accelerometer *accelerometer, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(accelerometer->p, function_id, response_expected);
}

int accelerometer_set_response_expected_all(Accelerometer *accelerometer, bool response_expected) {
	return device_set_response_expected_all(accelerometer->p, response_expected);
}

void accelerometer_register_callback(Accelerometer *accelerometer, uint8_t id, void *callback, void *user_data) {
	device_register_callback(accelerometer->p, id, callback, user_data);
}

int accelerometer_get_api_version(Accelerometer *accelerometer, uint8_t ret_api_version[3]) {
	return device_get_api_version(accelerometer->p, ret_api_version);
}

int accelerometer_get_acceleration(Accelerometer *accelerometer, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = accelerometer->p;
	GetAcceleration_ request;
	GetAccelerationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int accelerometer_set_acceleration_callback_period(Accelerometer *accelerometer, uint32_t period) {
	DevicePrivate *device_p = accelerometer->p;
	SetAccelerationCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int accelerometer_get_acceleration_callback_period(Accelerometer *accelerometer, uint32_t *ret_period) {
	DevicePrivate *device_p = accelerometer->p;
	GetAccelerationCallbackPeriod_ request;
	GetAccelerationCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int accelerometer_set_acceleration_callback_threshold(Accelerometer *accelerometer, char option, int16_t min_x, int16_t max_x, int16_t min_y, int16_t max_y, int16_t min_z, int16_t max_z) {
	DevicePrivate *device_p = accelerometer->p;
	SetAccelerationCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_x = leconvert_int16_to(min_x);
	request.max_x = leconvert_int16_to(max_x);
	request.min_y = leconvert_int16_to(min_y);
	request.max_y = leconvert_int16_to(max_y);
	request.min_z = leconvert_int16_to(min_z);
	request.max_z = leconvert_int16_to(max_z);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int accelerometer_get_acceleration_callback_threshold(Accelerometer *accelerometer, char *ret_option, int16_t *ret_min_x, int16_t *ret_max_x, int16_t *ret_min_y, int16_t *ret_max_y, int16_t *ret_min_z, int16_t *ret_max_z) {
	DevicePrivate *device_p = accelerometer->p;
	GetAccelerationCallbackThreshold_ request;
	GetAccelerationCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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
	*ret_min_z = leconvert_int16_from(response.min_z);
	*ret_max_z = leconvert_int16_from(response.max_z);



	return ret;
}

int accelerometer_set_debounce_period(Accelerometer *accelerometer, uint32_t debounce) {
	DevicePrivate *device_p = accelerometer->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int accelerometer_get_debounce_period(Accelerometer *accelerometer, uint32_t *ret_debounce) {
	DevicePrivate *device_p = accelerometer->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int accelerometer_get_temperature(Accelerometer *accelerometer, int16_t *ret_temperature) {
	DevicePrivate *device_p = accelerometer->p;
	GetTemperature_ request;
	GetTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_temperature = leconvert_int16_from(response.temperature);



	return ret;
}

int accelerometer_set_configuration(Accelerometer *accelerometer, uint8_t data_rate, uint8_t full_scale, uint8_t filter_bandwidth) {
	DevicePrivate *device_p = accelerometer->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.data_rate = data_rate;
	request.full_scale = full_scale;
	request.filter_bandwidth = filter_bandwidth;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int accelerometer_get_configuration(Accelerometer *accelerometer, uint8_t *ret_data_rate, uint8_t *ret_full_scale, uint8_t *ret_filter_bandwidth) {
	DevicePrivate *device_p = accelerometer->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_data_rate = response.data_rate;
	*ret_full_scale = response.full_scale;
	*ret_filter_bandwidth = response.filter_bandwidth;



	return ret;
}

int accelerometer_led_on(Accelerometer *accelerometer) {
	DevicePrivate *device_p = accelerometer->p;
	LEDOn_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_LED_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int accelerometer_led_off(Accelerometer *accelerometer) {
	DevicePrivate *device_p = accelerometer->p;
	LEDOff_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_LED_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int accelerometer_is_led_on(Accelerometer *accelerometer, bool *ret_on) {
	DevicePrivate *device_p = accelerometer->p;
	IsLEDOn_ request;
	IsLEDOnResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_IS_LED_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_on = response.on;



	return ret;
}

int accelerometer_get_identity(Accelerometer *accelerometer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = accelerometer->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

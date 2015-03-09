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

#include "bricklet_temperature.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*TemperatureCallbackFunction)(int16_t, void *);

typedef void (*TemperatureReachedCallbackFunction)(int16_t, void *);

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
	int16_t temperature;
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
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetTemperatureCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
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
	int16_t temperature;
} ATTRIBUTE_PACKED TemperatureCallback_;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED TemperatureReachedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetI2CMode_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetI2CMode_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetI2CModeResponse_;

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

static void temperature_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	TemperatureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[TEMPERATURE_CALLBACK_TEMPERATURE];
	TemperatureCallback_ *callback = (TemperatureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[TEMPERATURE_CALLBACK_TEMPERATURE];

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int16_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void temperature_callback_wrapper_temperature_reached(DevicePrivate *device_p, Packet *packet) {
	TemperatureReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[TEMPERATURE_CALLBACK_TEMPERATURE_REACHED];
	TemperatureReachedCallback_ *callback = (TemperatureReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[TEMPERATURE_CALLBACK_TEMPERATURE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int16_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

void temperature_create(Temperature *temperature, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(temperature, uid, ipcon->p, 2, 0, 0);

	device_p = temperature->p;

	device_p->response_expected[TEMPERATURE_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TEMPERATURE_CALLBACK_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[TEMPERATURE_CALLBACK_TEMPERATURE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[TEMPERATURE_FUNCTION_SET_I2C_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[TEMPERATURE_FUNCTION_GET_I2C_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TEMPERATURE_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[TEMPERATURE_CALLBACK_TEMPERATURE] = temperature_callback_wrapper_temperature;
	device_p->callback_wrappers[TEMPERATURE_CALLBACK_TEMPERATURE_REACHED] = temperature_callback_wrapper_temperature_reached;
}

void temperature_destroy(Temperature *temperature) {
	device_release(temperature->p);
}

int temperature_get_response_expected(Temperature *temperature, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(temperature->p, function_id, ret_response_expected);
}

int temperature_set_response_expected(Temperature *temperature, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(temperature->p, function_id, response_expected);
}

int temperature_set_response_expected_all(Temperature *temperature, bool response_expected) {
	return device_set_response_expected_all(temperature->p, response_expected);
}

void temperature_register_callback(Temperature *temperature, uint8_t id, void *callback, void *user_data) {
	device_register_callback(temperature->p, id, callback, user_data);
}

int temperature_get_api_version(Temperature *temperature, uint8_t ret_api_version[3]) {
	return device_get_api_version(temperature->p, ret_api_version);
}

int temperature_get_temperature(Temperature *temperature, int16_t *ret_temperature) {
	DevicePrivate *device_p = temperature->p;
	GetTemperature_ request;
	GetTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

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

int temperature_set_temperature_callback_period(Temperature *temperature, uint32_t period) {
	DevicePrivate *device_p = temperature->p;
	SetTemperatureCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int temperature_get_temperature_callback_period(Temperature *temperature, uint32_t *ret_period) {
	DevicePrivate *device_p = temperature->p;
	GetTemperatureCallbackPeriod_ request;
	GetTemperatureCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int temperature_set_temperature_callback_threshold(Temperature *temperature, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = temperature->p;
	SetTemperatureCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int temperature_get_temperature_callback_threshold(Temperature *temperature, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = temperature->p;
	GetTemperatureCallbackThreshold_ request;
	GetTemperatureCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int temperature_set_debounce_period(Temperature *temperature, uint32_t debounce) {
	DevicePrivate *device_p = temperature->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int temperature_get_debounce_period(Temperature *temperature, uint32_t *ret_debounce) {
	DevicePrivate *device_p = temperature->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int temperature_set_i2c_mode(Temperature *temperature, uint8_t mode) {
	DevicePrivate *device_p = temperature->p;
	SetI2CMode_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_SET_I2C_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int temperature_get_i2c_mode(Temperature *temperature, uint8_t *ret_mode) {
	DevicePrivate *device_p = temperature->p;
	GetI2CMode_ request;
	GetI2CModeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_GET_I2C_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_mode = response.mode;



	return ret;
}

int temperature_get_identity(Temperature *temperature, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = temperature->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TEMPERATURE_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

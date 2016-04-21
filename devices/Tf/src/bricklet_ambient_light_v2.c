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

#include "bricklet_ambient_light_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*IlluminanceCallbackFunction)(uint32_t, void *);

typedef void (*IlluminanceReachedCallbackFunction)(uint32_t, void *);

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
} ATTRIBUTE_PACKED GetIlluminance_;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED GetIlluminanceResponse_;

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
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED SetIlluminanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIlluminanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED GetIlluminanceCallbackThresholdResponse_;

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
	uint8_t illuminance_range;
	uint8_t integration_time;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t illuminance_range;
	uint8_t integration_time;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED IlluminanceCallback_;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED IlluminanceReachedCallback_;

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

static void ambient_light_v2_callback_wrapper_illuminance(DevicePrivate *device_p, Packet *packet) {
	IlluminanceCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE];
	IlluminanceCallback_ *callback = (IlluminanceCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE];

	if (callback_function == NULL) {
		return;
	}

	callback->illuminance = leconvert_uint32_from(callback->illuminance);

	callback_function(callback->illuminance, user_data);
}

static void ambient_light_v2_callback_wrapper_illuminance_reached(DevicePrivate *device_p, Packet *packet) {
	IlluminanceReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED];
	IlluminanceReachedCallback_ *callback = (IlluminanceReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->illuminance = leconvert_uint32_from(callback->illuminance);

	callback_function(callback->illuminance, user_data);
}

void ambient_light_v2_create(AmbientLightV2 *ambient_light_v2, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(ambient_light_v2, uid, ipcon->p, 2, 0, 1);

	device_p = ambient_light_v2->p;

	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_SET_ILLUMINANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE] = ambient_light_v2_callback_wrapper_illuminance;
	device_p->callback_wrappers[AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED] = ambient_light_v2_callback_wrapper_illuminance_reached;
}

void ambient_light_v2_destroy(AmbientLightV2 *ambient_light_v2) {
	device_release(ambient_light_v2->p);
}

int ambient_light_v2_get_response_expected(AmbientLightV2 *ambient_light_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(ambient_light_v2->p, function_id, ret_response_expected);
}

int ambient_light_v2_set_response_expected(AmbientLightV2 *ambient_light_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(ambient_light_v2->p, function_id, response_expected);
}

int ambient_light_v2_set_response_expected_all(AmbientLightV2 *ambient_light_v2, bool response_expected) {
	return device_set_response_expected_all(ambient_light_v2->p, response_expected);
}

void ambient_light_v2_register_callback(AmbientLightV2 *ambient_light_v2, uint8_t id, void *callback, void *user_data) {
	device_register_callback(ambient_light_v2->p, id, callback, user_data);
}

int ambient_light_v2_get_api_version(AmbientLightV2 *ambient_light_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(ambient_light_v2->p, ret_api_version);
}

int ambient_light_v2_get_illuminance(AmbientLightV2 *ambient_light_v2, uint32_t *ret_illuminance) {
	DevicePrivate *device_p = ambient_light_v2->p;
	GetIlluminance_ request;
	GetIlluminanceResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE, device_p->ipcon_p, device_p);

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

int ambient_light_v2_set_illuminance_callback_period(AmbientLightV2 *ambient_light_v2, uint32_t period) {
	DevicePrivate *device_p = ambient_light_v2->p;
	SetIlluminanceCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ambient_light_v2_get_illuminance_callback_period(AmbientLightV2 *ambient_light_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = ambient_light_v2->p;
	GetIlluminanceCallbackPeriod_ request;
	GetIlluminanceCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ambient_light_v2_set_illuminance_callback_threshold(AmbientLightV2 *ambient_light_v2, char option, uint32_t min, uint32_t max) {
	DevicePrivate *device_p = ambient_light_v2->p;
	SetIlluminanceCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_SET_ILLUMINANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint32_to(min);
	request.max = leconvert_uint32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ambient_light_v2_get_illuminance_callback_threshold(AmbientLightV2 *ambient_light_v2, char *ret_option, uint32_t *ret_min, uint32_t *ret_max) {
	DevicePrivate *device_p = ambient_light_v2->p;
	GetIlluminanceCallbackThreshold_ request;
	GetIlluminanceCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_uint32_from(response.min);
	*ret_max = leconvert_uint32_from(response.max);



	return ret;
}

int ambient_light_v2_set_debounce_period(AmbientLightV2 *ambient_light_v2, uint32_t debounce) {
	DevicePrivate *device_p = ambient_light_v2->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ambient_light_v2_get_debounce_period(AmbientLightV2 *ambient_light_v2, uint32_t *ret_debounce) {
	DevicePrivate *device_p = ambient_light_v2->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int ambient_light_v2_set_configuration(AmbientLightV2 *ambient_light_v2, uint8_t illuminance_range, uint8_t integration_time) {
	DevicePrivate *device_p = ambient_light_v2->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.illuminance_range = illuminance_range;
	request.integration_time = integration_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ambient_light_v2_get_configuration(AmbientLightV2 *ambient_light_v2, uint8_t *ret_illuminance_range, uint8_t *ret_integration_time) {
	DevicePrivate *device_p = ambient_light_v2->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_illuminance_range = response.illuminance_range;
	*ret_integration_time = response.integration_time;



	return ret;
}

int ambient_light_v2_get_identity(AmbientLightV2 *ambient_light_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = ambient_light_v2->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

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

#include "bricklet_distance_us.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*DistanceCallbackFunction)(uint16_t, void *);

typedef void (*DistanceReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetDistanceValue_;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED GetDistanceValueResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetDistanceCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetDistanceCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetDistanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetDistanceCallbackThresholdResponse_;

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
	uint16_t distance;
} ATTRIBUTE_PACKED DistanceCallback_;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED DistanceReachedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED SetMovingAverage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMovingAverage_;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED GetMovingAverageResponse_;

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

static void distance_us_callback_wrapper_distance(DevicePrivate *device_p, Packet *packet) {
	DistanceCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DISTANCE_US_CALLBACK_DISTANCE];
	DistanceCallback_ *callback = (DistanceCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DISTANCE_US_CALLBACK_DISTANCE];

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_uint16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

static void distance_us_callback_wrapper_distance_reached(DevicePrivate *device_p, Packet *packet) {
	DistanceReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DISTANCE_US_CALLBACK_DISTANCE_REACHED];
	DistanceReachedCallback_ *callback = (DistanceReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DISTANCE_US_CALLBACK_DISTANCE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_uint16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

void distance_us_create(DistanceUS *distance_us, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(distance_us, uid, ipcon->p, 2, 0, 0);

	device_p = distance_us->p;

	device_p->response_expected[DISTANCE_US_FUNCTION_GET_DISTANCE_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DISTANCE_US_CALLBACK_DISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DISTANCE_US_CALLBACK_DISTANCE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DISTANCE_US_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DISTANCE_US_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DISTANCE_US_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DISTANCE_US_CALLBACK_DISTANCE] = distance_us_callback_wrapper_distance;
	device_p->callback_wrappers[DISTANCE_US_CALLBACK_DISTANCE_REACHED] = distance_us_callback_wrapper_distance_reached;
}

void distance_us_destroy(DistanceUS *distance_us) {
	device_release(distance_us->p);
}

int distance_us_get_response_expected(DistanceUS *distance_us, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(distance_us->p, function_id, ret_response_expected);
}

int distance_us_set_response_expected(DistanceUS *distance_us, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(distance_us->p, function_id, response_expected);
}

int distance_us_set_response_expected_all(DistanceUS *distance_us, bool response_expected) {
	return device_set_response_expected_all(distance_us->p, response_expected);
}

void distance_us_register_callback(DistanceUS *distance_us, uint8_t id, void *callback, void *user_data) {
	device_register_callback(distance_us->p, id, callback, user_data);
}

int distance_us_get_api_version(DistanceUS *distance_us, uint8_t ret_api_version[3]) {
	return device_get_api_version(distance_us->p, ret_api_version);
}

int distance_us_get_distance_value(DistanceUS *distance_us, uint16_t *ret_distance) {
	DevicePrivate *device_p = distance_us->p;
	GetDistanceValue_ request;
	GetDistanceValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_GET_DISTANCE_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_distance = leconvert_uint16_from(response.distance);



	return ret;
}

int distance_us_set_distance_callback_period(DistanceUS *distance_us, uint32_t period) {
	DevicePrivate *device_p = distance_us->p;
	SetDistanceCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int distance_us_get_distance_callback_period(DistanceUS *distance_us, uint32_t *ret_period) {
	DevicePrivate *device_p = distance_us->p;
	GetDistanceCallbackPeriod_ request;
	GetDistanceCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int distance_us_set_distance_callback_threshold(DistanceUS *distance_us, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = distance_us->p;
	SetDistanceCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int distance_us_get_distance_callback_threshold(DistanceUS *distance_us, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = distance_us->p;
	GetDistanceCallbackThreshold_ request;
	GetDistanceCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int distance_us_set_debounce_period(DistanceUS *distance_us, uint32_t debounce) {
	DevicePrivate *device_p = distance_us->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int distance_us_get_debounce_period(DistanceUS *distance_us, uint32_t *ret_debounce) {
	DevicePrivate *device_p = distance_us->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int distance_us_set_moving_average(DistanceUS *distance_us, uint8_t average) {
	DevicePrivate *device_p = distance_us->p;
	SetMovingAverage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.average = average;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int distance_us_get_moving_average(DistanceUS *distance_us, uint8_t *ret_average) {
	DevicePrivate *device_p = distance_us->p;
	GetMovingAverage_ request;
	GetMovingAverageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

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

int distance_us_get_identity(DistanceUS *distance_us, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = distance_us->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DISTANCE_US_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

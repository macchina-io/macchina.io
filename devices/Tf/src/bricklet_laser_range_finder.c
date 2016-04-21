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

#include "bricklet_laser_range_finder.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*DistanceCallbackFunction)(uint16_t, void *);

typedef void (*VelocityCallbackFunction)(int16_t, void *);

typedef void (*DistanceReachedCallbackFunction)(uint16_t, void *);

typedef void (*VelocityReachedCallbackFunction)(int16_t, void *);

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
} ATTRIBUTE_PACKED GetDistance_;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED GetDistanceResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocity_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED GetVelocityResponse_;

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
	uint32_t period;
} ATTRIBUTE_PACKED SetVelocityCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocityCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetVelocityCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetDistanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetDistanceCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetVelocityCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocityCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetVelocityCallbackThresholdResponse_;

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
	uint8_t distance_average_length;
	uint8_t velocity_average_length;
} ATTRIBUTE_PACKED SetMovingAverage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMovingAverage_;

typedef struct {
	PacketHeader header;
	uint8_t distance_average_length;
	uint8_t velocity_average_length;
} ATTRIBUTE_PACKED GetMovingAverageResponse_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetMode_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMode_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetModeResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableLaser_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableLaser_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsLaserEnabled_;

typedef struct {
	PacketHeader header;
	bool laser_enabled;
} ATTRIBUTE_PACKED IsLaserEnabledResponse_;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED DistanceCallback_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED VelocityCallback_;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED DistanceReachedCallback_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED VelocityReachedCallback_;

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

static void laser_range_finder_callback_wrapper_distance(DevicePrivate *device_p, Packet *packet) {
	DistanceCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LASER_RANGE_FINDER_CALLBACK_DISTANCE];
	DistanceCallback_ *callback = (DistanceCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LASER_RANGE_FINDER_CALLBACK_DISTANCE];

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_uint16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

static void laser_range_finder_callback_wrapper_velocity(DevicePrivate *device_p, Packet *packet) {
	VelocityCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LASER_RANGE_FINDER_CALLBACK_VELOCITY];
	VelocityCallback_ *callback = (VelocityCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LASER_RANGE_FINDER_CALLBACK_VELOCITY];

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

static void laser_range_finder_callback_wrapper_distance_reached(DevicePrivate *device_p, Packet *packet) {
	DistanceReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED];
	DistanceReachedCallback_ *callback = (DistanceReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_uint16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

static void laser_range_finder_callback_wrapper_velocity_reached(DevicePrivate *device_p, Packet *packet) {
	VelocityReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED];
	VelocityReachedCallback_ *callback = (VelocityReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

void laser_range_finder_create(LaserRangeFinder *laser_range_finder, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(laser_range_finder, uid, ipcon->p, 2, 0, 0);

	device_p = laser_range_finder->p;

	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_ENABLE_LASER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_DISABLE_LASER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_IS_LASER_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_CALLBACK_DISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_CALLBACK_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_DISTANCE] = laser_range_finder_callback_wrapper_distance;
	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_VELOCITY] = laser_range_finder_callback_wrapper_velocity;
	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED] = laser_range_finder_callback_wrapper_distance_reached;
	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED] = laser_range_finder_callback_wrapper_velocity_reached;
}

void laser_range_finder_destroy(LaserRangeFinder *laser_range_finder) {
	device_release(laser_range_finder->p);
}

int laser_range_finder_get_response_expected(LaserRangeFinder *laser_range_finder, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(laser_range_finder->p, function_id, ret_response_expected);
}

int laser_range_finder_set_response_expected(LaserRangeFinder *laser_range_finder, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(laser_range_finder->p, function_id, response_expected);
}

int laser_range_finder_set_response_expected_all(LaserRangeFinder *laser_range_finder, bool response_expected) {
	return device_set_response_expected_all(laser_range_finder->p, response_expected);
}

void laser_range_finder_register_callback(LaserRangeFinder *laser_range_finder, uint8_t id, void *callback, void *user_data) {
	device_register_callback(laser_range_finder->p, id, callback, user_data);
}

int laser_range_finder_get_api_version(LaserRangeFinder *laser_range_finder, uint8_t ret_api_version[3]) {
	return device_get_api_version(laser_range_finder->p, ret_api_version);
}

int laser_range_finder_get_distance(LaserRangeFinder *laser_range_finder, uint16_t *ret_distance) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDistance_ request;
	GetDistanceResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE, device_p->ipcon_p, device_p);

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

int laser_range_finder_get_velocity(LaserRangeFinder *laser_range_finder, int16_t *ret_velocity) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetVelocity_ request;
	GetVelocityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_velocity = leconvert_int16_from(response.velocity);



	return ret;
}

int laser_range_finder_set_distance_callback_period(LaserRangeFinder *laser_range_finder, uint32_t period) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetDistanceCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_distance_callback_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_period) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDistanceCallbackPeriod_ request;
	GetDistanceCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_velocity_callback_period(LaserRangeFinder *laser_range_finder, uint32_t period) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetVelocityCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_velocity_callback_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_period) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetVelocityCallbackPeriod_ request;
	GetVelocityCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_distance_callback_threshold(LaserRangeFinder *laser_range_finder, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetDistanceCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_distance_callback_threshold(LaserRangeFinder *laser_range_finder, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDistanceCallbackThreshold_ request;
	GetDistanceCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_velocity_callback_threshold(LaserRangeFinder *laser_range_finder, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetVelocityCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_velocity_callback_threshold(LaserRangeFinder *laser_range_finder, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetVelocityCallbackThreshold_ request;
	GetVelocityCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_debounce_period(LaserRangeFinder *laser_range_finder, uint32_t debounce) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_debounce_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_debounce) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_moving_average(LaserRangeFinder *laser_range_finder, uint8_t distance_average_length, uint8_t velocity_average_length) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetMovingAverage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.distance_average_length = distance_average_length;
	request.velocity_average_length = velocity_average_length;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_moving_average(LaserRangeFinder *laser_range_finder, uint8_t *ret_distance_average_length, uint8_t *ret_velocity_average_length) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetMovingAverage_ request;
	GetMovingAverageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_distance_average_length = response.distance_average_length;
	*ret_velocity_average_length = response.velocity_average_length;



	return ret;
}

int laser_range_finder_set_mode(LaserRangeFinder *laser_range_finder, uint8_t mode) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetMode_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_get_mode(LaserRangeFinder *laser_range_finder, uint8_t *ret_mode) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetMode_ request;
	GetModeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_MODE, device_p->ipcon_p, device_p);

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

int laser_range_finder_enable_laser(LaserRangeFinder *laser_range_finder) {
	DevicePrivate *device_p = laser_range_finder->p;
	EnableLaser_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_ENABLE_LASER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_disable_laser(LaserRangeFinder *laser_range_finder) {
	DevicePrivate *device_p = laser_range_finder->p;
	DisableLaser_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_DISABLE_LASER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int laser_range_finder_is_laser_enabled(LaserRangeFinder *laser_range_finder, bool *ret_laser_enabled) {
	DevicePrivate *device_p = laser_range_finder->p;
	IsLaserEnabled_ request;
	IsLaserEnabledResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_IS_LASER_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_laser_enabled = response.laser_enabled;



	return ret;
}

int laser_range_finder_get_identity(LaserRangeFinder *laser_range_finder, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

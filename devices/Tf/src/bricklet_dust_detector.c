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

#include "bricklet_dust_detector.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*DustDensityCallbackFunction)(uint16_t, void *);

typedef void (*DustDensityReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetDustDensity_;

typedef struct {
	PacketHeader header;
	uint16_t dust_density;
} ATTRIBUTE_PACKED GetDustDensityResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetDustDensityCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDustDensityCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetDustDensityCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetDustDensityCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDustDensityCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetDustDensityCallbackThresholdResponse_;

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
	uint16_t dust_density;
} ATTRIBUTE_PACKED DustDensityCallback_;

typedef struct {
	PacketHeader header;
	uint16_t dust_density;
} ATTRIBUTE_PACKED DustDensityReachedCallback_;

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

static void dust_detector_callback_wrapper_dust_density(DevicePrivate *device_p, Packet *packet) {
	DustDensityCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DUST_DETECTOR_CALLBACK_DUST_DENSITY];
	DustDensityCallback_ *callback = (DustDensityCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DUST_DETECTOR_CALLBACK_DUST_DENSITY];

	if (callback_function == NULL) {
		return;
	}

	callback->dust_density = leconvert_uint16_from(callback->dust_density);

	callback_function(callback->dust_density, user_data);
}

static void dust_detector_callback_wrapper_dust_density_reached(DevicePrivate *device_p, Packet *packet) {
	DustDensityReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED];
	DustDensityReachedCallback_ *callback = (DustDensityReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->dust_density = leconvert_uint16_from(callback->dust_density);

	callback_function(callback->dust_density, user_data);
}

void dust_detector_create(DustDetector *dust_detector, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(dust_detector, uid, ipcon->p, 2, 0, 0);

	device_p = dust_detector->p;

	device_p->response_expected[DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_SET_DUST_DENSITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_SET_DUST_DENSITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUST_DETECTOR_CALLBACK_DUST_DENSITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUST_DETECTOR_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DUST_DETECTOR_CALLBACK_DUST_DENSITY] = dust_detector_callback_wrapper_dust_density;
	device_p->callback_wrappers[DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED] = dust_detector_callback_wrapper_dust_density_reached;
}

void dust_detector_destroy(DustDetector *dust_detector) {
	device_release(dust_detector->p);
}

int dust_detector_get_response_expected(DustDetector *dust_detector, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dust_detector->p, function_id, ret_response_expected);
}

int dust_detector_set_response_expected(DustDetector *dust_detector, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dust_detector->p, function_id, response_expected);
}

int dust_detector_set_response_expected_all(DustDetector *dust_detector, bool response_expected) {
	return device_set_response_expected_all(dust_detector->p, response_expected);
}

void dust_detector_register_callback(DustDetector *dust_detector, uint8_t id, void *callback, void *user_data) {
	device_register_callback(dust_detector->p, id, callback, user_data);
}

int dust_detector_get_api_version(DustDetector *dust_detector, uint8_t ret_api_version[3]) {
	return device_get_api_version(dust_detector->p, ret_api_version);
}

int dust_detector_get_dust_density(DustDetector *dust_detector, uint16_t *ret_dust_density) {
	DevicePrivate *device_p = dust_detector->p;
	GetDustDensity_ request;
	GetDustDensityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_dust_density = leconvert_uint16_from(response.dust_density);



	return ret;
}

int dust_detector_set_dust_density_callback_period(DustDetector *dust_detector, uint32_t period) {
	DevicePrivate *device_p = dust_detector->p;
	SetDustDensityCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_SET_DUST_DENSITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dust_detector_get_dust_density_callback_period(DustDetector *dust_detector, uint32_t *ret_period) {
	DevicePrivate *device_p = dust_detector->p;
	GetDustDensityCallbackPeriod_ request;
	GetDustDensityCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int dust_detector_set_dust_density_callback_threshold(DustDetector *dust_detector, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = dust_detector->p;
	SetDustDensityCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_SET_DUST_DENSITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dust_detector_get_dust_density_callback_threshold(DustDetector *dust_detector, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = dust_detector->p;
	GetDustDensityCallbackThreshold_ request;
	GetDustDensityCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int dust_detector_set_debounce_period(DustDetector *dust_detector, uint32_t debounce) {
	DevicePrivate *device_p = dust_detector->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dust_detector_get_debounce_period(DustDetector *dust_detector, uint32_t *ret_debounce) {
	DevicePrivate *device_p = dust_detector->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int dust_detector_set_moving_average(DustDetector *dust_detector, uint8_t average) {
	DevicePrivate *device_p = dust_detector->p;
	SetMovingAverage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.average = average;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dust_detector_get_moving_average(DustDetector *dust_detector, uint8_t *ret_average) {
	DevicePrivate *device_p = dust_detector->p;
	GetMovingAverage_ request;
	GetMovingAverageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

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

int dust_detector_get_identity(DustDetector *dust_detector, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dust_detector->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUST_DETECTOR_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

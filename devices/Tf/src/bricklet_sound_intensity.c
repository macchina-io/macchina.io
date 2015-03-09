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

#include "bricklet_sound_intensity.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*IntensityCallbackFunction)(uint16_t, void *);

typedef void (*IntensityReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetIntensity_;

typedef struct {
	PacketHeader header;
	uint16_t intensity;
} ATTRIBUTE_PACKED GetIntensityResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetIntensityCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIntensityCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetIntensityCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetIntensityCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIntensityCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetIntensityCallbackThresholdResponse_;

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
	uint16_t intensity;
} ATTRIBUTE_PACKED IntensityCallback_;

typedef struct {
	PacketHeader header;
	uint16_t intensity;
} ATTRIBUTE_PACKED IntensityReachedCallback_;

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

static void sound_intensity_callback_wrapper_intensity(DevicePrivate *device_p, Packet *packet) {
	IntensityCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[SOUND_INTENSITY_CALLBACK_INTENSITY];
	IntensityCallback_ *callback = (IntensityCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[SOUND_INTENSITY_CALLBACK_INTENSITY];

	if (callback_function == NULL) {
		return;
	}

	callback->intensity = leconvert_uint16_from(callback->intensity);

	callback_function(callback->intensity, user_data);
}

static void sound_intensity_callback_wrapper_intensity_reached(DevicePrivate *device_p, Packet *packet) {
	IntensityReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED];
	IntensityReachedCallback_ *callback = (IntensityReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->intensity = leconvert_uint16_from(callback->intensity);

	callback_function(callback->intensity, user_data);
}

void sound_intensity_create(SoundIntensity *sound_intensity, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(sound_intensity, uid, ipcon->p, 2, 0, 0);

	device_p = sound_intensity->p;

	device_p->response_expected[SOUND_INTENSITY_FUNCTION_GET_INTENSITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_SET_INTENSITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_GET_INTENSITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_SET_INTENSITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_GET_INTENSITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_INTENSITY_CALLBACK_INTENSITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[SOUND_INTENSITY_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SOUND_INTENSITY_CALLBACK_INTENSITY] = sound_intensity_callback_wrapper_intensity;
	device_p->callback_wrappers[SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED] = sound_intensity_callback_wrapper_intensity_reached;
}

void sound_intensity_destroy(SoundIntensity *sound_intensity) {
	device_release(sound_intensity->p);
}

int sound_intensity_get_response_expected(SoundIntensity *sound_intensity, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(sound_intensity->p, function_id, ret_response_expected);
}

int sound_intensity_set_response_expected(SoundIntensity *sound_intensity, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(sound_intensity->p, function_id, response_expected);
}

int sound_intensity_set_response_expected_all(SoundIntensity *sound_intensity, bool response_expected) {
	return device_set_response_expected_all(sound_intensity->p, response_expected);
}

void sound_intensity_register_callback(SoundIntensity *sound_intensity, uint8_t id, void *callback, void *user_data) {
	device_register_callback(sound_intensity->p, id, callback, user_data);
}

int sound_intensity_get_api_version(SoundIntensity *sound_intensity, uint8_t ret_api_version[3]) {
	return device_get_api_version(sound_intensity->p, ret_api_version);
}

int sound_intensity_get_intensity(SoundIntensity *sound_intensity, uint16_t *ret_intensity) {
	DevicePrivate *device_p = sound_intensity->p;
	GetIntensity_ request;
	GetIntensityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_GET_INTENSITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_intensity = leconvert_uint16_from(response.intensity);



	return ret;
}

int sound_intensity_set_intensity_callback_period(SoundIntensity *sound_intensity, uint32_t period) {
	DevicePrivate *device_p = sound_intensity->p;
	SetIntensityCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_SET_INTENSITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int sound_intensity_get_intensity_callback_period(SoundIntensity *sound_intensity, uint32_t *ret_period) {
	DevicePrivate *device_p = sound_intensity->p;
	GetIntensityCallbackPeriod_ request;
	GetIntensityCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_GET_INTENSITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int sound_intensity_set_intensity_callback_threshold(SoundIntensity *sound_intensity, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = sound_intensity->p;
	SetIntensityCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_SET_INTENSITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int sound_intensity_get_intensity_callback_threshold(SoundIntensity *sound_intensity, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = sound_intensity->p;
	GetIntensityCallbackThreshold_ request;
	GetIntensityCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_GET_INTENSITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int sound_intensity_set_debounce_period(SoundIntensity *sound_intensity, uint32_t debounce) {
	DevicePrivate *device_p = sound_intensity->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int sound_intensity_get_debounce_period(SoundIntensity *sound_intensity, uint32_t *ret_debounce) {
	DevicePrivate *device_p = sound_intensity->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int sound_intensity_get_identity(SoundIntensity *sound_intensity, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = sound_intensity->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_INTENSITY_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

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

#include "bricklet_tilt.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*TiltStateCallbackFunction)(uint8_t, void *);

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
} ATTRIBUTE_PACKED GetTiltState_;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED GetTiltStateResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableTiltStateCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableTiltStateCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsTiltStateCallbackEnabled_;

typedef struct {
	PacketHeader header;
	bool enabled;
} ATTRIBUTE_PACKED IsTiltStateCallbackEnabledResponse_;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED TiltStateCallback_;

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

static void tilt_callback_wrapper_tilt_state(DevicePrivate *device_p, Packet *packet) {
	TiltStateCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[TILT_CALLBACK_TILT_STATE];
	TiltStateCallback_ *callback = (TiltStateCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[TILT_CALLBACK_TILT_STATE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->state, user_data);
}

void tilt_create(Tilt *tilt, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(tilt, uid, ipcon->p, 2, 0, 0);

	device_p = tilt->p;

	device_p->response_expected[TILT_FUNCTION_GET_TILT_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TILT_FUNCTION_ENABLE_TILT_STATE_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TILT_FUNCTION_DISABLE_TILT_STATE_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TILT_FUNCTION_IS_TILT_STATE_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TILT_CALLBACK_TILT_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[TILT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[TILT_CALLBACK_TILT_STATE] = tilt_callback_wrapper_tilt_state;
}

void tilt_destroy(Tilt *tilt) {
	device_release(tilt->p);
}

int tilt_get_response_expected(Tilt *tilt, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(tilt->p, function_id, ret_response_expected);
}

int tilt_set_response_expected(Tilt *tilt, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(tilt->p, function_id, response_expected);
}

int tilt_set_response_expected_all(Tilt *tilt, bool response_expected) {
	return device_set_response_expected_all(tilt->p, response_expected);
}

void tilt_register_callback(Tilt *tilt, uint8_t id, void *callback, void *user_data) {
	device_register_callback(tilt->p, id, callback, user_data);
}

int tilt_get_api_version(Tilt *tilt, uint8_t ret_api_version[3]) {
	return device_get_api_version(tilt->p, ret_api_version);
}

int tilt_get_tilt_state(Tilt *tilt, uint8_t *ret_state) {
	DevicePrivate *device_p = tilt->p;
	GetTiltState_ request;
	GetTiltStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_GET_TILT_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_state = response.state;



	return ret;
}

int tilt_enable_tilt_state_callback(Tilt *tilt) {
	DevicePrivate *device_p = tilt->p;
	EnableTiltStateCallback_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_ENABLE_TILT_STATE_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int tilt_disable_tilt_state_callback(Tilt *tilt) {
	DevicePrivate *device_p = tilt->p;
	DisableTiltStateCallback_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_DISABLE_TILT_STATE_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int tilt_is_tilt_state_callback_enabled(Tilt *tilt, bool *ret_enabled) {
	DevicePrivate *device_p = tilt->p;
	IsTiltStateCallbackEnabled_ request;
	IsTiltStateCallbackEnabledResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_IS_TILT_STATE_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_enabled = response.enabled;



	return ret;
}

int tilt_get_identity(Tilt *tilt, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = tilt->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

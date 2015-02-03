/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_multi_touch.h"

#include <string.h>



typedef void (*TouchStateCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetTouchState_;

typedef struct {
	PacketHeader header;
	uint16_t state;
} ATTRIBUTE_PACKED GetTouchStateResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Recalibrate_;

typedef struct {
	PacketHeader header;
	uint16_t enabled_electrodes;
} ATTRIBUTE_PACKED SetElectrodeConfig_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetElectrodeConfig_;

typedef struct {
	PacketHeader header;
	uint16_t enabled_electrodes;
} ATTRIBUTE_PACKED GetElectrodeConfigResponse_;

typedef struct {
	PacketHeader header;
	uint16_t state;
} ATTRIBUTE_PACKED TouchStateCallback_;

typedef struct {
	PacketHeader header;
	uint8_t sensitivity;
} ATTRIBUTE_PACKED SetElectrodeSensitivity_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetElectrodeSensitivity_;

typedef struct {
	PacketHeader header;
	uint8_t sensitivity;
} ATTRIBUTE_PACKED GetElectrodeSensitivityResponse_;

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

static void multi_touch_callback_wrapper_touch_state(DevicePrivate *device_p, Packet *packet) {
	TouchStateCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MULTI_TOUCH_CALLBACK_TOUCH_STATE];
	TouchStateCallback_ *callback = (TouchStateCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MULTI_TOUCH_CALLBACK_TOUCH_STATE];

	if (callback_function == NULL) {
		return;
	}

	callback->state = leconvert_uint16_from(callback->state);

	callback_function(callback->state, user_data);
}

void multi_touch_create(MultiTouch *multi_touch, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(multi_touch, uid, ipcon->p, 2, 0, 0);

	device_p = multi_touch->p;

	device_p->response_expected[MULTI_TOUCH_FUNCTION_GET_TOUCH_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MULTI_TOUCH_FUNCTION_RECALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MULTI_TOUCH_FUNCTION_SET_ELECTRODE_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MULTI_TOUCH_FUNCTION_GET_ELECTRODE_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MULTI_TOUCH_CALLBACK_TOUCH_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MULTI_TOUCH_FUNCTION_SET_ELECTRODE_SENSITIVITY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MULTI_TOUCH_FUNCTION_GET_ELECTRODE_SENSITIVITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MULTI_TOUCH_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[MULTI_TOUCH_CALLBACK_TOUCH_STATE] = multi_touch_callback_wrapper_touch_state;
}

void multi_touch_destroy(MultiTouch *multi_touch) {
	device_destroy(multi_touch);
}

int multi_touch_get_response_expected(MultiTouch *multi_touch, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(multi_touch->p, function_id, ret_response_expected);
}

int multi_touch_set_response_expected(MultiTouch *multi_touch, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(multi_touch->p, function_id, response_expected);
}

int multi_touch_set_response_expected_all(MultiTouch *multi_touch, bool response_expected) {
	return device_set_response_expected_all(multi_touch->p, response_expected);
}

void multi_touch_register_callback(MultiTouch *multi_touch, uint8_t id, void *callback, void *user_data) {
	device_register_callback(multi_touch->p, id, callback, user_data);
}

int multi_touch_get_api_version(MultiTouch *multi_touch, uint8_t ret_api_version[3]) {
	return device_get_api_version(multi_touch->p, ret_api_version);
}

int multi_touch_get_touch_state(MultiTouch *multi_touch, uint16_t *ret_state) {
	DevicePrivate *device_p = multi_touch->p;
	GetTouchState_ request;
	GetTouchStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_GET_TOUCH_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_state = leconvert_uint16_from(response.state);



	return ret;
}

int multi_touch_recalibrate(MultiTouch *multi_touch) {
	DevicePrivate *device_p = multi_touch->p;
	Recalibrate_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_RECALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int multi_touch_set_electrode_config(MultiTouch *multi_touch, uint16_t enabled_electrodes) {
	DevicePrivate *device_p = multi_touch->p;
	SetElectrodeConfig_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_SET_ELECTRODE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled_electrodes = leconvert_uint16_to(enabled_electrodes);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int multi_touch_get_electrode_config(MultiTouch *multi_touch, uint16_t *ret_enabled_electrodes) {
	DevicePrivate *device_p = multi_touch->p;
	GetElectrodeConfig_ request;
	GetElectrodeConfigResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_GET_ELECTRODE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_enabled_electrodes = leconvert_uint16_from(response.enabled_electrodes);



	return ret;
}

int multi_touch_set_electrode_sensitivity(MultiTouch *multi_touch, uint8_t sensitivity) {
	DevicePrivate *device_p = multi_touch->p;
	SetElectrodeSensitivity_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_SET_ELECTRODE_SENSITIVITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.sensitivity = sensitivity;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int multi_touch_get_electrode_sensitivity(MultiTouch *multi_touch, uint8_t *ret_sensitivity) {
	DevicePrivate *device_p = multi_touch->p;
	GetElectrodeSensitivity_ request;
	GetElectrodeSensitivityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_GET_ELECTRODE_SENSITIVITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_sensitivity = response.sensitivity;



	return ret;
}

int multi_touch_get_identity(MultiTouch *multi_touch, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = multi_touch->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MULTI_TOUCH_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

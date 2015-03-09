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

#include "bricklet_dual_button.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*StateChangedCallbackFunction)(uint8_t, uint8_t, uint8_t, uint8_t, void *);

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
	uint8_t led_l;
	uint8_t led_r;
} ATTRIBUTE_PACKED SetLEDState_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLEDState_;

typedef struct {
	PacketHeader header;
	uint8_t led_l;
	uint8_t led_r;
} ATTRIBUTE_PACKED GetLEDStateResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetButtonState_;

typedef struct {
	PacketHeader header;
	uint8_t button_l;
	uint8_t button_r;
} ATTRIBUTE_PACKED GetButtonStateResponse_;

typedef struct {
	PacketHeader header;
	uint8_t button_l;
	uint8_t button_r;
	uint8_t led_l;
	uint8_t led_r;
} ATTRIBUTE_PACKED StateChangedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t led;
	uint8_t state;
} ATTRIBUTE_PACKED SetSelectedLEDState_;

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

static void dual_button_callback_wrapper_state_changed(DevicePrivate *device_p, Packet *packet) {
	StateChangedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DUAL_BUTTON_CALLBACK_STATE_CHANGED];
	StateChangedCallback_ *callback = (StateChangedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DUAL_BUTTON_CALLBACK_STATE_CHANGED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->button_l, callback->button_r, callback->led_l, callback->led_r, user_data);
}

void dual_button_create(DualButton *dual_button, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(dual_button, uid, ipcon->p, 2, 0, 0);

	device_p = dual_button->p;

	device_p->response_expected[DUAL_BUTTON_FUNCTION_SET_LED_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_FUNCTION_GET_LED_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_FUNCTION_GET_BUTTON_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_CALLBACK_STATE_CHANGED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DUAL_BUTTON_FUNCTION_SET_SELECTED_LED_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DUAL_BUTTON_CALLBACK_STATE_CHANGED] = dual_button_callback_wrapper_state_changed;
}

void dual_button_destroy(DualButton *dual_button) {
	device_release(dual_button->p);
}

int dual_button_get_response_expected(DualButton *dual_button, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dual_button->p, function_id, ret_response_expected);
}

int dual_button_set_response_expected(DualButton *dual_button, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dual_button->p, function_id, response_expected);
}

int dual_button_set_response_expected_all(DualButton *dual_button, bool response_expected) {
	return device_set_response_expected_all(dual_button->p, response_expected);
}

void dual_button_register_callback(DualButton *dual_button, uint8_t id, void *callback, void *user_data) {
	device_register_callback(dual_button->p, id, callback, user_data);
}

int dual_button_get_api_version(DualButton *dual_button, uint8_t ret_api_version[3]) {
	return device_get_api_version(dual_button->p, ret_api_version);
}

int dual_button_set_led_state(DualButton *dual_button, uint8_t led_l, uint8_t led_r) {
	DevicePrivate *device_p = dual_button->p;
	SetLEDState_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_FUNCTION_SET_LED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.led_l = led_l;
	request.led_r = led_r;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dual_button_get_led_state(DualButton *dual_button, uint8_t *ret_led_l, uint8_t *ret_led_r) {
	DevicePrivate *device_p = dual_button->p;
	GetLEDState_ request;
	GetLEDStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_FUNCTION_GET_LED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_led_l = response.led_l;
	*ret_led_r = response.led_r;



	return ret;
}

int dual_button_get_button_state(DualButton *dual_button, uint8_t *ret_button_l, uint8_t *ret_button_r) {
	DevicePrivate *device_p = dual_button->p;
	GetButtonState_ request;
	GetButtonStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_FUNCTION_GET_BUTTON_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_button_l = response.button_l;
	*ret_button_r = response.button_r;



	return ret;
}

int dual_button_set_selected_led_state(DualButton *dual_button, uint8_t led, uint8_t state) {
	DevicePrivate *device_p = dual_button->p;
	SetSelectedLEDState_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_FUNCTION_SET_SELECTED_LED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.led = led;
	request.state = state;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dual_button_get_identity(DualButton *dual_button, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dual_button->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

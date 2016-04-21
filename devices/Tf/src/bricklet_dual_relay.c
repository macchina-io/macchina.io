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

#include "bricklet_dual_relay.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*MonoflopDoneCallbackFunction)(uint8_t, bool, void *);

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
	bool relay1;
	bool relay2;
} ATTRIBUTE_PACKED SetState_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetState_;

typedef struct {
	PacketHeader header;
	bool relay1;
	bool relay2;
} ATTRIBUTE_PACKED GetStateResponse_;

typedef struct {
	PacketHeader header;
	uint8_t relay;
	bool state;
	uint32_t time;
} ATTRIBUTE_PACKED SetMonoflop_;

typedef struct {
	PacketHeader header;
	uint8_t relay;
} ATTRIBUTE_PACKED GetMonoflop_;

typedef struct {
	PacketHeader header;
	bool state;
	uint32_t time;
	uint32_t time_remaining;
} ATTRIBUTE_PACKED GetMonoflopResponse_;

typedef struct {
	PacketHeader header;
	uint8_t relay;
	bool state;
} ATTRIBUTE_PACKED MonoflopDoneCallback_;

typedef struct {
	PacketHeader header;
	uint8_t relay;
	bool state;
} ATTRIBUTE_PACKED SetSelectedState_;

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

static void dual_relay_callback_wrapper_monoflop_done(DevicePrivate *device_p, Packet *packet) {
	MonoflopDoneCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DUAL_RELAY_CALLBACK_MONOFLOP_DONE];
	MonoflopDoneCallback_ *callback = (MonoflopDoneCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DUAL_RELAY_CALLBACK_MONOFLOP_DONE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->relay, callback->state, user_data);
}

void dual_relay_create(DualRelay *dual_relay, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(dual_relay, uid, ipcon->p, 2, 0, 0);

	device_p = dual_relay->p;

	device_p->response_expected[DUAL_RELAY_FUNCTION_SET_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_RELAY_FUNCTION_GET_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_RELAY_FUNCTION_SET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_RELAY_FUNCTION_GET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_RELAY_CALLBACK_MONOFLOP_DONE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DUAL_RELAY_FUNCTION_SET_SELECTED_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_RELAY_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DUAL_RELAY_CALLBACK_MONOFLOP_DONE] = dual_relay_callback_wrapper_monoflop_done;
}

void dual_relay_destroy(DualRelay *dual_relay) {
	device_release(dual_relay->p);
}

int dual_relay_get_response_expected(DualRelay *dual_relay, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dual_relay->p, function_id, ret_response_expected);
}

int dual_relay_set_response_expected(DualRelay *dual_relay, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dual_relay->p, function_id, response_expected);
}

int dual_relay_set_response_expected_all(DualRelay *dual_relay, bool response_expected) {
	return device_set_response_expected_all(dual_relay->p, response_expected);
}

void dual_relay_register_callback(DualRelay *dual_relay, uint8_t id, void *callback, void *user_data) {
	device_register_callback(dual_relay->p, id, callback, user_data);
}

int dual_relay_get_api_version(DualRelay *dual_relay, uint8_t ret_api_version[3]) {
	return device_get_api_version(dual_relay->p, ret_api_version);
}

int dual_relay_set_state(DualRelay *dual_relay, bool relay1, bool relay2) {
	DevicePrivate *device_p = dual_relay->p;
	SetState_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_RELAY_FUNCTION_SET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.relay1 = relay1;
	request.relay2 = relay2;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dual_relay_get_state(DualRelay *dual_relay, bool *ret_relay1, bool *ret_relay2) {
	DevicePrivate *device_p = dual_relay->p;
	GetState_ request;
	GetStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_RELAY_FUNCTION_GET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_relay1 = response.relay1;
	*ret_relay2 = response.relay2;



	return ret;
}

int dual_relay_set_monoflop(DualRelay *dual_relay, uint8_t relay, bool state, uint32_t time) {
	DevicePrivate *device_p = dual_relay->p;
	SetMonoflop_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_RELAY_FUNCTION_SET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.relay = relay;
	request.state = state;
	request.time = leconvert_uint32_to(time);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dual_relay_get_monoflop(DualRelay *dual_relay, uint8_t relay, bool *ret_state, uint32_t *ret_time, uint32_t *ret_time_remaining) {
	DevicePrivate *device_p = dual_relay->p;
	GetMonoflop_ request;
	GetMonoflopResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_RELAY_FUNCTION_GET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.relay = relay;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_state = response.state;
	*ret_time = leconvert_uint32_from(response.time);
	*ret_time_remaining = leconvert_uint32_from(response.time_remaining);



	return ret;
}

int dual_relay_set_selected_state(DualRelay *dual_relay, uint8_t relay, bool state) {
	DevicePrivate *device_p = dual_relay->p;
	SetSelectedState_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_RELAY_FUNCTION_SET_SELECTED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.relay = relay;
	request.state = state;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dual_relay_get_identity(DualRelay *dual_relay, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dual_relay->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_RELAY_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

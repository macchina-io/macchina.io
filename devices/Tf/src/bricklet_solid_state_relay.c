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

#include "bricklet_solid_state_relay.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*MonoflopDoneCallbackFunction)(bool, void *);

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
	bool state;
} ATTRIBUTE_PACKED SetState_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetState_;

typedef struct {
	PacketHeader header;
	bool state;
} ATTRIBUTE_PACKED GetStateResponse_;

typedef struct {
	PacketHeader header;
	bool state;
	uint32_t time;
} ATTRIBUTE_PACKED SetMonoflop_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMonoflop_;

typedef struct {
	PacketHeader header;
	bool state;
	uint32_t time;
	uint32_t time_remaining;
} ATTRIBUTE_PACKED GetMonoflopResponse_;

typedef struct {
	PacketHeader header;
	bool state;
} ATTRIBUTE_PACKED MonoflopDoneCallback_;

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

static void solid_state_relay_callback_wrapper_monoflop_done(DevicePrivate *device_p, Packet *packet) {
	MonoflopDoneCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[SOLID_STATE_RELAY_CALLBACK_MONOFLOP_DONE];
	MonoflopDoneCallback_ *callback = (MonoflopDoneCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[SOLID_STATE_RELAY_CALLBACK_MONOFLOP_DONE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->state, user_data);
}

void solid_state_relay_create(SolidStateRelay *solid_state_relay, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(solid_state_relay, uid, ipcon->p, 2, 0, 0);

	device_p = solid_state_relay->p;

	device_p->response_expected[SOLID_STATE_RELAY_FUNCTION_SET_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOLID_STATE_RELAY_FUNCTION_GET_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOLID_STATE_RELAY_FUNCTION_SET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOLID_STATE_RELAY_FUNCTION_GET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOLID_STATE_RELAY_CALLBACK_MONOFLOP_DONE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[SOLID_STATE_RELAY_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SOLID_STATE_RELAY_CALLBACK_MONOFLOP_DONE] = solid_state_relay_callback_wrapper_monoflop_done;
}

void solid_state_relay_destroy(SolidStateRelay *solid_state_relay) {
	device_release(solid_state_relay->p);
}

int solid_state_relay_get_response_expected(SolidStateRelay *solid_state_relay, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(solid_state_relay->p, function_id, ret_response_expected);
}

int solid_state_relay_set_response_expected(SolidStateRelay *solid_state_relay, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(solid_state_relay->p, function_id, response_expected);
}

int solid_state_relay_set_response_expected_all(SolidStateRelay *solid_state_relay, bool response_expected) {
	return device_set_response_expected_all(solid_state_relay->p, response_expected);
}

void solid_state_relay_register_callback(SolidStateRelay *solid_state_relay, uint8_t id, void *callback, void *user_data) {
	device_register_callback(solid_state_relay->p, id, callback, user_data);
}

int solid_state_relay_get_api_version(SolidStateRelay *solid_state_relay, uint8_t ret_api_version[3]) {
	return device_get_api_version(solid_state_relay->p, ret_api_version);
}

int solid_state_relay_set_state(SolidStateRelay *solid_state_relay, bool state) {
	DevicePrivate *device_p = solid_state_relay->p;
	SetState_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOLID_STATE_RELAY_FUNCTION_SET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.state = state;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int solid_state_relay_get_state(SolidStateRelay *solid_state_relay, bool *ret_state) {
	DevicePrivate *device_p = solid_state_relay->p;
	GetState_ request;
	GetStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOLID_STATE_RELAY_FUNCTION_GET_STATE, device_p->ipcon_p, device_p);

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

int solid_state_relay_set_monoflop(SolidStateRelay *solid_state_relay, bool state, uint32_t time) {
	DevicePrivate *device_p = solid_state_relay->p;
	SetMonoflop_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOLID_STATE_RELAY_FUNCTION_SET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.state = state;
	request.time = leconvert_uint32_to(time);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int solid_state_relay_get_monoflop(SolidStateRelay *solid_state_relay, bool *ret_state, uint32_t *ret_time, uint32_t *ret_time_remaining) {
	DevicePrivate *device_p = solid_state_relay->p;
	GetMonoflop_ request;
	GetMonoflopResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOLID_STATE_RELAY_FUNCTION_GET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_state = response.state;
	*ret_time = leconvert_uint32_from(response.time);
	*ret_time_remaining = leconvert_uint32_from(response.time_remaining);



	return ret;
}

int solid_state_relay_get_identity(SolidStateRelay *solid_state_relay, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = solid_state_relay->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOLID_STATE_RELAY_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

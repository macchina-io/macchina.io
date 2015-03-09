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

#include "bricklet_industrial_digital_out_4.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*MonoflopDoneCallbackFunction)(uint16_t, uint16_t, void *);

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
	uint16_t value_mask;
} ATTRIBUTE_PACKED SetValue_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetValue_;

typedef struct {
	PacketHeader header;
	uint16_t value_mask;
} ATTRIBUTE_PACKED GetValueResponse_;

typedef struct {
	PacketHeader header;
	uint16_t selection_mask;
	uint16_t value_mask;
	uint32_t time;
} ATTRIBUTE_PACKED SetMonoflop_;

typedef struct {
	PacketHeader header;
	uint8_t pin;
} ATTRIBUTE_PACKED GetMonoflop_;

typedef struct {
	PacketHeader header;
	uint16_t value;
	uint32_t time;
	uint32_t time_remaining;
} ATTRIBUTE_PACKED GetMonoflopResponse_;

typedef struct {
	PacketHeader header;
	char group[4];
} ATTRIBUTE_PACKED SetGroup_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGroup_;

typedef struct {
	PacketHeader header;
	char group[4];
} ATTRIBUTE_PACKED GetGroupResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAvailableForGroup_;

typedef struct {
	PacketHeader header;
	uint8_t available;
} ATTRIBUTE_PACKED GetAvailableForGroupResponse_;

typedef struct {
	PacketHeader header;
	uint16_t selection_mask;
	uint16_t value_mask;
} ATTRIBUTE_PACKED MonoflopDoneCallback_;

typedef struct {
	PacketHeader header;
	uint16_t selection_mask;
	uint16_t value_mask;
} ATTRIBUTE_PACKED SetSelectedValues_;

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

static void industrial_digital_out_4_callback_wrapper_monoflop_done(DevicePrivate *device_p, Packet *packet) {
	MonoflopDoneCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[INDUSTRIAL_DIGITAL_OUT_4_CALLBACK_MONOFLOP_DONE];
	MonoflopDoneCallback_ *callback = (MonoflopDoneCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[INDUSTRIAL_DIGITAL_OUT_4_CALLBACK_MONOFLOP_DONE];

	if (callback_function == NULL) {
		return;
	}

	callback->selection_mask = leconvert_uint16_from(callback->selection_mask);
	callback->value_mask = leconvert_uint16_from(callback->value_mask);

	callback_function(callback->selection_mask, callback->value_mask, user_data);
}

void industrial_digital_out_4_create(IndustrialDigitalOut4 *industrial_digital_out_4, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(industrial_digital_out_4, uid, ipcon->p, 2, 0, 0);

	device_p = industrial_digital_out_4->p;

	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_VALUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_GROUP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_GROUP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_AVAILABLE_FOR_GROUP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_CALLBACK_MONOFLOP_DONE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_SELECTED_VALUES] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[INDUSTRIAL_DIGITAL_OUT_4_CALLBACK_MONOFLOP_DONE] = industrial_digital_out_4_callback_wrapper_monoflop_done;
}

void industrial_digital_out_4_destroy(IndustrialDigitalOut4 *industrial_digital_out_4) {
	device_release(industrial_digital_out_4->p);
}

int industrial_digital_out_4_get_response_expected(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(industrial_digital_out_4->p, function_id, ret_response_expected);
}

int industrial_digital_out_4_set_response_expected(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(industrial_digital_out_4->p, function_id, response_expected);
}

int industrial_digital_out_4_set_response_expected_all(IndustrialDigitalOut4 *industrial_digital_out_4, bool response_expected) {
	return device_set_response_expected_all(industrial_digital_out_4->p, response_expected);
}

void industrial_digital_out_4_register_callback(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t id, void *callback, void *user_data) {
	device_register_callback(industrial_digital_out_4->p, id, callback, user_data);
}

int industrial_digital_out_4_get_api_version(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t ret_api_version[3]) {
	return device_get_api_version(industrial_digital_out_4->p, ret_api_version);
}

int industrial_digital_out_4_set_value(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t value_mask) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	SetValue_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.value_mask = leconvert_uint16_to(value_mask);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_digital_out_4_get_value(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t *ret_value_mask) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	GetValue_ request;
	GetValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value_mask = leconvert_uint16_from(response.value_mask);



	return ret;
}

int industrial_digital_out_4_set_monoflop(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t selection_mask, uint16_t value_mask, uint32_t time) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	SetMonoflop_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = leconvert_uint16_to(selection_mask);
	request.value_mask = leconvert_uint16_to(value_mask);
	request.time = leconvert_uint32_to(time);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_digital_out_4_get_monoflop(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t pin, uint16_t *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	GetMonoflop_ request;
	GetMonoflopResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value = leconvert_uint16_from(response.value);
	*ret_time = leconvert_uint32_from(response.time);
	*ret_time_remaining = leconvert_uint32_from(response.time_remaining);



	return ret;
}

int industrial_digital_out_4_set_group(IndustrialDigitalOut4 *industrial_digital_out_4, char group[4]) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	SetGroup_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_GROUP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.group, group, 4 * sizeof(char));

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_digital_out_4_get_group(IndustrialDigitalOut4 *industrial_digital_out_4, char ret_group[4]) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	GetGroup_ request;
	GetGroupResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_GROUP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	memcpy(ret_group, response.group, 4 * sizeof(char));



	return ret;
}

int industrial_digital_out_4_get_available_for_group(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t *ret_available) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	GetAvailableForGroup_ request;
	GetAvailableForGroupResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_AVAILABLE_FOR_GROUP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_available = response.available;



	return ret;
}

int industrial_digital_out_4_set_selected_values(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t selection_mask, uint16_t value_mask) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	SetSelectedValues_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_SELECTED_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = leconvert_uint16_to(selection_mask);
	request.value_mask = leconvert_uint16_to(value_mask);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_digital_out_4_get_identity(IndustrialDigitalOut4 *industrial_digital_out_4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = industrial_digital_out_4->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

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

#include "bricklet_hall_effect.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*EdgeCountCallbackFunction)(uint32_t, bool, void *);

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
} ATTRIBUTE_PACKED GetValue_;

typedef struct {
	PacketHeader header;
	bool value;
} ATTRIBUTE_PACKED GetValueResponse_;

typedef struct {
	PacketHeader header;
	bool reset_counter;
} ATTRIBUTE_PACKED GetEdgeCount_;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetEdgeCountResponse_;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED SetEdgeCountConfig_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEdgeCountConfig_;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED GetEdgeCountConfigResponse_;

typedef struct {
	PacketHeader header;
	uint32_t edges;
} ATTRIBUTE_PACKED SetEdgeInterrupt_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEdgeInterrupt_;

typedef struct {
	PacketHeader header;
	uint32_t edges;
} ATTRIBUTE_PACKED GetEdgeInterruptResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetEdgeCountCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEdgeCountCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetEdgeCountCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EdgeInterrupt_;

typedef struct {
	PacketHeader header;
	uint32_t count;
	bool value;
} ATTRIBUTE_PACKED EdgeInterruptResponse_;

typedef struct {
	PacketHeader header;
	uint32_t count;
	bool value;
} ATTRIBUTE_PACKED EdgeCountCallback_;

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

static void hall_effect_callback_wrapper_edge_count(DevicePrivate *device_p, Packet *packet) {
	EdgeCountCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[HALL_EFFECT_CALLBACK_EDGE_COUNT];
	EdgeCountCallback_ *callback = (EdgeCountCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[HALL_EFFECT_CALLBACK_EDGE_COUNT];

	if (callback_function == NULL) {
		return;
	}

	callback->count = leconvert_uint32_from(callback->count);

	callback_function(callback->count, callback->value, user_data);
}

void hall_effect_create(HallEffect *hall_effect, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(hall_effect, uid, ipcon->p, 2, 0, 0);

	device_p = hall_effect->p;

	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_SET_EDGE_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_EDGE_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_CALLBACK_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[HALL_EFFECT_CALLBACK_EDGE_COUNT] = hall_effect_callback_wrapper_edge_count;
}

void hall_effect_destroy(HallEffect *hall_effect) {
	device_release(hall_effect->p);
}

int hall_effect_get_response_expected(HallEffect *hall_effect, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(hall_effect->p, function_id, ret_response_expected);
}

int hall_effect_set_response_expected(HallEffect *hall_effect, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(hall_effect->p, function_id, response_expected);
}

int hall_effect_set_response_expected_all(HallEffect *hall_effect, bool response_expected) {
	return device_set_response_expected_all(hall_effect->p, response_expected);
}

void hall_effect_register_callback(HallEffect *hall_effect, uint8_t id, void *callback, void *user_data) {
	device_register_callback(hall_effect->p, id, callback, user_data);
}

int hall_effect_get_api_version(HallEffect *hall_effect, uint8_t ret_api_version[3]) {
	return device_get_api_version(hall_effect->p, ret_api_version);
}

int hall_effect_get_value(HallEffect *hall_effect, bool *ret_value) {
	DevicePrivate *device_p = hall_effect->p;
	GetValue_ request;
	GetValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value = response.value;



	return ret;
}

int hall_effect_get_edge_count(HallEffect *hall_effect, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeCount_ request;
	GetEdgeCountResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.reset_counter = reset_counter;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_count = leconvert_uint32_from(response.count);



	return ret;
}

int hall_effect_set_edge_count_config(HallEffect *hall_effect, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = hall_effect->p;
	SetEdgeCountConfig_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int hall_effect_get_edge_count_config(HallEffect *hall_effect, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeCountConfig_ request;
	GetEdgeCountConfigResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_edge_type = response.edge_type;
	*ret_debounce = response.debounce;



	return ret;
}

int hall_effect_set_edge_interrupt(HallEffect *hall_effect, uint32_t edges) {
	DevicePrivate *device_p = hall_effect->p;
	SetEdgeInterrupt_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_SET_EDGE_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.edges = leconvert_uint32_to(edges);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int hall_effect_get_edge_interrupt(HallEffect *hall_effect, uint32_t *ret_edges) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeInterrupt_ request;
	GetEdgeInterruptResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_edges = leconvert_uint32_from(response.edges);



	return ret;
}

int hall_effect_set_edge_count_callback_period(HallEffect *hall_effect, uint32_t period) {
	DevicePrivate *device_p = hall_effect->p;
	SetEdgeCountCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int hall_effect_get_edge_count_callback_period(HallEffect *hall_effect, uint32_t *ret_period) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeCountCallbackPeriod_ request;
	GetEdgeCountCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int hall_effect_edge_interrupt(HallEffect *hall_effect, uint32_t *ret_count, bool *ret_value) {
	DevicePrivate *device_p = hall_effect->p;
	EdgeInterrupt_ request;
	EdgeInterruptResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_EDGE_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_count = leconvert_uint32_from(response.count);
	*ret_value = response.value;



	return ret;
}

int hall_effect_get_identity(HallEffect *hall_effect, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = hall_effect->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

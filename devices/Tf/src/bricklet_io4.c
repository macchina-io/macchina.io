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

#include "bricklet_io4.h"

#include <string.h>



typedef void (*InterruptCallbackFunction)(uint8_t, uint8_t, void *);

typedef void (*MonoflopDoneCallbackFunction)(uint8_t, uint8_t, void *);

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
	uint8_t value_mask;
} ATTRIBUTE_PACKED SetValue_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetValue_;

typedef struct {
	PacketHeader header;
	uint8_t value_mask;
} ATTRIBUTE_PACKED GetValueResponse_;

typedef struct {
	PacketHeader header;
	uint8_t selection_mask;
	char direction;
	bool value;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t direction_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

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
	uint8_t interrupt_mask;
} ATTRIBUTE_PACKED SetInterrupt_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInterrupt_;

typedef struct {
	PacketHeader header;
	uint8_t interrupt_mask;
} ATTRIBUTE_PACKED GetInterruptResponse_;

typedef struct {
	PacketHeader header;
	uint8_t interrupt_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED InterruptCallback_;

typedef struct {
	PacketHeader header;
	uint8_t selection_mask;
	uint8_t value_mask;
	uint32_t time;
} ATTRIBUTE_PACKED SetMonoflop_;

typedef struct {
	PacketHeader header;
	uint8_t pin;
} ATTRIBUTE_PACKED GetMonoflop_;

typedef struct {
	PacketHeader header;
	uint8_t value;
	uint32_t time;
	uint32_t time_remaining;
} ATTRIBUTE_PACKED GetMonoflopResponse_;

typedef struct {
	PacketHeader header;
	uint8_t selection_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED MonoflopDoneCallback_;

typedef struct {
	PacketHeader header;
	uint8_t selection_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED SetSelectedValues_;

typedef struct {
	PacketHeader header;
	uint8_t pin;
	bool reset_counter;
} ATTRIBUTE_PACKED GetEdgeCount_;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetEdgeCountResponse_;

typedef struct {
	PacketHeader header;
	uint8_t selection_mask;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED SetEdgeCountConfig_;

typedef struct {
	PacketHeader header;
	uint8_t pin;
} ATTRIBUTE_PACKED GetEdgeCountConfig_;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED GetEdgeCountConfigResponse_;

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

static void io4_callback_wrapper_interrupt(DevicePrivate *device_p, Packet *packet) {
	InterruptCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IO4_CALLBACK_INTERRUPT];
	InterruptCallback_ *callback = (InterruptCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IO4_CALLBACK_INTERRUPT];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->interrupt_mask, callback->value_mask, user_data);
}

static void io4_callback_wrapper_monoflop_done(DevicePrivate *device_p, Packet *packet) {
	MonoflopDoneCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IO4_CALLBACK_MONOFLOP_DONE];
	MonoflopDoneCallback_ *callback = (MonoflopDoneCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IO4_CALLBACK_MONOFLOP_DONE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->selection_mask, callback->value_mask, user_data);
}

void io4_create(IO4 *io4, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(io4, uid, ipcon->p, 2, 0, 1);

	device_p = io4->p;

	device_p->response_expected[IO4_FUNCTION_SET_VALUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO4_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO4_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IO4_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_FUNCTION_SET_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IO4_FUNCTION_GET_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_CALLBACK_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IO4_FUNCTION_SET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO4_FUNCTION_GET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_CALLBACK_MONOFLOP_DONE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IO4_FUNCTION_SET_SELECTED_VALUES] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO4_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_FUNCTION_SET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO4_FUNCTION_GET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO4_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[IO4_CALLBACK_INTERRUPT] = io4_callback_wrapper_interrupt;
	device_p->callback_wrappers[IO4_CALLBACK_MONOFLOP_DONE] = io4_callback_wrapper_monoflop_done;
}

void io4_destroy(IO4 *io4) {
	device_destroy(io4);
}

int io4_get_response_expected(IO4 *io4, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(io4->p, function_id, ret_response_expected);
}

int io4_set_response_expected(IO4 *io4, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(io4->p, function_id, response_expected);
}

int io4_set_response_expected_all(IO4 *io4, bool response_expected) {
	return device_set_response_expected_all(io4->p, response_expected);
}

void io4_register_callback(IO4 *io4, uint8_t id, void *callback, void *user_data) {
	device_register_callback(io4->p, id, callback, user_data);
}

int io4_get_api_version(IO4 *io4, uint8_t ret_api_version[3]) {
	return device_get_api_version(io4->p, ret_api_version);
}

int io4_set_value(IO4 *io4, uint8_t value_mask) {
	DevicePrivate *device_p = io4->p;
	SetValue_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.value_mask = value_mask;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_value(IO4 *io4, uint8_t *ret_value_mask) {
	DevicePrivate *device_p = io4->p;
	GetValue_ request;
	GetValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value_mask = response.value_mask;



	return ret;
}

int io4_set_configuration(IO4 *io4, uint8_t selection_mask, char direction, bool value) {
	DevicePrivate *device_p = io4->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = selection_mask;
	request.direction = direction;
	request.value = value;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_configuration(IO4 *io4, uint8_t *ret_direction_mask, uint8_t *ret_value_mask) {
	DevicePrivate *device_p = io4->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_direction_mask = response.direction_mask;
	*ret_value_mask = response.value_mask;



	return ret;
}

int io4_set_debounce_period(IO4 *io4, uint32_t debounce) {
	DevicePrivate *device_p = io4->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_debounce_period(IO4 *io4, uint32_t *ret_debounce) {
	DevicePrivate *device_p = io4->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int io4_set_interrupt(IO4 *io4, uint8_t interrupt_mask) {
	DevicePrivate *device_p = io4->p;
	SetInterrupt_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.interrupt_mask = interrupt_mask;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_interrupt(IO4 *io4, uint8_t *ret_interrupt_mask) {
	DevicePrivate *device_p = io4->p;
	GetInterrupt_ request;
	GetInterruptResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_interrupt_mask = response.interrupt_mask;



	return ret;
}

int io4_set_monoflop(IO4 *io4, uint8_t selection_mask, uint8_t value_mask, uint32_t time) {
	DevicePrivate *device_p = io4->p;
	SetMonoflop_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = selection_mask;
	request.value_mask = value_mask;
	request.time = leconvert_uint32_to(time);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_monoflop(IO4 *io4, uint8_t pin, uint8_t *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining) {
	DevicePrivate *device_p = io4->p;
	GetMonoflop_ request;
	GetMonoflopResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value = response.value;
	*ret_time = leconvert_uint32_from(response.time);
	*ret_time_remaining = leconvert_uint32_from(response.time_remaining);



	return ret;
}

int io4_set_selected_values(IO4 *io4, uint8_t selection_mask, uint8_t value_mask) {
	DevicePrivate *device_p = io4->p;
	SetSelectedValues_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_SELECTED_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = selection_mask;
	request.value_mask = value_mask;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_edge_count(IO4 *io4, uint8_t pin, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = io4->p;
	GetEdgeCount_ request;
	GetEdgeCountResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;
	request.reset_counter = reset_counter;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_count = leconvert_uint32_from(response.count);



	return ret;
}

int io4_set_edge_count_config(IO4 *io4, uint8_t selection_mask, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = io4->p;
	SetEdgeCountConfig_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_SET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = selection_mask;
	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io4_get_edge_count_config(IO4 *io4, uint8_t pin, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = io4->p;
	GetEdgeCountConfig_ request;
	GetEdgeCountConfigResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_edge_type = response.edge_type;
	*ret_debounce = response.debounce;



	return ret;
}

int io4_get_identity(IO4 *io4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = io4->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO4_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

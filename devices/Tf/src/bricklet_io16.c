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

#include "bricklet_io16.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*InterruptCallbackFunction)(char, uint8_t, uint8_t, void *);

typedef void (*MonoflopDoneCallbackFunction)(char, uint8_t, uint8_t, void *);

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
	char port;
	uint8_t value_mask;
} ATTRIBUTE_PACKED SetPort_;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetPort_;

typedef struct {
	PacketHeader header;
	uint8_t value_mask;
} ATTRIBUTE_PACKED GetPortResponse_;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t selection_mask;
	char direction;
	bool value;
} ATTRIBUTE_PACKED SetPortConfiguration_;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetPortConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t direction_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED GetPortConfigurationResponse_;

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
	char port;
	uint8_t interrupt_mask;
} ATTRIBUTE_PACKED SetPortInterrupt_;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetPortInterrupt_;

typedef struct {
	PacketHeader header;
	uint8_t interrupt_mask;
} ATTRIBUTE_PACKED GetPortInterruptResponse_;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t interrupt_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED InterruptCallback_;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t selection_mask;
	uint8_t value_mask;
	uint32_t time;
} ATTRIBUTE_PACKED SetPortMonoflop_;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t pin;
} ATTRIBUTE_PACKED GetPortMonoflop_;

typedef struct {
	PacketHeader header;
	uint8_t value;
	uint32_t time;
	uint32_t time_remaining;
} ATTRIBUTE_PACKED GetPortMonoflopResponse_;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t selection_mask;
	uint8_t value_mask;
} ATTRIBUTE_PACKED MonoflopDoneCallback_;

typedef struct {
	PacketHeader header;
	char port;
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
	uint8_t pin;
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

static void io16_callback_wrapper_interrupt(DevicePrivate *device_p, Packet *packet) {
	InterruptCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IO16_CALLBACK_INTERRUPT];
	InterruptCallback_ *callback = (InterruptCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IO16_CALLBACK_INTERRUPT];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->port, callback->interrupt_mask, callback->value_mask, user_data);
}

static void io16_callback_wrapper_monoflop_done(DevicePrivate *device_p, Packet *packet) {
	MonoflopDoneCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IO16_CALLBACK_MONOFLOP_DONE];
	MonoflopDoneCallback_ *callback = (MonoflopDoneCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IO16_CALLBACK_MONOFLOP_DONE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->port, callback->selection_mask, callback->value_mask, user_data);
}

void io16_create(IO16 *io16, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(io16, uid, ipcon->p, 2, 0, 1);

	device_p = io16->p;

	device_p->response_expected[IO16_FUNCTION_SET_PORT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_FUNCTION_GET_PORT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_FUNCTION_SET_PORT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_FUNCTION_GET_PORT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IO16_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_FUNCTION_SET_PORT_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IO16_FUNCTION_GET_PORT_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_CALLBACK_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IO16_FUNCTION_SET_PORT_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_FUNCTION_GET_PORT_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_CALLBACK_MONOFLOP_DONE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IO16_FUNCTION_SET_SELECTED_VALUES] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_FUNCTION_SET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_FUNCTION_GET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[IO16_CALLBACK_INTERRUPT] = io16_callback_wrapper_interrupt;
	device_p->callback_wrappers[IO16_CALLBACK_MONOFLOP_DONE] = io16_callback_wrapper_monoflop_done;
}

void io16_destroy(IO16 *io16) {
	device_release(io16->p);
}

int io16_get_response_expected(IO16 *io16, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(io16->p, function_id, ret_response_expected);
}

int io16_set_response_expected(IO16 *io16, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(io16->p, function_id, response_expected);
}

int io16_set_response_expected_all(IO16 *io16, bool response_expected) {
	return device_set_response_expected_all(io16->p, response_expected);
}

void io16_register_callback(IO16 *io16, uint8_t id, void *callback, void *user_data) {
	device_register_callback(io16->p, id, callback, user_data);
}

int io16_get_api_version(IO16 *io16, uint8_t ret_api_version[3]) {
	return device_get_api_version(io16->p, ret_api_version);
}

int io16_set_port(IO16 *io16, char port, uint8_t value_mask) {
	DevicePrivate *device_p = io16->p;
	SetPort_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_PORT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.value_mask = value_mask;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_port(IO16 *io16, char port, uint8_t *ret_value_mask) {
	DevicePrivate *device_p = io16->p;
	GetPort_ request;
	GetPortResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_PORT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_value_mask = response.value_mask;



	return ret;
}

int io16_set_port_configuration(IO16 *io16, char port, uint8_t selection_mask, char direction, bool value) {
	DevicePrivate *device_p = io16->p;
	SetPortConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_PORT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.selection_mask = selection_mask;
	request.direction = direction;
	request.value = value;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_port_configuration(IO16 *io16, char port, uint8_t *ret_direction_mask, uint8_t *ret_value_mask) {
	DevicePrivate *device_p = io16->p;
	GetPortConfiguration_ request;
	GetPortConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_PORT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_direction_mask = response.direction_mask;
	*ret_value_mask = response.value_mask;



	return ret;
}

int io16_set_debounce_period(IO16 *io16, uint32_t debounce) {
	DevicePrivate *device_p = io16->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_debounce_period(IO16 *io16, uint32_t *ret_debounce) {
	DevicePrivate *device_p = io16->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int io16_set_port_interrupt(IO16 *io16, char port, uint8_t interrupt_mask) {
	DevicePrivate *device_p = io16->p;
	SetPortInterrupt_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_PORT_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.interrupt_mask = interrupt_mask;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_port_interrupt(IO16 *io16, char port, uint8_t *ret_interrupt_mask) {
	DevicePrivate *device_p = io16->p;
	GetPortInterrupt_ request;
	GetPortInterruptResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_PORT_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_interrupt_mask = response.interrupt_mask;



	return ret;
}

int io16_set_port_monoflop(IO16 *io16, char port, uint8_t selection_mask, uint8_t value_mask, uint32_t time) {
	DevicePrivate *device_p = io16->p;
	SetPortMonoflop_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_PORT_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.selection_mask = selection_mask;
	request.value_mask = value_mask;
	request.time = leconvert_uint32_to(time);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_port_monoflop(IO16 *io16, char port, uint8_t pin, uint8_t *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining) {
	DevicePrivate *device_p = io16->p;
	GetPortMonoflop_ request;
	GetPortMonoflopResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_PORT_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
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

int io16_set_selected_values(IO16 *io16, char port, uint8_t selection_mask, uint8_t value_mask) {
	DevicePrivate *device_p = io16->p;
	SetSelectedValues_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_SELECTED_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.selection_mask = selection_mask;
	request.value_mask = value_mask;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_edge_count(IO16 *io16, uint8_t pin, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = io16->p;
	GetEdgeCount_ request;
	GetEdgeCountResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

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

int io16_set_edge_count_config(IO16 *io16, uint8_t pin, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = io16->p;
	SetEdgeCountConfig_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_SET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;
	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int io16_get_edge_count_config(IO16 *io16, uint8_t pin, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = io16->p;
	GetEdgeCountConfig_ request;
	GetEdgeCountConfigResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

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

int io16_get_identity(IO16 *io16, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = io16->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

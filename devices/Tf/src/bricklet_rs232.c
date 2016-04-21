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

#include "bricklet_rs232.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ReadCallbackCallbackFunction)(char[60], uint8_t, void *);

typedef void (*ErrorCallbackCallbackFunction)(uint8_t, void *);

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
	char message[60];
	uint8_t length;
} ATTRIBUTE_PACKED Write_;

typedef struct {
	PacketHeader header;
	uint8_t written;
} ATTRIBUTE_PACKED WriteResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Read_;

typedef struct {
	PacketHeader header;
	char message[60];
	uint8_t length;
} ATTRIBUTE_PACKED ReadResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableReadCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableReadCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsReadCallbackEnabled_;

typedef struct {
	PacketHeader header;
	bool enabled;
} ATTRIBUTE_PACKED IsReadCallbackEnabledResponse_;

typedef struct {
	PacketHeader header;
	uint8_t baudrate;
	uint8_t parity;
	uint8_t stopbits;
	uint8_t wordlength;
	uint8_t hardware_flowcontrol;
	uint8_t software_flowcontrol;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t baudrate;
	uint8_t parity;
	uint8_t stopbits;
	uint8_t wordlength;
	uint8_t hardware_flowcontrol;
	uint8_t software_flowcontrol;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

typedef struct {
	PacketHeader header;
	char message[60];
	uint8_t length;
} ATTRIBUTE_PACKED ReadCallbackCallback_;

typedef struct {
	PacketHeader header;
	uint8_t error;
} ATTRIBUTE_PACKED ErrorCallbackCallback_;

typedef struct {
	PacketHeader header;
	uint16_t break_time;
} ATTRIBUTE_PACKED SetBreakCondition_;

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

static void rs232_callback_wrapper_read_callback(DevicePrivate *device_p, Packet *packet) {
	ReadCallbackCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RS232_CALLBACK_READ_CALLBACK];
	ReadCallbackCallback_ *callback = (ReadCallbackCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RS232_CALLBACK_READ_CALLBACK];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->message, callback->length, user_data);
}

static void rs232_callback_wrapper_error_callback(DevicePrivate *device_p, Packet *packet) {
	ErrorCallbackCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RS232_CALLBACK_ERROR_CALLBACK];
	ErrorCallbackCallback_ *callback = (ErrorCallbackCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RS232_CALLBACK_ERROR_CALLBACK];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->error, user_data);
}

void rs232_create(RS232 *rs232, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(rs232, uid, ipcon->p, 2, 0, 2);

	device_p = rs232->p;

	device_p->response_expected[RS232_FUNCTION_WRITE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_FUNCTION_READ] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_FUNCTION_ENABLE_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS232_FUNCTION_DISABLE_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS232_FUNCTION_IS_READ_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_CALLBACK_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RS232_CALLBACK_ERROR_CALLBACK] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RS232_FUNCTION_SET_BREAK_CONDITION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[RS232_CALLBACK_READ_CALLBACK] = rs232_callback_wrapper_read_callback;
	device_p->callback_wrappers[RS232_CALLBACK_ERROR_CALLBACK] = rs232_callback_wrapper_error_callback;
}

void rs232_destroy(RS232 *rs232) {
	device_release(rs232->p);
}

int rs232_get_response_expected(RS232 *rs232, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rs232->p, function_id, ret_response_expected);
}

int rs232_set_response_expected(RS232 *rs232, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rs232->p, function_id, response_expected);
}

int rs232_set_response_expected_all(RS232 *rs232, bool response_expected) {
	return device_set_response_expected_all(rs232->p, response_expected);
}

void rs232_register_callback(RS232 *rs232, uint8_t id, void *callback, void *user_data) {
	device_register_callback(rs232->p, id, callback, user_data);
}

int rs232_get_api_version(RS232 *rs232, uint8_t ret_api_version[3]) {
	return device_get_api_version(rs232->p, ret_api_version);
}

int rs232_write(RS232 *rs232, char message[60], uint8_t length, uint8_t *ret_written) {
	DevicePrivate *device_p = rs232->p;
	Write_ request;
	WriteResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_WRITE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.message, message, 60 * sizeof(char));
	request.length = length;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_written = response.written;



	return ret;
}

int rs232_read(RS232 *rs232, char ret_message[60], uint8_t *ret_length) {
	DevicePrivate *device_p = rs232->p;
	Read_ request;
	ReadResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_READ, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	memcpy(ret_message, response.message, 60 * sizeof(char));
	*ret_length = response.length;



	return ret;
}

int rs232_enable_read_callback(RS232 *rs232) {
	DevicePrivate *device_p = rs232->p;
	EnableReadCallback_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_ENABLE_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rs232_disable_read_callback(RS232 *rs232) {
	DevicePrivate *device_p = rs232->p;
	DisableReadCallback_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_DISABLE_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rs232_is_read_callback_enabled(RS232 *rs232, bool *ret_enabled) {
	DevicePrivate *device_p = rs232->p;
	IsReadCallbackEnabled_ request;
	IsReadCallbackEnabledResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_IS_READ_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

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

int rs232_set_configuration(RS232 *rs232, uint8_t baudrate, uint8_t parity, uint8_t stopbits, uint8_t wordlength, uint8_t hardware_flowcontrol, uint8_t software_flowcontrol) {
	DevicePrivate *device_p = rs232->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.baudrate = baudrate;
	request.parity = parity;
	request.stopbits = stopbits;
	request.wordlength = wordlength;
	request.hardware_flowcontrol = hardware_flowcontrol;
	request.software_flowcontrol = software_flowcontrol;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rs232_get_configuration(RS232 *rs232, uint8_t *ret_baudrate, uint8_t *ret_parity, uint8_t *ret_stopbits, uint8_t *ret_wordlength, uint8_t *ret_hardware_flowcontrol, uint8_t *ret_software_flowcontrol) {
	DevicePrivate *device_p = rs232->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_baudrate = response.baudrate;
	*ret_parity = response.parity;
	*ret_stopbits = response.stopbits;
	*ret_wordlength = response.wordlength;
	*ret_hardware_flowcontrol = response.hardware_flowcontrol;
	*ret_software_flowcontrol = response.software_flowcontrol;



	return ret;
}

int rs232_set_break_condition(RS232 *rs232, uint16_t break_time) {
	DevicePrivate *device_p = rs232->p;
	SetBreakCondition_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_SET_BREAK_CONDITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.break_time = leconvert_uint16_to(break_time);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int rs232_get_identity(RS232 *rs232, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rs232->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

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

#include "bricklet_oled_128x64.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



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
	uint8_t data[64];
} ATTRIBUTE_PACKED Write_;

typedef struct {
	PacketHeader header;
	uint8_t column_from;
	uint8_t column_to;
	uint8_t row_from;
	uint8_t row_to;
} ATTRIBUTE_PACKED NewWindow_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ClearDisplay_;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	bool invert;
} ATTRIBUTE_PACKED SetDisplayConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDisplayConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	bool invert;
} ATTRIBUTE_PACKED GetDisplayConfigurationResponse_;

typedef struct {
	PacketHeader header;
	uint8_t line;
	uint8_t position;
	char text[26];
} ATTRIBUTE_PACKED WriteLine_;

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

void oled_128x64_create(OLED128x64 *oled_128x64, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(oled_128x64, uid, ipcon->p, 2, 0, 0);

	device_p = oled_128x64->p;

	device_p->response_expected[OLED_128X64_FUNCTION_WRITE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_NEW_WINDOW] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_CLEAR_DISPLAY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_FUNCTION_WRITE_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

}

void oled_128x64_destroy(OLED128x64 *oled_128x64) {
	device_release(oled_128x64->p);
}

int oled_128x64_get_response_expected(OLED128x64 *oled_128x64, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(oled_128x64->p, function_id, ret_response_expected);
}

int oled_128x64_set_response_expected(OLED128x64 *oled_128x64, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(oled_128x64->p, function_id, response_expected);
}

int oled_128x64_set_response_expected_all(OLED128x64 *oled_128x64, bool response_expected) {
	return device_set_response_expected_all(oled_128x64->p, response_expected);
}

void oled_128x64_register_callback(OLED128x64 *oled_128x64, uint8_t id, void *callback, void *user_data) {
	device_register_callback(oled_128x64->p, id, callback, user_data);
}

int oled_128x64_get_api_version(OLED128x64 *oled_128x64, uint8_t ret_api_version[3]) {
	return device_get_api_version(oled_128x64->p, ret_api_version);
}

int oled_128x64_write(OLED128x64 *oled_128x64, uint8_t data[64]) {
	DevicePrivate *device_p = oled_128x64->p;
	Write_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_WRITE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int oled_128x64_new_window(OLED128x64 *oled_128x64, uint8_t column_from, uint8_t column_to, uint8_t row_from, uint8_t row_to) {
	DevicePrivate *device_p = oled_128x64->p;
	NewWindow_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_NEW_WINDOW, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.column_from = column_from;
	request.column_to = column_to;
	request.row_from = row_from;
	request.row_to = row_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int oled_128x64_clear_display(OLED128x64 *oled_128x64) {
	DevicePrivate *device_p = oled_128x64->p;
	ClearDisplay_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_CLEAR_DISPLAY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int oled_128x64_set_display_configuration(OLED128x64 *oled_128x64, uint8_t contrast, bool invert) {
	DevicePrivate *device_p = oled_128x64->p;
	SetDisplayConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.contrast = contrast;
	request.invert = invert;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int oled_128x64_get_display_configuration(OLED128x64 *oled_128x64, uint8_t *ret_contrast, bool *ret_invert) {
	DevicePrivate *device_p = oled_128x64->p;
	GetDisplayConfiguration_ request;
	GetDisplayConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_contrast = response.contrast;
	*ret_invert = response.invert;



	return ret;
}

int oled_128x64_write_line(OLED128x64 *oled_128x64, uint8_t line, uint8_t position, const char text[26]) {
	DevicePrivate *device_p = oled_128x64->p;
	WriteLine_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_WRITE_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.line = line;
	request.position = position;
	strncpy(request.text, text, 26);


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int oled_128x64_get_identity(OLED128x64 *oled_128x64, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = oled_128x64->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

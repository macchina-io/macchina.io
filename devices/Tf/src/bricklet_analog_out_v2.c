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

#include "bricklet_analog_out_v2.h"

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
	uint16_t voltage;
} ATTRIBUTE_PACKED SetOutputVoltage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOutputVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetOutputVoltageResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInputVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetInputVoltageResponse_;

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

void analog_out_v2_create(AnalogOutV2 *analog_out_v2, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(analog_out_v2, uid, ipcon->p, 2, 0, 0);

	device_p = analog_out_v2->p;

	device_p->response_expected[ANALOG_OUT_V2_FUNCTION_SET_OUTPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ANALOG_OUT_V2_FUNCTION_GET_OUTPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_OUT_V2_FUNCTION_GET_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_OUT_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

}

void analog_out_v2_destroy(AnalogOutV2 *analog_out_v2) {
	device_release(analog_out_v2->p);
}

int analog_out_v2_get_response_expected(AnalogOutV2 *analog_out_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(analog_out_v2->p, function_id, ret_response_expected);
}

int analog_out_v2_set_response_expected(AnalogOutV2 *analog_out_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(analog_out_v2->p, function_id, response_expected);
}

int analog_out_v2_set_response_expected_all(AnalogOutV2 *analog_out_v2, bool response_expected) {
	return device_set_response_expected_all(analog_out_v2->p, response_expected);
}

void analog_out_v2_register_callback(AnalogOutV2 *analog_out_v2, uint8_t id, void *callback, void *user_data) {
	device_register_callback(analog_out_v2->p, id, callback, user_data);
}

int analog_out_v2_get_api_version(AnalogOutV2 *analog_out_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(analog_out_v2->p, ret_api_version);
}

int analog_out_v2_set_output_voltage(AnalogOutV2 *analog_out_v2, uint16_t voltage) {
	DevicePrivate *device_p = analog_out_v2->p;
	SetOutputVoltage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_OUT_V2_FUNCTION_SET_OUTPUT_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage = leconvert_uint16_to(voltage);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int analog_out_v2_get_output_voltage(AnalogOutV2 *analog_out_v2, uint16_t *ret_voltage) {
	DevicePrivate *device_p = analog_out_v2->p;
	GetOutputVoltage_ request;
	GetOutputVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_OUT_V2_FUNCTION_GET_OUTPUT_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_voltage = leconvert_uint16_from(response.voltage);



	return ret;
}

int analog_out_v2_get_input_voltage(AnalogOutV2 *analog_out_v2, uint16_t *ret_voltage) {
	DevicePrivate *device_p = analog_out_v2->p;
	GetInputVoltage_ request;
	GetInputVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_OUT_V2_FUNCTION_GET_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_voltage = leconvert_uint16_from(response.voltage);



	return ret;
}

int analog_out_v2_get_identity(AnalogOutV2 *analog_out_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = analog_out_v2->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_OUT_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

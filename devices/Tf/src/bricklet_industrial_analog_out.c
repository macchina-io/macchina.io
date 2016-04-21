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

#include "bricklet_industrial_analog_out.h"

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
} ATTRIBUTE_PACKED Enable_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Disable_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsEnabled_;

typedef struct {
	PacketHeader header;
	bool enabled;
} ATTRIBUTE_PACKED IsEnabledResponse_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED SetVoltage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetVoltageResponse_;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED SetCurrent_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrent_;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetCurrentResponse_;

typedef struct {
	PacketHeader header;
	uint8_t voltage_range;
	uint8_t current_range;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t voltage_range;
	uint8_t current_range;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

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

void industrial_analog_out_create(IndustrialAnalogOut *industrial_analog_out, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(industrial_analog_out, uid, ipcon->p, 2, 0, 0);

	device_p = industrial_analog_out->p;

	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_ENABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_DISABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_IS_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_CURRENT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

}

void industrial_analog_out_destroy(IndustrialAnalogOut *industrial_analog_out) {
	device_release(industrial_analog_out->p);
}

int industrial_analog_out_get_response_expected(IndustrialAnalogOut *industrial_analog_out, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(industrial_analog_out->p, function_id, ret_response_expected);
}

int industrial_analog_out_set_response_expected(IndustrialAnalogOut *industrial_analog_out, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(industrial_analog_out->p, function_id, response_expected);
}

int industrial_analog_out_set_response_expected_all(IndustrialAnalogOut *industrial_analog_out, bool response_expected) {
	return device_set_response_expected_all(industrial_analog_out->p, response_expected);
}

void industrial_analog_out_register_callback(IndustrialAnalogOut *industrial_analog_out, uint8_t id, void *callback, void *user_data) {
	device_register_callback(industrial_analog_out->p, id, callback, user_data);
}

int industrial_analog_out_get_api_version(IndustrialAnalogOut *industrial_analog_out, uint8_t ret_api_version[3]) {
	return device_get_api_version(industrial_analog_out->p, ret_api_version);
}

int industrial_analog_out_enable(IndustrialAnalogOut *industrial_analog_out) {
	DevicePrivate *device_p = industrial_analog_out->p;
	Enable_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_analog_out_disable(IndustrialAnalogOut *industrial_analog_out) {
	DevicePrivate *device_p = industrial_analog_out->p;
	Disable_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_DISABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_analog_out_is_enabled(IndustrialAnalogOut *industrial_analog_out, bool *ret_enabled) {
	DevicePrivate *device_p = industrial_analog_out->p;
	IsEnabled_ request;
	IsEnabledResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_IS_ENABLED, device_p->ipcon_p, device_p);

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

int industrial_analog_out_set_voltage(IndustrialAnalogOut *industrial_analog_out, uint16_t voltage) {
	DevicePrivate *device_p = industrial_analog_out->p;
	SetVoltage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage = leconvert_uint16_to(voltage);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_analog_out_get_voltage(IndustrialAnalogOut *industrial_analog_out, uint16_t *ret_voltage) {
	DevicePrivate *device_p = industrial_analog_out->p;
	GetVoltage_ request;
	GetVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_VOLTAGE, device_p->ipcon_p, device_p);

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

int industrial_analog_out_set_current(IndustrialAnalogOut *industrial_analog_out, uint16_t current) {
	DevicePrivate *device_p = industrial_analog_out->p;
	SetCurrent_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.current = leconvert_uint16_to(current);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_analog_out_get_current(IndustrialAnalogOut *industrial_analog_out, uint16_t *ret_current) {
	DevicePrivate *device_p = industrial_analog_out->p;
	GetCurrent_ request;
	GetCurrentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_current = leconvert_uint16_from(response.current);



	return ret;
}

int industrial_analog_out_set_configuration(IndustrialAnalogOut *industrial_analog_out, uint8_t voltage_range, uint8_t current_range) {
	DevicePrivate *device_p = industrial_analog_out->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage_range = voltage_range;
	request.current_range = current_range;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_analog_out_get_configuration(IndustrialAnalogOut *industrial_analog_out, uint8_t *ret_voltage_range, uint8_t *ret_current_range) {
	DevicePrivate *device_p = industrial_analog_out->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_voltage_range = response.voltage_range;
	*ret_current_range = response.current_range;



	return ret;
}

int industrial_analog_out_get_identity(IndustrialAnalogOut *industrial_analog_out, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = industrial_analog_out->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

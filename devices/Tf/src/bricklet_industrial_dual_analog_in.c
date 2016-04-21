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

#include "bricklet_industrial_dual_analog_in.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*VoltageCallbackFunction)(uint8_t, int32_t, void *);

typedef void (*VoltageReachedCallbackFunction)(uint8_t, int32_t, void *);

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
	uint8_t channel;
} ATTRIBUTE_PACKED GetVoltage_;

typedef struct {
	PacketHeader header;
	int32_t voltage;
} ATTRIBUTE_PACKED GetVoltageResponse_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint32_t period;
} ATTRIBUTE_PACKED SetVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetVoltageCallbackThresholdResponse_;

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
	uint8_t rate;
} ATTRIBUTE_PACKED SetSampleRate_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSampleRate_;

typedef struct {
	PacketHeader header;
	uint8_t rate;
} ATTRIBUTE_PACKED GetSampleRateResponse_;

typedef struct {
	PacketHeader header;
	int32_t offset[2];
	int32_t gain[2];
} ATTRIBUTE_PACKED SetCalibration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCalibration_;

typedef struct {
	PacketHeader header;
	int32_t offset[2];
	int32_t gain[2];
} ATTRIBUTE_PACKED GetCalibrationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetADCValues_;

typedef struct {
	PacketHeader header;
	int32_t value[2];
} ATTRIBUTE_PACKED GetADCValuesResponse_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	int32_t voltage;
} ATTRIBUTE_PACKED VoltageCallback_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	int32_t voltage;
} ATTRIBUTE_PACKED VoltageReachedCallback_;

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

static void industrial_dual_analog_in_callback_wrapper_voltage(DevicePrivate *device_p, Packet *packet) {
	VoltageCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE];
	VoltageCallback_ *callback = (VoltageCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_int32_from(callback->voltage);

	callback_function(callback->channel, callback->voltage, user_data);
}

static void industrial_dual_analog_in_callback_wrapper_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	VoltageReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED];
	VoltageReachedCallback_ *callback = (VoltageReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_int32_from(callback->voltage);

	callback_function(callback->channel, callback->voltage, user_data);
}

void industrial_dual_analog_in_create(IndustrialDualAnalogIn *industrial_dual_analog_in, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(industrial_dual_analog_in, uid, ipcon->p, 2, 0, 0);

	device_p = industrial_dual_analog_in->p;

	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_SAMPLE_RATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_SAMPLE_RATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_ADC_VALUES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE] = industrial_dual_analog_in_callback_wrapper_voltage;
	device_p->callback_wrappers[INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED] = industrial_dual_analog_in_callback_wrapper_voltage_reached;
}

void industrial_dual_analog_in_destroy(IndustrialDualAnalogIn *industrial_dual_analog_in) {
	device_release(industrial_dual_analog_in->p);
}

int industrial_dual_analog_in_get_response_expected(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(industrial_dual_analog_in->p, function_id, ret_response_expected);
}

int industrial_dual_analog_in_set_response_expected(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(industrial_dual_analog_in->p, function_id, response_expected);
}

int industrial_dual_analog_in_set_response_expected_all(IndustrialDualAnalogIn *industrial_dual_analog_in, bool response_expected) {
	return device_set_response_expected_all(industrial_dual_analog_in->p, response_expected);
}

void industrial_dual_analog_in_register_callback(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t id, void *callback, void *user_data) {
	device_register_callback(industrial_dual_analog_in->p, id, callback, user_data);
}

int industrial_dual_analog_in_get_api_version(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t ret_api_version[3]) {
	return device_get_api_version(industrial_dual_analog_in->p, ret_api_version);
}

int industrial_dual_analog_in_get_voltage(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, int32_t *ret_voltage) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetVoltage_ request;
	GetVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_voltage = leconvert_int32_from(response.voltage);



	return ret;
}

int industrial_dual_analog_in_set_voltage_callback_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, uint32_t period) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	SetVoltageCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_dual_analog_in_get_voltage_callback_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, uint32_t *ret_period) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetVoltageCallbackPeriod_ request;
	GetVoltageCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int industrial_dual_analog_in_set_voltage_callback_threshold(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	SetVoltageCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_dual_analog_in_get_voltage_callback_threshold(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetVoltageCallbackThreshold_ request;
	GetVoltageCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);



	return ret;
}

int industrial_dual_analog_in_set_debounce_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint32_t debounce) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_dual_analog_in_get_debounce_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint32_t *ret_debounce) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int industrial_dual_analog_in_set_sample_rate(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t rate) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	SetSampleRate_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_SAMPLE_RATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.rate = rate;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_dual_analog_in_get_sample_rate(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t *ret_rate) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetSampleRate_ request;
	GetSampleRateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_SAMPLE_RATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_rate = response.rate;



	return ret;
}

int industrial_dual_analog_in_set_calibration(IndustrialDualAnalogIn *industrial_dual_analog_in, int32_t offset[2], int32_t gain[2]) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	SetCalibration_ request;
	int ret;
	int i;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 2; i++) request.offset[i] = leconvert_int32_to(offset[i]);
	for (i = 0; i < 2; i++) request.gain[i] = leconvert_int32_to(gain[i]);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int industrial_dual_analog_in_get_calibration(IndustrialDualAnalogIn *industrial_dual_analog_in, int32_t ret_offset[2], int32_t ret_gain[2]) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetCalibration_ request;
	GetCalibrationResponse_ response;
	int ret;
	int i;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	for (i = 0; i < 2; i++) ret_offset[i] = leconvert_int32_from(response.offset[i]);
	for (i = 0; i < 2; i++) ret_gain[i] = leconvert_int32_from(response.gain[i]);



	return ret;
}

int industrial_dual_analog_in_get_adc_values(IndustrialDualAnalogIn *industrial_dual_analog_in, int32_t ret_value[2]) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetADCValues_ request;
	GetADCValuesResponse_ response;
	int ret;
	int i;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_ADC_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	for (i = 0; i < 2; i++) ret_value[i] = leconvert_int32_from(response.value[i]);



	return ret;
}

int industrial_dual_analog_in_get_identity(IndustrialDualAnalogIn *industrial_dual_analog_in, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = industrial_dual_analog_in->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

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

#include "bricklet_voltage_current.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*CurrentCallbackFunction)(int32_t, void *);

typedef void (*VoltageCallbackFunction)(int32_t, void *);

typedef void (*PowerCallbackFunction)(int32_t, void *);

typedef void (*CurrentReachedCallbackFunction)(int32_t, void *);

typedef void (*VoltageReachedCallbackFunction)(int32_t, void *);

typedef void (*PowerReachedCallbackFunction)(int32_t, void *);

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
} ATTRIBUTE_PACKED GetCurrent_;

typedef struct {
	PacketHeader header;
	int32_t current;
} ATTRIBUTE_PACKED GetCurrentResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltage_;

typedef struct {
	PacketHeader header;
	int32_t voltage;
} ATTRIBUTE_PACKED GetVoltageResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPower_;

typedef struct {
	PacketHeader header;
	int32_t power;
} ATTRIBUTE_PACKED GetPowerResponse_;

typedef struct {
	PacketHeader header;
	uint8_t averaging;
	uint8_t voltage_conversion_time;
	uint8_t current_conversion_time;
} ATTRIBUTE_PACKED SetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t averaging;
	uint8_t voltage_conversion_time;
	uint8_t current_conversion_time;
} ATTRIBUTE_PACKED GetConfigurationResponse_;

typedef struct {
	PacketHeader header;
	uint16_t gain_multiplier;
	uint16_t gain_divisor;
} ATTRIBUTE_PACKED SetCalibration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCalibration_;

typedef struct {
	PacketHeader header;
	uint16_t gain_multiplier;
	uint16_t gain_divisor;
} ATTRIBUTE_PACKED GetCalibrationResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetCurrentCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCurrentCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetPowerCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPowerCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetPowerCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetCurrentCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetCurrentCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetVoltageCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetPowerCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPowerCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetPowerCallbackThresholdResponse_;

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
	int32_t current;
} ATTRIBUTE_PACKED CurrentCallback_;

typedef struct {
	PacketHeader header;
	int32_t voltage;
} ATTRIBUTE_PACKED VoltageCallback_;

typedef struct {
	PacketHeader header;
	int32_t power;
} ATTRIBUTE_PACKED PowerCallback_;

typedef struct {
	PacketHeader header;
	int32_t current;
} ATTRIBUTE_PACKED CurrentReachedCallback_;

typedef struct {
	PacketHeader header;
	int32_t voltage;
} ATTRIBUTE_PACKED VoltageReachedCallback_;

typedef struct {
	PacketHeader header;
	int32_t power;
} ATTRIBUTE_PACKED PowerReachedCallback_;

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

static void voltage_current_callback_wrapper_current(DevicePrivate *device_p, Packet *packet) {
	CurrentCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[VOLTAGE_CURRENT_CALLBACK_CURRENT];
	CurrentCallback_ *callback = (CurrentCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[VOLTAGE_CURRENT_CALLBACK_CURRENT];

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int32_from(callback->current);

	callback_function(callback->current, user_data);
}

static void voltage_current_callback_wrapper_voltage(DevicePrivate *device_p, Packet *packet) {
	VoltageCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[VOLTAGE_CURRENT_CALLBACK_VOLTAGE];
	VoltageCallback_ *callback = (VoltageCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[VOLTAGE_CURRENT_CALLBACK_VOLTAGE];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_int32_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void voltage_current_callback_wrapper_power(DevicePrivate *device_p, Packet *packet) {
	PowerCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[VOLTAGE_CURRENT_CALLBACK_POWER];
	PowerCallback_ *callback = (PowerCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[VOLTAGE_CURRENT_CALLBACK_POWER];

	if (callback_function == NULL) {
		return;
	}

	callback->power = leconvert_int32_from(callback->power);

	callback_function(callback->power, user_data);
}

static void voltage_current_callback_wrapper_current_reached(DevicePrivate *device_p, Packet *packet) {
	CurrentReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED];
	CurrentReachedCallback_ *callback = (CurrentReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int32_from(callback->current);

	callback_function(callback->current, user_data);
}

static void voltage_current_callback_wrapper_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	VoltageReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED];
	VoltageReachedCallback_ *callback = (VoltageReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_int32_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void voltage_current_callback_wrapper_power_reached(DevicePrivate *device_p, Packet *packet) {
	PowerReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[VOLTAGE_CURRENT_CALLBACK_POWER_REACHED];
	PowerReachedCallback_ *callback = (PowerReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[VOLTAGE_CURRENT_CALLBACK_POWER_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->power = leconvert_int32_from(callback->power);

	callback_function(callback->power, user_data);
}

void voltage_current_create(VoltageCurrent *voltage_current, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(voltage_current, uid, ipcon->p, 2, 0, 0);

	device_p = voltage_current->p;

	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_POWER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_POWER_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_POWER_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_POWER_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_POWER_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_CALLBACK_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_CALLBACK_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_CALLBACK_POWER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_CALLBACK_POWER_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[VOLTAGE_CURRENT_CALLBACK_CURRENT] = voltage_current_callback_wrapper_current;
	device_p->callback_wrappers[VOLTAGE_CURRENT_CALLBACK_VOLTAGE] = voltage_current_callback_wrapper_voltage;
	device_p->callback_wrappers[VOLTAGE_CURRENT_CALLBACK_POWER] = voltage_current_callback_wrapper_power;
	device_p->callback_wrappers[VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED] = voltage_current_callback_wrapper_current_reached;
	device_p->callback_wrappers[VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED] = voltage_current_callback_wrapper_voltage_reached;
	device_p->callback_wrappers[VOLTAGE_CURRENT_CALLBACK_POWER_REACHED] = voltage_current_callback_wrapper_power_reached;
}

void voltage_current_destroy(VoltageCurrent *voltage_current) {
	device_release(voltage_current->p);
}

int voltage_current_get_response_expected(VoltageCurrent *voltage_current, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(voltage_current->p, function_id, ret_response_expected);
}

int voltage_current_set_response_expected(VoltageCurrent *voltage_current, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(voltage_current->p, function_id, response_expected);
}

int voltage_current_set_response_expected_all(VoltageCurrent *voltage_current, bool response_expected) {
	return device_set_response_expected_all(voltage_current->p, response_expected);
}

void voltage_current_register_callback(VoltageCurrent *voltage_current, uint8_t id, void *callback, void *user_data) {
	device_register_callback(voltage_current->p, id, callback, user_data);
}

int voltage_current_get_api_version(VoltageCurrent *voltage_current, uint8_t ret_api_version[3]) {
	return device_get_api_version(voltage_current->p, ret_api_version);
}

int voltage_current_get_current(VoltageCurrent *voltage_current, int32_t *ret_current) {
	DevicePrivate *device_p = voltage_current->p;
	GetCurrent_ request;
	GetCurrentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_current = leconvert_int32_from(response.current);



	return ret;
}

int voltage_current_get_voltage(VoltageCurrent *voltage_current, int32_t *ret_voltage) {
	DevicePrivate *device_p = voltage_current->p;
	GetVoltage_ request;
	GetVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_voltage = leconvert_int32_from(response.voltage);



	return ret;
}

int voltage_current_get_power(VoltageCurrent *voltage_current, int32_t *ret_power) {
	DevicePrivate *device_p = voltage_current->p;
	GetPower_ request;
	GetPowerResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_POWER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_power = leconvert_int32_from(response.power);



	return ret;
}

int voltage_current_set_configuration(VoltageCurrent *voltage_current, uint8_t averaging, uint8_t voltage_conversion_time, uint8_t current_conversion_time) {
	DevicePrivate *device_p = voltage_current->p;
	SetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.averaging = averaging;
	request.voltage_conversion_time = voltage_conversion_time;
	request.current_conversion_time = current_conversion_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_configuration(VoltageCurrent *voltage_current, uint8_t *ret_averaging, uint8_t *ret_voltage_conversion_time, uint8_t *ret_current_conversion_time) {
	DevicePrivate *device_p = voltage_current->p;
	GetConfiguration_ request;
	GetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_averaging = response.averaging;
	*ret_voltage_conversion_time = response.voltage_conversion_time;
	*ret_current_conversion_time = response.current_conversion_time;



	return ret;
}

int voltage_current_set_calibration(VoltageCurrent *voltage_current, uint16_t gain_multiplier, uint16_t gain_divisor) {
	DevicePrivate *device_p = voltage_current->p;
	SetCalibration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.gain_multiplier = leconvert_uint16_to(gain_multiplier);
	request.gain_divisor = leconvert_uint16_to(gain_divisor);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_calibration(VoltageCurrent *voltage_current, uint16_t *ret_gain_multiplier, uint16_t *ret_gain_divisor) {
	DevicePrivate *device_p = voltage_current->p;
	GetCalibration_ request;
	GetCalibrationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_gain_multiplier = leconvert_uint16_from(response.gain_multiplier);
	*ret_gain_divisor = leconvert_uint16_from(response.gain_divisor);



	return ret;
}

int voltage_current_set_current_callback_period(VoltageCurrent *voltage_current, uint32_t period) {
	DevicePrivate *device_p = voltage_current->p;
	SetCurrentCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_current_callback_period(VoltageCurrent *voltage_current, uint32_t *ret_period) {
	DevicePrivate *device_p = voltage_current->p;
	GetCurrentCallbackPeriod_ request;
	GetCurrentCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int voltage_current_set_voltage_callback_period(VoltageCurrent *voltage_current, uint32_t period) {
	DevicePrivate *device_p = voltage_current->p;
	SetVoltageCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_voltage_callback_period(VoltageCurrent *voltage_current, uint32_t *ret_period) {
	DevicePrivate *device_p = voltage_current->p;
	GetVoltageCallbackPeriod_ request;
	GetVoltageCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int voltage_current_set_power_callback_period(VoltageCurrent *voltage_current, uint32_t period) {
	DevicePrivate *device_p = voltage_current->p;
	SetPowerCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_POWER_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_power_callback_period(VoltageCurrent *voltage_current, uint32_t *ret_period) {
	DevicePrivate *device_p = voltage_current->p;
	GetPowerCallbackPeriod_ request;
	GetPowerCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_POWER_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int voltage_current_set_current_callback_threshold(VoltageCurrent *voltage_current, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = voltage_current->p;
	SetCurrentCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_current_callback_threshold(VoltageCurrent *voltage_current, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = voltage_current->p;
	GetCurrentCallbackThreshold_ request;
	GetCurrentCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);



	return ret;
}

int voltage_current_set_voltage_callback_threshold(VoltageCurrent *voltage_current, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = voltage_current->p;
	SetVoltageCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_voltage_callback_threshold(VoltageCurrent *voltage_current, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = voltage_current->p;
	GetVoltageCallbackThreshold_ request;
	GetVoltageCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);



	return ret;
}

int voltage_current_set_power_callback_threshold(VoltageCurrent *voltage_current, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = voltage_current->p;
	SetPowerCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_POWER_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_power_callback_threshold(VoltageCurrent *voltage_current, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = voltage_current->p;
	GetPowerCallbackThreshold_ request;
	GetPowerCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_POWER_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);



	return ret;
}

int voltage_current_set_debounce_period(VoltageCurrent *voltage_current, uint32_t debounce) {
	DevicePrivate *device_p = voltage_current->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int voltage_current_get_debounce_period(VoltageCurrent *voltage_current, uint32_t *ret_debounce) {
	DevicePrivate *device_p = voltage_current->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int voltage_current_get_identity(VoltageCurrent *voltage_current, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = voltage_current->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

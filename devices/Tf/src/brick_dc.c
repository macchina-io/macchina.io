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

#include "brick_dc.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*UnderVoltageCallbackFunction)(uint16_t, void *);

typedef void (*EmergencyShutdownCallbackFunction)(void *);

typedef void (*VelocityReachedCallbackFunction)(int16_t, void *);

typedef void (*CurrentVelocityCallbackFunction)(int16_t, void *);

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
	int16_t velocity;
} ATTRIBUTE_PACKED SetVelocity_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocity_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED GetVelocityResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentVelocity_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED GetCurrentVelocityResponse_;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
} ATTRIBUTE_PACKED SetAcceleration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAcceleration_;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
} ATTRIBUTE_PACKED GetAccelerationResponse_;

typedef struct {
	PacketHeader header;
	uint16_t frequency;
} ATTRIBUTE_PACKED SetPWMFrequency_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPWMFrequency_;

typedef struct {
	PacketHeader header;
	uint16_t frequency;
} ATTRIBUTE_PACKED GetPWMFrequencyResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED FullBrake_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackInputVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetStackInputVoltageResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetExternalInputVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetExternalInputVoltageResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentConsumption_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetCurrentConsumptionResponse_;

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
} ATTRIBUTE_PACKED SetMinimumVoltage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMinimumVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetMinimumVoltageResponse_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetDriveMode_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDriveMode_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetDriveModeResponse_;

typedef struct {
	PacketHeader header;
	uint16_t period;
} ATTRIBUTE_PACKED SetCurrentVelocityPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentVelocityPeriod_;

typedef struct {
	PacketHeader header;
	uint16_t period;
} ATTRIBUTE_PACKED GetCurrentVelocityPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED UnderVoltageCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EmergencyShutdownCallback_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED VelocityReachedCallback_;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED CurrentVelocityCallback_;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetProtocol1BrickletName_;

typedef struct {
	PacketHeader header;
	uint8_t protocol_version;
	uint8_t firmware_version[3];
	char name[40];
} ATTRIBUTE_PACKED GetProtocol1BrickletNameResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperatureResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Reset_;

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

static void dc_callback_wrapper_under_voltage(DevicePrivate *device_p, Packet *packet) {
	UnderVoltageCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DC_CALLBACK_UNDER_VOLTAGE];
	UnderVoltageCallback_ *callback = (UnderVoltageCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DC_CALLBACK_UNDER_VOLTAGE];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void dc_callback_wrapper_emergency_shutdown(DevicePrivate *device_p, Packet *packet) {
	EmergencyShutdownCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DC_CALLBACK_EMERGENCY_SHUTDOWN];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DC_CALLBACK_EMERGENCY_SHUTDOWN];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void dc_callback_wrapper_velocity_reached(DevicePrivate *device_p, Packet *packet) {
	VelocityReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DC_CALLBACK_VELOCITY_REACHED];
	VelocityReachedCallback_ *callback = (VelocityReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DC_CALLBACK_VELOCITY_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

static void dc_callback_wrapper_current_velocity(DevicePrivate *device_p, Packet *packet) {
	CurrentVelocityCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DC_CALLBACK_CURRENT_VELOCITY];
	CurrentVelocityCallback_ *callback = (CurrentVelocityCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[DC_CALLBACK_CURRENT_VELOCITY];

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

void dc_create(DC *dc, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(dc, uid, ipcon->p, 2, 0, 0);

	device_p = dc->p;

	device_p->response_expected[DC_FUNCTION_SET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_GET_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_SET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_SET_PWM_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_PWM_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_FULL_BRAKE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_STACK_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_GET_EXTERNAL_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_GET_CURRENT_CONSUMPTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_ENABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_DISABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_IS_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_SET_MINIMUM_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DC_FUNCTION_GET_MINIMUM_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_SET_DRIVE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_DRIVE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_SET_CURRENT_VELOCITY_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DC_FUNCTION_GET_CURRENT_VELOCITY_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_CALLBACK_UNDER_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DC_CALLBACK_EMERGENCY_SHUTDOWN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DC_CALLBACK_VELOCITY_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DC_CALLBACK_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DC_CALLBACK_UNDER_VOLTAGE] = dc_callback_wrapper_under_voltage;
	device_p->callback_wrappers[DC_CALLBACK_EMERGENCY_SHUTDOWN] = dc_callback_wrapper_emergency_shutdown;
	device_p->callback_wrappers[DC_CALLBACK_VELOCITY_REACHED] = dc_callback_wrapper_velocity_reached;
	device_p->callback_wrappers[DC_CALLBACK_CURRENT_VELOCITY] = dc_callback_wrapper_current_velocity;
}

void dc_destroy(DC *dc) {
	device_release(dc->p);
}

int dc_get_response_expected(DC *dc, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dc->p, function_id, ret_response_expected);
}

int dc_set_response_expected(DC *dc, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dc->p, function_id, response_expected);
}

int dc_set_response_expected_all(DC *dc, bool response_expected) {
	return device_set_response_expected_all(dc->p, response_expected);
}

void dc_register_callback(DC *dc, uint8_t id, void *callback, void *user_data) {
	device_register_callback(dc->p, id, callback, user_data);
}

int dc_get_api_version(DC *dc, uint8_t ret_api_version[3]) {
	return device_get_api_version(dc->p, ret_api_version);
}

int dc_set_velocity(DC *dc, int16_t velocity) {
	DevicePrivate *device_p = dc->p;
	SetVelocity_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_SET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.velocity = leconvert_int16_to(velocity);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_velocity(DC *dc, int16_t *ret_velocity) {
	DevicePrivate *device_p = dc->p;
	GetVelocity_ request;
	GetVelocityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_velocity = leconvert_int16_from(response.velocity);



	return ret;
}

int dc_get_current_velocity(DC *dc, int16_t *ret_velocity) {
	DevicePrivate *device_p = dc->p;
	GetCurrentVelocity_ request;
	GetCurrentVelocityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_CURRENT_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_velocity = leconvert_int16_from(response.velocity);



	return ret;
}

int dc_set_acceleration(DC *dc, uint16_t acceleration) {
	DevicePrivate *device_p = dc->p;
	SetAcceleration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_SET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.acceleration = leconvert_uint16_to(acceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_acceleration(DC *dc, uint16_t *ret_acceleration) {
	DevicePrivate *device_p = dc->p;
	GetAcceleration_ request;
	GetAccelerationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_acceleration = leconvert_uint16_from(response.acceleration);



	return ret;
}

int dc_set_pwm_frequency(DC *dc, uint16_t frequency) {
	DevicePrivate *device_p = dc->p;
	SetPWMFrequency_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_SET_PWM_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = leconvert_uint16_to(frequency);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_pwm_frequency(DC *dc, uint16_t *ret_frequency) {
	DevicePrivate *device_p = dc->p;
	GetPWMFrequency_ request;
	GetPWMFrequencyResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_PWM_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_frequency = leconvert_uint16_from(response.frequency);



	return ret;
}

int dc_full_brake(DC *dc) {
	DevicePrivate *device_p = dc->p;
	FullBrake_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_FULL_BRAKE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_stack_input_voltage(DC *dc, uint16_t *ret_voltage) {
	DevicePrivate *device_p = dc->p;
	GetStackInputVoltage_ request;
	GetStackInputVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_STACK_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int dc_get_external_input_voltage(DC *dc, uint16_t *ret_voltage) {
	DevicePrivate *device_p = dc->p;
	GetExternalInputVoltage_ request;
	GetExternalInputVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_EXTERNAL_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int dc_get_current_consumption(DC *dc, uint16_t *ret_voltage) {
	DevicePrivate *device_p = dc->p;
	GetCurrentConsumption_ request;
	GetCurrentConsumptionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_CURRENT_CONSUMPTION, device_p->ipcon_p, device_p);

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

int dc_enable(DC *dc) {
	DevicePrivate *device_p = dc->p;
	Enable_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_disable(DC *dc) {
	DevicePrivate *device_p = dc->p;
	Disable_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_DISABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_is_enabled(DC *dc, bool *ret_enabled) {
	DevicePrivate *device_p = dc->p;
	IsEnabled_ request;
	IsEnabledResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_IS_ENABLED, device_p->ipcon_p, device_p);

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

int dc_set_minimum_voltage(DC *dc, uint16_t voltage) {
	DevicePrivate *device_p = dc->p;
	SetMinimumVoltage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_SET_MINIMUM_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage = leconvert_uint16_to(voltage);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_minimum_voltage(DC *dc, uint16_t *ret_voltage) {
	DevicePrivate *device_p = dc->p;
	GetMinimumVoltage_ request;
	GetMinimumVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_MINIMUM_VOLTAGE, device_p->ipcon_p, device_p);

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

int dc_set_drive_mode(DC *dc, uint8_t mode) {
	DevicePrivate *device_p = dc->p;
	SetDriveMode_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_SET_DRIVE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_drive_mode(DC *dc, uint8_t *ret_mode) {
	DevicePrivate *device_p = dc->p;
	GetDriveMode_ request;
	GetDriveModeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_DRIVE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_mode = response.mode;



	return ret;
}

int dc_set_current_velocity_period(DC *dc, uint16_t period) {
	DevicePrivate *device_p = dc->p;
	SetCurrentVelocityPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_SET_CURRENT_VELOCITY_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint16_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_current_velocity_period(DC *dc, uint16_t *ret_period) {
	DevicePrivate *device_p = dc->p;
	GetCurrentVelocityPeriod_ request;
	GetCurrentVelocityPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_CURRENT_VELOCITY_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint16_from(response.period);



	return ret;
}

int dc_get_protocol1_bricklet_name(DC *dc, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]) {
	DevicePrivate *device_p = dc->p;
	GetProtocol1BrickletName_ request;
	GetProtocol1BrickletNameResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_protocol_version = response.protocol_version;
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	strncpy(ret_name, response.name, 40);



	return ret;
}

int dc_get_chip_temperature(DC *dc, int16_t *ret_temperature) {
	DevicePrivate *device_p = dc->p;
	GetChipTemperature_ request;
	GetChipTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_temperature = leconvert_int16_from(response.temperature);



	return ret;
}

int dc_reset(DC *dc) {
	DevicePrivate *device_p = dc->p;
	Reset_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int dc_get_identity(DC *dc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dc->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

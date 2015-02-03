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

#include "bricklet_barometer.h"

#include <string.h>



typedef void (*AirPressureCallbackFunction)(int32_t, void *);

typedef void (*AltitudeCallbackFunction)(int32_t, void *);

typedef void (*AirPressureReachedCallbackFunction)(int32_t, void *);

typedef void (*AltitudeReachedCallbackFunction)(int32_t, void *);

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
} ATTRIBUTE_PACKED GetAirPressure_;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED GetAirPressureResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitude_;

typedef struct {
	PacketHeader header;
	int32_t altitude;
} ATTRIBUTE_PACKED GetAltitudeResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAirPressureCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressureCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAirPressureCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAltitudeCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitudeCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAltitudeCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetAirPressureCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressureCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetAirPressureCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetAltitudeCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitudeCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetAltitudeCallbackThresholdResponse_;

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
	int32_t air_pressure;
} ATTRIBUTE_PACKED SetReferenceAirPressure_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperatureResponse_;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED AirPressureCallback_;

typedef struct {
	PacketHeader header;
	int32_t altitude;
} ATTRIBUTE_PACKED AltitudeCallback_;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED AirPressureReachedCallback_;

typedef struct {
	PacketHeader header;
	int32_t altitude;
} ATTRIBUTE_PACKED AltitudeReachedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReferenceAirPressure_;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED GetReferenceAirPressureResponse_;

typedef struct {
	PacketHeader header;
	uint8_t moving_average_pressure;
	uint8_t average_pressure;
	uint8_t average_temperature;
} ATTRIBUTE_PACKED SetAveraging_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAveraging_;

typedef struct {
	PacketHeader header;
	uint8_t moving_average_pressure;
	uint8_t average_pressure;
	uint8_t average_temperature;
} ATTRIBUTE_PACKED GetAveragingResponse_;

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

static void barometer_callback_wrapper_air_pressure(DevicePrivate *device_p, Packet *packet) {
	AirPressureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[BAROMETER_CALLBACK_AIR_PRESSURE];
	AirPressureCallback_ *callback = (AirPressureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[BAROMETER_CALLBACK_AIR_PRESSURE];

	if (callback_function == NULL) {
		return;
	}

	callback->air_pressure = leconvert_int32_from(callback->air_pressure);

	callback_function(callback->air_pressure, user_data);
}

static void barometer_callback_wrapper_altitude(DevicePrivate *device_p, Packet *packet) {
	AltitudeCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[BAROMETER_CALLBACK_ALTITUDE];
	AltitudeCallback_ *callback = (AltitudeCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[BAROMETER_CALLBACK_ALTITUDE];

	if (callback_function == NULL) {
		return;
	}

	callback->altitude = leconvert_int32_from(callback->altitude);

	callback_function(callback->altitude, user_data);
}

static void barometer_callback_wrapper_air_pressure_reached(DevicePrivate *device_p, Packet *packet) {
	AirPressureReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[BAROMETER_CALLBACK_AIR_PRESSURE_REACHED];
	AirPressureReachedCallback_ *callback = (AirPressureReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[BAROMETER_CALLBACK_AIR_PRESSURE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->air_pressure = leconvert_int32_from(callback->air_pressure);

	callback_function(callback->air_pressure, user_data);
}

static void barometer_callback_wrapper_altitude_reached(DevicePrivate *device_p, Packet *packet) {
	AltitudeReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[BAROMETER_CALLBACK_ALTITUDE_REACHED];
	AltitudeReachedCallback_ *callback = (AltitudeReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[BAROMETER_CALLBACK_ALTITUDE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->altitude = leconvert_int32_from(callback->altitude);

	callback_function(callback->altitude, user_data);
}

void barometer_create(Barometer *barometer, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(barometer, uid, ipcon->p, 2, 0, 1);

	device_p = barometer->p;

	device_p->response_expected[BAROMETER_FUNCTION_GET_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_ALTITUDE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_REFERENCE_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_CALLBACK_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[BAROMETER_CALLBACK_ALTITUDE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[BAROMETER_CALLBACK_AIR_PRESSURE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[BAROMETER_CALLBACK_ALTITUDE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_REFERENCE_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_AVERAGING] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_AVERAGING] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[BAROMETER_CALLBACK_AIR_PRESSURE] = barometer_callback_wrapper_air_pressure;
	device_p->callback_wrappers[BAROMETER_CALLBACK_ALTITUDE] = barometer_callback_wrapper_altitude;
	device_p->callback_wrappers[BAROMETER_CALLBACK_AIR_PRESSURE_REACHED] = barometer_callback_wrapper_air_pressure_reached;
	device_p->callback_wrappers[BAROMETER_CALLBACK_ALTITUDE_REACHED] = barometer_callback_wrapper_altitude_reached;
}

void barometer_destroy(Barometer *barometer) {
	device_destroy(barometer);
}

int barometer_get_response_expected(Barometer *barometer, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(barometer->p, function_id, ret_response_expected);
}

int barometer_set_response_expected(Barometer *barometer, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(barometer->p, function_id, response_expected);
}

int barometer_set_response_expected_all(Barometer *barometer, bool response_expected) {
	return device_set_response_expected_all(barometer->p, response_expected);
}

void barometer_register_callback(Barometer *barometer, uint8_t id, void *callback, void *user_data) {
	device_register_callback(barometer->p, id, callback, user_data);
}

int barometer_get_api_version(Barometer *barometer, uint8_t ret_api_version[3]) {
	return device_get_api_version(barometer->p, ret_api_version);
}

int barometer_get_air_pressure(Barometer *barometer, int32_t *ret_air_pressure) {
	DevicePrivate *device_p = barometer->p;
	GetAirPressure_ request;
	GetAirPressureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_air_pressure = leconvert_int32_from(response.air_pressure);



	return ret;
}

int barometer_get_altitude(Barometer *barometer, int32_t *ret_altitude) {
	DevicePrivate *device_p = barometer->p;
	GetAltitude_ request;
	GetAltitudeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_ALTITUDE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_altitude = leconvert_int32_from(response.altitude);



	return ret;
}

int barometer_set_air_pressure_callback_period(Barometer *barometer, uint32_t period) {
	DevicePrivate *device_p = barometer->p;
	SetAirPressureCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_air_pressure_callback_period(Barometer *barometer, uint32_t *ret_period) {
	DevicePrivate *device_p = barometer->p;
	GetAirPressureCallbackPeriod_ request;
	GetAirPressureCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int barometer_set_altitude_callback_period(Barometer *barometer, uint32_t period) {
	DevicePrivate *device_p = barometer->p;
	SetAltitudeCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_altitude_callback_period(Barometer *barometer, uint32_t *ret_period) {
	DevicePrivate *device_p = barometer->p;
	GetAltitudeCallbackPeriod_ request;
	GetAltitudeCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int barometer_set_air_pressure_callback_threshold(Barometer *barometer, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = barometer->p;
	SetAirPressureCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_air_pressure_callback_threshold(Barometer *barometer, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = barometer->p;
	GetAirPressureCallbackThreshold_ request;
	GetAirPressureCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int barometer_set_altitude_callback_threshold(Barometer *barometer, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = barometer->p;
	SetAltitudeCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_altitude_callback_threshold(Barometer *barometer, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = barometer->p;
	GetAltitudeCallbackThreshold_ request;
	GetAltitudeCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int barometer_set_debounce_period(Barometer *barometer, uint32_t debounce) {
	DevicePrivate *device_p = barometer->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_debounce_period(Barometer *barometer, uint32_t *ret_debounce) {
	DevicePrivate *device_p = barometer->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int barometer_set_reference_air_pressure(Barometer *barometer, int32_t air_pressure) {
	DevicePrivate *device_p = barometer->p;
	SetReferenceAirPressure_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_REFERENCE_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.air_pressure = leconvert_int32_to(air_pressure);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_chip_temperature(Barometer *barometer, int16_t *ret_temperature) {
	DevicePrivate *device_p = barometer->p;
	GetChipTemperature_ request;
	GetChipTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int barometer_get_reference_air_pressure(Barometer *barometer, int32_t *ret_air_pressure) {
	DevicePrivate *device_p = barometer->p;
	GetReferenceAirPressure_ request;
	GetReferenceAirPressureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_REFERENCE_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_air_pressure = leconvert_int32_from(response.air_pressure);



	return ret;
}

int barometer_set_averaging(Barometer *barometer, uint8_t moving_average_pressure, uint8_t average_pressure, uint8_t average_temperature) {
	DevicePrivate *device_p = barometer->p;
	SetAveraging_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_AVERAGING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.moving_average_pressure = moving_average_pressure;
	request.average_pressure = average_pressure;
	request.average_temperature = average_temperature;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int barometer_get_averaging(Barometer *barometer, uint8_t *ret_moving_average_pressure, uint8_t *ret_average_pressure, uint8_t *ret_average_temperature) {
	DevicePrivate *device_p = barometer->p;
	GetAveraging_ request;
	GetAveragingResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AVERAGING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_moving_average_pressure = response.moving_average_pressure;
	*ret_average_pressure = response.average_pressure;
	*ret_average_temperature = response.average_temperature;



	return ret;
}

int barometer_get_identity(Barometer *barometer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = barometer->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

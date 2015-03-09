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

#include "bricklet_ptc.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*TemperatureCallbackFunction)(int32_t, void *);

typedef void (*TemperatureReachedCallbackFunction)(int32_t, void *);

typedef void (*ResistanceCallbackFunction)(uint16_t, void *);

typedef void (*ResistanceReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetTemperature_;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED GetTemperatureResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistance_;

typedef struct {
	PacketHeader header;
	uint16_t resistance;
} ATTRIBUTE_PACKED GetResistanceResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetTemperatureCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetTemperatureCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetResistanceCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistanceCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetResistanceCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetTemperatureCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetTemperatureCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetResistanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistanceCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetResistanceCallbackThresholdResponse_;

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
	int32_t temperature;
} ATTRIBUTE_PACKED TemperatureCallback_;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED TemperatureReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t resistance;
} ATTRIBUTE_PACKED ResistanceCallback_;

typedef struct {
	PacketHeader header;
	uint16_t resistance;
} ATTRIBUTE_PACKED ResistanceReachedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t filter;
} ATTRIBUTE_PACKED SetNoiseRejectionFilter_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetNoiseRejectionFilter_;

typedef struct {
	PacketHeader header;
	uint8_t filter;
} ATTRIBUTE_PACKED GetNoiseRejectionFilterResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsSensorConnected_;

typedef struct {
	PacketHeader header;
	bool connected;
} ATTRIBUTE_PACKED IsSensorConnectedResponse_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetWireMode_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWireMode_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetWireModeResponse_;

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

static void ptc_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	TemperatureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[PTC_CALLBACK_TEMPERATURE];
	TemperatureCallback_ *callback = (TemperatureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[PTC_CALLBACK_TEMPERATURE];

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void ptc_callback_wrapper_temperature_reached(DevicePrivate *device_p, Packet *packet) {
	TemperatureReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[PTC_CALLBACK_TEMPERATURE_REACHED];
	TemperatureReachedCallback_ *callback = (TemperatureReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[PTC_CALLBACK_TEMPERATURE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void ptc_callback_wrapper_resistance(DevicePrivate *device_p, Packet *packet) {
	ResistanceCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[PTC_CALLBACK_RESISTANCE];
	ResistanceCallback_ *callback = (ResistanceCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[PTC_CALLBACK_RESISTANCE];

	if (callback_function == NULL) {
		return;
	}

	callback->resistance = leconvert_uint16_from(callback->resistance);

	callback_function(callback->resistance, user_data);
}

static void ptc_callback_wrapper_resistance_reached(DevicePrivate *device_p, Packet *packet) {
	ResistanceReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[PTC_CALLBACK_RESISTANCE_REACHED];
	ResistanceReachedCallback_ *callback = (ResistanceReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[PTC_CALLBACK_RESISTANCE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->resistance = leconvert_uint16_from(callback->resistance);

	callback_function(callback->resistance, user_data);
}

void ptc_create(PTC *ptc, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(ptc, uid, ipcon->p, 2, 0, 0);

	device_p = ptc->p;

	device_p->response_expected[PTC_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_RESISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_RESISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_RESISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_RESISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_RESISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_CALLBACK_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[PTC_CALLBACK_TEMPERATURE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[PTC_CALLBACK_RESISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[PTC_CALLBACK_RESISTANCE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[PTC_FUNCTION_SET_NOISE_REJECTION_FILTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_FUNCTION_GET_NOISE_REJECTION_FILTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_IS_SENSOR_CONNECTED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_WIRE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_FUNCTION_GET_WIRE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PTC_CALLBACK_TEMPERATURE] = ptc_callback_wrapper_temperature;
	device_p->callback_wrappers[PTC_CALLBACK_TEMPERATURE_REACHED] = ptc_callback_wrapper_temperature_reached;
	device_p->callback_wrappers[PTC_CALLBACK_RESISTANCE] = ptc_callback_wrapper_resistance;
	device_p->callback_wrappers[PTC_CALLBACK_RESISTANCE_REACHED] = ptc_callback_wrapper_resistance_reached;
}

void ptc_destroy(PTC *ptc) {
	device_release(ptc->p);
}

int ptc_get_response_expected(PTC *ptc, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(ptc->p, function_id, ret_response_expected);
}

int ptc_set_response_expected(PTC *ptc, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(ptc->p, function_id, response_expected);
}

int ptc_set_response_expected_all(PTC *ptc, bool response_expected) {
	return device_set_response_expected_all(ptc->p, response_expected);
}

void ptc_register_callback(PTC *ptc, uint8_t id, void *callback, void *user_data) {
	device_register_callback(ptc->p, id, callback, user_data);
}

int ptc_get_api_version(PTC *ptc, uint8_t ret_api_version[3]) {
	return device_get_api_version(ptc->p, ret_api_version);
}

int ptc_get_temperature(PTC *ptc, int32_t *ret_temperature) {
	DevicePrivate *device_p = ptc->p;
	GetTemperature_ request;
	GetTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_temperature = leconvert_int32_from(response.temperature);



	return ret;
}

int ptc_get_resistance(PTC *ptc, uint16_t *ret_resistance) {
	DevicePrivate *device_p = ptc->p;
	GetResistance_ request;
	GetResistanceResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_RESISTANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_resistance = leconvert_uint16_from(response.resistance);



	return ret;
}

int ptc_set_temperature_callback_period(PTC *ptc, uint32_t period) {
	DevicePrivate *device_p = ptc->p;
	SetTemperatureCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_temperature_callback_period(PTC *ptc, uint32_t *ret_period) {
	DevicePrivate *device_p = ptc->p;
	GetTemperatureCallbackPeriod_ request;
	GetTemperatureCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ptc_set_resistance_callback_period(PTC *ptc, uint32_t period) {
	DevicePrivate *device_p = ptc->p;
	SetResistanceCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_RESISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_resistance_callback_period(PTC *ptc, uint32_t *ret_period) {
	DevicePrivate *device_p = ptc->p;
	GetResistanceCallbackPeriod_ request;
	GetResistanceCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_RESISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ptc_set_temperature_callback_threshold(PTC *ptc, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = ptc->p;
	SetTemperatureCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_temperature_callback_threshold(PTC *ptc, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = ptc->p;
	GetTemperatureCallbackThreshold_ request;
	GetTemperatureCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int ptc_set_resistance_callback_threshold(PTC *ptc, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = ptc->p;
	SetResistanceCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_RESISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_resistance_callback_threshold(PTC *ptc, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = ptc->p;
	GetResistanceCallbackThreshold_ request;
	GetResistanceCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_RESISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);



	return ret;
}

int ptc_set_debounce_period(PTC *ptc, uint32_t debounce) {
	DevicePrivate *device_p = ptc->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_debounce_period(PTC *ptc, uint32_t *ret_debounce) {
	DevicePrivate *device_p = ptc->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int ptc_set_noise_rejection_filter(PTC *ptc, uint8_t filter) {
	DevicePrivate *device_p = ptc->p;
	SetNoiseRejectionFilter_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_NOISE_REJECTION_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.filter = filter;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_noise_rejection_filter(PTC *ptc, uint8_t *ret_filter) {
	DevicePrivate *device_p = ptc->p;
	GetNoiseRejectionFilter_ request;
	GetNoiseRejectionFilterResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_NOISE_REJECTION_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_filter = response.filter;



	return ret;
}

int ptc_is_sensor_connected(PTC *ptc, bool *ret_connected) {
	DevicePrivate *device_p = ptc->p;
	IsSensorConnected_ request;
	IsSensorConnectedResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_IS_SENSOR_CONNECTED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_connected = response.connected;



	return ret;
}

int ptc_set_wire_mode(PTC *ptc, uint8_t mode) {
	DevicePrivate *device_p = ptc->p;
	SetWireMode_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_WIRE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int ptc_get_wire_mode(PTC *ptc, uint8_t *ret_mode) {
	DevicePrivate *device_p = ptc->p;
	GetWireMode_ request;
	GetWireModeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_WIRE_MODE, device_p->ipcon_p, device_p);

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

int ptc_get_identity(PTC *ptc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = ptc->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

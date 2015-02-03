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

#include "bricklet_moisture.h"

#include <string.h>



typedef void (*MoistureCallbackFunction)(uint16_t, void *);

typedef void (*MoistureReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetMoistureValue_;

typedef struct {
	PacketHeader header;
	uint16_t moisture;
} ATTRIBUTE_PACKED GetMoistureValueResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetMoistureCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMoistureCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetMoistureCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetMoistureCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMoistureCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetMoistureCallbackThresholdResponse_;

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
	uint16_t moisture;
} ATTRIBUTE_PACKED MoistureCallback_;

typedef struct {
	PacketHeader header;
	uint16_t moisture;
} ATTRIBUTE_PACKED MoistureReachedCallback_;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED SetMovingAverage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMovingAverage_;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED GetMovingAverageResponse_;

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

static void moisture_callback_wrapper_moisture(DevicePrivate *device_p, Packet *packet) {
	MoistureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MOISTURE_CALLBACK_MOISTURE];
	MoistureCallback_ *callback = (MoistureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MOISTURE_CALLBACK_MOISTURE];

	if (callback_function == NULL) {
		return;
	}

	callback->moisture = leconvert_uint16_from(callback->moisture);

	callback_function(callback->moisture, user_data);
}

static void moisture_callback_wrapper_moisture_reached(DevicePrivate *device_p, Packet *packet) {
	MoistureReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MOISTURE_CALLBACK_MOISTURE_REACHED];
	MoistureReachedCallback_ *callback = (MoistureReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MOISTURE_CALLBACK_MOISTURE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->moisture = leconvert_uint16_from(callback->moisture);

	callback_function(callback->moisture, user_data);
}

void moisture_create(Moisture *moisture, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(moisture, uid, ipcon->p, 2, 0, 0);

	device_p = moisture->p;

	device_p->response_expected[MOISTURE_FUNCTION_GET_MOISTURE_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_SET_MOISTURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_GET_MOISTURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_SET_MOISTURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_GET_MOISTURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOISTURE_CALLBACK_MOISTURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MOISTURE_CALLBACK_MOISTURE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MOISTURE_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOISTURE_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOISTURE_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[MOISTURE_CALLBACK_MOISTURE] = moisture_callback_wrapper_moisture;
	device_p->callback_wrappers[MOISTURE_CALLBACK_MOISTURE_REACHED] = moisture_callback_wrapper_moisture_reached;
}

void moisture_destroy(Moisture *moisture) {
	device_destroy(moisture);
}

int moisture_get_response_expected(Moisture *moisture, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(moisture->p, function_id, ret_response_expected);
}

int moisture_set_response_expected(Moisture *moisture, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(moisture->p, function_id, response_expected);
}

int moisture_set_response_expected_all(Moisture *moisture, bool response_expected) {
	return device_set_response_expected_all(moisture->p, response_expected);
}

void moisture_register_callback(Moisture *moisture, uint8_t id, void *callback, void *user_data) {
	device_register_callback(moisture->p, id, callback, user_data);
}

int moisture_get_api_version(Moisture *moisture, uint8_t ret_api_version[3]) {
	return device_get_api_version(moisture->p, ret_api_version);
}

int moisture_get_moisture_value(Moisture *moisture, uint16_t *ret_moisture) {
	DevicePrivate *device_p = moisture->p;
	GetMoistureValue_ request;
	GetMoistureValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_GET_MOISTURE_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_moisture = leconvert_uint16_from(response.moisture);



	return ret;
}

int moisture_set_moisture_callback_period(Moisture *moisture, uint32_t period) {
	DevicePrivate *device_p = moisture->p;
	SetMoistureCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_SET_MOISTURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int moisture_get_moisture_callback_period(Moisture *moisture, uint32_t *ret_period) {
	DevicePrivate *device_p = moisture->p;
	GetMoistureCallbackPeriod_ request;
	GetMoistureCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_GET_MOISTURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int moisture_set_moisture_callback_threshold(Moisture *moisture, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = moisture->p;
	SetMoistureCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_SET_MOISTURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int moisture_get_moisture_callback_threshold(Moisture *moisture, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = moisture->p;
	GetMoistureCallbackThreshold_ request;
	GetMoistureCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_GET_MOISTURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int moisture_set_debounce_period(Moisture *moisture, uint32_t debounce) {
	DevicePrivate *device_p = moisture->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int moisture_get_debounce_period(Moisture *moisture, uint32_t *ret_debounce) {
	DevicePrivate *device_p = moisture->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int moisture_set_moving_average(Moisture *moisture, uint8_t average) {
	DevicePrivate *device_p = moisture->p;
	SetMovingAverage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.average = average;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int moisture_get_moving_average(Moisture *moisture, uint8_t *ret_average) {
	DevicePrivate *device_p = moisture->p;
	GetMovingAverage_ request;
	GetMovingAverageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_average = response.average;



	return ret;
}

int moisture_get_identity(Moisture *moisture, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = moisture->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOISTURE_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

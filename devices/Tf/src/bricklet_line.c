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

#include "bricklet_line.h"

#include <string.h>



typedef void (*ReflectivityCallbackFunction)(uint16_t, void *);

typedef void (*ReflectivityReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetReflectivity_;

typedef struct {
	PacketHeader header;
	uint16_t reflectivity;
} ATTRIBUTE_PACKED GetReflectivityResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetReflectivityCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReflectivityCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetReflectivityCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetReflectivityCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReflectivityCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetReflectivityCallbackThresholdResponse_;

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
	uint16_t reflectivity;
} ATTRIBUTE_PACKED ReflectivityCallback_;

typedef struct {
	PacketHeader header;
	uint16_t reflectivity;
} ATTRIBUTE_PACKED ReflectivityReachedCallback_;

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

static void line_callback_wrapper_reflectivity(DevicePrivate *device_p, Packet *packet) {
	ReflectivityCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LINE_CALLBACK_REFLECTIVITY];
	ReflectivityCallback_ *callback = (ReflectivityCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LINE_CALLBACK_REFLECTIVITY];

	if (callback_function == NULL) {
		return;
	}

	callback->reflectivity = leconvert_uint16_from(callback->reflectivity);

	callback_function(callback->reflectivity, user_data);
}

static void line_callback_wrapper_reflectivity_reached(DevicePrivate *device_p, Packet *packet) {
	ReflectivityReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[LINE_CALLBACK_REFLECTIVITY_REACHED];
	ReflectivityReachedCallback_ *callback = (ReflectivityReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[LINE_CALLBACK_REFLECTIVITY_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->reflectivity = leconvert_uint16_from(callback->reflectivity);

	callback_function(callback->reflectivity, user_data);
}

void line_create(Line *line, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(line, uid, ipcon->p, 2, 0, 0);

	device_p = line->p;

	device_p->response_expected[LINE_FUNCTION_GET_REFLECTIVITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_CALLBACK_REFLECTIVITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LINE_CALLBACK_REFLECTIVITY_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[LINE_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LINE_CALLBACK_REFLECTIVITY] = line_callback_wrapper_reflectivity;
	device_p->callback_wrappers[LINE_CALLBACK_REFLECTIVITY_REACHED] = line_callback_wrapper_reflectivity_reached;
}

void line_destroy(Line *line) {
	device_destroy(line);
}

int line_get_response_expected(Line *line, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(line->p, function_id, ret_response_expected);
}

int line_set_response_expected(Line *line, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(line->p, function_id, response_expected);
}

int line_set_response_expected_all(Line *line, bool response_expected) {
	return device_set_response_expected_all(line->p, response_expected);
}

void line_register_callback(Line *line, uint8_t id, void *callback, void *user_data) {
	device_register_callback(line->p, id, callback, user_data);
}

int line_get_api_version(Line *line, uint8_t ret_api_version[3]) {
	return device_get_api_version(line->p, ret_api_version);
}

int line_get_reflectivity(Line *line, uint16_t *ret_reflectivity) {
	DevicePrivate *device_p = line->p;
	GetReflectivity_ request;
	GetReflectivityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_REFLECTIVITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_reflectivity = leconvert_uint16_from(response.reflectivity);



	return ret;
}

int line_set_reflectivity_callback_period(Line *line, uint32_t period) {
	DevicePrivate *device_p = line->p;
	SetReflectivityCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int line_get_reflectivity_callback_period(Line *line, uint32_t *ret_period) {
	DevicePrivate *device_p = line->p;
	GetReflectivityCallbackPeriod_ request;
	GetReflectivityCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int line_set_reflectivity_callback_threshold(Line *line, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = line->p;
	SetReflectivityCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int line_get_reflectivity_callback_threshold(Line *line, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = line->p;
	GetReflectivityCallbackThreshold_ request;
	GetReflectivityCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int line_set_debounce_period(Line *line, uint32_t debounce) {
	DevicePrivate *device_p = line->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int line_get_debounce_period(Line *line, uint32_t *ret_debounce) {
	DevicePrivate *device_p = line->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int line_get_identity(Line *line, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = line->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

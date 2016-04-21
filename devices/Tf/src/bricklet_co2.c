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

#include "bricklet_co2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*CO2ConcentrationCallbackFunction)(uint16_t, void *);

typedef void (*CO2ConcentrationReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetCO2Concentration_;

typedef struct {
	PacketHeader header;
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED GetCO2ConcentrationResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetCO2ConcentrationCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetCO2ConcentrationCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackThresholdResponse_;

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
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED CO2ConcentrationCallback_;

typedef struct {
	PacketHeader header;
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED CO2ConcentrationReachedCallback_;

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

static void co2_callback_wrapper_co2_concentration(DevicePrivate *device_p, Packet *packet) {
	CO2ConcentrationCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CO2_CALLBACK_CO2_CONCENTRATION];
	CO2ConcentrationCallback_ *callback = (CO2ConcentrationCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CO2_CALLBACK_CO2_CONCENTRATION];

	if (callback_function == NULL) {
		return;
	}

	callback->co2_concentration = leconvert_uint16_from(callback->co2_concentration);

	callback_function(callback->co2_concentration, user_data);
}

static void co2_callback_wrapper_co2_concentration_reached(DevicePrivate *device_p, Packet *packet) {
	CO2ConcentrationReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[CO2_CALLBACK_CO2_CONCENTRATION_REACHED];
	CO2ConcentrationReachedCallback_ *callback = (CO2ConcentrationReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[CO2_CALLBACK_CO2_CONCENTRATION_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->co2_concentration = leconvert_uint16_from(callback->co2_concentration);

	callback_function(callback->co2_concentration, user_data);
}

void co2_create(CO2 *co2, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(co2, uid, ipcon->p, 2, 0, 0);

	device_p = co2->p;

	device_p->response_expected[CO2_FUNCTION_GET_CO2_CONCENTRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_CALLBACK_CO2_CONCENTRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CO2_CALLBACK_CO2_CONCENTRATION_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[CO2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CO2_CALLBACK_CO2_CONCENTRATION] = co2_callback_wrapper_co2_concentration;
	device_p->callback_wrappers[CO2_CALLBACK_CO2_CONCENTRATION_REACHED] = co2_callback_wrapper_co2_concentration_reached;
}

void co2_destroy(CO2 *co2) {
	device_release(co2->p);
}

int co2_get_response_expected(CO2 *co2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(co2->p, function_id, ret_response_expected);
}

int co2_set_response_expected(CO2 *co2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(co2->p, function_id, response_expected);
}

int co2_set_response_expected_all(CO2 *co2, bool response_expected) {
	return device_set_response_expected_all(co2->p, response_expected);
}

void co2_register_callback(CO2 *co2, uint8_t id, void *callback, void *user_data) {
	device_register_callback(co2->p, id, callback, user_data);
}

int co2_get_api_version(CO2 *co2, uint8_t ret_api_version[3]) {
	return device_get_api_version(co2->p, ret_api_version);
}

int co2_get_co2_concentration(CO2 *co2, uint16_t *ret_co2_concentration) {
	DevicePrivate *device_p = co2->p;
	GetCO2Concentration_ request;
	GetCO2ConcentrationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_CO2_CONCENTRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_co2_concentration = leconvert_uint16_from(response.co2_concentration);



	return ret;
}

int co2_set_co2_concentration_callback_period(CO2 *co2, uint32_t period) {
	DevicePrivate *device_p = co2->p;
	SetCO2ConcentrationCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int co2_get_co2_concentration_callback_period(CO2 *co2, uint32_t *ret_period) {
	DevicePrivate *device_p = co2->p;
	GetCO2ConcentrationCallbackPeriod_ request;
	GetCO2ConcentrationCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int co2_set_co2_concentration_callback_threshold(CO2 *co2, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = co2->p;
	SetCO2ConcentrationCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int co2_get_co2_concentration_callback_threshold(CO2 *co2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = co2->p;
	GetCO2ConcentrationCallbackThreshold_ request;
	GetCO2ConcentrationCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int co2_set_debounce_period(CO2 *co2, uint32_t debounce) {
	DevicePrivate *device_p = co2->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int co2_get_debounce_period(CO2 *co2, uint32_t *ret_debounce) {
	DevicePrivate *device_p = co2->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int co2_get_identity(CO2 *co2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = co2->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

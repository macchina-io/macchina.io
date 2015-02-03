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

#include "bricklet_piezo_buzzer.h"

#include <string.h>



typedef void (*BeepFinishedCallbackFunction)(void *);

typedef void (*MorseCodeFinishedCallbackFunction)(void *);

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
	uint32_t duration;
} ATTRIBUTE_PACKED Beep_;

typedef struct {
	PacketHeader header;
	char morse[60];
} ATTRIBUTE_PACKED MorseCode_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED BeepFinishedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED MorseCodeFinishedCallback_;

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

static void piezo_buzzer_callback_wrapper_beep_finished(DevicePrivate *device_p, Packet *packet) {
	BeepFinishedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[PIEZO_BUZZER_CALLBACK_BEEP_FINISHED];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[PIEZO_BUZZER_CALLBACK_BEEP_FINISHED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void piezo_buzzer_callback_wrapper_morse_code_finished(DevicePrivate *device_p, Packet *packet) {
	MorseCodeFinishedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[PIEZO_BUZZER_CALLBACK_MORSE_CODE_FINISHED];
	(void)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[PIEZO_BUZZER_CALLBACK_MORSE_CODE_FINISHED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void piezo_buzzer_create(PiezoBuzzer *piezo_buzzer, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(piezo_buzzer, uid, ipcon->p, 2, 0, 0);

	device_p = piezo_buzzer->p;

	device_p->response_expected[PIEZO_BUZZER_FUNCTION_BEEP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_BUZZER_FUNCTION_MORSE_CODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_BUZZER_CALLBACK_BEEP_FINISHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[PIEZO_BUZZER_CALLBACK_MORSE_CODE_FINISHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[PIEZO_BUZZER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PIEZO_BUZZER_CALLBACK_BEEP_FINISHED] = piezo_buzzer_callback_wrapper_beep_finished;
	device_p->callback_wrappers[PIEZO_BUZZER_CALLBACK_MORSE_CODE_FINISHED] = piezo_buzzer_callback_wrapper_morse_code_finished;
}

void piezo_buzzer_destroy(PiezoBuzzer *piezo_buzzer) {
	device_destroy(piezo_buzzer);
}

int piezo_buzzer_get_response_expected(PiezoBuzzer *piezo_buzzer, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(piezo_buzzer->p, function_id, ret_response_expected);
}

int piezo_buzzer_set_response_expected(PiezoBuzzer *piezo_buzzer, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(piezo_buzzer->p, function_id, response_expected);
}

int piezo_buzzer_set_response_expected_all(PiezoBuzzer *piezo_buzzer, bool response_expected) {
	return device_set_response_expected_all(piezo_buzzer->p, response_expected);
}

void piezo_buzzer_register_callback(PiezoBuzzer *piezo_buzzer, uint8_t id, void *callback, void *user_data) {
	device_register_callback(piezo_buzzer->p, id, callback, user_data);
}

int piezo_buzzer_get_api_version(PiezoBuzzer *piezo_buzzer, uint8_t ret_api_version[3]) {
	return device_get_api_version(piezo_buzzer->p, ret_api_version);
}

int piezo_buzzer_beep(PiezoBuzzer *piezo_buzzer, uint32_t duration) {
	DevicePrivate *device_p = piezo_buzzer->p;
	Beep_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_BUZZER_FUNCTION_BEEP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.duration = leconvert_uint32_to(duration);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int piezo_buzzer_morse_code(PiezoBuzzer *piezo_buzzer, const char morse[60]) {
	DevicePrivate *device_p = piezo_buzzer->p;
	MorseCode_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_BUZZER_FUNCTION_MORSE_CODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	strncpy(request.morse, morse, 60);


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int piezo_buzzer_get_identity(PiezoBuzzer *piezo_buzzer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = piezo_buzzer->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_BUZZER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

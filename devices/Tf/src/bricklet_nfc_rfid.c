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

#include "bricklet_nfc_rfid.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*StateChangedCallbackFunction)(uint8_t, bool, void *);

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
	uint8_t tag_type;
} ATTRIBUTE_PACKED RequestTagID_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTagID_;

typedef struct {
	PacketHeader header;
	uint8_t tag_type;
	uint8_t tid_length;
	uint8_t tid[7];
} ATTRIBUTE_PACKED GetTagIDResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetState_;

typedef struct {
	PacketHeader header;
	uint8_t state;
	bool idle;
} ATTRIBUTE_PACKED GetStateResponse_;

typedef struct {
	PacketHeader header;
	uint16_t page;
	uint8_t key_number;
	uint8_t key[6];
} ATTRIBUTE_PACKED AuthenticateMifareClassicPage_;

typedef struct {
	PacketHeader header;
	uint16_t page;
	uint8_t data[16];
} ATTRIBUTE_PACKED WritePage_;

typedef struct {
	PacketHeader header;
	uint16_t page;
} ATTRIBUTE_PACKED RequestPage_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPage_;

typedef struct {
	PacketHeader header;
	uint8_t data[16];
} ATTRIBUTE_PACKED GetPageResponse_;

typedef struct {
	PacketHeader header;
	uint8_t state;
	bool idle;
} ATTRIBUTE_PACKED StateChangedCallback_;

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

static void nfc_rfid_callback_wrapper_state_changed(DevicePrivate *device_p, Packet *packet) {
	StateChangedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[NFC_RFID_CALLBACK_STATE_CHANGED];
	StateChangedCallback_ *callback = (StateChangedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[NFC_RFID_CALLBACK_STATE_CHANGED];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->state, callback->idle, user_data);
}

void nfc_rfid_create(NFCRFID *nfc_rfid, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(nfc_rfid, uid, ipcon->p, 2, 0, 0);

	device_p = nfc_rfid->p;

	device_p->response_expected[NFC_RFID_FUNCTION_REQUEST_TAG_ID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_RFID_FUNCTION_GET_TAG_ID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_RFID_FUNCTION_GET_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_RFID_FUNCTION_AUTHENTICATE_MIFARE_CLASSIC_PAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_RFID_FUNCTION_WRITE_PAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_RFID_FUNCTION_REQUEST_PAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_RFID_FUNCTION_GET_PAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_RFID_CALLBACK_STATE_CHANGED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[NFC_RFID_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[NFC_RFID_CALLBACK_STATE_CHANGED] = nfc_rfid_callback_wrapper_state_changed;
}

void nfc_rfid_destroy(NFCRFID *nfc_rfid) {
	device_release(nfc_rfid->p);
}

int nfc_rfid_get_response_expected(NFCRFID *nfc_rfid, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(nfc_rfid->p, function_id, ret_response_expected);
}

int nfc_rfid_set_response_expected(NFCRFID *nfc_rfid, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(nfc_rfid->p, function_id, response_expected);
}

int nfc_rfid_set_response_expected_all(NFCRFID *nfc_rfid, bool response_expected) {
	return device_set_response_expected_all(nfc_rfid->p, response_expected);
}

void nfc_rfid_register_callback(NFCRFID *nfc_rfid, uint8_t id, void *callback, void *user_data) {
	device_register_callback(nfc_rfid->p, id, callback, user_data);
}

int nfc_rfid_get_api_version(NFCRFID *nfc_rfid, uint8_t ret_api_version[3]) {
	return device_get_api_version(nfc_rfid->p, ret_api_version);
}

int nfc_rfid_request_tag_id(NFCRFID *nfc_rfid, uint8_t tag_type) {
	DevicePrivate *device_p = nfc_rfid->p;
	RequestTagID_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_REQUEST_TAG_ID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.tag_type = tag_type;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int nfc_rfid_get_tag_id(NFCRFID *nfc_rfid, uint8_t *ret_tag_type, uint8_t *ret_tid_length, uint8_t ret_tid[7]) {
	DevicePrivate *device_p = nfc_rfid->p;
	GetTagID_ request;
	GetTagIDResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_GET_TAG_ID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_tag_type = response.tag_type;
	*ret_tid_length = response.tid_length;
	memcpy(ret_tid, response.tid, 7 * sizeof(uint8_t));



	return ret;
}

int nfc_rfid_get_state(NFCRFID *nfc_rfid, uint8_t *ret_state, bool *ret_idle) {
	DevicePrivate *device_p = nfc_rfid->p;
	GetState_ request;
	GetStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_GET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_state = response.state;
	*ret_idle = response.idle;



	return ret;
}

int nfc_rfid_authenticate_mifare_classic_page(NFCRFID *nfc_rfid, uint16_t page, uint8_t key_number, uint8_t key[6]) {
	DevicePrivate *device_p = nfc_rfid->p;
	AuthenticateMifareClassicPage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_AUTHENTICATE_MIFARE_CLASSIC_PAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.page = leconvert_uint16_to(page);
	request.key_number = key_number;
	memcpy(request.key, key, 6 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int nfc_rfid_write_page(NFCRFID *nfc_rfid, uint16_t page, uint8_t data[16]) {
	DevicePrivate *device_p = nfc_rfid->p;
	WritePage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_WRITE_PAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.page = leconvert_uint16_to(page);
	memcpy(request.data, data, 16 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int nfc_rfid_request_page(NFCRFID *nfc_rfid, uint16_t page) {
	DevicePrivate *device_p = nfc_rfid->p;
	RequestPage_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_REQUEST_PAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.page = leconvert_uint16_to(page);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int nfc_rfid_get_page(NFCRFID *nfc_rfid, uint8_t ret_data[16]) {
	DevicePrivate *device_p = nfc_rfid->p;
	GetPage_ request;
	GetPageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_GET_PAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	memcpy(ret_data, response.data, 16 * sizeof(uint8_t));



	return ret;
}

int nfc_rfid_get_identity(NFCRFID *nfc_rfid, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = nfc_rfid->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_RFID_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

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

#include "brick_master.h"

#include <string.h>



typedef void (*StackCurrentCallbackFunction)(uint16_t, void *);

typedef void (*StackVoltageCallbackFunction)(uint16_t, void *);

typedef void (*USBVoltageCallbackFunction)(uint16_t, void *);

typedef void (*StackCurrentReachedCallbackFunction)(uint16_t, void *);

typedef void (*StackVoltageReachedCallbackFunction)(uint16_t, void *);

typedef void (*USBVoltageReachedCallbackFunction)(uint16_t, void *);

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
} ATTRIBUTE_PACKED GetStackVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetStackVoltageResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackCurrent_;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetStackCurrentResponse_;

typedef struct {
	PacketHeader header;
	uint8_t extension;
	uint32_t exttype;
} ATTRIBUTE_PACKED SetExtensionType_;

typedef struct {
	PacketHeader header;
	uint8_t extension;
} ATTRIBUTE_PACKED GetExtensionType_;

typedef struct {
	PacketHeader header;
	uint32_t exttype;
} ATTRIBUTE_PACKED GetExtensionTypeResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsChibiPresent_;

typedef struct {
	PacketHeader header;
	bool present;
} ATTRIBUTE_PACKED IsChibiPresentResponse_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED SetChibiAddress_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiAddress_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetChibiAddressResponse_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED SetChibiMasterAddress_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiMasterAddress_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetChibiMasterAddressResponse_;

typedef struct {
	PacketHeader header;
	uint8_t num;
	uint8_t address;
} ATTRIBUTE_PACKED SetChibiSlaveAddress_;

typedef struct {
	PacketHeader header;
	uint8_t num;
} ATTRIBUTE_PACKED GetChibiSlaveAddress_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetChibiSlaveAddressResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiSignalStrength_;

typedef struct {
	PacketHeader header;
	uint8_t signal_strength;
} ATTRIBUTE_PACKED GetChibiSignalStrengthResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiErrorLog_;

typedef struct {
	PacketHeader header;
	uint16_t underrun;
	uint16_t crc_error;
	uint16_t no_ack;
	uint16_t overflow;
} ATTRIBUTE_PACKED GetChibiErrorLogResponse_;

typedef struct {
	PacketHeader header;
	uint8_t frequency;
} ATTRIBUTE_PACKED SetChibiFrequency_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiFrequency_;

typedef struct {
	PacketHeader header;
	uint8_t frequency;
} ATTRIBUTE_PACKED GetChibiFrequencyResponse_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED SetChibiChannel_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiChannel_;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetChibiChannelResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsRS485Present_;

typedef struct {
	PacketHeader header;
	bool present;
} ATTRIBUTE_PACKED IsRS485PresentResponse_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED SetRS485Address_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485Address_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetRS485AddressResponse_;

typedef struct {
	PacketHeader header;
	uint8_t num;
	uint8_t address;
} ATTRIBUTE_PACKED SetRS485SlaveAddress_;

typedef struct {
	PacketHeader header;
	uint8_t num;
} ATTRIBUTE_PACKED GetRS485SlaveAddress_;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetRS485SlaveAddressResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485ErrorLog_;

typedef struct {
	PacketHeader header;
	uint16_t crc_error;
} ATTRIBUTE_PACKED GetRS485ErrorLogResponse_;

typedef struct {
	PacketHeader header;
	uint32_t speed;
	char parity;
	uint8_t stopbits;
} ATTRIBUTE_PACKED SetRS485Configuration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485Configuration_;

typedef struct {
	PacketHeader header;
	uint32_t speed;
	char parity;
	uint8_t stopbits;
} ATTRIBUTE_PACKED GetRS485ConfigurationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsWifiPresent_;

typedef struct {
	PacketHeader header;
	bool present;
} ATTRIBUTE_PACKED IsWifiPresentResponse_;

typedef struct {
	PacketHeader header;
	char ssid[32];
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED SetWifiConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiConfiguration_;

typedef struct {
	PacketHeader header;
	char ssid[32];
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED GetWifiConfigurationResponse_;

typedef struct {
	PacketHeader header;
	uint8_t encryption;
	char key[50];
	uint8_t key_index;
	uint8_t eap_options;
	uint16_t ca_certificate_length;
	uint16_t client_certificate_length;
	uint16_t private_key_length;
} ATTRIBUTE_PACKED SetWifiEncryption_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiEncryption_;

typedef struct {
	PacketHeader header;
	uint8_t encryption;
	char key[50];
	uint8_t key_index;
	uint8_t eap_options;
	uint16_t ca_certificate_length;
	uint16_t client_certificate_length;
	uint16_t private_key_length;
} ATTRIBUTE_PACKED GetWifiEncryptionResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiStatus_;

typedef struct {
	PacketHeader header;
	uint8_t mac_address[6];
	uint8_t bssid[6];
	uint8_t channel;
	int16_t rssi;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint32_t rx_count;
	uint32_t tx_count;
	uint8_t state;
} ATTRIBUTE_PACKED GetWifiStatusResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED RefreshWifiStatus_;

typedef struct {
	PacketHeader header;
	uint16_t index;
	uint8_t data[32];
	uint8_t data_length;
} ATTRIBUTE_PACKED SetWifiCertificate_;

typedef struct {
	PacketHeader header;
	uint16_t index;
} ATTRIBUTE_PACKED GetWifiCertificate_;

typedef struct {
	PacketHeader header;
	uint8_t data[32];
	uint8_t data_length;
} ATTRIBUTE_PACKED GetWifiCertificateResponse_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetWifiPowerMode_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiPowerMode_;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetWifiPowerModeResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiBufferInfo_;

typedef struct {
	PacketHeader header;
	uint32_t overflow;
	uint16_t low_watermark;
	uint16_t used;
} ATTRIBUTE_PACKED GetWifiBufferInfoResponse_;

typedef struct {
	PacketHeader header;
	uint8_t domain;
} ATTRIBUTE_PACKED SetWifiRegulatoryDomain_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiRegulatoryDomain_;

typedef struct {
	PacketHeader header;
	uint8_t domain;
} ATTRIBUTE_PACKED GetWifiRegulatoryDomainResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUSBVoltage_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetUSBVoltageResponse_;

typedef struct {
	PacketHeader header;
	char key[64];
} ATTRIBUTE_PACKED SetLongWifiKey_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLongWifiKey_;

typedef struct {
	PacketHeader header;
	char key[64];
} ATTRIBUTE_PACKED GetLongWifiKeyResponse_;

typedef struct {
	PacketHeader header;
	char hostname[16];
} ATTRIBUTE_PACKED SetWifiHostname_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiHostname_;

typedef struct {
	PacketHeader header;
	char hostname[16];
} ATTRIBUTE_PACKED GetWifiHostnameResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetStackCurrentCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackCurrentCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetStackCurrentCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetStackVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetStackVoltageCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetUSBVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackPeriodResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetStackCurrentCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackCurrentCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetStackCurrentCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetStackVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetStackVoltageCallbackThresholdResponse_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetUSBVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackThreshold_;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackThresholdResponse_;

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
	uint16_t current;
} ATTRIBUTE_PACKED StackCurrentCallback_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED StackVoltageCallback_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED USBVoltageCallback_;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED StackCurrentReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED StackVoltageReachedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED USBVoltageReachedCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsEthernetPresent_;

typedef struct {
	PacketHeader header;
	bool present;
} ATTRIBUTE_PACKED IsEthernetPresentResponse_;

typedef struct {
	PacketHeader header;
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED SetEthernetConfiguration_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEthernetConfiguration_;

typedef struct {
	PacketHeader header;
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED GetEthernetConfigurationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEthernetStatus_;

typedef struct {
	PacketHeader header;
	uint8_t mac_address[6];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint32_t rx_count;
	uint32_t tx_count;
	char hostname[32];
} ATTRIBUTE_PACKED GetEthernetStatusResponse_;

typedef struct {
	PacketHeader header;
	char hostname[32];
} ATTRIBUTE_PACKED SetEthernetHostname_;

typedef struct {
	PacketHeader header;
	uint8_t mac_address[6];
} ATTRIBUTE_PACKED SetEthernetMACAddress_;

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

static void master_callback_wrapper_stack_current(DevicePrivate *device_p, Packet *packet) {
	StackCurrentCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MASTER_CALLBACK_STACK_CURRENT];
	StackCurrentCallback_ *callback = (StackCurrentCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MASTER_CALLBACK_STACK_CURRENT];

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_uint16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void master_callback_wrapper_stack_voltage(DevicePrivate *device_p, Packet *packet) {
	StackVoltageCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MASTER_CALLBACK_STACK_VOLTAGE];
	StackVoltageCallback_ *callback = (StackVoltageCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MASTER_CALLBACK_STACK_VOLTAGE];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void master_callback_wrapper_usb_voltage(DevicePrivate *device_p, Packet *packet) {
	USBVoltageCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MASTER_CALLBACK_USB_VOLTAGE];
	USBVoltageCallback_ *callback = (USBVoltageCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MASTER_CALLBACK_USB_VOLTAGE];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void master_callback_wrapper_stack_current_reached(DevicePrivate *device_p, Packet *packet) {
	StackCurrentReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MASTER_CALLBACK_STACK_CURRENT_REACHED];
	StackCurrentReachedCallback_ *callback = (StackCurrentReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MASTER_CALLBACK_STACK_CURRENT_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_uint16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void master_callback_wrapper_stack_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	StackVoltageReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MASTER_CALLBACK_STACK_VOLTAGE_REACHED];
	StackVoltageReachedCallback_ *callback = (StackVoltageReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MASTER_CALLBACK_STACK_VOLTAGE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void master_callback_wrapper_usb_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	USBVoltageReachedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[MASTER_CALLBACK_USB_VOLTAGE_REACHED];
	USBVoltageReachedCallback_ *callback = (USBVoltageReachedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[MASTER_CALLBACK_USB_VOLTAGE_REACHED];

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

void master_create(Master *master, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(master, uid, ipcon->p, 2, 0, 2);

	device_p = master->p;

	device_p->response_expected[MASTER_FUNCTION_GET_STACK_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_EXTENSION_TYPE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_EXTENSION_TYPE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_CHIBI_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_MASTER_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_MASTER_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_SIGNAL_STRENGTH] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_ERROR_LOG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_CHANNEL] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_CHANNEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_RS485_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_RS485_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_RS485_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_ERROR_LOG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_RS485_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_WIFI_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_ENCRYPTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_ENCRYPTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_REFRESH_WIFI_STATUS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_CERTIFICATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_CERTIFICATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_POWER_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_POWER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_BUFFER_INFO] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_REGULATORY_DOMAIN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_REGULATORY_DOMAIN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_USB_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_LONG_WIFI_KEY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_LONG_WIFI_KEY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_CALLBACK_STACK_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MASTER_CALLBACK_STACK_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MASTER_CALLBACK_USB_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MASTER_CALLBACK_STACK_CURRENT_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MASTER_CALLBACK_STACK_VOLTAGE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MASTER_CALLBACK_USB_VOLTAGE_REACHED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[MASTER_FUNCTION_IS_ETHERNET_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_ETHERNET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_ETHERNET_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_MAC_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[MASTER_CALLBACK_STACK_CURRENT] = master_callback_wrapper_stack_current;
	device_p->callback_wrappers[MASTER_CALLBACK_STACK_VOLTAGE] = master_callback_wrapper_stack_voltage;
	device_p->callback_wrappers[MASTER_CALLBACK_USB_VOLTAGE] = master_callback_wrapper_usb_voltage;
	device_p->callback_wrappers[MASTER_CALLBACK_STACK_CURRENT_REACHED] = master_callback_wrapper_stack_current_reached;
	device_p->callback_wrappers[MASTER_CALLBACK_STACK_VOLTAGE_REACHED] = master_callback_wrapper_stack_voltage_reached;
	device_p->callback_wrappers[MASTER_CALLBACK_USB_VOLTAGE_REACHED] = master_callback_wrapper_usb_voltage_reached;
}

void master_destroy(Master *master) {
	device_destroy(master);
}

int master_get_response_expected(Master *master, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(master->p, function_id, ret_response_expected);
}

int master_set_response_expected(Master *master, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(master->p, function_id, response_expected);
}

int master_set_response_expected_all(Master *master, bool response_expected) {
	return device_set_response_expected_all(master->p, response_expected);
}

void master_register_callback(Master *master, uint8_t id, void *callback, void *user_data) {
	device_register_callback(master->p, id, callback, user_data);
}

int master_get_api_version(Master *master, uint8_t ret_api_version[3]) {
	return device_get_api_version(master->p, ret_api_version);
}

int master_get_stack_voltage(Master *master, uint16_t *ret_voltage) {
	DevicePrivate *device_p = master->p;
	GetStackVoltage_ request;
	GetStackVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_VOLTAGE, device_p->ipcon_p, device_p);

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

int master_get_stack_current(Master *master, uint16_t *ret_current) {
	DevicePrivate *device_p = master->p;
	GetStackCurrent_ request;
	GetStackCurrentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_current = leconvert_uint16_from(response.current);



	return ret;
}

int master_set_extension_type(Master *master, uint8_t extension, uint32_t exttype) {
	DevicePrivate *device_p = master->p;
	SetExtensionType_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_EXTENSION_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.extension = extension;
	request.exttype = leconvert_uint32_to(exttype);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_extension_type(Master *master, uint8_t extension, uint32_t *ret_exttype) {
	DevicePrivate *device_p = master->p;
	GetExtensionType_ request;
	GetExtensionTypeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_EXTENSION_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.extension = extension;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_exttype = leconvert_uint32_from(response.exttype);



	return ret;
}

int master_is_chibi_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsChibiPresent_ request;
	IsChibiPresentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_CHIBI_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_present = response.present;



	return ret;
}

int master_set_chibi_address(Master *master, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetChibiAddress_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_chibi_address(Master *master, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetChibiAddress_ request;
	GetChibiAddressResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_address = response.address;



	return ret;
}

int master_set_chibi_master_address(Master *master, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetChibiMasterAddress_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_MASTER_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_chibi_master_address(Master *master, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetChibiMasterAddress_ request;
	GetChibiMasterAddressResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_MASTER_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_address = response.address;



	return ret;
}

int master_set_chibi_slave_address(Master *master, uint8_t num, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetChibiSlaveAddress_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;
	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_chibi_slave_address(Master *master, uint8_t num, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetChibiSlaveAddress_ request;
	GetChibiSlaveAddressResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_address = response.address;



	return ret;
}

int master_get_chibi_signal_strength(Master *master, uint8_t *ret_signal_strength) {
	DevicePrivate *device_p = master->p;
	GetChibiSignalStrength_ request;
	GetChibiSignalStrengthResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_SIGNAL_STRENGTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_signal_strength = response.signal_strength;



	return ret;
}

int master_get_chibi_error_log(Master *master, uint16_t *ret_underrun, uint16_t *ret_crc_error, uint16_t *ret_no_ack, uint16_t *ret_overflow) {
	DevicePrivate *device_p = master->p;
	GetChibiErrorLog_ request;
	GetChibiErrorLogResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_ERROR_LOG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_underrun = leconvert_uint16_from(response.underrun);
	*ret_crc_error = leconvert_uint16_from(response.crc_error);
	*ret_no_ack = leconvert_uint16_from(response.no_ack);
	*ret_overflow = leconvert_uint16_from(response.overflow);



	return ret;
}

int master_set_chibi_frequency(Master *master, uint8_t frequency) {
	DevicePrivate *device_p = master->p;
	SetChibiFrequency_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = frequency;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_chibi_frequency(Master *master, uint8_t *ret_frequency) {
	DevicePrivate *device_p = master->p;
	GetChibiFrequency_ request;
	GetChibiFrequencyResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_frequency = response.frequency;



	return ret;
}

int master_set_chibi_channel(Master *master, uint8_t channel) {
	DevicePrivate *device_p = master->p;
	SetChibiChannel_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_CHANNEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_chibi_channel(Master *master, uint8_t *ret_channel) {
	DevicePrivate *device_p = master->p;
	GetChibiChannel_ request;
	GetChibiChannelResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_CHANNEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_channel = response.channel;



	return ret;
}

int master_is_rs485_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsRS485Present_ request;
	IsRS485PresentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_RS485_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_present = response.present;



	return ret;
}

int master_set_rs485_address(Master *master, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetRS485Address_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_RS485_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_rs485_address(Master *master, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetRS485Address_ request;
	GetRS485AddressResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_address = response.address;



	return ret;
}

int master_set_rs485_slave_address(Master *master, uint8_t num, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetRS485SlaveAddress_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_RS485_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;
	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_rs485_slave_address(Master *master, uint8_t num, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetRS485SlaveAddress_ request;
	GetRS485SlaveAddressResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_address = response.address;



	return ret;
}

int master_get_rs485_error_log(Master *master, uint16_t *ret_crc_error) {
	DevicePrivate *device_p = master->p;
	GetRS485ErrorLog_ request;
	GetRS485ErrorLogResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_ERROR_LOG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_crc_error = leconvert_uint16_from(response.crc_error);



	return ret;
}

int master_set_rs485_configuration(Master *master, uint32_t speed, char parity, uint8_t stopbits) {
	DevicePrivate *device_p = master->p;
	SetRS485Configuration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_RS485_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.speed = leconvert_uint32_to(speed);
	request.parity = parity;
	request.stopbits = stopbits;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_rs485_configuration(Master *master, uint32_t *ret_speed, char *ret_parity, uint8_t *ret_stopbits) {
	DevicePrivate *device_p = master->p;
	GetRS485Configuration_ request;
	GetRS485ConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_speed = leconvert_uint32_from(response.speed);
	*ret_parity = response.parity;
	*ret_stopbits = response.stopbits;



	return ret;
}

int master_is_wifi_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsWifiPresent_ request;
	IsWifiPresentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_WIFI_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_present = response.present;



	return ret;
}

int master_set_wifi_configuration(Master *master, const char ssid[32], uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port) {
	DevicePrivate *device_p = master->p;
	SetWifiConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	strncpy(request.ssid, ssid, 32);

	request.connection = connection;
	memcpy(request.ip, ip, 4 * sizeof(uint8_t));
	memcpy(request.subnet_mask, subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.gateway, gateway, 4 * sizeof(uint8_t));
	request.port = leconvert_uint16_to(port);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_wifi_configuration(Master *master, char ret_ssid[32], uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port) {
	DevicePrivate *device_p = master->p;
	GetWifiConfiguration_ request;
	GetWifiConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	strncpy(ret_ssid, response.ssid, 32);
	*ret_connection = response.connection;
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_port = leconvert_uint16_from(response.port);



	return ret;
}

int master_set_wifi_encryption(Master *master, uint8_t encryption, const char key[50], uint8_t key_index, uint8_t eap_options, uint16_t ca_certificate_length, uint16_t client_certificate_length, uint16_t private_key_length) {
	DevicePrivate *device_p = master->p;
	SetWifiEncryption_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_ENCRYPTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.encryption = encryption;
	strncpy(request.key, key, 50);

	request.key_index = key_index;
	request.eap_options = eap_options;
	request.ca_certificate_length = leconvert_uint16_to(ca_certificate_length);
	request.client_certificate_length = leconvert_uint16_to(client_certificate_length);
	request.private_key_length = leconvert_uint16_to(private_key_length);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_wifi_encryption(Master *master, uint8_t *ret_encryption, char ret_key[50], uint8_t *ret_key_index, uint8_t *ret_eap_options, uint16_t *ret_ca_certificate_length, uint16_t *ret_client_certificate_length, uint16_t *ret_private_key_length) {
	DevicePrivate *device_p = master->p;
	GetWifiEncryption_ request;
	GetWifiEncryptionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_ENCRYPTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_encryption = response.encryption;
	strncpy(ret_key, response.key, 50);
	*ret_key_index = response.key_index;
	*ret_eap_options = response.eap_options;
	*ret_ca_certificate_length = leconvert_uint16_from(response.ca_certificate_length);
	*ret_client_certificate_length = leconvert_uint16_from(response.client_certificate_length);
	*ret_private_key_length = leconvert_uint16_from(response.private_key_length);



	return ret;
}

int master_get_wifi_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_bssid[6], uint8_t *ret_channel, int16_t *ret_rssi, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, uint8_t *ret_state) {
	DevicePrivate *device_p = master->p;
	GetWifiStatus_ request;
	GetWifiStatusResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));
	memcpy(ret_bssid, response.bssid, 6 * sizeof(uint8_t));
	*ret_channel = response.channel;
	*ret_rssi = leconvert_int16_from(response.rssi);
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_rx_count = leconvert_uint32_from(response.rx_count);
	*ret_tx_count = leconvert_uint32_from(response.tx_count);
	*ret_state = response.state;



	return ret;
}

int master_refresh_wifi_status(Master *master) {
	DevicePrivate *device_p = master->p;
	RefreshWifiStatus_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_REFRESH_WIFI_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_set_wifi_certificate(Master *master, uint16_t index, uint8_t data[32], uint8_t data_length) {
	DevicePrivate *device_p = master->p;
	SetWifiCertificate_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_CERTIFICATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = leconvert_uint16_to(index);
	memcpy(request.data, data, 32 * sizeof(uint8_t));
	request.data_length = data_length;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_wifi_certificate(Master *master, uint16_t index, uint8_t ret_data[32], uint8_t *ret_data_length) {
	DevicePrivate *device_p = master->p;
	GetWifiCertificate_ request;
	GetWifiCertificateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_CERTIFICATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = leconvert_uint16_to(index);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	memcpy(ret_data, response.data, 32 * sizeof(uint8_t));
	*ret_data_length = response.data_length;



	return ret;
}

int master_set_wifi_power_mode(Master *master, uint8_t mode) {
	DevicePrivate *device_p = master->p;
	SetWifiPowerMode_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_POWER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_wifi_power_mode(Master *master, uint8_t *ret_mode) {
	DevicePrivate *device_p = master->p;
	GetWifiPowerMode_ request;
	GetWifiPowerModeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_POWER_MODE, device_p->ipcon_p, device_p);

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

int master_get_wifi_buffer_info(Master *master, uint32_t *ret_overflow, uint16_t *ret_low_watermark, uint16_t *ret_used) {
	DevicePrivate *device_p = master->p;
	GetWifiBufferInfo_ request;
	GetWifiBufferInfoResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_BUFFER_INFO, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_overflow = leconvert_uint32_from(response.overflow);
	*ret_low_watermark = leconvert_uint16_from(response.low_watermark);
	*ret_used = leconvert_uint16_from(response.used);



	return ret;
}

int master_set_wifi_regulatory_domain(Master *master, uint8_t domain) {
	DevicePrivate *device_p = master->p;
	SetWifiRegulatoryDomain_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_REGULATORY_DOMAIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.domain = domain;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_wifi_regulatory_domain(Master *master, uint8_t *ret_domain) {
	DevicePrivate *device_p = master->p;
	GetWifiRegulatoryDomain_ request;
	GetWifiRegulatoryDomainResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_REGULATORY_DOMAIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_domain = response.domain;



	return ret;
}

int master_get_usb_voltage(Master *master, uint16_t *ret_voltage) {
	DevicePrivate *device_p = master->p;
	GetUSBVoltage_ request;
	GetUSBVoltageResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_USB_VOLTAGE, device_p->ipcon_p, device_p);

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

int master_set_long_wifi_key(Master *master, const char key[64]) {
	DevicePrivate *device_p = master->p;
	SetLongWifiKey_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_LONG_WIFI_KEY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	strncpy(request.key, key, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_long_wifi_key(Master *master, char ret_key[64]) {
	DevicePrivate *device_p = master->p;
	GetLongWifiKey_ request;
	GetLongWifiKeyResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_LONG_WIFI_KEY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	strncpy(ret_key, response.key, 64);



	return ret;
}

int master_set_wifi_hostname(Master *master, const char hostname[16]) {
	DevicePrivate *device_p = master->p;
	SetWifiHostname_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	strncpy(request.hostname, hostname, 16);


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_wifi_hostname(Master *master, char ret_hostname[16]) {
	DevicePrivate *device_p = master->p;
	GetWifiHostname_ request;
	GetWifiHostnameResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	strncpy(ret_hostname, response.hostname, 16);



	return ret;
}

int master_set_stack_current_callback_period(Master *master, uint32_t period) {
	DevicePrivate *device_p = master->p;
	SetStackCurrentCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_stack_current_callback_period(Master *master, uint32_t *ret_period) {
	DevicePrivate *device_p = master->p;
	GetStackCurrentCallbackPeriod_ request;
	GetStackCurrentCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int master_set_stack_voltage_callback_period(Master *master, uint32_t period) {
	DevicePrivate *device_p = master->p;
	SetStackVoltageCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_stack_voltage_callback_period(Master *master, uint32_t *ret_period) {
	DevicePrivate *device_p = master->p;
	GetStackVoltageCallbackPeriod_ request;
	GetStackVoltageCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int master_set_usb_voltage_callback_period(Master *master, uint32_t period) {
	DevicePrivate *device_p = master->p;
	SetUSBVoltageCallbackPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_usb_voltage_callback_period(Master *master, uint32_t *ret_period) {
	DevicePrivate *device_p = master->p;
	GetUSBVoltageCallbackPeriod_ request;
	GetUSBVoltageCallbackPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int master_set_stack_current_callback_threshold(Master *master, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = master->p;
	SetStackCurrentCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_stack_current_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = master->p;
	GetStackCurrentCallbackThreshold_ request;
	GetStackCurrentCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int master_set_stack_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = master->p;
	SetStackVoltageCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_stack_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = master->p;
	GetStackVoltageCallbackThreshold_ request;
	GetStackVoltageCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int master_set_usb_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = master->p;
	SetUSBVoltageCallbackThreshold_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_usb_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = master->p;
	GetUSBVoltageCallbackThreshold_ request;
	GetUSBVoltageCallbackThresholdResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int master_set_debounce_period(Master *master, uint32_t debounce) {
	DevicePrivate *device_p = master->p;
	SetDebouncePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_debounce_period(Master *master, uint32_t *ret_debounce) {
	DevicePrivate *device_p = master->p;
	GetDebouncePeriod_ request;
	GetDebouncePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int master_is_ethernet_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsEthernetPresent_ request;
	IsEthernetPresentResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_ETHERNET_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_present = response.present;



	return ret;
}

int master_set_ethernet_configuration(Master *master, uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port) {
	DevicePrivate *device_p = master->p;
	SetEthernetConfiguration_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.connection = connection;
	memcpy(request.ip, ip, 4 * sizeof(uint8_t));
	memcpy(request.subnet_mask, subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.gateway, gateway, 4 * sizeof(uint8_t));
	request.port = leconvert_uint16_to(port);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_ethernet_configuration(Master *master, uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port) {
	DevicePrivate *device_p = master->p;
	GetEthernetConfiguration_ request;
	GetEthernetConfigurationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_ETHERNET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_connection = response.connection;
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_port = leconvert_uint16_from(response.port);



	return ret;
}

int master_get_ethernet_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, char ret_hostname[32]) {
	DevicePrivate *device_p = master->p;
	GetEthernetStatus_ request;
	GetEthernetStatusResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_ETHERNET_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_rx_count = leconvert_uint32_from(response.rx_count);
	*ret_tx_count = leconvert_uint32_from(response.tx_count);
	strncpy(ret_hostname, response.hostname, 32);



	return ret;
}

int master_set_ethernet_hostname(Master *master, const char hostname[32]) {
	DevicePrivate *device_p = master->p;
	SetEthernetHostname_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	strncpy(request.hostname, hostname, 32);


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_set_ethernet_mac_address(Master *master, uint8_t mac_address[6]) {
	DevicePrivate *device_p = master->p;
	SetEthernetMACAddress_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_MAC_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.mac_address, mac_address, 6 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_protocol1_bricklet_name(Master *master, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]) {
	DevicePrivate *device_p = master->p;
	GetProtocol1BrickletName_ request;
	GetProtocol1BrickletNameResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME, device_p->ipcon_p, device_p);

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

int master_get_chip_temperature(Master *master, int16_t *ret_temperature) {
	DevicePrivate *device_p = master->p;
	GetChipTemperature_ request;
	GetChipTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int master_reset(Master *master) {
	DevicePrivate *device_p = master->p;
	Reset_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int master_get_identity(Master *master, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = master->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

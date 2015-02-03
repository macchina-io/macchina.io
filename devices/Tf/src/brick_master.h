/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICK_MASTER_H
#define BRICK_MASTER_H

#include "ip_connection.h"

/**
 * \defgroup BrickMaster Master Brick
 */

/**
 * \ingroup BrickMaster
 *
 * Device for controlling Stacks and four Bricklets
 */
typedef Device Master;

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_VOLTAGE 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_CURRENT 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_EXTENSION_TYPE 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_EXTENSION_TYPE 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_CHIBI_PRESENT 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_ADDRESS 6

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_ADDRESS 7

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_MASTER_ADDRESS 8

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_MASTER_ADDRESS 9

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_SLAVE_ADDRESS 10

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_SLAVE_ADDRESS 11

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_SIGNAL_STRENGTH 12

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_ERROR_LOG 13

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_FREQUENCY 14

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_FREQUENCY 15

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_CHANNEL 16

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_CHANNEL 17

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_RS485_PRESENT 18

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_RS485_ADDRESS 19

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_ADDRESS 20

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_RS485_SLAVE_ADDRESS 21

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_SLAVE_ADDRESS 22

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_ERROR_LOG 23

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_RS485_CONFIGURATION 24

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_CONFIGURATION 25

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_WIFI_PRESENT 26

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_CONFIGURATION 27

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_CONFIGURATION 28

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_ENCRYPTION 29

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_ENCRYPTION 30

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_STATUS 31

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_REFRESH_WIFI_STATUS 32

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_CERTIFICATE 33

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_CERTIFICATE 34

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_POWER_MODE 35

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_POWER_MODE 36

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_BUFFER_INFO 37

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_REGULATORY_DOMAIN 38

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_REGULATORY_DOMAIN 39

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_USB_VOLTAGE 40

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_LONG_WIFI_KEY 41

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_LONG_WIFI_KEY 42

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_HOSTNAME 43

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_HOSTNAME 44

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_PERIOD 45

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_PERIOD 46

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_PERIOD 47

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_PERIOD 48

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_PERIOD 49

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_PERIOD 50

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_THRESHOLD 51

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_THRESHOLD 52

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_THRESHOLD 53

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_THRESHOLD 54

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_THRESHOLD 55

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_THRESHOLD 56

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_DEBOUNCE_PERIOD 57

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_DEBOUNCE_PERIOD 58

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_ETHERNET_PRESENT 65

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_CONFIGURATION 66

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_ETHERNET_CONFIGURATION 67

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_ETHERNET_STATUS 68

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_HOSTNAME 69

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_MAC_ADDRESS 70

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME 241

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_RESET 243

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t current, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link master_set_stack_current_callback_period}. The parameter is the current of the
 * sensor.
 * 
 * {@link MASTER_CALLBACK_STACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
#define MASTER_CALLBACK_STACK_CURRENT 59

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link master_set_stack_voltage_callback_period}. The parameter is the voltage of the
 * sensor.
 * 
 * {@link MASTER_CALLBACK_STACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
#define MASTER_CALLBACK_STACK_VOLTAGE 60

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link master_set_usb_voltage_callback_period}. The parameter is the USB voltage
 * in mV.
 * 
 * {@link MASTER_CALLBACK_USB_VOLTAGE} is only triggered if the USB voltage has changed since the
 * last triggering.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
#define MASTER_CALLBACK_USB_VOLTAGE 61

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t current, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link master_set_stack_current_callback_threshold} is reached.
 * The parameter is the stack current in mA.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
#define MASTER_CALLBACK_STACK_CURRENT_REACHED 62

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link master_set_stack_voltage_callback_threshold} is reached.
 * The parameter is the stack voltage in mV.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
#define MASTER_CALLBACK_STACK_VOLTAGE_REACHED 63

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link master_set_usb_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
#define MASTER_CALLBACK_USB_VOLTAGE_REACHED 64


/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_CHIBI 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_RS485 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_WIFI 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_ETHERNET 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_OQPSK_868_MHZ 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_OQPSK_915_MHZ 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_OQPSK_780_MHZ 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_BPSK40_915_MHZ 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_RS485_PARITY_NONE 'n'

/**
 * \ingroup BrickMaster
 */
#define MASTER_RS485_PARITY_EVEN 'e'

/**
 * \ingroup BrickMaster
 */
#define MASTER_RS485_PARITY_ODD 'o'

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_DHCP 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_STATIC_IP 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_ACCESS_POINT_DHCP 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_ACCESS_POINT_STATIC_IP 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_AD_HOC_DHCP 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_AD_HOC_STATIC_IP 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_WPA_WPA2 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_WPA_ENTERPRISE 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_WEP 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_NO_ENCRYPTION 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_FAST 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_TLS 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_TTLS 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_PEAP 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_INNER_AUTH_EAP_MSCHAP 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_INNER_AUTH_EAP_GTC 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_CERT_TYPE_CA_CERT 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_CERT_TYPE_CLIENT_CERT 8

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_CERT_TYPE_PRIVATE_KEY 16

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_DISASSOCIATED 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_ASSOCIATED 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_ASSOCIATING 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_ERROR 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_NOT_INITIALIZED_YET 255

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_POWER_MODE_FULL_SPEED 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_POWER_MODE_LOW_POWER 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_DOMAIN_CHANNEL_1TO11 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_DOMAIN_CHANNEL_1TO13 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_DOMAIN_CHANNEL_1TO14 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickMaster
 */
#define MASTER_ETHERNET_CONNECTION_DHCP 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_ETHERNET_CONNECTION_STATIC_IP 1

/**
 * \ingroup BrickMaster
 *
 * This constant is used to identify a Master Brick.
 *
 * The {@link master_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define MASTER_DEVICE_IDENTIFIER 13

/**
 * \ingroup BrickMaster
 *
 * Creates the device object \c master with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void master_create(Master *master, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickMaster
 *
 * Removes the device object \c master from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void master_destroy(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the master_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int master_get_response_expected(Master *master, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickMaster
 *
 * Changes the response expected flag of the function specified by the
 * \c function_id parameter. This flag can only be changed for setter
 * (default value: *false*) and callback configuration functions
 * (default value: *true*). For getter functions it is always enabled and
 * callbacks it is always disabled.
 *
 * Enabling the response expected flag for a setter function allows to detect
 * timeouts and other error conditions calls of this setter as well. The device
 * will then send a response for this purpose. If this flag is disabled for a
 * setter function then no response is send and errors are silently ignored,
 * because they cannot be detected.
 */
int master_set_response_expected(Master *master, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickMaster
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int master_set_response_expected_all(Master *master, bool response_expected);

/**
 * \ingroup BrickMaster
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void master_register_callback(Master *master, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickMaster
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int master_get_api_version(Master *master, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickMaster
 *
 * Returns the stack voltage in mV. The stack voltage is the
 * voltage that is supplied via the stack, i.e. it is given by a 
 * Step-Down or Step-Up Power Supply.
 */
int master_get_stack_voltage(Master *master, uint16_t *ret_voltage);

/**
 * \ingroup BrickMaster
 *
 * Returns the stack current in mA. The stack current is the
 * current that is drawn via the stack, i.e. it is given by a
 * Step-Down or Step-Up Power Supply.
 */
int master_get_stack_current(Master *master, uint16_t *ret_current);

/**
 * \ingroup BrickMaster
 *
 * Writes the extension type to the EEPROM of a specified extension. 
 * The extension is either 0 or 1 (0 is the on the bottom, 1 is the on on top, 
 * if only one extension is present use 0).
 * 
 * Possible extension types:
 * 
 * \verbatim
 *  "Type", "Description"
 * 
 *  "1",    "Chibi"
 *  "2",    "RS485"
 *  "3",    "WIFI"
 *  "4",    "Ethernet"
 * \endverbatim
 * 
 * The extension type is already set when bought and it can be set with the 
 * Brick Viewer, it is unlikely that you need this function.
 */
int master_set_extension_type(Master *master, uint8_t extension, uint32_t exttype);

/**
 * \ingroup BrickMaster
 *
 * Returns the type for a given extension as set by {@link master_set_extension_type}.
 */
int master_get_extension_type(Master *master, uint8_t extension, uint32_t *ret_exttype);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if a Chibi Extension is available to be used by the Master Brick.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_is_chibi_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the address (1-255) belonging to the Chibi Extension.
 * 
 * It is possible to set the address with the Brick Viewer and it will be 
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_set_chibi_address(Master *master, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the address as set by {@link master_set_chibi_address}.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_address(Master *master, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Sets the address (1-255) of the Chibi Master. This address is used if the
 * Chibi Extension is used as slave (i.e. it does not have a USB connection).
 * 
 * It is possible to set the address with the Brick Viewer and it will be 
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_set_chibi_master_address(Master *master, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the address as set by {@link master_set_chibi_master_address}.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_master_address(Master *master, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Sets up to 254 slave addresses. Valid addresses are in range 1-255. 0 has a
 * special meaning, it is used as list terminator and not allowed as normal slave
 * address. The address numeration (via ``num`` parameter) has to be used
 * ascending from 0. For example: If you use the Chibi Extension in Master mode
 * (i.e. the stack has an USB connection) and you want to talk to three other
 * Chibi stacks with the slave addresses 17, 23, and 42, you should call with
 * ``(0, 17)``, ``(1, 23)``, ``(2, 42)`` and ``(3, 0)``. The last call with
 * ``(3, 0)`` is a list terminator and indicates that the Chibi slave address
 * list contains 3 addresses in this case.
 * 
 * It is possible to set the addresses with the Brick Viewer, that will take care
 * of correct address numeration and list termination.
 * 
 * The slave addresses will be saved in the EEPROM of the Chibi Extension, they
 * don't have to be set on every startup.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_set_chibi_slave_address(Master *master, uint8_t num, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the slave address for a given ``num`` as set by
 * {@link master_set_chibi_slave_address}.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_slave_address(Master *master, uint8_t num, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Returns the signal strength in dBm. The signal strength updates every time a
 * packet is received.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_signal_strength(Master *master, uint8_t *ret_signal_strength);

/**
 * \ingroup BrickMaster
 *
 * Returns underrun, CRC error, no ACK and overflow error counts of the Chibi
 * communication. If these errors start rising, it is likely that either the
 * distance between two Chibi stacks is becoming too big or there are
 * interferences.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_error_log(Master *master, uint16_t *ret_underrun, uint16_t *ret_crc_error, uint16_t *ret_no_ack, uint16_t *ret_overflow);

/**
 * \ingroup BrickMaster
 *
 * Sets the Chibi frequency range for the Chibi Extension. Possible values are:
 * 
 * \verbatim
 *  "Type", "Description"
 * 
 *  "0",    "OQPSK 868MHz (Europe)"
 *  "1",    "OQPSK 915MHz (US)"
 *  "2",    "OQPSK 780MHz (China)"
 *  "3",    "BPSK40 915MHz"
 * \endverbatim
 * 
 * It is possible to set the frequency with the Brick Viewer and it will be 
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_set_chibi_frequency(Master *master, uint8_t frequency);

/**
 * \ingroup BrickMaster
 *
 * Returns the frequency value as set by {@link master_set_chibi_frequency}.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_frequency(Master *master, uint8_t *ret_frequency);

/**
 * \ingroup BrickMaster
 *
 * Sets the channel used by the Chibi Extension. Possible channels are
 * different for different frequencies:
 * 
 * \verbatim
 *  "Frequency",             "Possible Channels"
 * 
 *  "OQPSK 868MHz (Europe)", "0"
 *  "OQPSK 915MHz (US)",     "1, 2, 3, 4, 5, 6, 7, 8, 9, 10"
 *  "OQPSK 780MHz (China)",  "0, 1, 2, 3"
 *  "BPSK40 915MHz",         "1, 2, 3, 4, 5, 6, 7, 8, 9, 10"
 * \endverbatim
 * 
 * It is possible to set the channel with the Brick Viewer and it will be 
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_set_chibi_channel(Master *master, uint8_t channel);

/**
 * \ingroup BrickMaster
 *
 * Returns the channel as set by {@link master_set_chibi_channel}.
 * 
 * .. versionadded:: 1.1.0~(Firmware)
 */
int master_get_chibi_channel(Master *master, uint8_t *ret_channel);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if a RS485 Extension is available to be used by the Master Brick.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_is_rs485_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the address (0-255) belonging to the RS485 Extension.
 * 
 * Set to 0 if the RS485 Extension should be the RS485 Master (i.e.
 * connected to a PC via USB).
 * 
 * It is possible to set the address with the Brick Viewer and it will be 
 * saved in the EEPROM of the RS485 Extension, it does not
 * have to be set on every startup.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_set_rs485_address(Master *master, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the address as set by {@link master_set_rs485_address}.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_get_rs485_address(Master *master, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Sets up to 255 slave addresses. Valid addresses are in range 1-255. 0 has a
 * special meaning, it is used as list terminator and not allowed as normal slave
 * address. The address numeration (via ``num`` parameter) has to be used
 * ascending from 0. For example: If you use the RS485 Extension in Master mode
 * (i.e. the stack has an USB connection) and you want to talk to three other
 * RS485 stacks with the addresses 17, 23, and 42, you should call with
 * ``(0, 17)``, ``(1, 23)``, ``(2, 42)`` and ``(3, 0)``. The last call with
 * ``(3, 0)`` is a list terminator and indicates that the RS485 slave address list
 * contains 3 addresses in this case.
 * 
 * It is possible to set the addresses with the Brick Viewer, that will take care
 * of correct address numeration and list termination.
 * 
 * The slave addresses will be saved in the EEPROM of the Chibi Extension, they
 * don't have to be set on every startup.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_set_rs485_slave_address(Master *master, uint8_t num, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the slave address for a given ``num`` as set by
 * {@link master_set_rs485_slave_address}.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_get_rs485_slave_address(Master *master, uint8_t num, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Returns CRC error counts of the RS485 communication.
 * If this counter starts rising, it is likely that the distance
 * between the RS485 nodes is too big or there is some kind of
 * interference.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_get_rs485_error_log(Master *master, uint16_t *ret_crc_error);

/**
 * \ingroup BrickMaster
 *
 * Sets the configuration of the RS485 Extension. Speed is given in baud. The
 * Master Brick will try to match the given baud rate as exactly as possible.
 * The maximum recommended baud rate is 2000000 (2Mbit/s).
 * Possible values for parity are 'n' (none), 'e' (even) and 'o' (odd).
 * Possible values for stop bits are 1 and 2.
 * 
 * If your RS485 is unstable (lost messages etc.), the first thing you should
 * try is to decrease the speed. On very large bus (e.g. 1km), you probably
 * should use a value in the range of 100000 (100kbit/s).
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_set_rs485_configuration(Master *master, uint32_t speed, char parity, uint8_t stopbits);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_rs485_configuration}.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_get_rs485_configuration(Master *master, uint32_t *ret_speed, char *ret_parity, uint8_t *ret_stopbits);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if a WIFI Extension is available to be used by the Master Brick.
 * 
 * .. versionadded:: 1.2.0~(Firmware)
 */
int master_is_wifi_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the configuration of the WIFI Extension. The ``ssid`` can have a max length
 * of 32 characters. Possible values for ``connection`` are:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "DHCP"
 *  "1", "Static IP"
 *  "2", "Access Point: DHCP"
 *  "3", "Access Point: Static IP"
 *  "4", "Ad Hoc: DHCP"
 *  "5", "Ad Hoc: Static IP"
 * \endverbatim
 * 
 * If you set ``connection`` to one of the static IP options then you have to
 * supply ``ip``, ``subnet_mask`` and ``gateway`` as an array of size 4 (first
 * element of the array is the least significant byte of the address). If
 * ``connection`` is set to one of the DHCP options then ``ip``, ``subnet_mask``
 * and ``gateway`` are ignored, you can set them to 0.
 * 
 * The last parameter is the port that your program will connect to. The
 * default port, that is used by brickd, is 4223.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the WIFI configuration.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_set_wifi_configuration(Master *master, const char ssid[32], uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_wifi_configuration}.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_get_wifi_configuration(Master *master, char ret_ssid[32], uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port);

/**
 * \ingroup BrickMaster
 *
 * Sets the encryption of the WIFI Extension. The first parameter is the
 * type of the encryption. Possible values are:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "WPA/WPA2"
 *  "1", "WPA Enterprise (EAP-FAST, EAP-TLS, EAP-TTLS, PEAP)"
 *  "2", "WEP"
 *  "3", "No Encryption"
 * \endverbatim
 * 
 * The ``key`` has a max length of 50 characters and is used if ``encryption``
 * is set to 0 or 2 (WPA/WPA2 or WEP). Otherwise the value is ignored.
 * 
 * For WPA/WPA2 the key has to be at least 8 characters long. If you want to set
 * a key with more than 50 characters, see {@link master_set_long_wifi_key}.
 * 
 * For WEP the key has to be either 10 or 26 hexadecimal digits long. It is
 * possible to set the WEP ``key_index`` (1-4). If you don't know your
 * ``key_index``, it is likely 1.
 * 
 * If you choose WPA Enterprise as encryption, you have to set ``eap_options`` and
 * the length of the certificates (for other encryption types these parameters
 * are ignored). The certificate length are given in byte and the certificates
 * themselves can be set with {@link master_set_wifi_certificate}. ``eap_options`` consist
 * of the outer authentication (bits 1-2), inner authentication (bit 3) and
 * certificate type (bits 4-5):
 * 
 * \verbatim
 *  "Option", "Bits", "Description"
 * 
 *  "outer authentication", "1-2", "0=EAP-FAST, 1=EAP-TLS, 2=EAP-TTLS, 3=EAP-PEAP"
 *  "inner authentication", "3", "0=EAP-MSCHAP, 1=EAP-GTC"
 *  "certificate type", "4-5", "0=CA Certificate, 1=Client Certificate, 2=Private Key"
 * \endverbatim
 * 
 * Example for EAP-TTLS + EAP-GTC + Private Key: ``option = 2 | (1 << 2) | (2 << 3)``.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the WIFI encryption.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_set_wifi_encryption(Master *master, uint8_t encryption, const char key[50], uint8_t key_index, uint8_t eap_options, uint16_t ca_certificate_length, uint16_t client_certificate_length, uint16_t private_key_length);

/**
 * \ingroup BrickMaster
 *
 * Returns the encryption as set by {@link master_set_wifi_encryption}.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_get_wifi_encryption(Master *master, uint8_t *ret_encryption, char ret_key[50], uint8_t *ret_key_index, uint8_t *ret_eap_options, uint16_t *ret_ca_certificate_length, uint16_t *ret_client_certificate_length, uint16_t *ret_private_key_length);

/**
 * \ingroup BrickMaster
 *
 * Returns the status of the WIFI Extension. The ``state`` is updated automatically,
 * all of the other parameters are updated on startup and every time
 * {@link master_refresh_wifi_status} is called.
 * 
 * Possible states are:
 * 
 * \verbatim
 *  "State", "Description"
 * 
 *  "0", "Disassociated"
 *  "1", "Associated"
 *  "2", "Associating"
 *  "3", "Error"
 *  "255", "Not initialized yet"
 * \endverbatim
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_get_wifi_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_bssid[6], uint8_t *ret_channel, int16_t *ret_rssi, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, uint8_t *ret_state);

/**
 * \ingroup BrickMaster
 *
 * Refreshes the WIFI status (see {@link master_get_wifi_status}). To read the status
 * of the WIFI module, the Master Brick has to change from data mode to
 * command mode and back. This transaction and the readout itself is
 * unfortunately time consuming. This means, that it might take some ms
 * until the stack with attached WIFI Extension reacts again after this
 * function is called.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_refresh_wifi_status(Master *master);

/**
 * \ingroup BrickMaster
 *
 * This function is used to set the certificate as well as password and username
 * for WPA Enterprise. To set the username use index 0xFFFF,
 * to set the password use index 0xFFFE. The max length of username and 
 * password is 32.
 * 
 * The certificate is written in chunks of size 32 and the index is used as
 * the index of the chunk. ``data_length`` should nearly always be 32. Only
 * the last chunk can have a length that is not equal to 32.
 * 
 * The starting index of the CA Certificate is 0, of the Client Certificate
 * 10000 and for the Private Key 20000. Maximum sizes are 1312, 1312 and
 * 4320 byte respectively.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after uploading the certificate.
 * 
 * It is recommended to use the Brick Viewer to set the certificate, username
 * and password.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_set_wifi_certificate(Master *master, uint16_t index, uint8_t data[32], uint8_t data_length);

/**
 * \ingroup BrickMaster
 *
 * Returns the certificate for a given index as set by {@link master_set_wifi_certificate}.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_get_wifi_certificate(Master *master, uint16_t index, uint8_t ret_data[32], uint8_t *ret_data_length);

/**
 * \ingroup BrickMaster
 *
 * Sets the power mode of the WIFI Extension. Possible modes are:
 * 
 * \verbatim
 *  "Mode", "Description"
 * 
 *  "0", "Full Speed (high power consumption, high throughput)"
 *  "1", "Low Power (low power consumption, low throughput)"
 * \endverbatim
 * 
 * The default value is 0 (Full Speed).
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_set_wifi_power_mode(Master *master, uint8_t mode);

/**
 * \ingroup BrickMaster
 *
 * Returns the power mode as set by {@link master_set_wifi_power_mode}.
 * 
 * .. versionadded:: 1.3.0~(Firmware)
 */
int master_get_wifi_power_mode(Master *master, uint8_t *ret_mode);

/**
 * \ingroup BrickMaster
 *
 * Returns informations about the WIFI receive buffer. The WIFI
 * receive buffer has a max size of 1500 byte and if data is transfered
 * too fast, it might overflow.
 * 
 * The return values are the number of overflows, the low watermark 
 * (i.e. the smallest number of bytes that were free in the buffer) and
 * the bytes that are currently used.
 * 
 * You should always try to keep the buffer empty, otherwise you will
 * have a permanent latency. A good rule of thumb is, that you can transfer
 * 1000 messages per second without problems.
 * 
 * Try to not send more then 50 messages at a time without any kind of
 * break between them.
 * 
 * .. versionadded:: 1.3.2~(Firmware)
 */
int master_get_wifi_buffer_info(Master *master, uint32_t *ret_overflow, uint16_t *ret_low_watermark, uint16_t *ret_used);

/**
 * \ingroup BrickMaster
 *
 * Sets the regulatory domain of the WIFI Extension. Possible domains are:
 * 
 * \verbatim
 *  "Domain", "Description"
 * 
 *  "0", "FCC: Channel 1-11 (N/S America, Australia, New Zealand)"
 *  "1", "ETSI: Channel 1-13 (Europe, Middle East, Africa)"
 *  "2", "TELEC: Channel 1-14 (Japan)"
 * \endverbatim
 * 
 * The default value is 1 (ETSI).
 * 
 * .. versionadded:: 1.3.4~(Firmware)
 */
int master_set_wifi_regulatory_domain(Master *master, uint8_t domain);

/**
 * \ingroup BrickMaster
 *
 * Returns the regulatory domain as set by {@link master_set_wifi_regulatory_domain}.
 * 
 * .. versionadded:: 1.3.4~(Firmware)
 */
int master_get_wifi_regulatory_domain(Master *master, uint8_t *ret_domain);

/**
 * \ingroup BrickMaster
 *
 * Returns the USB voltage in mV.
 * 
 * .. versionadded:: 1.3.5~(Firmware)
 */
int master_get_usb_voltage(Master *master, uint16_t *ret_voltage);

/**
 * \ingroup BrickMaster
 *
 * Sets a long WIFI key (up to 63 chars, at least 8 chars) for WPA encryption.
 * This key will be used
 * if the key in {@link master_set_wifi_encryption} is set to "-". In the old protocol,
 * a payload of size 63 was not possible, so the maximum key length was 50 chars.
 * 
 * With the new protocol this is possible, since we didn't want to break API,
 * this function was added additionally.
 * 
 * .. versionadded:: 2.0.2~(Firmware)
 */
int master_set_long_wifi_key(Master *master, const char key[64]);

/**
 * \ingroup BrickMaster
 *
 * Returns the encryption key as set by {@link master_set_long_wifi_key}.
 * 
 * .. versionadded:: 2.0.2~(Firmware)
 */
int master_get_long_wifi_key(Master *master, char ret_key[64]);

/**
 * \ingroup BrickMaster
 *
 * Sets the hostname of the WIFI Extension. The hostname will be displayed 
 * by access points as the hostname in the DHCP clients table.
 * 
 * Setting an empty String will restore the default hostname.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_wifi_hostname(Master *master, const char hostname[16]);

/**
 * \ingroup BrickMaster
 *
 * Returns the hostname as set by {@link master_get_wifi_hostname}.
 * 
 * An empty String means, that the default hostname is used.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_wifi_hostname(Master *master, char ret_hostname[16]);

/**
 * \ingroup BrickMaster
 *
 * Sets the period in ms with which the {@link MASTER_CALLBACK_STACK_CURRENT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link MASTER_CALLBACK_STACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 * 
 * The default value is 0.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_stack_current_callback_period(Master *master, uint32_t period);

/**
 * \ingroup BrickMaster
 *
 * Returns the period as set by :func:`SetCurrentCallbackPeriod`.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_stack_current_callback_period(Master *master, uint32_t *ret_period);

/**
 * \ingroup BrickMaster
 *
 * Sets the period in ms with which the {@link MASTER_CALLBACK_STACK_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link MASTER_CALLBACK_STACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_stack_voltage_callback_period(Master *master, uint32_t period);

/**
 * \ingroup BrickMaster
 *
 * Returns the period as set by {@link master_set_stack_voltage_callback_period}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_stack_voltage_callback_period(Master *master, uint32_t *ret_period);

/**
 * \ingroup BrickMaster
 *
 * Sets the period in ms with which the {@link MASTER_CALLBACK_USB_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link MASTER_CALLBACK_USB_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_usb_voltage_callback_period(Master *master, uint32_t period);

/**
 * \ingroup BrickMaster
 *
 * Returns the period as set by {@link master_set_usb_voltage_callback_period}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_usb_voltage_callback_period(Master *master, uint32_t *ret_period);

/**
 * \ingroup BrickMaster
 *
 * Sets the thresholds for the {@link MASTER_CALLBACK_STACK_CURRENT_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the current is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the current is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the current is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the current is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_stack_current_callback_threshold(Master *master, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickMaster
 *
 * Returns the threshold as set by {@link master_set_stack_current_callback_threshold}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_stack_current_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickMaster
 *
 * Sets the thresholds for the :func:`StackStackVoltageReached` callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the voltage is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the voltage is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the voltage is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the voltage is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_stack_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickMaster
 *
 * Returns the threshold as set by {@link master_set_stack_voltage_callback_threshold}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_stack_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickMaster
 *
 * Sets the thresholds for the {@link MASTER_CALLBACK_USB_VOLTAGE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the voltage is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the voltage is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the voltage is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the voltage is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_usb_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickMaster
 *
 * Returns the threshold as set by {@link master_set_usb_voltage_callback_threshold}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_usb_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickMaster
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link MASTER_CALLBACK_STACK_CURRENT_REACHED},
 * * {@link MASTER_CALLBACK_STACK_VOLTAGE_REACHED},
 * * {@link MASTER_CALLBACK_USB_VOLTAGE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link master_set_stack_current_callback_threshold},
 * * {@link master_set_stack_voltage_callback_threshold},
 * * {@link master_set_usb_voltage_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_set_debounce_period(Master *master, uint32_t debounce);

/**
 * \ingroup BrickMaster
 *
 * Returns the debounce period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5~(Firmware)
 */
int master_get_debounce_period(Master *master, uint32_t *ret_debounce);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if a Ethernet Extension is available to be used by the Master
 * Brick.
 * 
 * .. versionadded:: 2.1.0~(Firmware)
 */
int master_is_ethernet_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the configuration of the Ethernet Extension. Possible values for
 * ``connection`` are:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "DHCP"
 *  "1", "Static IP"
 * \endverbatim
 * 
 * If you set ``connection`` to static IP options then you have to supply ``ip``,
 * ``subnet_mask`` and ``gateway`` as an array of size 4 (first element of the
 * array is the least significant byte of the address). If ``connection`` is set
 * to the DHCP options then ``ip``, ``subnet_mask`` and ``gateway`` are ignored,
 * you can set them to 0.
 * 
 * The last parameter is the port that your program will connect to. The
 * default port, that is used by brickd, is 4223.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the Ethernet configuration.
 * 
 * .. versionadded:: 2.1.0~(Firmware)
 */
int master_set_ethernet_configuration(Master *master, uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_ethernet_configuration}.
 * 
 * .. versionadded:: 2.1.0~(Firmware)
 */
int master_get_ethernet_configuration(Master *master, uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port);

/**
 * \ingroup BrickMaster
 *
 * Returns the status of the Ethernet Extension.
 * 
 * ``mac_address``, ``ip``, ``subnet_mask`` and ``gateway`` are given as an array.
 * The first element of the array is the least significant byte of the address.
 * 
 * ``rx_count`` and ``tx_count`` are the number of bytes that have been
 * received/send since last restart.
 * 
 * ``hostname`` is the currently used hostname.
 * 
 * .. versionadded:: 2.1.0~(Firmware)
 */
int master_get_ethernet_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, char ret_hostname[32]);

/**
 * \ingroup BrickMaster
 *
 * Sets the hostname of the Ethernet Extension. The hostname will be displayed 
 * by access points as the hostname in the DHCP clients table.
 * 
 * Setting an empty String will restore the default hostname.
 * 
 * The current hostname can be discovered with {@link master_get_ethernet_status}.
 * 
 * .. versionadded:: 2.1.0~(Firmware)
 */
int master_set_ethernet_hostname(Master *master, const char hostname[32]);

/**
 * \ingroup BrickMaster
 *
 * Sets the MAC address of the Ethernet Extension. The Ethernet Extension should
 * come configured with a valid MAC address, that is also written on a
 * sticker of the extension itself.
 * 
 * The MAC address can be read out again with {@link master_get_ethernet_status}.
 * 
 * .. versionadded:: 2.1.0~(Firmware)
 */
int master_set_ethernet_mac_address(Master *master, uint8_t mac_address[6]);

/**
 * \ingroup BrickMaster
 *
 * Returns the firmware and protocol version and the name of the Bricklet for a
 * given port.
 * 
 * This functions sole purpose is to allow automatic flashing of v1.x.y Bricklet
 * plugins.
 * 
 * .. versionadded:: 2.0.0~(Firmware)
 */
int master_get_protocol1_bricklet_name(Master *master, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]);

/**
 * \ingroup BrickMaster
 *
 * Returns the temperature in °C/10 as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has an
 * accuracy of +-15%. Practically it is only useful as an indicator for
 * temperature changes.
 * 
 * .. versionadded:: 1.2.1~(Firmware)
 */
int master_get_chip_temperature(Master *master, int16_t *ret_temperature);

/**
 * \ingroup BrickMaster
 *
 * Calling this function will reset the Brick. Calling this function
 * on a Brick inside of a stack will reset the whole stack.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 * 
 * .. versionadded:: 1.2.1~(Firmware)
 */
int master_reset(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Returns the UID, the UID where the Brick is connected to, 
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position can be '0'-'8' (stack position).
 * 
 * The device identifiers can be found :ref:`here <device_identifier>`.
 * 
 * .. versionadded:: 2.0.0~(Firmware)
 */
int master_get_identity(Master *master, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

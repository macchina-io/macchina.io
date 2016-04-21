/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_RS232_H
#define BRICKLET_RS232_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRS232 RS232 Bricklet
 */

/**
 * \ingroup BrickletRS232
 *
 * Communicates with RS232 devices
 */
typedef Device RS232;

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_WRITE 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_READ 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_ENABLE_READ_CALLBACK 3

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_DISABLE_READ_CALLBACK 4

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_IS_READ_CALLBACK_ENABLED 5

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_SET_CONFIGURATION 6

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_GET_CONFIGURATION 7

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_SET_BREAK_CONDITION 10

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(char ret_message[60], uint8_t length, void *user_data) \endcode
 * 
 * This callback is called if new data is available. The message has
 * a maximum size of 60 characters. The actual length of the message
 * is given in addition.
 * 
 * To enable this callback, use {@link rs232_enable_read_callback}.
 */
#define RS232_CALLBACK_READ_CALLBACK 8

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(uint8_t error, void *user_data) \endcode
 * 
 * This callback is called if an error occurs. 
 * Possible errors are overrun, parity or framing error.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define RS232_CALLBACK_ERROR_CALLBACK 9


/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_300 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_600 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_1200 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_2400 3

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_4800 4

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_9600 5

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_14400 6

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_19200 7

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_28800 8

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_38400 9

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_57600 10

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_115200 11

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_230400 12

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_NONE 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_ODD 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_EVEN 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_FORCED_PARITY_1 3

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_FORCED_PARITY_0 4

/**
 * \ingroup BrickletRS232
 */
#define RS232_STOPBITS_1 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_STOPBITS_2 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_5 5

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_6 6

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_7 7

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_8 8

/**
 * \ingroup BrickletRS232
 */
#define RS232_HARDWARE_FLOWCONTROL_OFF 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_HARDWARE_FLOWCONTROL_ON 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_SOFTWARE_FLOWCONTROL_OFF 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_SOFTWARE_FLOWCONTROL_ON 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_ERROR_OVERRUN 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_ERROR_PARITY 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_ERROR_FRAMING 4

/**
 * \ingroup BrickletRS232
 *
 * This constant is used to identify a RS232 Bricklet.
 *
 * The {@link rs232_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define RS232_DEVICE_IDENTIFIER 254

/**
 * \ingroup BrickletRS232
 *
 * This constant represents the display name of a RS232 Bricklet.
 */
#define RS232_DEVICE_DISPLAY_NAME "RS232 Bricklet"

/**
 * \ingroup BrickletRS232
 *
 * Creates the device object \c rs232 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void rs232_create(RS232 *rs232, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRS232
 *
 * Removes the device object \c rs232 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void rs232_destroy(RS232 *rs232);

/**
 * \ingroup BrickletRS232
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the rs232_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int rs232_get_response_expected(RS232 *rs232, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRS232
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
int rs232_set_response_expected(RS232 *rs232, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRS232
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int rs232_set_response_expected_all(RS232 *rs232, bool response_expected);

/**
 * \ingroup BrickletRS232
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void rs232_register_callback(RS232 *rs232, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletRS232
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int rs232_get_api_version(RS232 *rs232, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRS232
 *
 * Writes a string of up to 60 characters to the RS232 interface. The string
 * can be binary data, ASCII or similar is not necessary.
 * 
 * The length of the string has to be given as an additional parameter.
 * 
 * The return value is the number of bytes that could be written.
 * 
 * See :func:`SetConfigurations` for configuration possibilities
 * regarding baudrate, parity and so on.
 */
int rs232_write(RS232 *rs232, char message[60], uint8_t length, uint8_t *ret_written);

/**
 * \ingroup BrickletRS232
 *
 * Returns the currently buffered message. The maximum length
 * of message is 60. If the length is given as 0, there was no
 * new data available.
 * 
 * Instead of polling with this function, you can also use
 * callbacks. See {@link rs232_enable_read_callback} and {@link RS232_CALLBACK_READ_CALLBACK}.
 */
int rs232_read(RS232 *rs232, char ret_message[60], uint8_t *ret_length);

/**
 * \ingroup BrickletRS232
 *
 * Enables the {@link RS232_CALLBACK_READ_CALLBACK}.
 * 
 * By default the callback is disabled.
 */
int rs232_enable_read_callback(RS232 *rs232);

/**
 * \ingroup BrickletRS232
 *
 * Disables the {@link RS232_CALLBACK_READ_CALLBACK}.
 * 
 * By default the callback is disabled.
 */
int rs232_disable_read_callback(RS232 *rs232);

/**
 * \ingroup BrickletRS232
 *
 * Returns *true* if the {@link RS232_CALLBACK_READ_CALLBACK} is enabled,
 * *false* otherwise.
 */
int rs232_is_read_callback_enabled(RS232 *rs232, bool *ret_enabled);

/**
 * \ingroup BrickletRS232
 *
 * Sets the configuration for the RS232 communication. Available options:
 * 
 * * Baudrate between 300 and 230400 baud.
 * * Parity of none, odd, even or forced parity.
 * * Stopbits can be 1 or 2.
 * * Word length of 5 to 8.
 * * Hard-/Software flow control can each be on or off.
 * 
 * The default is: 115200 baud, parity none, 1 stop bit, word length 8, hard-/software flow control off.
 */
int rs232_set_configuration(RS232 *rs232, uint8_t baudrate, uint8_t parity, uint8_t stopbits, uint8_t wordlength, uint8_t hardware_flowcontrol, uint8_t software_flowcontrol);

/**
 * \ingroup BrickletRS232
 *
 * Returns the configuration as set by {@link rs232_set_configuration}.
 */
int rs232_get_configuration(RS232 *rs232, uint8_t *ret_baudrate, uint8_t *ret_parity, uint8_t *ret_stopbits, uint8_t *ret_wordlength, uint8_t *ret_hardware_flowcontrol, uint8_t *ret_software_flowcontrol);

/**
 * \ingroup BrickletRS232
 *
 * Sets a break condition (the TX output is forced to a logic 0 state). 
 * The parameter sets the hold-time of the break condition (in ms). 
 * 
 * .. versionadded:: 2.0.2$nbsp;(Plugin)
 */
int rs232_set_break_condition(RS232 *rs232, uint16_t break_time);

/**
 * \ingroup BrickletRS232
 *
 * Returns the UID, the UID where the Bricklet is connected to, 
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position can be 'a', 'b', 'c' or 'd'.
 * 
 * The device identifier numbers can be found :ref:`here <device_identifier>`.
 * |device_identifier_constant|
 */
int rs232_get_identity(RS232 *rs232, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

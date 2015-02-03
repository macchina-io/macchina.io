/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_ANALOG_OUT_H
#define BRICKLET_ANALOG_OUT_H

#include "ip_connection.h"

/**
 * \defgroup BrickletAnalogOut AnalogOut Bricklet
 */

/**
 * \ingroup BrickletAnalogOut
 *
 * Device for output of voltage between 0 and 5V
 */
typedef Device AnalogOut;

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_FUNCTION_SET_VOLTAGE 1

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_FUNCTION_GET_VOLTAGE 2

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_FUNCTION_SET_MODE 3

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_FUNCTION_GET_MODE 4

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_MODE_ANALOG_VALUE 0

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_MODE_1K_TO_GROUND 1

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_MODE_100K_TO_GROUND 2

/**
 * \ingroup BrickletAnalogOut
 */
#define ANALOG_OUT_MODE_500K_TO_GROUND 3

/**
 * \ingroup BrickletAnalogOut
 *
 * This constant is used to identify a AnalogOut Bricklet.
 *
 * The {@link analog_out_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ANALOG_OUT_DEVICE_IDENTIFIER 220

/**
 * \ingroup BrickletAnalogOut
 *
 * Creates the device object \c analog_out with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void analog_out_create(AnalogOut *analog_out, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletAnalogOut
 *
 * Removes the device object \c analog_out from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void analog_out_destroy(AnalogOut *analog_out);

/**
 * \ingroup BrickletAnalogOut
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the analog_out_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int analog_out_get_response_expected(AnalogOut *analog_out, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletAnalogOut
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
int analog_out_set_response_expected(AnalogOut *analog_out, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletAnalogOut
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int analog_out_set_response_expected_all(AnalogOut *analog_out, bool response_expected);


/**
 * \ingroup BrickletAnalogOut
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int analog_out_get_api_version(AnalogOut *analog_out, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletAnalogOut
 *
 * Sets the voltage in mV. The possible range is 0V to 5V (0-5000).
 * Calling this function will set the mode to 0 (see {@link analog_out_set_mode}).
 * 
 * The default value is 0 (with mode 1).
 */
int analog_out_set_voltage(AnalogOut *analog_out, uint16_t voltage);

/**
 * \ingroup BrickletAnalogOut
 *
 * Returns the voltage as set by {@link analog_out_set_voltage}.
 */
int analog_out_get_voltage(AnalogOut *analog_out, uint16_t *ret_voltage);

/**
 * \ingroup BrickletAnalogOut
 *
 * Sets the mode of the analog value. Possible modes:
 * 
 * * 0: Normal Mode (Analog value as set by {@link analog_out_set_voltage} is applied)
 * * 1: 1k Ohm resistor to ground
 * * 2: 100k Ohm resistor to ground
 * * 3: 500k Ohm resistor to ground
 * 
 * Setting the mode to 0 will result in an output voltage of 0. You can jump
 * to a higher output voltage directly by calling {@link analog_out_set_voltage}.
 * 
 * The default mode is 1.
 */
int analog_out_set_mode(AnalogOut *analog_out, uint8_t mode);

/**
 * \ingroup BrickletAnalogOut
 *
 * Returns the mode as set by {@link analog_out_set_mode}.
 */
int analog_out_get_mode(AnalogOut *analog_out, uint8_t *ret_mode);

/**
 * \ingroup BrickletAnalogOut
 *
 * Returns the UID, the UID where the Bricklet is connected to, 
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position can be 'a', 'b', 'c' or 'd'.
 * 
 * The device identifiers can be found :ref:`here <device_identifier>`.
 * 
 * .. versionadded:: 2.0.0~(Plugin)
 */
int analog_out_get_identity(AnalogOut *analog_out, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

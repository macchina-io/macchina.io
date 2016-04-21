/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_ANALOG_OUT_V2_H
#define BRICKLET_ANALOG_OUT_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletAnalogOutV2 Analog Out Bricklet 2.0
 */

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Generates configurable DC voltage between 0V and 12V
 */
typedef Device AnalogOutV2;

/**
 * \ingroup BrickletAnalogOutV2
 */
#define ANALOG_OUT_V2_FUNCTION_SET_OUTPUT_VOLTAGE 1

/**
 * \ingroup BrickletAnalogOutV2
 */
#define ANALOG_OUT_V2_FUNCTION_GET_OUTPUT_VOLTAGE 2

/**
 * \ingroup BrickletAnalogOutV2
 */
#define ANALOG_OUT_V2_FUNCTION_GET_INPUT_VOLTAGE 3

/**
 * \ingroup BrickletAnalogOutV2
 */
#define ANALOG_OUT_V2_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletAnalogOutV2
 *
 * This constant is used to identify a Analog Out Bricklet 2.0.
 *
 * The {@link analog_out_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ANALOG_OUT_V2_DEVICE_IDENTIFIER 256

/**
 * \ingroup BrickletAnalogOutV2
 *
 * This constant represents the display name of a Analog Out Bricklet 2.0.
 */
#define ANALOG_OUT_V2_DEVICE_DISPLAY_NAME "Analog Out Bricklet 2.0"

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Creates the device object \c analog_out_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void analog_out_v2_create(AnalogOutV2 *analog_out_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Removes the device object \c analog_out_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void analog_out_v2_destroy(AnalogOutV2 *analog_out_v2);

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the analog_out_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int analog_out_v2_get_response_expected(AnalogOutV2 *analog_out_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletAnalogOutV2
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
int analog_out_v2_set_response_expected(AnalogOutV2 *analog_out_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int analog_out_v2_set_response_expected_all(AnalogOutV2 *analog_out_v2, bool response_expected);


/**
 * \ingroup BrickletAnalogOutV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int analog_out_v2_get_api_version(AnalogOutV2 *analog_out_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Sets the voltage in mV. The possible range is 0V to 12V (0-12000).
 */
int analog_out_v2_set_output_voltage(AnalogOutV2 *analog_out_v2, uint16_t voltage);

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Returns the voltage as set by {@link analog_out_v2_set_output_voltage}.
 */
int analog_out_v2_get_output_voltage(AnalogOutV2 *analog_out_v2, uint16_t *ret_voltage);

/**
 * \ingroup BrickletAnalogOutV2
 *
 * Returns the input voltage in mV.
 */
int analog_out_v2_get_input_voltage(AnalogOutV2 *analog_out_v2, uint16_t *ret_voltage);

/**
 * \ingroup BrickletAnalogOutV2
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
int analog_out_v2_get_identity(AnalogOutV2 *analog_out_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

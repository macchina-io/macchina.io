/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_ANALOG_OUT_H
#define BRICKLET_INDUSTRIAL_ANALOG_OUT_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialAnalogOut Industrial Analog Out Bricklet
 */

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Generates configurable DC voltage and current, 0V to 10V and 4mA to 20mA
 */
typedef Device IndustrialAnalogOut;

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_ENABLE 1

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_DISABLE 2

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_IS_ENABLED 3

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_VOLTAGE 4

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_VOLTAGE 5

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_CURRENT 6

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_CURRENT 7

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_SET_CONFIGURATION 8

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_CONFIGURATION 9

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_VOLTAGE_RANGE_0_TO_5V 0

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_VOLTAGE_RANGE_0_TO_10V 1

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_CURRENT_RANGE_4_TO_20MA 0

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_CURRENT_RANGE_0_TO_20MA 1

/**
 * \ingroup BrickletIndustrialAnalogOut
 */
#define INDUSTRIAL_ANALOG_OUT_CURRENT_RANGE_0_TO_24MA 2

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * This constant is used to identify a Industrial Analog Out Bricklet.
 *
 * The {@link industrial_analog_out_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_ANALOG_OUT_DEVICE_IDENTIFIER 258

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * This constant represents the display name of a Industrial Analog Out Bricklet.
 */
#define INDUSTRIAL_ANALOG_OUT_DEVICE_DISPLAY_NAME "Industrial Analog Out Bricklet"

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Creates the device object \c industrial_analog_out with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_analog_out_create(IndustrialAnalogOut *industrial_analog_out, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Removes the device object \c industrial_analog_out from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_analog_out_destroy(IndustrialAnalogOut *industrial_analog_out);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_analog_out_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_analog_out_get_response_expected(IndustrialAnalogOut *industrial_analog_out, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialAnalogOut
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
int industrial_analog_out_set_response_expected(IndustrialAnalogOut *industrial_analog_out, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_analog_out_set_response_expected_all(IndustrialAnalogOut *industrial_analog_out, bool response_expected);


/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_analog_out_get_api_version(IndustrialAnalogOut *industrial_analog_out, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Enables the output of voltage and current.
 * 
 * The default is disabled.
 */
int industrial_analog_out_enable(IndustrialAnalogOut *industrial_analog_out);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Disables the output of voltage and current.
 * 
 * The default is disabled.
 */
int industrial_analog_out_disable(IndustrialAnalogOut *industrial_analog_out);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Returns *true* if output of voltage and current is enabled, *false* otherwise.
 */
int industrial_analog_out_is_enabled(IndustrialAnalogOut *industrial_analog_out, bool *ret_enabled);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Sets the output voltage in mV.
 * 
 * The output voltage and output current are linked. Changing the output voltage
 * also changes the output current.
 */
int industrial_analog_out_set_voltage(IndustrialAnalogOut *industrial_analog_out, uint16_t voltage);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Returns the voltage as set by {@link industrial_analog_out_set_voltage}.
 */
int industrial_analog_out_get_voltage(IndustrialAnalogOut *industrial_analog_out, uint16_t *ret_voltage);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Sets the output current in µA.
 * 
 * The output current and output voltage are linked. Changing the output current
 * also changes the output voltage.
 */
int industrial_analog_out_set_current(IndustrialAnalogOut *industrial_analog_out, uint16_t current);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Returns the current as set by {@link industrial_analog_out_set_current}.
 */
int industrial_analog_out_get_current(IndustrialAnalogOut *industrial_analog_out, uint16_t *ret_current);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Configures the voltage and current range.
 * 
 * Possible voltage ranges are:
 * 
 * * 0V to 5V
 * * 0V to 10V (default)
 * 
 * Possible current ranges are:
 * 
 * * 4mA to 20mA (default)
 * * 0mA to 20mA
 * * 0mA to 24mA
 * 
 * The resolution will always be 12 bit. This means, that the
 * precision is higher with a smaller range.
 */
int industrial_analog_out_set_configuration(IndustrialAnalogOut *industrial_analog_out, uint8_t voltage_range, uint8_t current_range);

/**
 * \ingroup BrickletIndustrialAnalogOut
 *
 * Returns the configuration as set by {@link industrial_analog_out_set_configuration}.
 */
int industrial_analog_out_get_configuration(IndustrialAnalogOut *industrial_analog_out, uint8_t *ret_voltage_range, uint8_t *ret_current_range);

/**
 * \ingroup BrickletIndustrialAnalogOut
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
int industrial_analog_out_get_identity(IndustrialAnalogOut *industrial_analog_out, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

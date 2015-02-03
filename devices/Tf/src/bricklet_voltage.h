/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_VOLTAGE_H
#define BRICKLET_VOLTAGE_H

#include "ip_connection.h"

/**
 * \defgroup BrickletVoltage Voltage Bricklet
 */

/**
 * \ingroup BrickletVoltage
 *
 * Device for sensing Voltages between 0 and 50V
 */
typedef Device Voltage;

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_VOLTAGE 1

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_ANALOG_VALUE 2

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletVoltage
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link voltage_set_voltage_callback_period}. The parameter is the voltage of the
 * sensor.
 * 
 * {@link VOLTAGE_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define VOLTAGE_CALLBACK_VOLTAGE 13

/**
 * \ingroup BrickletVoltage
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link voltage_set_analog_value_callback_period}. The parameter is the analog value of the
 * sensor.
 * 
 * {@link VOLTAGE_CALLBACK_ANALOG_VALUE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define VOLTAGE_CALLBACK_ANALOG_VALUE 14

/**
 * \ingroup BrickletVoltage
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link voltage_set_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link voltage_set_debounce_period}.
 */
#define VOLTAGE_CALLBACK_VOLTAGE_REACHED 15

/**
 * \ingroup BrickletVoltage
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link voltage_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link voltage_set_debounce_period}.
 */
#define VOLTAGE_CALLBACK_ANALOG_VALUE_REACHED 16


/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletVoltage
 */
#define VOLTAGE_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletVoltage
 *
 * This constant is used to identify a Voltage Bricklet.
 *
 * The {@link voltage_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define VOLTAGE_DEVICE_IDENTIFIER 218

/**
 * \ingroup BrickletVoltage
 *
 * Creates the device object \c voltage with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void voltage_create(Voltage *voltage, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletVoltage
 *
 * Removes the device object \c voltage from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void voltage_destroy(Voltage *voltage);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the voltage_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int voltage_get_response_expected(Voltage *voltage, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletVoltage
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
int voltage_set_response_expected(Voltage *voltage, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletVoltage
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int voltage_set_response_expected_all(Voltage *voltage, bool response_expected);

/**
 * \ingroup BrickletVoltage
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void voltage_register_callback(Voltage *voltage, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int voltage_get_api_version(Voltage *voltage, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the voltage of the sensor. The value is in mV and
 * between 0mV and 50000mV.
 * 
 * If you want to get the voltage periodically, it is recommended to use the
 * callback {@link VOLTAGE_CALLBACK_VOLTAGE} and set the period with 
 * {@link voltage_set_voltage_callback_period}.
 */
int voltage_get_voltage(Voltage *voltage, uint16_t *ret_voltage);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * \note
 *  The value returned by {@link voltage_get_voltage} is averaged over several samples
 *  to yield less noise, while {@link voltage_get_analog_value} gives back raw
 *  unfiltered analog values. The only reason to use {@link voltage_get_analog_value} is,
 *  if you need the full resolution of the analog-to-digital converter.
 * 
 * If you want the analog value periodically, it is recommended to use the 
 * callback {@link VOLTAGE_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link voltage_set_analog_value_callback_period}.
 */
int voltage_get_analog_value(Voltage *voltage, uint16_t *ret_value);

/**
 * \ingroup BrickletVoltage
 *
 * Sets the period in ms with which the {@link VOLTAGE_CALLBACK_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link VOLTAGE_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int voltage_set_voltage_callback_period(Voltage *voltage, uint32_t period);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the period as set by {@link voltage_set_voltage_callback_period}.
 */
int voltage_get_voltage_callback_period(Voltage *voltage, uint32_t *ret_period);

/**
 * \ingroup BrickletVoltage
 *
 * Sets the period in ms with which the {@link VOLTAGE_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link VOLTAGE_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int voltage_set_analog_value_callback_period(Voltage *voltage, uint32_t period);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the period as set by {@link voltage_set_analog_value_callback_period}.
 */
int voltage_get_analog_value_callback_period(Voltage *voltage, uint32_t *ret_period);

/**
 * \ingroup BrickletVoltage
 *
 * Sets the thresholds for the {@link VOLTAGE_CALLBACK_VOLTAGE_REACHED} callback. 
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
 */
int voltage_set_voltage_callback_threshold(Voltage *voltage, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the threshold as set by {@link voltage_set_voltage_callback_threshold}.
 */
int voltage_get_voltage_callback_threshold(Voltage *voltage, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletVoltage
 *
 * Sets the thresholds for the {@link VOLTAGE_CALLBACK_ANALOG_VALUE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the analog value is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the analog value is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the analog value is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the analog value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int voltage_set_analog_value_callback_threshold(Voltage *voltage, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the threshold as set by {@link voltage_set_analog_value_callback_threshold}.
 */
int voltage_get_analog_value_callback_threshold(Voltage *voltage, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletVoltage
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link VOLTAGE_CALLBACK_VOLTAGE_REACHED},
 * * {@link VOLTAGE_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link voltage_set_voltage_callback_threshold},
 * * {@link voltage_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int voltage_set_debounce_period(Voltage *voltage, uint32_t debounce);

/**
 * \ingroup BrickletVoltage
 *
 * Returns the debounce period as set by {@link voltage_set_debounce_period}.
 */
int voltage_get_debounce_period(Voltage *voltage, uint32_t *ret_debounce);

/**
 * \ingroup BrickletVoltage
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
int voltage_get_identity(Voltage *voltage, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

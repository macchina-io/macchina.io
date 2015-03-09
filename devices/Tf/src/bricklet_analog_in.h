/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_ANALOG_IN_H
#define BRICKLET_ANALOG_IN_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletAnalogIn AnalogIn Bricklet
 */

/**
 * \ingroup BrickletAnalogIn
 *
 * Device for sensing Voltages between 0 and 45V
 */
typedef Device AnalogIn;

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_VOLTAGE 1

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_ANALOG_VALUE 2

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_RANGE 17

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_RANGE 18

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_SET_AVERAGING 19

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_AVERAGING 20

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletAnalogIn
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link analog_in_set_voltage_callback_period}. The parameter is the voltage of the
 * sensor.
 * 
 * {@link ANALOG_IN_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define ANALOG_IN_CALLBACK_VOLTAGE 13

/**
 * \ingroup BrickletAnalogIn
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link analog_in_set_analog_value_callback_period}. The parameter is the analog value of the
 * sensor.
 * 
 * {@link ANALOG_IN_CALLBACK_ANALOG_VALUE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define ANALOG_IN_CALLBACK_ANALOG_VALUE 14

/**
 * \ingroup BrickletAnalogIn
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link analog_in_set_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link analog_in_set_debounce_period}.
 */
#define ANALOG_IN_CALLBACK_VOLTAGE_REACHED 15

/**
 * \ingroup BrickletAnalogIn
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link analog_in_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link analog_in_set_debounce_period}.
 */
#define ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED 16


/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_RANGE_AUTOMATIC 0

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_RANGE_UP_TO_6V 1

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_RANGE_UP_TO_10V 2

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_RANGE_UP_TO_36V 3

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_RANGE_UP_TO_45V 4

/**
 * \ingroup BrickletAnalogIn
 */
#define ANALOG_IN_RANGE_UP_TO_3V 5

/**
 * \ingroup BrickletAnalogIn
 *
 * This constant is used to identify a AnalogIn Bricklet.
 *
 * The {@link analog_in_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ANALOG_IN_DEVICE_IDENTIFIER 219

/**
 * \ingroup BrickletAnalogIn
 *
 * Creates the device object \c analog_in with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void analog_in_create(AnalogIn *analog_in, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletAnalogIn
 *
 * Removes the device object \c analog_in from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void analog_in_destroy(AnalogIn *analog_in);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the analog_in_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int analog_in_get_response_expected(AnalogIn *analog_in, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletAnalogIn
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
int analog_in_set_response_expected(AnalogIn *analog_in, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletAnalogIn
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int analog_in_set_response_expected_all(AnalogIn *analog_in, bool response_expected);

/**
 * \ingroup BrickletAnalogIn
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void analog_in_register_callback(AnalogIn *analog_in, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int analog_in_get_api_version(AnalogIn *analog_in, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the voltage of the sensor. The value is in mV and
 * between 0V and 45V. The resolution between 0 and 6V is about 2mV.
 * Between 6 and 45V the resolution is about 10mV.
 * 
 * If you want to get the voltage periodically, it is recommended to use the
 * callback {@link ANALOG_IN_CALLBACK_VOLTAGE} and set the period with 
 * {@link analog_in_set_voltage_callback_period}.
 */
int analog_in_get_voltage(AnalogIn *analog_in, uint16_t *ret_voltage);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * \note
 *  The value returned by {@link analog_in_get_voltage} is averaged over several samples
 *  to yield less noise, while {@link analog_in_get_analog_value} gives back raw
 *  unfiltered analog values. The only reason to use {@link analog_in_get_analog_value} is,
 *  if you need the full resolution of the analog-to-digital converter.
 * 
 * If you want the analog value periodically, it is recommended to use the 
 * callback {@link ANALOG_IN_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link analog_in_set_analog_value_callback_period}.
 */
int analog_in_get_analog_value(AnalogIn *analog_in, uint16_t *ret_value);

/**
 * \ingroup BrickletAnalogIn
 *
 * Sets the period in ms with which the {@link ANALOG_IN_CALLBACK_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link ANALOG_IN_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int analog_in_set_voltage_callback_period(AnalogIn *analog_in, uint32_t period);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the period as set by {@link analog_in_set_voltage_callback_period}.
 */
int analog_in_get_voltage_callback_period(AnalogIn *analog_in, uint32_t *ret_period);

/**
 * \ingroup BrickletAnalogIn
 *
 * Sets the period in ms with which the {@link ANALOG_IN_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link ANALOG_IN_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int analog_in_set_analog_value_callback_period(AnalogIn *analog_in, uint32_t period);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the period as set by {@link analog_in_set_analog_value_callback_period}.
 */
int analog_in_get_analog_value_callback_period(AnalogIn *analog_in, uint32_t *ret_period);

/**
 * \ingroup BrickletAnalogIn
 *
 * Sets the thresholds for the {@link ANALOG_IN_CALLBACK_VOLTAGE_REACHED} callback. 
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
int analog_in_set_voltage_callback_threshold(AnalogIn *analog_in, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the threshold as set by {@link analog_in_set_voltage_callback_threshold}.
 */
int analog_in_get_voltage_callback_threshold(AnalogIn *analog_in, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletAnalogIn
 *
 * Sets the thresholds for the {@link ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED} callback. 
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
int analog_in_set_analog_value_callback_threshold(AnalogIn *analog_in, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the threshold as set by {@link analog_in_set_analog_value_callback_threshold}.
 */
int analog_in_get_analog_value_callback_threshold(AnalogIn *analog_in, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletAnalogIn
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link ANALOG_IN_CALLBACK_VOLTAGE_REACHED},
 * * {@link ANALOG_IN_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link analog_in_set_voltage_callback_threshold},
 * * {@link analog_in_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int analog_in_set_debounce_period(AnalogIn *analog_in, uint32_t debounce);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the debounce period as set by {@link analog_in_set_debounce_period}.
 */
int analog_in_get_debounce_period(AnalogIn *analog_in, uint32_t *ret_debounce);

/**
 * \ingroup BrickletAnalogIn
 *
 * Sets the measurement range. Possible ranges:
 * 
 * * 0: Automatically switched
 * * 1: 0V - 6.05V, ~1.48mV resolution
 * * 2: 0V - 10.32V, ~2.52mV resolution
 * * 3: 0V - 36.30V, ~8.86mV resolution
 * * 4: 0V - 45.00V, ~11.25mV resolution
 * * 5: 0V - 3.3V, ~0.81mV resolution, new in version 2.0.3 (Plugin)
 * 
 * The default measurement range is 0.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int analog_in_set_range(AnalogIn *analog_in, uint8_t range);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the measurement range as set by {@link analog_in_set_range}.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int analog_in_get_range(AnalogIn *analog_in, uint8_t *ret_range);

/**
 * \ingroup BrickletAnalogIn
 *
 * Set the length of a averaging for the voltage value.
 * 
 * Setting the length to 0 will turn the averaging completely off. If the
 * averaging is off, there is more noise on the data, but the data is without
 * delay.
 * 
 * The default value is 50.
 * 
 * .. versionadded:: 2.0.3~(Plugin)
 */
int analog_in_set_averaging(AnalogIn *analog_in, uint8_t average);

/**
 * \ingroup BrickletAnalogIn
 *
 * Returns the averaging configuration as set by {@link analog_in_set_averaging}.
 * 
 * .. versionadded:: 2.0.3~(Plugin)
 */
int analog_in_get_averaging(AnalogIn *analog_in, uint8_t *ret_average);

/**
 * \ingroup BrickletAnalogIn
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
int analog_in_get_identity(AnalogIn *analog_in, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

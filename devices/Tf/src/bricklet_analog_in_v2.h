/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_ANALOG_IN_V2_H
#define BRICKLET_ANALOG_IN_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletAnalogInV2 Analog In Bricklet 2.0
 */

/**
 * \ingroup BrickletAnalogInV2
 *
 * Measures DC voltage between 0V and 42V
 */
typedef Device AnalogInV2;

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_VOLTAGE 1

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE 2

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_SET_MOVING_AVERAGE 13

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_MOVING_AVERAGE 14

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletAnalogInV2
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link analog_in_v2_set_voltage_callback_period}. The parameter is the voltage of the
 * sensor.
 * 
 * {@link ANALOG_IN_V2_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define ANALOG_IN_V2_CALLBACK_VOLTAGE 15

/**
 * \ingroup BrickletAnalogInV2
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link analog_in_v2_set_analog_value_callback_period}. The parameter is the analog value of the
 * sensor.
 * 
 * {@link ANALOG_IN_V2_CALLBACK_ANALOG_VALUE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define ANALOG_IN_V2_CALLBACK_ANALOG_VALUE 16

/**
 * \ingroup BrickletAnalogInV2
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link analog_in_v2_set_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link analog_in_v2_set_debounce_period}.
 */
#define ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED 17

/**
 * \ingroup BrickletAnalogInV2
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link analog_in_v2_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link analog_in_v2_set_debounce_period}.
 */
#define ANALOG_IN_V2_CALLBACK_ANALOG_VALUE_REACHED 18


/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletAnalogInV2
 */
#define ANALOG_IN_V2_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletAnalogInV2
 *
 * This constant is used to identify a Analog In Bricklet 2.0.
 *
 * The {@link analog_in_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ANALOG_IN_V2_DEVICE_IDENTIFIER 251

/**
 * \ingroup BrickletAnalogInV2
 *
 * This constant represents the display name of a Analog In Bricklet 2.0.
 */
#define ANALOG_IN_V2_DEVICE_DISPLAY_NAME "Analog In Bricklet 2.0"

/**
 * \ingroup BrickletAnalogInV2
 *
 * Creates the device object \c analog_in_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void analog_in_v2_create(AnalogInV2 *analog_in_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Removes the device object \c analog_in_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void analog_in_v2_destroy(AnalogInV2 *analog_in_v2);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the analog_in_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int analog_in_v2_get_response_expected(AnalogInV2 *analog_in_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletAnalogInV2
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
int analog_in_v2_set_response_expected(AnalogInV2 *analog_in_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int analog_in_v2_set_response_expected_all(AnalogInV2 *analog_in_v2, bool response_expected);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void analog_in_v2_register_callback(AnalogInV2 *analog_in_v2, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int analog_in_v2_get_api_version(AnalogInV2 *analog_in_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the measured voltage. The value is in mV and
 * between 0V and 42V. The resolution is approximately 10mV.
 * 
 * If you want to get the voltage periodically, it is recommended to use the
 * callback {@link ANALOG_IN_V2_CALLBACK_VOLTAGE} and set the period with
 * {@link analog_in_v2_set_voltage_callback_period}.
 */
int analog_in_v2_get_voltage(AnalogInV2 *analog_in_v2, uint16_t *ret_voltage);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * If you want the analog value periodically, it is recommended to use the
 * callback {@link ANALOG_IN_V2_CALLBACK_ANALOG_VALUE} and set the period with
 * {@link analog_in_v2_set_analog_value_callback_period}.
 */
int analog_in_v2_get_analog_value(AnalogInV2 *analog_in_v2, uint16_t *ret_value);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Sets the period in ms with which the {@link ANALOG_IN_V2_CALLBACK_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link ANALOG_IN_V2_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int analog_in_v2_set_voltage_callback_period(AnalogInV2 *analog_in_v2, uint32_t period);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the period as set by {@link analog_in_v2_set_voltage_callback_period}.
 */
int analog_in_v2_get_voltage_callback_period(AnalogInV2 *analog_in_v2, uint32_t *ret_period);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Sets the period in ms with which the {@link ANALOG_IN_V2_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link ANALOG_IN_V2_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int analog_in_v2_set_analog_value_callback_period(AnalogInV2 *analog_in_v2, uint32_t period);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the period as set by {@link analog_in_v2_set_analog_value_callback_period}.
 */
int analog_in_v2_get_analog_value_callback_period(AnalogInV2 *analog_in_v2, uint32_t *ret_period);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Sets the thresholds for the {@link ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED} callback.
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
int analog_in_v2_set_voltage_callback_threshold(AnalogInV2 *analog_in_v2, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the threshold as set by {@link analog_in_v2_set_voltage_callback_threshold}.
 */
int analog_in_v2_get_voltage_callback_threshold(AnalogInV2 *analog_in_v2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Sets the thresholds for the {@link ANALOG_IN_V2_CALLBACK_ANALOG_VALUE_REACHED} callback.
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
int analog_in_v2_set_analog_value_callback_threshold(AnalogInV2 *analog_in_v2, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the threshold as set by {@link analog_in_v2_set_analog_value_callback_threshold}.
 */
int analog_in_v2_get_analog_value_callback_threshold(AnalogInV2 *analog_in_v2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED},
 * * {@link ANALOG_IN_V2_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link analog_in_v2_set_voltage_callback_threshold},
 * * {@link analog_in_v2_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int analog_in_v2_set_debounce_period(AnalogInV2 *analog_in_v2, uint32_t debounce);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the debounce period as set by {@link analog_in_v2_set_debounce_period}.
 */
int analog_in_v2_get_debounce_period(AnalogInV2 *analog_in_v2, uint32_t *ret_debounce);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Sets the length of a `moving averaging <https://en.wikipedia.org/wiki/Moving_average>`__
 * for the voltage.
 * 
 * Setting the length to 1 will turn the averaging off. With less
 * averaging, there is more noise on the data.
 * 
 * The range for the averaging is 1-50.
 * 
 * The default value is 50.
 */
int analog_in_v2_set_moving_average(AnalogInV2 *analog_in_v2, uint8_t average);

/**
 * \ingroup BrickletAnalogInV2
 *
 * Returns the length of the moving average as set by {@link analog_in_v2_set_moving_average}.
 */
int analog_in_v2_get_moving_average(AnalogInV2 *analog_in_v2, uint8_t *ret_average);

/**
 * \ingroup BrickletAnalogInV2
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
int analog_in_v2_get_identity(AnalogInV2 *analog_in_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

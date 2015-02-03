/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_LINEAR_POTI_H
#define BRICKLET_LINEAR_POTI_H

#include "ip_connection.h"

/**
 * \defgroup BrickletLinearPoti LinearPoti Bricklet
 */

/**
 * \ingroup BrickletLinearPoti
 *
 * Device for sensing Linear Potentiometer input
 */
typedef Device LinearPoti;

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_POSITION 1

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE 2

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletLinearPoti
 *
 * Signature: \code void callback(uint16_t position, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link linear_poti_set_position_callback_period}. The parameter is the position of the
 * Linear Potentiometer.
 * 
 * {@link LINEAR_POTI_CALLBACK_POSITION} is only triggered if the position has changed since the
 * last triggering.
 */
#define LINEAR_POTI_CALLBACK_POSITION 13

/**
 * \ingroup BrickletLinearPoti
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link linear_poti_set_analog_value_callback_period}. The parameter is the analog value of the
 * Linear Potentiometer.
 * 
 * {@link LINEAR_POTI_CALLBACK_ANALOG_VALUE} is only triggered if the position has changed since the
 * last triggering.
 */
#define LINEAR_POTI_CALLBACK_ANALOG_VALUE 14

/**
 * \ingroup BrickletLinearPoti
 *
 * Signature: \code void callback(uint16_t position, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link linear_poti_set_position_callback_threshold} is reached.
 * The parameter is the position of the Linear Potentiometer.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link linear_poti_set_debounce_period}.
 */
#define LINEAR_POTI_CALLBACK_POSITION_REACHED 15

/**
 * \ingroup BrickletLinearPoti
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link linear_poti_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the Linear Potentiometer.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link linear_poti_set_debounce_period}.
 */
#define LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED 16


/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletLinearPoti
 */
#define LINEAR_POTI_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletLinearPoti
 *
 * This constant is used to identify a LinearPoti Bricklet.
 *
 * The {@link linear_poti_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define LINEAR_POTI_DEVICE_IDENTIFIER 213

/**
 * \ingroup BrickletLinearPoti
 *
 * Creates the device object \c linear_poti with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void linear_poti_create(LinearPoti *linear_poti, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletLinearPoti
 *
 * Removes the device object \c linear_poti from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void linear_poti_destroy(LinearPoti *linear_poti);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the linear_poti_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int linear_poti_get_response_expected(LinearPoti *linear_poti, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletLinearPoti
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
int linear_poti_set_response_expected(LinearPoti *linear_poti, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletLinearPoti
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int linear_poti_set_response_expected_all(LinearPoti *linear_poti, bool response_expected);

/**
 * \ingroup BrickletLinearPoti
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void linear_poti_register_callback(LinearPoti *linear_poti, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int linear_poti_get_api_version(LinearPoti *linear_poti, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the position of the Linear Potentiometer. The value is  
 * between 0 (slider down) and 100 (slider up).
 * 
 * If you want to get the position periodically, it is recommended to use the
 * callback {@link LINEAR_POTI_CALLBACK_POSITION} and set the period with 
 * {@link linear_poti_set_position_callback_period}.
 */
int linear_poti_get_position(LinearPoti *linear_poti, uint16_t *ret_position);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * \note
 *  The value returned by {@link linear_poti_get_position} is averaged over several samples
 *  to yield less noise, while {@link linear_poti_get_analog_value} gives back raw
 *  unfiltered analog values. The only reason to use {@link linear_poti_get_analog_value} is,
 *  if you need the full resolution of the analog-to-digital converter.
 * 
 * If you want the analog value periodically, it is recommended to use the 
 * callback {@link LINEAR_POTI_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link linear_poti_set_analog_value_callback_period}.
 */
int linear_poti_get_analog_value(LinearPoti *linear_poti, uint16_t *ret_value);

/**
 * \ingroup BrickletLinearPoti
 *
 * Sets the period in ms with which the {@link LINEAR_POTI_CALLBACK_POSITION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link LINEAR_POTI_CALLBACK_POSITION} is only triggered if the position has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int linear_poti_set_position_callback_period(LinearPoti *linear_poti, uint32_t period);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the period as set by {@link linear_poti_set_position_callback_period}.
 */
int linear_poti_get_position_callback_period(LinearPoti *linear_poti, uint32_t *ret_period);

/**
 * \ingroup BrickletLinearPoti
 *
 * Sets the period in ms with which the {@link LINEAR_POTI_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link LINEAR_POTI_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int linear_poti_set_analog_value_callback_period(LinearPoti *linear_poti, uint32_t period);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the period as set by {@link linear_poti_set_analog_value_callback_period}.
 */
int linear_poti_get_analog_value_callback_period(LinearPoti *linear_poti, uint32_t *ret_period);

/**
 * \ingroup BrickletLinearPoti
 *
 * Sets the thresholds for the {@link LINEAR_POTI_CALLBACK_POSITION_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the position is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the position is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the position is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the position is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int linear_poti_set_position_callback_threshold(LinearPoti *linear_poti, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the threshold as set by {@link linear_poti_set_position_callback_threshold}.
 */
int linear_poti_get_position_callback_threshold(LinearPoti *linear_poti, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletLinearPoti
 *
 * Sets the thresholds for the {@link LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED} callback. 
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
int linear_poti_set_analog_value_callback_threshold(LinearPoti *linear_poti, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the threshold as set by {@link linear_poti_set_analog_value_callback_threshold}.
 */
int linear_poti_get_analog_value_callback_threshold(LinearPoti *linear_poti, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletLinearPoti
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link LINEAR_POTI_CALLBACK_POSITION_REACHED},
 * * {@link LINEAR_POTI_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link linear_poti_set_position_callback_threshold},
 * * {@link linear_poti_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int linear_poti_set_debounce_period(LinearPoti *linear_poti, uint32_t debounce);

/**
 * \ingroup BrickletLinearPoti
 *
 * Returns the debounce period as set by {@link linear_poti_set_debounce_period}.
 */
int linear_poti_get_debounce_period(LinearPoti *linear_poti, uint32_t *ret_debounce);

/**
 * \ingroup BrickletLinearPoti
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
int linear_poti_get_identity(LinearPoti *linear_poti, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

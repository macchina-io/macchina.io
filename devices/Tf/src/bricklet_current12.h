/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_CURRENT12_H
#define BRICKLET_CURRENT12_H

#include "ip_connection.h"

/**
 * \defgroup BrickletCurrent12 Current12 Bricklet
 */

/**
 * \ingroup BrickletCurrent12
 *
 * Device for sensing current of up to 12.5A
 */
typedef Device Current12;

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_CURRENT 1

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_CALIBRATE 2

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_IS_OVER_CURRENT 3

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_ANALOG_VALUE 4

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_SET_CURRENT_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_CURRENT_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 11

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 12

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_SET_DEBOUNCE_PERIOD 13

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_DEBOUNCE_PERIOD 14

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletCurrent12
 *
 * Signature: \code void callback(int16_t current, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link current12_set_current_callback_period}. The parameter is the current of the
 * sensor.
 * 
 * {@link CURRENT12_CALLBACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 */
#define CURRENT12_CALLBACK_CURRENT 15

/**
 * \ingroup BrickletCurrent12
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link current12_set_analog_value_callback_period}. The parameter is the analog value
 * of the sensor.
 * 
 * {@link CURRENT12_CALLBACK_ANALOG_VALUE} is only triggered if the current has changed since the
 * last triggering.
 */
#define CURRENT12_CALLBACK_ANALOG_VALUE 16

/**
 * \ingroup BrickletCurrent12
 *
 * Signature: \code void callback(int16_t current, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link current12_set_current_callback_threshold} is reached.
 * The parameter is the current of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link current12_set_debounce_period}.
 */
#define CURRENT12_CALLBACK_CURRENT_REACHED 17

/**
 * \ingroup BrickletCurrent12
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link current12_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link current12_set_debounce_period}.
 */
#define CURRENT12_CALLBACK_ANALOG_VALUE_REACHED 18

/**
 * \ingroup BrickletCurrent12
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered when an over current is measured
 * (see {@link current12_is_over_current}).
 */
#define CURRENT12_CALLBACK_OVER_CURRENT 19


/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletCurrent12
 */
#define CURRENT12_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletCurrent12
 *
 * This constant is used to identify a Current12 Bricklet.
 *
 * The {@link current12_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define CURRENT12_DEVICE_IDENTIFIER 23

/**
 * \ingroup BrickletCurrent12
 *
 * Creates the device object \c current12 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void current12_create(Current12 *current12, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletCurrent12
 *
 * Removes the device object \c current12 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void current12_destroy(Current12 *current12);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the current12_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int current12_get_response_expected(Current12 *current12, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletCurrent12
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
int current12_set_response_expected(Current12 *current12, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletCurrent12
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int current12_set_response_expected_all(Current12 *current12, bool response_expected);

/**
 * \ingroup BrickletCurrent12
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void current12_register_callback(Current12 *current12, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int current12_get_api_version(Current12 *current12, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the current of the sensor. The value is in mA
 * and between -12500mA and 12500mA.
 * 
 * If you want to get the current periodically, it is recommended to use the
 * callback {@link CURRENT12_CALLBACK_CURRENT} and set the period with 
 * {@link current12_set_current_callback_period}.
 */
int current12_get_current(Current12 *current12, int16_t *ret_current);

/**
 * \ingroup BrickletCurrent12
 *
 * Calibrates the 0 value of the sensor. You have to call this function
 * when there is no current present. 
 * 
 * The zero point of the current sensor
 * is depending on the exact properties of the analog-to-digital converter,
 * the length of the Bricklet cable and the temperature. Thus, if you change
 * the Brick or the environment in which the Bricklet is used, you might
 * have to recalibrate.
 * 
 * The resulting calibration will be saved on the EEPROM of the Current
 * Bricklet.
 */
int current12_calibrate(Current12 *current12);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns *true* if more than 12.5A were measured.
 * 
 * \note
 *  To reset this value you have to power cycle the Bricklet.
 */
int current12_is_over_current(Current12 *current12, bool *ret_over);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * \note
 *  The value returned by {@link current12_get_current} is averaged over several samples
 *  to yield less noise, while {@link current12_get_analog_value} gives back raw
 *  unfiltered analog values. The only reason to use {@link current12_get_analog_value} is,
 *  if you need the full resolution of the analog-to-digital converter.
 * 
 * If you want the analog value periodically, it is recommended to use the 
 * callback {@link CURRENT12_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link current12_set_analog_value_callback_period}.
 */
int current12_get_analog_value(Current12 *current12, uint16_t *ret_value);

/**
 * \ingroup BrickletCurrent12
 *
 * Sets the period in ms with which the {@link CURRENT12_CALLBACK_CURRENT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link CURRENT12_CALLBACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int current12_set_current_callback_period(Current12 *current12, uint32_t period);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the period as set by {@link current12_set_current_callback_period}.
 */
int current12_get_current_callback_period(Current12 *current12, uint32_t *ret_period);

/**
 * \ingroup BrickletCurrent12
 *
 * Sets the period in ms with which the {@link CURRENT12_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link CURRENT12_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int current12_set_analog_value_callback_period(Current12 *current12, uint32_t period);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the period as set by {@link current12_set_analog_value_callback_period}.
 */
int current12_get_analog_value_callback_period(Current12 *current12, uint32_t *ret_period);

/**
 * \ingroup BrickletCurrent12
 *
 * Sets the thresholds for the {@link CURRENT12_CALLBACK_CURRENT_REACHED} callback. 
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
 */
int current12_set_current_callback_threshold(Current12 *current12, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the threshold as set by {@link current12_set_current_callback_threshold}.
 */
int current12_get_current_callback_threshold(Current12 *current12, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletCurrent12
 *
 * Sets the thresholds for the {@link CURRENT12_CALLBACK_ANALOG_VALUE_REACHED} callback. 
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
int current12_set_analog_value_callback_threshold(Current12 *current12, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the threshold as set by {@link current12_set_analog_value_callback_threshold}.
 */
int current12_get_analog_value_callback_threshold(Current12 *current12, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletCurrent12
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link CURRENT12_CALLBACK_CURRENT_REACHED},
 * * {@link CURRENT12_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link current12_set_current_callback_threshold},
 * * {@link current12_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int current12_set_debounce_period(Current12 *current12, uint32_t debounce);

/**
 * \ingroup BrickletCurrent12
 *
 * Returns the debounce period as set by {@link current12_set_debounce_period}.
 */
int current12_get_debounce_period(Current12 *current12, uint32_t *ret_debounce);

/**
 * \ingroup BrickletCurrent12
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
int current12_get_identity(Current12 *current12, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

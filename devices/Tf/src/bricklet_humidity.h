/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_HUMIDITY_H
#define BRICKLET_HUMIDITY_H

#include "ip_connection.h"

/**
 * \defgroup BrickletHumidity Humidity Bricklet
 */

/**
 * \ingroup BrickletHumidity
 *
 * Device for sensing Humidity
 */
typedef Device Humidity;

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_HUMIDITY 1

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_ANALOG_VALUE 2

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_SET_HUMIDITY_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_HUMIDITY_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_SET_HUMIDITY_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_HUMIDITY_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletHumidity
 *
 * Signature: \code void callback(uint16_t humidity, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link humidity_set_humidity_callback_period}. The parameter is the humidity of the
 * sensor.
 * 
 * {@link HUMIDITY_CALLBACK_HUMIDITY} is only triggered if the humidity has changed since the
 * last triggering.
 */
#define HUMIDITY_CALLBACK_HUMIDITY 13

/**
 * \ingroup BrickletHumidity
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link humidity_set_analog_value_callback_period}. The parameter is the analog value of the
 * sensor.
 * 
 * {@link HUMIDITY_CALLBACK_ANALOG_VALUE} is only triggered if the humidity has changed since the
 * last triggering.
 */
#define HUMIDITY_CALLBACK_ANALOG_VALUE 14

/**
 * \ingroup BrickletHumidity
 *
 * Signature: \code void callback(uint16_t humidity, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link humidity_set_humidity_callback_threshold} is reached.
 * The parameter is the humidity of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link humidity_set_debounce_period}.
 */
#define HUMIDITY_CALLBACK_HUMIDITY_REACHED 15

/**
 * \ingroup BrickletHumidity
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link humidity_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link humidity_set_debounce_period}.
 */
#define HUMIDITY_CALLBACK_ANALOG_VALUE_REACHED 16


/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletHumidity
 */
#define HUMIDITY_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletHumidity
 *
 * This constant is used to identify a Humidity Bricklet.
 *
 * The {@link humidity_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define HUMIDITY_DEVICE_IDENTIFIER 27

/**
 * \ingroup BrickletHumidity
 *
 * Creates the device object \c humidity with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void humidity_create(Humidity *humidity, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletHumidity
 *
 * Removes the device object \c humidity from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void humidity_destroy(Humidity *humidity);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the humidity_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int humidity_get_response_expected(Humidity *humidity, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletHumidity
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
int humidity_set_response_expected(Humidity *humidity, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletHumidity
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int humidity_set_response_expected_all(Humidity *humidity, bool response_expected);

/**
 * \ingroup BrickletHumidity
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void humidity_register_callback(Humidity *humidity, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int humidity_get_api_version(Humidity *humidity, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the humidity of the sensor. The value
 * has a range of 0 to 1000 and is given in %RH/10 (Relative Humidity), 
 * i.e. a value of 421 means that a humidity of 42.1 %RH is measured.
 * 
 * If you want to get the humidity periodically, it is recommended to use the
 * callback {@link HUMIDITY_CALLBACK_HUMIDITY} and set the period with 
 * {@link humidity_set_humidity_callback_period}.
 */
int humidity_get_humidity(Humidity *humidity, uint16_t *ret_humidity);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * \note
 *  The value returned by {@link humidity_get_humidity} is averaged over several samples
 *  to yield less noise, while {@link humidity_get_analog_value} gives back raw
 *  unfiltered analog values. The returned humidity value is calibrated for
 *  room temperatures, if you use the sensor in extreme cold or extreme
 *  warm environments, you might want to calculate the humidity from
 *  the analog value yourself. See the `HIH 5030 datasheet
 *  <https://github.com/Tinkerforge/humidity-bricklet/raw/master/datasheets/hih-5030.pdf>`__.
 * 
 * If you want the analog value periodically, it is recommended to use the 
 * callback {@link HUMIDITY_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link humidity_set_analog_value_callback_period}.
 */
int humidity_get_analog_value(Humidity *humidity, uint16_t *ret_value);

/**
 * \ingroup BrickletHumidity
 *
 * Sets the period in ms with which the {@link HUMIDITY_CALLBACK_HUMIDITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link HUMIDITY_CALLBACK_HUMIDITY} is only triggered if the humidity has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int humidity_set_humidity_callback_period(Humidity *humidity, uint32_t period);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the period as set by {@link humidity_set_humidity_callback_period}.
 */
int humidity_get_humidity_callback_period(Humidity *humidity, uint32_t *ret_period);

/**
 * \ingroup BrickletHumidity
 *
 * Sets the period in ms with which the {@link HUMIDITY_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link HUMIDITY_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int humidity_set_analog_value_callback_period(Humidity *humidity, uint32_t period);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the period as set by {@link humidity_set_analog_value_callback_period}.
 */
int humidity_get_analog_value_callback_period(Humidity *humidity, uint32_t *ret_period);

/**
 * \ingroup BrickletHumidity
 *
 * Sets the thresholds for the {@link HUMIDITY_CALLBACK_HUMIDITY_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the humidity is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the humidity is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the humidity is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the humidity is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int humidity_set_humidity_callback_threshold(Humidity *humidity, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the threshold as set by {@link humidity_set_humidity_callback_threshold}.
 */
int humidity_get_humidity_callback_threshold(Humidity *humidity, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletHumidity
 *
 * Sets the thresholds for the {@link HUMIDITY_CALLBACK_ANALOG_VALUE_REACHED} callback. 
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
int humidity_set_analog_value_callback_threshold(Humidity *humidity, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the threshold as set by {@link humidity_set_analog_value_callback_threshold}.
 */
int humidity_get_analog_value_callback_threshold(Humidity *humidity, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletHumidity
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link HUMIDITY_CALLBACK_HUMIDITY_REACHED},
 * * {@link HUMIDITY_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link humidity_set_humidity_callback_threshold},
 * * {@link humidity_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int humidity_set_debounce_period(Humidity *humidity, uint32_t debounce);

/**
 * \ingroup BrickletHumidity
 *
 * Returns the debounce period as set by {@link humidity_set_debounce_period}.
 */
int humidity_get_debounce_period(Humidity *humidity, uint32_t *ret_debounce);

/**
 * \ingroup BrickletHumidity
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
int humidity_get_identity(Humidity *humidity, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_MOISTURE_H
#define BRICKLET_MOISTURE_H

#include "ip_connection.h"

/**
 * \defgroup BrickletMoisture Moisture Bricklet
 */

/**
 * \ingroup BrickletMoisture
 *
 * Device for sensing Moisture
 */
typedef Device Moisture;

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_GET_MOISTURE_VALUE 1

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_SET_MOISTURE_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_GET_MOISTURE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_SET_MOISTURE_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_GET_MOISTURE_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_SET_MOVING_AVERAGE 10

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_GET_MOVING_AVERAGE 11

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletMoisture
 *
 * Signature: \code void callback(uint16_t moisture, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link moisture_set_moisture_callback_period}. The parameter is the moisture value
 * of the sensor.
 * 
 * {@link MOISTURE_CALLBACK_MOISTURE} is only triggered if the moisture value has changed since the
 * last triggering.
 */
#define MOISTURE_CALLBACK_MOISTURE 8

/**
 * \ingroup BrickletMoisture
 *
 * Signature: \code void callback(uint16_t moisture, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link moisture_set_moisture_callback_threshold} is reached.
 * The parameter is the moisture value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link moisture_set_debounce_period}.
 */
#define MOISTURE_CALLBACK_MOISTURE_REACHED 9


/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletMoisture
 */
#define MOISTURE_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletMoisture
 *
 * This constant is used to identify a Moisture Bricklet.
 *
 * The {@link moisture_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define MOISTURE_DEVICE_IDENTIFIER 232

/**
 * \ingroup BrickletMoisture
 *
 * Creates the device object \c moisture with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void moisture_create(Moisture *moisture, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletMoisture
 *
 * Removes the device object \c moisture from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void moisture_destroy(Moisture *moisture);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the moisture_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int moisture_get_response_expected(Moisture *moisture, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletMoisture
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
int moisture_set_response_expected(Moisture *moisture, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletMoisture
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int moisture_set_response_expected_all(Moisture *moisture, bool response_expected);

/**
 * \ingroup BrickletMoisture
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void moisture_register_callback(Moisture *moisture, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int moisture_get_api_version(Moisture *moisture, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the current moisture value. The value has a range of
 * 0 to 4095. A small value corresponds to little moisture, a big
 * value corresponds to much moisture.
 * 
 * If you want to get the moisture value periodically, it is recommended 
 * to use the callback {@link MOISTURE_CALLBACK_MOISTURE} and set the period with 
 * {@link moisture_set_moisture_callback_period}.
 */
int moisture_get_moisture_value(Moisture *moisture, uint16_t *ret_moisture);

/**
 * \ingroup BrickletMoisture
 *
 * Sets the period in ms with which the {@link MOISTURE_CALLBACK_MOISTURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link MOISTURE_CALLBACK_MOISTURE} is only triggered if the moisture value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int moisture_set_moisture_callback_period(Moisture *moisture, uint32_t period);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the period as set by {@link moisture_set_moisture_callback_period}.
 */
int moisture_get_moisture_callback_period(Moisture *moisture, uint32_t *ret_period);

/**
 * \ingroup BrickletMoisture
 *
 * Sets the thresholds for the {@link MOISTURE_CALLBACK_MOISTURE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the moisture value is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the moisture value is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the moisture value is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the moisture value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int moisture_set_moisture_callback_threshold(Moisture *moisture, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the threshold as set by {@link moisture_set_moisture_callback_threshold}.
 */
int moisture_get_moisture_callback_threshold(Moisture *moisture, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletMoisture
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link MOISTURE_CALLBACK_MOISTURE_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link moisture_set_moisture_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int moisture_set_debounce_period(Moisture *moisture, uint32_t debounce);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the debounce period as set by {@link moisture_set_debounce_period}.
 */
int moisture_get_debounce_period(Moisture *moisture, uint32_t *ret_debounce);

/**
 * \ingroup BrickletMoisture
 *
 * Sets the length of a `moving averaging <http://en.wikipedia.org/wiki/Moving_average>`__ 
 * for the moisture value.
 * 
 * Setting the length to 0 will turn the averaging completely off. With less
 * averaging, there is more noise on the data.
 * 
 * The range for the averaging is 0-100.
 * 
 * The default value is 100.
 */
int moisture_set_moving_average(Moisture *moisture, uint8_t average);

/**
 * \ingroup BrickletMoisture
 *
 * Returns the length moving average as set by {@link moisture_set_moving_average}.
 */
int moisture_get_moving_average(Moisture *moisture, uint8_t *ret_average);

/**
 * \ingroup BrickletMoisture
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
int moisture_get_identity(Moisture *moisture, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_ACCELEROMETER_H
#define BRICKLET_ACCELEROMETER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletAccelerometer Accelerometer Bricklet
 */

/**
 * \ingroup BrickletAccelerometer
 *
 * Measures acceleration in three axis
 */
typedef Device Accelerometer;

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_ACCELERATION 1

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_TEMPERATURE 8

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_SET_CONFIGURATION 9

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_CONFIGURATION 10

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_LED_ON 11

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_LED_OFF 12

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_IS_LED_ON 13

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletAccelerometer
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link accelerometer_set_acceleration_callback_period}. The parameters are the
 * X, Y and Z acceleration.
 * 
 * {@link ACCELEROMETER_CALLBACK_ACCELERATION} is only triggered if the acceleration has changed since the
 * last triggering.
 */
#define ACCELEROMETER_CALLBACK_ACCELERATION 14

/**
 * \ingroup BrickletAccelerometer
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link accelerometer_set_acceleration_callback_threshold} is reached.
 * The parameters are the X, Y and Z acceleration.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link accelerometer_set_debounce_period}.
 */
#define ACCELEROMETER_CALLBACK_ACCELERATION_REACHED 15


/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_OFF 0

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_3HZ 1

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_6HZ 2

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_12HZ 3

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_25HZ 4

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_50HZ 5

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_100HZ 6

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_400HZ 7

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_800HZ 8

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_DATA_RATE_1600HZ 9

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FULL_SCALE_2G 0

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FULL_SCALE_4G 1

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FULL_SCALE_6G 2

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FULL_SCALE_8G 3

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FULL_SCALE_16G 4

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FILTER_BANDWIDTH_800HZ 0

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FILTER_BANDWIDTH_400HZ 1

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FILTER_BANDWIDTH_200HZ 2

/**
 * \ingroup BrickletAccelerometer
 */
#define ACCELEROMETER_FILTER_BANDWIDTH_50HZ 3

/**
 * \ingroup BrickletAccelerometer
 *
 * This constant is used to identify a Accelerometer Bricklet.
 *
 * The {@link accelerometer_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ACCELEROMETER_DEVICE_IDENTIFIER 250

/**
 * \ingroup BrickletAccelerometer
 *
 * This constant represents the display name of a Accelerometer Bricklet.
 */
#define ACCELEROMETER_DEVICE_DISPLAY_NAME "Accelerometer Bricklet"

/**
 * \ingroup BrickletAccelerometer
 *
 * Creates the device object \c accelerometer with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void accelerometer_create(Accelerometer *accelerometer, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletAccelerometer
 *
 * Removes the device object \c accelerometer from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void accelerometer_destroy(Accelerometer *accelerometer);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the accelerometer_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int accelerometer_get_response_expected(Accelerometer *accelerometer, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletAccelerometer
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
int accelerometer_set_response_expected(Accelerometer *accelerometer, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletAccelerometer
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int accelerometer_set_response_expected_all(Accelerometer *accelerometer, bool response_expected);

/**
 * \ingroup BrickletAccelerometer
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void accelerometer_register_callback(Accelerometer *accelerometer, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int accelerometer_get_api_version(Accelerometer *accelerometer, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the acceleration in x, y and z direction. The values
 * are given in g/1000 (1g = 9.80665m/s²), not to be confused with grams.
 * 
 * If you want to get the acceleration periodically, it is recommended 
 * to use the callback {@link ACCELEROMETER_CALLBACK_ACCELERATION} and set the period with 
 * {@link accelerometer_set_acceleration_callback_period}.
 */
int accelerometer_get_acceleration(Accelerometer *accelerometer, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickletAccelerometer
 *
 * Sets the period in ms with which the {@link ACCELEROMETER_CALLBACK_ACCELERATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link ACCELEROMETER_CALLBACK_ACCELERATION} is only triggered if the acceleration has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int accelerometer_set_acceleration_callback_period(Accelerometer *accelerometer, uint32_t period);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the period as set by {@link accelerometer_set_acceleration_callback_period}.
 */
int accelerometer_get_acceleration_callback_period(Accelerometer *accelerometer, uint32_t *ret_period);

/**
 * \ingroup BrickletAccelerometer
 *
 * Sets the thresholds for the {@link ACCELEROMETER_CALLBACK_ACCELERATION_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the acceleration is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the acceleration is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the acceleration is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the acceleration is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0, 0, 0, 0, 0).
 */
int accelerometer_set_acceleration_callback_threshold(Accelerometer *accelerometer, char option, int16_t min_x, int16_t max_x, int16_t min_y, int16_t max_y, int16_t min_z, int16_t max_z);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the threshold as set by {@link accelerometer_set_acceleration_callback_threshold}.
 */
int accelerometer_get_acceleration_callback_threshold(Accelerometer *accelerometer, char *ret_option, int16_t *ret_min_x, int16_t *ret_max_x, int16_t *ret_min_y, int16_t *ret_max_y, int16_t *ret_min_z, int16_t *ret_max_z);

/**
 * \ingroup BrickletAccelerometer
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link ACCELEROMETER_CALLBACK_ACCELERATION_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link accelerometer_set_acceleration_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int accelerometer_set_debounce_period(Accelerometer *accelerometer, uint32_t debounce);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the debounce period as set by {@link accelerometer_set_debounce_period}.
 */
int accelerometer_get_debounce_period(Accelerometer *accelerometer, uint32_t *ret_debounce);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the temperature of the accelerometer in °C.
 */
int accelerometer_get_temperature(Accelerometer *accelerometer, int16_t *ret_temperature);

/**
 * \ingroup BrickletAccelerometer
 *
 * Configures the data rate, full scale range and filter bandwidth.
 * Possible values are:
 * 
 * * Data rate of 0Hz to 1600Hz.
 * * Full scale range of -2G to +2G up to -16G to +16G.
 * * Filter bandwidth between 50Hz and 800Hz.
 * 
 * Decreasing data rate or full scale range will also decrease the noise on 
 * the data.
 * 
 * The default values are 100Hz data rate, -4G to +4G range and 200Hz
 * filter bandwidth.
 */
int accelerometer_set_configuration(Accelerometer *accelerometer, uint8_t data_rate, uint8_t full_scale, uint8_t filter_bandwidth);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns the configuration as set by {@link accelerometer_set_configuration}.
 */
int accelerometer_get_configuration(Accelerometer *accelerometer, uint8_t *ret_data_rate, uint8_t *ret_full_scale, uint8_t *ret_filter_bandwidth);

/**
 * \ingroup BrickletAccelerometer
 *
 * Enables the LED on the Bricklet.
 */
int accelerometer_led_on(Accelerometer *accelerometer);

/**
 * \ingroup BrickletAccelerometer
 *
 * Disables the LED on the Bricklet.
 */
int accelerometer_led_off(Accelerometer *accelerometer);

/**
 * \ingroup BrickletAccelerometer
 *
 * Returns *true* if the LED is enabled, *false* otherwise.
 */
int accelerometer_is_led_on(Accelerometer *accelerometer, bool *ret_on);

/**
 * \ingroup BrickletAccelerometer
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
int accelerometer_get_identity(Accelerometer *accelerometer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_LOAD_CELL_H
#define BRICKLET_LOAD_CELL_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletLoadCell Load Cell Bricklet
 */

/**
 * \ingroup BrickletLoadCell
 *
 * Measures weight with a load cell
 */
typedef Device LoadCell;

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_WEIGHT 1

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_SET_WEIGHT_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_WEIGHT_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_SET_WEIGHT_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_WEIGHT_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_SET_MOVING_AVERAGE 8

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_MOVING_AVERAGE 9

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_LED_ON 10

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_LED_OFF 11

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_IS_LED_ON 12

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_CALIBRATE 13

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_TARE 14

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_SET_CONFIGURATION 15

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_CONFIGURATION 16

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletLoadCell
 *
 * Signature: \code void callback(int32_t weight, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link load_cell_set_weight_callback_period}. The parameter is the weight
 * as measured by the load cell.
 * 
 * {@link LOAD_CELL_CALLBACK_WEIGHT} is only triggered if the weight has changed since the
 * last triggering.
 */
#define LOAD_CELL_CALLBACK_WEIGHT 17

/**
 * \ingroup BrickletLoadCell
 *
 * Signature: \code void callback(int32_t weight, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link load_cell_set_weight_callback_threshold} is reached.
 * The parameter is the weight as measured by the load cell.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link load_cell_set_debounce_period}.
 */
#define LOAD_CELL_CALLBACK_WEIGHT_REACHED 18


/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_RATE_10HZ 0

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_RATE_80HZ 1

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_GAIN_128X 0

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_GAIN_64X 1

/**
 * \ingroup BrickletLoadCell
 */
#define LOAD_CELL_GAIN_32X 2

/**
 * \ingroup BrickletLoadCell
 *
 * This constant is used to identify a Load Cell Bricklet.
 *
 * The {@link load_cell_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define LOAD_CELL_DEVICE_IDENTIFIER 253

/**
 * \ingroup BrickletLoadCell
 *
 * This constant represents the display name of a Load Cell Bricklet.
 */
#define LOAD_CELL_DEVICE_DISPLAY_NAME "Load Cell Bricklet"

/**
 * \ingroup BrickletLoadCell
 *
 * Creates the device object \c load_cell with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void load_cell_create(LoadCell *load_cell, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletLoadCell
 *
 * Removes the device object \c load_cell from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void load_cell_destroy(LoadCell *load_cell);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the load_cell_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int load_cell_get_response_expected(LoadCell *load_cell, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletLoadCell
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
int load_cell_set_response_expected(LoadCell *load_cell, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletLoadCell
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int load_cell_set_response_expected_all(LoadCell *load_cell, bool response_expected);

/**
 * \ingroup BrickletLoadCell
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void load_cell_register_callback(LoadCell *load_cell, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int load_cell_get_api_version(LoadCell *load_cell, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the currently measured weight in grams.
 * 
 * If you want to get the weight periodically, it is recommended 
 * to use the callback {@link LOAD_CELL_CALLBACK_WEIGHT} and set the period with 
 * {@link load_cell_set_weight_callback_period}.
 */
int load_cell_get_weight(LoadCell *load_cell, int32_t *ret_weight);

/**
 * \ingroup BrickletLoadCell
 *
 * Sets the period in ms with which the {@link LOAD_CELL_CALLBACK_WEIGHT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link LOAD_CELL_CALLBACK_WEIGHT} is only triggered if the weight has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int load_cell_set_weight_callback_period(LoadCell *load_cell, uint32_t period);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the period as set by {@link load_cell_set_weight_callback_period}.
 */
int load_cell_get_weight_callback_period(LoadCell *load_cell, uint32_t *ret_period);

/**
 * \ingroup BrickletLoadCell
 *
 * Sets the thresholds for the {@link LOAD_CELL_CALLBACK_WEIGHT_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the weight is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the weight is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the weight is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the weight is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int load_cell_set_weight_callback_threshold(LoadCell *load_cell, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the threshold as set by {@link load_cell_set_weight_callback_threshold}.
 */
int load_cell_get_weight_callback_threshold(LoadCell *load_cell, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletLoadCell
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link LOAD_CELL_CALLBACK_WEIGHT_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link load_cell_set_weight_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int load_cell_set_debounce_period(LoadCell *load_cell, uint32_t debounce);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the debounce period as set by {@link load_cell_set_debounce_period}.
 */
int load_cell_get_debounce_period(LoadCell *load_cell, uint32_t *ret_debounce);

/**
 * \ingroup BrickletLoadCell
 *
 * Sets the length of a `moving averaging <https://en.wikipedia.org/wiki/Moving_average>`__
 * for the weight value.
 * 
 * Setting the length to 1 will turn the averaging off. With less
 * averaging, there is more noise on the data.
 * 
 * The range for the averaging is 1-40.
 * 
 * The default value is 4.
 */
int load_cell_set_moving_average(LoadCell *load_cell, uint8_t average);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the length moving average as set by {@link load_cell_set_moving_average}.
 */
int load_cell_get_moving_average(LoadCell *load_cell, uint8_t *ret_average);

/**
 * \ingroup BrickletLoadCell
 *
 * Turns the LED on.
 */
int load_cell_led_on(LoadCell *load_cell);

/**
 * \ingroup BrickletLoadCell
 *
 * Turns the LED off.
 */
int load_cell_led_off(LoadCell *load_cell);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns *true* if the led is on, *false* otherwise.
 */
int load_cell_is_led_on(LoadCell *load_cell, bool *ret_on);

/**
 * \ingroup BrickletLoadCell
 *
 * To calibrate your Load Cell Bricklet you have to
 * 
 * * empty the scale and call this function with 0 and
 * * add a known weight to the scale and call this function with the weight in 
 *   grams.
 * 
 * The calibration is saved in the EEPROM of the Bricklet and only
 * needs to be done once.
 * 
 * We recommend to use the Brick Viewer for calibration, you don't need
 * to call this function in your source code.
 */
int load_cell_calibrate(LoadCell *load_cell, uint32_t weight);

/**
 * \ingroup BrickletLoadCell
 *
 * Sets the currently measured weight as tare weight.
 */
int load_cell_tare(LoadCell *load_cell);

/**
 * \ingroup BrickletLoadCell
 *
 * The measurement rate and gain are configurable.
 * 
 * The rate can be either 10Hz or 80Hz. A faster rate will produce more noise.
 * It is additionally possible to add a moving average
 * (see {@link load_cell_set_moving_average}) to the measurements.
 * 
 * The gain can be 128x, 64x or 32x. It represents a measurement range of
 * ±20mV, ±40mV and ±80mV respectively. The Load Cell Bricklet uses an
 * excitation voltage of 5V and most load cells use an output of 2mV/V. That
 * means the voltage range is ±15mV for most load cells (i.e. gain of 128x
 * is best). If you don't know what all of this means you should keep it at 
 * 128x, it will most likely be correct.
 * 
 * The configuration is saved in the EEPROM of the Bricklet and only
 * needs to be done once.
 * 
 * We recommend to use the Brick Viewer for configuration, you don't need
 * to call this function in your source code.
 * 
 * The default rate is 10Hz and the default gain is 128x.
 */
int load_cell_set_configuration(LoadCell *load_cell, uint8_t rate, uint8_t gain);

/**
 * \ingroup BrickletLoadCell
 *
 * Returns the configuration as set by {@link load_cell_set_configuration}.
 */
int load_cell_get_configuration(LoadCell *load_cell, uint8_t *ret_rate, uint8_t *ret_gain);

/**
 * \ingroup BrickletLoadCell
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
int load_cell_get_identity(LoadCell *load_cell, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

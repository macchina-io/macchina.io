/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_JOYSTICK_H
#define BRICKLET_JOYSTICK_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletJoystick Joystick Bricklet
 */

/**
 * \ingroup BrickletJoystick
 *
 * 2-axis joystick with push-button
 */
typedef Device Joystick;

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_POSITION 1

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_IS_PRESSED 2

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_ANALOG_VALUE 3

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_CALIBRATE 4

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 11

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 12

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_SET_DEBOUNCE_PERIOD 13

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_DEBOUNCE_PERIOD 14

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletJoystick
 *
 * Signature: \code void callback(int16_t x, int16_t y, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link joystick_set_position_callback_period}. The parameter is the position of the
 * Joystick.
 * 
 * {@link JOYSTICK_CALLBACK_POSITION} is only triggered if the position has changed since the
 * last triggering.
 */
#define JOYSTICK_CALLBACK_POSITION 15

/**
 * \ingroup BrickletJoystick
 *
 * Signature: \code void callback(uint16_t x, uint16_t y, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link joystick_set_analog_value_callback_period}. The parameters are the analog values
 * of the Joystick.
 * 
 * {@link JOYSTICK_CALLBACK_ANALOG_VALUE} is only triggered if the values have changed since the
 * last triggering.
 */
#define JOYSTICK_CALLBACK_ANALOG_VALUE 16

/**
 * \ingroup BrickletJoystick
 *
 * Signature: \code void callback(int16_t x, int16_t y, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link joystick_set_position_callback_threshold} is reached.
 * The parameters are the position of the Joystick.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link joystick_set_debounce_period}.
 */
#define JOYSTICK_CALLBACK_POSITION_REACHED 17

/**
 * \ingroup BrickletJoystick
 *
 * Signature: \code void callback(uint16_t x, uint16_t y, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link joystick_set_analog_value_callback_threshold} is reached.
 * The parameters are the analog values of the Joystick.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link joystick_set_debounce_period}.
 */
#define JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED 18

/**
 * \ingroup BrickletJoystick
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered when the button is pressed.
 */
#define JOYSTICK_CALLBACK_PRESSED 19

/**
 * \ingroup BrickletJoystick
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered when the button is released.
 */
#define JOYSTICK_CALLBACK_RELEASED 20


/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletJoystick
 */
#define JOYSTICK_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletJoystick
 *
 * This constant is used to identify a Joystick Bricklet.
 *
 * The {@link joystick_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define JOYSTICK_DEVICE_IDENTIFIER 210

/**
 * \ingroup BrickletJoystick
 *
 * This constant represents the display name of a Joystick Bricklet.
 */
#define JOYSTICK_DEVICE_DISPLAY_NAME "Joystick Bricklet"

/**
 * \ingroup BrickletJoystick
 *
 * Creates the device object \c joystick with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void joystick_create(Joystick *joystick, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletJoystick
 *
 * Removes the device object \c joystick from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void joystick_destroy(Joystick *joystick);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the joystick_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int joystick_get_response_expected(Joystick *joystick, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletJoystick
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
int joystick_set_response_expected(Joystick *joystick, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletJoystick
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int joystick_set_response_expected_all(Joystick *joystick, bool response_expected);

/**
 * \ingroup BrickletJoystick
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void joystick_register_callback(Joystick *joystick, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int joystick_get_api_version(Joystick *joystick, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the position of the Joystick. The value ranges between -100 and
 * 100 for both axis. The middle position of the joystick is x=0, y=0. The
 * returned values are averaged and calibrated (see {@link joystick_calibrate}).
 * 
 * If you want to get the position periodically, it is recommended to use the
 * callback {@link JOYSTICK_CALLBACK_POSITION} and set the period with 
 * {@link joystick_set_position_callback_period}.
 */
int joystick_get_position(Joystick *joystick, int16_t *ret_x, int16_t *ret_y);

/**
 * \ingroup BrickletJoystick
 *
 * Returns *true* if the button is pressed and *false* otherwise.
 * 
 * It is recommended to use the {@link JOYSTICK_CALLBACK_PRESSED} and {@link JOYSTICK_CALLBACK_RELEASED} callbacks
 * to handle the button.
 */
int joystick_is_pressed(Joystick *joystick, bool *ret_pressed);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the values as read by a 12-bit analog-to-digital converter.
 * The values are between 0 and 4095 for both axis.
 * 
 * \note
 *  The values returned by {@link joystick_get_position} are averaged over several samples
 *  to yield less noise, while {@link joystick_get_analog_value} gives back raw
 *  unfiltered analog values. The only reason to use {@link joystick_get_analog_value} is,
 *  if you need the full resolution of the analog-to-digital converter.
 * 
 * If you want the analog values periodically, it is recommended to use the 
 * callback {@link JOYSTICK_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link joystick_set_analog_value_callback_period}.
 */
int joystick_get_analog_value(Joystick *joystick, uint16_t *ret_x, uint16_t *ret_y);

/**
 * \ingroup BrickletJoystick
 *
 * Calibrates the middle position of the Joystick. If your Joystick Bricklet
 * does not return x=0 and y=0 in the middle position, call this function
 * while the Joystick is standing still in the middle position.
 * 
 * The resulting calibration will be saved on the EEPROM of the Joystick
 * Bricklet, thus you only have to calibrate it once.
 */
int joystick_calibrate(Joystick *joystick);

/**
 * \ingroup BrickletJoystick
 *
 * Sets the period in ms with which the {@link JOYSTICK_CALLBACK_POSITION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link JOYSTICK_CALLBACK_POSITION} is only triggered if the position has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int joystick_set_position_callback_period(Joystick *joystick, uint32_t period);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the period as set by {@link joystick_set_position_callback_period}.
 */
int joystick_get_position_callback_period(Joystick *joystick, uint32_t *ret_period);

/**
 * \ingroup BrickletJoystick
 *
 * Sets the period in ms with which the {@link JOYSTICK_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link JOYSTICK_CALLBACK_ANALOG_VALUE} is only triggered if the analog values have changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int joystick_set_analog_value_callback_period(Joystick *joystick, uint32_t period);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the period as set by {@link joystick_set_analog_value_callback_period}.
 */
int joystick_get_analog_value_callback_period(Joystick *joystick, uint32_t *ret_period);

/**
 * \ingroup BrickletJoystick
 *
 * Sets the thresholds for the {@link JOYSTICK_CALLBACK_POSITION_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the position is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the position is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the position is smaller than the min values (max is ignored)"
 *  "'>'",    "Callback is triggered when the position is greater than the min values (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0, 0, 0).
 */
int joystick_set_position_callback_threshold(Joystick *joystick, char option, int16_t min_x, int16_t max_x, int16_t min_y, int16_t max_y);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the threshold as set by {@link joystick_set_position_callback_threshold}.
 */
int joystick_get_position_callback_threshold(Joystick *joystick, char *ret_option, int16_t *ret_min_x, int16_t *ret_max_x, int16_t *ret_min_y, int16_t *ret_max_y);

/**
 * \ingroup BrickletJoystick
 *
 * Sets the thresholds for the {@link JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the analog values are *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the analog values are *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the analog values are smaller than the min values (max is ignored)"
 *  "'>'",    "Callback is triggered when the analog values are greater than the min values (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0, 0, 0).
 */
int joystick_set_analog_value_callback_threshold(Joystick *joystick, char option, uint16_t min_x, uint16_t max_x, uint16_t min_y, uint16_t max_y);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the threshold as set by {@link joystick_set_analog_value_callback_threshold}.
 */
int joystick_get_analog_value_callback_threshold(Joystick *joystick, char *ret_option, uint16_t *ret_min_x, uint16_t *ret_max_x, uint16_t *ret_min_y, uint16_t *ret_max_y);

/**
 * \ingroup BrickletJoystick
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link JOYSTICK_CALLBACK_POSITION_REACHED},
 * * {@link JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link joystick_set_position_callback_threshold},
 * * {@link joystick_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int joystick_set_debounce_period(Joystick *joystick, uint32_t debounce);

/**
 * \ingroup BrickletJoystick
 *
 * Returns the debounce period as set by {@link joystick_set_debounce_period}.
 */
int joystick_get_debounce_period(Joystick *joystick, uint32_t *ret_debounce);

/**
 * \ingroup BrickletJoystick
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
int joystick_get_identity(Joystick *joystick, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

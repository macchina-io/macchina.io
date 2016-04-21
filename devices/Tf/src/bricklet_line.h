/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_LINE_H
#define BRICKLET_LINE_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletLine Line Bricklet
 */

/**
 * \ingroup BrickletLine
 *
 * Measures reflectivity of a surface
 */
typedef Device Line;

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_GET_REFLECTIVITY 1

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletLine
 */
#define LINE_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletLine
 *
 * Signature: \code void callback(uint16_t reflectivity, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link line_set_reflectivity_callback_period}. The parameter is the reflectivity
 * of the sensor.
 * 
 * {@link LINE_CALLBACK_REFLECTIVITY} is only triggered if the reflectivity has changed since the
 * last triggering.
 */
#define LINE_CALLBACK_REFLECTIVITY 8

/**
 * \ingroup BrickletLine
 *
 * Signature: \code void callback(uint16_t reflectivity, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link line_set_reflectivity_callback_threshold} is reached.
 * The parameter is the reflectivity of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link line_set_debounce_period}.
 */
#define LINE_CALLBACK_REFLECTIVITY_REACHED 9


/**
 * \ingroup BrickletLine
 */
#define LINE_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletLine
 */
#define LINE_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletLine
 */
#define LINE_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletLine
 */
#define LINE_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletLine
 */
#define LINE_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletLine
 *
 * This constant is used to identify a Line Bricklet.
 *
 * The {@link line_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define LINE_DEVICE_IDENTIFIER 241

/**
 * \ingroup BrickletLine
 *
 * This constant represents the display name of a Line Bricklet.
 */
#define LINE_DEVICE_DISPLAY_NAME "Line Bricklet"

/**
 * \ingroup BrickletLine
 *
 * Creates the device object \c line with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void line_create(Line *line, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletLine
 *
 * Removes the device object \c line from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void line_destroy(Line *line);

/**
 * \ingroup BrickletLine
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the line_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int line_get_response_expected(Line *line, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletLine
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
int line_set_response_expected(Line *line, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletLine
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int line_set_response_expected_all(Line *line, bool response_expected);

/**
 * \ingroup BrickletLine
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void line_register_callback(Line *line, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletLine
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int line_get_api_version(Line *line, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletLine
 *
 * Returns the currently measured reflectivity. The reflectivity is
 * a value between 0 (not reflective) and 4095 (very reflective).
 * 
 * Usually black has a low reflectivity while white has a high
 * reflectivity.
 * 
 * If you want to get the reflectivity periodically, it is recommended 
 * to use the callback {@link LINE_CALLBACK_REFLECTIVITY} and set the period with 
 * {@link line_set_reflectivity_callback_period}.
 */
int line_get_reflectivity(Line *line, uint16_t *ret_reflectivity);

/**
 * \ingroup BrickletLine
 *
 * Sets the period in ms with which the {@link LINE_CALLBACK_REFLECTIVITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link LINE_CALLBACK_REFLECTIVITY} is only triggered if the reflectivity has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int line_set_reflectivity_callback_period(Line *line, uint32_t period);

/**
 * \ingroup BrickletLine
 *
 * Returns the period as set by {@link line_set_reflectivity_callback_period}.
 */
int line_get_reflectivity_callback_period(Line *line, uint32_t *ret_period);

/**
 * \ingroup BrickletLine
 *
 * Sets the thresholds for the {@link LINE_CALLBACK_REFLECTIVITY_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the reflectivity is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the reflectivity is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the reflectivity is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the reflectivity is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int line_set_reflectivity_callback_threshold(Line *line, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletLine
 *
 * Returns the threshold as set by {@link line_set_reflectivity_callback_threshold}.
 */
int line_get_reflectivity_callback_threshold(Line *line, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletLine
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link LINE_CALLBACK_REFLECTIVITY_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link line_set_reflectivity_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int line_set_debounce_period(Line *line, uint32_t debounce);

/**
 * \ingroup BrickletLine
 *
 * Returns the debounce period as set by {@link line_set_debounce_period}.
 */
int line_get_debounce_period(Line *line, uint32_t *ret_debounce);

/**
 * \ingroup BrickletLine
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
int line_get_identity(Line *line, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

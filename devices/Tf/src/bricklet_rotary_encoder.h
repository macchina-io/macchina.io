/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_ROTARY_ENCODER_H
#define BRICKLET_ROTARY_ENCODER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRotaryEncoder Rotary Encoder Bricklet
 */

/**
 * \ingroup BrickletRotaryEncoder
 *
 * 360° rotary encoder with push-button
 */
typedef Device RotaryEncoder;

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_GET_COUNT 1

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_SET_COUNT_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_GET_COUNT_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_SET_COUNT_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_GET_COUNT_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_IS_PRESSED 10

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Signature: \code void callback(int32_t count, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link rotary_encoder_set_count_callback_period}. The parameter is the count of
 * the encoder.
 * 
 * {@link ROTARY_ENCODER_CALLBACK_COUNT} is only triggered if the count has changed since the
 * last triggering.
 */
#define ROTARY_ENCODER_CALLBACK_COUNT 8

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Signature: \code void callback(int32_t count, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link rotary_encoder_set_count_callback_threshold} is reached.
 * The parameter is the count of the encoder.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link rotary_encoder_set_debounce_period}.
 */
#define ROTARY_ENCODER_CALLBACK_COUNT_REACHED 9

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered when the button is pressed.
 */
#define ROTARY_ENCODER_CALLBACK_PRESSED 11

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered when the button is released.
 */
#define ROTARY_ENCODER_CALLBACK_RELEASED 12


/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletRotaryEncoder
 */
#define ROTARY_ENCODER_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletRotaryEncoder
 *
 * This constant is used to identify a Rotary Encoder Bricklet.
 *
 * The {@link rotary_encoder_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ROTARY_ENCODER_DEVICE_IDENTIFIER 236

/**
 * \ingroup BrickletRotaryEncoder
 *
 * This constant represents the display name of a Rotary Encoder Bricklet.
 */
#define ROTARY_ENCODER_DEVICE_DISPLAY_NAME "Rotary Encoder Bricklet"

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Creates the device object \c rotary_encoder with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void rotary_encoder_create(RotaryEncoder *rotary_encoder, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Removes the device object \c rotary_encoder from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void rotary_encoder_destroy(RotaryEncoder *rotary_encoder);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the rotary_encoder_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int rotary_encoder_get_response_expected(RotaryEncoder *rotary_encoder, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRotaryEncoder
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
int rotary_encoder_set_response_expected(RotaryEncoder *rotary_encoder, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int rotary_encoder_set_response_expected_all(RotaryEncoder *rotary_encoder, bool response_expected);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void rotary_encoder_register_callback(RotaryEncoder *rotary_encoder, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int rotary_encoder_get_api_version(RotaryEncoder *rotary_encoder, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns the current count of the encoder. If you set reset
 * to true, the count is set back to 0 directly after the
 * current count is read.
 * 
 * The encoder has 24 steps per rotation
 * 
 * Turning the encoder to the left decrements the counter,
 * so a negative count is possible.
 */
int rotary_encoder_get_count(RotaryEncoder *rotary_encoder, bool reset, int32_t *ret_count);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Sets the period in ms with which the {@link ROTARY_ENCODER_CALLBACK_COUNT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link ROTARY_ENCODER_CALLBACK_COUNT} is only triggered if the count has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int rotary_encoder_set_count_callback_period(RotaryEncoder *rotary_encoder, uint32_t period);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns the period as set by {@link rotary_encoder_set_count_callback_period}.
 */
int rotary_encoder_get_count_callback_period(RotaryEncoder *rotary_encoder, uint32_t *ret_period);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Sets the thresholds for the {@link ROTARY_ENCODER_CALLBACK_COUNT_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the count is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the count is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the count is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the count is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int rotary_encoder_set_count_callback_threshold(RotaryEncoder *rotary_encoder, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns the threshold as set by {@link rotary_encoder_set_count_callback_threshold}.
 */
int rotary_encoder_get_count_callback_threshold(RotaryEncoder *rotary_encoder, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link ROTARY_ENCODER_CALLBACK_COUNT_REACHED}
 * 
 * is triggered, if the thresholds
 * 
 * * {@link rotary_encoder_set_count_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int rotary_encoder_set_debounce_period(RotaryEncoder *rotary_encoder, uint32_t debounce);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns the debounce period as set by {@link rotary_encoder_set_debounce_period}.
 */
int rotary_encoder_get_debounce_period(RotaryEncoder *rotary_encoder, uint32_t *ret_debounce);

/**
 * \ingroup BrickletRotaryEncoder
 *
 * Returns *true* if the button is pressed and *false* otherwise.
 * 
 * It is recommended to use the {@link ROTARY_ENCODER_CALLBACK_PRESSED} and {@link ROTARY_ENCODER_CALLBACK_RELEASED} callbacks
 * to handle the button.
 */
int rotary_encoder_is_pressed(RotaryEncoder *rotary_encoder, bool *ret_pressed);

/**
 * \ingroup BrickletRotaryEncoder
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
int rotary_encoder_get_identity(RotaryEncoder *rotary_encoder, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

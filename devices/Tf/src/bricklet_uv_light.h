/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_UV_LIGHT_H
#define BRICKLET_UV_LIGHT_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletUVLight UV Light Bricklet
 */

/**
 * \ingroup BrickletUVLight
 *
 * Measures UV light
 */
typedef Device UVLight;

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_GET_UV_LIGHT 1

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_SET_UV_LIGHT_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_GET_UV_LIGHT_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_SET_UV_LIGHT_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_GET_UV_LIGHT_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletUVLight
 *
 * Signature: \code void callback(uint32_t uv_light, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link uv_light_set_uv_light_callback_period}. The parameter is the UV Light 
 * intensity of the sensor.
 * 
 * {@link UV_LIGHT_CALLBACK_UV_LIGHT} is only triggered if the intensity has changed since the
 * last triggering.
 */
#define UV_LIGHT_CALLBACK_UV_LIGHT 8

/**
 * \ingroup BrickletUVLight
 *
 * Signature: \code void callback(uint32_t uv_light, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link uv_light_set_uv_light_callback_threshold} is reached.
 * The parameter is the UV Light intensity of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link uv_light_set_debounce_period}.
 */
#define UV_LIGHT_CALLBACK_UV_LIGHT_REACHED 9


/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletUVLight
 */
#define UV_LIGHT_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletUVLight
 *
 * This constant is used to identify a UV Light Bricklet.
 *
 * The {@link uv_light_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define UV_LIGHT_DEVICE_IDENTIFIER 265

/**
 * \ingroup BrickletUVLight
 *
 * This constant represents the display name of a UV Light Bricklet.
 */
#define UV_LIGHT_DEVICE_DISPLAY_NAME "UV Light Bricklet"

/**
 * \ingroup BrickletUVLight
 *
 * Creates the device object \c uv_light with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void uv_light_create(UVLight *uv_light, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletUVLight
 *
 * Removes the device object \c uv_light from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void uv_light_destroy(UVLight *uv_light);

/**
 * \ingroup BrickletUVLight
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the uv_light_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int uv_light_get_response_expected(UVLight *uv_light, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletUVLight
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
int uv_light_set_response_expected(UVLight *uv_light, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletUVLight
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int uv_light_set_response_expected_all(UVLight *uv_light, bool response_expected);

/**
 * \ingroup BrickletUVLight
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void uv_light_register_callback(UVLight *uv_light, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletUVLight
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int uv_light_get_api_version(UVLight *uv_light, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletUVLight
 *
 * Returns the UV light intensity of the sensor, the intensity is given
 * in µW/cm².
 * 
 * To get UV Index you have to divide the value by 250. For example, a UV Light
 * intensity of 500µW/cm² is equivalent to an UV Index of 2.
 * 
 * If you want to get the intensity periodically, it is recommended to use the
 * callback {@link UV_LIGHT_CALLBACK_UV_LIGHT} and set the period with 
 * {@link uv_light_set_uv_light_callback_period}.
 */
int uv_light_get_uv_light(UVLight *uv_light, uint32_t *ret_uv_light);

/**
 * \ingroup BrickletUVLight
 *
 * Sets the period in ms with which the {@link UV_LIGHT_CALLBACK_UV_LIGHT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link UV_LIGHT_CALLBACK_UV_LIGHT} is only triggered if the intensity has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int uv_light_set_uv_light_callback_period(UVLight *uv_light, uint32_t period);

/**
 * \ingroup BrickletUVLight
 *
 * Returns the period as set by {@link uv_light_set_uv_light_callback_period}.
 */
int uv_light_get_uv_light_callback_period(UVLight *uv_light, uint32_t *ret_period);

/**
 * \ingroup BrickletUVLight
 *
 * Sets the thresholds for the {@link UV_LIGHT_CALLBACK_UV_LIGHT_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the intensity is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the intensity is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the intensity is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the intensity is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int uv_light_set_uv_light_callback_threshold(UVLight *uv_light, char option, uint32_t min, uint32_t max);

/**
 * \ingroup BrickletUVLight
 *
 * Returns the threshold as set by {@link uv_light_set_uv_light_callback_threshold}.
 */
int uv_light_get_uv_light_callback_threshold(UVLight *uv_light, char *ret_option, uint32_t *ret_min, uint32_t *ret_max);

/**
 * \ingroup BrickletUVLight
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link UV_LIGHT_CALLBACK_UV_LIGHT_REACHED},
 * 
 * are triggered, if the thresholds
 * 
 * * {@link uv_light_set_uv_light_callback_threshold},
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int uv_light_set_debounce_period(UVLight *uv_light, uint32_t debounce);

/**
 * \ingroup BrickletUVLight
 *
 * Returns the debounce period as set by {@link uv_light_set_debounce_period}.
 */
int uv_light_get_debounce_period(UVLight *uv_light, uint32_t *ret_debounce);

/**
 * \ingroup BrickletUVLight
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
int uv_light_get_identity(UVLight *uv_light, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

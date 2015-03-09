/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_COLOR_H
#define BRICKLET_COLOR_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletColor Color Bricklet
 */

/**
 * \ingroup BrickletColor
 *
 * Device for measuring color (RGB value), illuminance and color temperature
 */
typedef Device Color;

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_COLOR 1

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_SET_COLOR_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_COLOR_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_SET_COLOR_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_COLOR_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_LIGHT_ON 10

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_LIGHT_OFF 11

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_IS_LIGHT_ON 12

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_SET_CONFIG 13

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_CONFIG 14

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_ILLUMINANCE 15

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_COLOR_TEMPERATURE 16

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD 17

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD 18

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_SET_COLOR_TEMPERATURE_CALLBACK_PERIOD 19

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_COLOR_TEMPERATURE_CALLBACK_PERIOD 20

/**
 * \ingroup BrickletColor
 */
#define COLOR_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletColor
 *
 * Signature: \code void callback(uint16_t r, uint16_t g, uint16_t b, uint16_t c, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link color_set_color_callback_period}. The parameter is the color
 * of the sensor as RGBC.
 * 
 * {@link COLOR_CALLBACK_COLOR} is only triggered if the color has changed since the
 * last triggering.
 */
#define COLOR_CALLBACK_COLOR 8

/**
 * \ingroup BrickletColor
 *
 * Signature: \code void callback(uint16_t r, uint16_t g, uint16_t b, uint16_t c, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link color_set_color_callback_period}. The parameter is the color
 * of the sensor as RGBC.
 * 
 * {@link COLOR_CALLBACK_COLOR} is only triggered if the color has changed since the
 * last triggering.
 */
#define COLOR_CALLBACK_COLOR_REACHED 9

/**
 * \ingroup BrickletColor
 *
 * Signature: \code void callback(uint32_t illuminance, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link color_set_illuminance_callback_period}. The parameter is the illuminance.
 * See {@link color_get_illuminance} for how to interrept this value.
 * 
 * {@link COLOR_CALLBACK_ILLUMINANCE} is only triggered if the illuminance has changed since the
 * last triggering.
 */
#define COLOR_CALLBACK_ILLUMINANCE 21

/**
 * \ingroup BrickletColor
 *
 * Signature: \code void callback(uint16_t color_temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link color_set_color_temperature_callback_period}. The parameter is the 
 * color temperature in Kelvin.
 * 
 * {@link COLOR_CALLBACK_COLOR_TEMPERATURE} is only triggered if the color temperature has 
 * changed since the last triggering.
 */
#define COLOR_CALLBACK_COLOR_TEMPERATURE 22


/**
 * \ingroup BrickletColor
 */
#define COLOR_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletColor
 */
#define COLOR_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletColor
 */
#define COLOR_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletColor
 */
#define COLOR_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletColor
 */
#define COLOR_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletColor
 */
#define COLOR_LIGHT_ON 0

/**
 * \ingroup BrickletColor
 */
#define COLOR_LIGHT_OFF 1

/**
 * \ingroup BrickletColor
 */
#define COLOR_GAIN_1X 0

/**
 * \ingroup BrickletColor
 */
#define COLOR_GAIN_4X 1

/**
 * \ingroup BrickletColor
 */
#define COLOR_GAIN_16X 2

/**
 * \ingroup BrickletColor
 */
#define COLOR_GAIN_60X 3

/**
 * \ingroup BrickletColor
 */
#define COLOR_INTEGRATION_TIME_2MS 0

/**
 * \ingroup BrickletColor
 */
#define COLOR_INTEGRATION_TIME_24MS 1

/**
 * \ingroup BrickletColor
 */
#define COLOR_INTEGRATION_TIME_101MS 2

/**
 * \ingroup BrickletColor
 */
#define COLOR_INTEGRATION_TIME_154MS 3

/**
 * \ingroup BrickletColor
 */
#define COLOR_INTEGRATION_TIME_700MS 4

/**
 * \ingroup BrickletColor
 *
 * This constant is used to identify a Color Bricklet.
 *
 * The {@link color_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define COLOR_DEVICE_IDENTIFIER 243

/**
 * \ingroup BrickletColor
 *
 * Creates the device object \c color with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void color_create(Color *color, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletColor
 *
 * Removes the device object \c color from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void color_destroy(Color *color);

/**
 * \ingroup BrickletColor
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the color_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int color_get_response_expected(Color *color, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletColor
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
int color_set_response_expected(Color *color, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletColor
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int color_set_response_expected_all(Color *color, bool response_expected);

/**
 * \ingroup BrickletColor
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void color_register_callback(Color *color, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletColor
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int color_get_api_version(Color *color, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletColor
 *
 * Returns the measured color of the sensor. The values
 * have a range of 0 to 65535.
 * 
 * The red (r), green (g), blue (b) and clear (c) colors are measured
 * with four different photodiodes that are responsive at different
 * wavelengths:
 * 
 * .. image:: /Images/Bricklets/bricklet_color_wavelength_chart_600.jpg
 *    :scale: 100 %
 *    :alt: Chart Responsivity / Wavelength
 *    :align: center
 *    :target: ../../_images/Bricklets/bricklet_color_wavelength_chart_600.jpg
 * 
 * If you want to get the color periodically, it is recommended 
 * to use the callback {@link COLOR_CALLBACK_COLOR} and set the period with 
 * {@link color_set_color_callback_period}.
 */
int color_get_color(Color *color, uint16_t *ret_r, uint16_t *ret_g, uint16_t *ret_b, uint16_t *ret_c);

/**
 * \ingroup BrickletColor
 *
 * Sets the period in ms with which the {@link COLOR_CALLBACK_COLOR} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link COLOR_CALLBACK_COLOR} is only triggered if the color has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int color_set_color_callback_period(Color *color, uint32_t period);

/**
 * \ingroup BrickletColor
 *
 * Returns the period as set by {@link color_set_color_callback_period}.
 */
int color_get_color_callback_period(Color *color, uint32_t *ret_period);

/**
 * \ingroup BrickletColor
 *
 * Sets the thresholds for the {@link COLOR_CALLBACK_COLOR_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the temperature is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the temperature is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the temperature is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the temperature is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0, 0, 0, 0, 0, 0, 0).
 */
int color_set_color_callback_threshold(Color *color, char option, uint16_t min_r, uint16_t max_r, uint16_t min_g, uint16_t max_g, uint16_t min_b, uint16_t max_b, uint16_t min_c, uint16_t max_c);

/**
 * \ingroup BrickletColor
 *
 * Returns the threshold as set by {@link color_set_color_callback_threshold}.
 */
int color_get_color_callback_threshold(Color *color, char *ret_option, uint16_t *ret_min_r, uint16_t *ret_max_r, uint16_t *ret_min_g, uint16_t *ret_max_g, uint16_t *ret_min_b, uint16_t *ret_max_b, uint16_t *ret_min_c, uint16_t *ret_max_c);

/**
 * \ingroup BrickletColor
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link COLOR_CALLBACK_COLOR_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link color_set_color_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int color_set_debounce_period(Color *color, uint32_t debounce);

/**
 * \ingroup BrickletColor
 *
 * Returns the debounce period as set by {@link color_set_debounce_period}.
 */
int color_get_debounce_period(Color *color, uint32_t *ret_debounce);

/**
 * \ingroup BrickletColor
 *
 * Turns the LED on.
 */
int color_light_on(Color *color);

/**
 * \ingroup BrickletColor
 *
 * Turns the LED off.
 */
int color_light_off(Color *color);

/**
 * \ingroup BrickletColor
 *
 * Returns the state of the LED. Possible values are:
 * 
 * * 0: On
 * * 1: Off
 */
int color_is_light_on(Color *color, uint8_t *ret_light);

/**
 * \ingroup BrickletColor
 *
 * Sets the configuration of the sensor. Gain and integration time
 * can be configured in this way.
 * 
 * For configuring the gain:
 * 
 * * 0: 1x Gain
 * * 1: 4x Gain
 * * 2: 16x Gain
 * * 3: 60x Gain
 * 
 * For configuring the integration time:
 * 
 * * 0: 2.4ms
 * * 1: 24ms
 * * 2: 101ms
 * * 3: 154ms
 * * 4: 700ms
 * 
 * Increasing the gain enables the sensor to detect a
 * color from a higher distance.
 * 
 * The integration time provides a trade-off between conversion time
 * and accuracy. With a longer integration time the values read will
 * be more accurate but it will take longer time to get the conversion
 * results.
 * 
 * The default values are 60x gain and 154ms integration time.
 */
int color_set_config(Color *color, uint8_t gain, uint8_t integration_time);

/**
 * \ingroup BrickletColor
 *
 * Returns the configuration as set by {@link color_set_config}.
 */
int color_get_config(Color *color, uint8_t *ret_gain, uint8_t *ret_integration_time);

/**
 * \ingroup BrickletColor
 *
 * Returns the illuminance affected by the gain and integration time as
 * set by {@link color_set_config}. To get the illuminance in Lux apply this formula::
 * 
 *  lux = illuminance * 700 / gain / integration_time
 * 
 * To get a correct illuminance measurement make sure that the color
 * values themself are not saturated. The color value (R, G or B)
 * is saturated if it is equal to the maximum value of 65535.
 * In that case you have to reduce the gain, see {@link color_set_config}.
 */
int color_get_illuminance(Color *color, uint32_t *ret_illuminance);

/**
 * \ingroup BrickletColor
 *
 * Returns the color temperature in Kelvin.
 * 
 * To get a correct color temperature measurement make sure that the color
 * values themself are not saturated. The color value (R, G or B)
 * is saturated if it is equal to the maximum value of 65535.
 * In that case you have to reduce the gain, see {@link color_set_config}.
 */
int color_get_color_temperature(Color *color, uint16_t *ret_color_temperature);

/**
 * \ingroup BrickletColor
 *
 * Sets the period in ms with which the {@link COLOR_CALLBACK_ILLUMINANCE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link COLOR_CALLBACK_ILLUMINANCE} is only triggered if the illuminance has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int color_set_illuminance_callback_period(Color *color, uint32_t period);

/**
 * \ingroup BrickletColor
 *
 * Returns the period as set by {@link color_set_illuminance_callback_period}.
 */
int color_get_illuminance_callback_period(Color *color, uint32_t *ret_period);

/**
 * \ingroup BrickletColor
 *
 * Sets the period in ms with which the {@link COLOR_CALLBACK_COLOR_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link COLOR_CALLBACK_COLOR_TEMPERATURE} is only triggered if the color temperature has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int color_set_color_temperature_callback_period(Color *color, uint32_t period);

/**
 * \ingroup BrickletColor
 *
 * Returns the period as set by {@link color_set_color_temperature_callback_period}.
 */
int color_get_color_temperature_callback_period(Color *color, uint32_t *ret_period);

/**
 * \ingroup BrickletColor
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
int color_get_identity(Color *color, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

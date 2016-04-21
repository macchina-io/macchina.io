/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_AMBIENT_LIGHT_V2_H
#define BRICKLET_AMBIENT_LIGHT_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletAmbientLightV2 Ambient Light Bricklet 2.0
 */

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Measures ambient light up to 64000lux
 */
typedef Device AmbientLightV2;

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE 1

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_SET_ILLUMINANCE_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_GET_ILLUMINANCE_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_SET_CONFIGURATION 8

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_GET_CONFIGURATION 9

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Signature: \code void callback(uint32_t illuminance, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link ambient_light_v2_set_illuminance_callback_period}. The parameter is the illuminance of the
 * ambient light sensor.
 * 
 * {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE} is only triggered if the illuminance has changed since the
 * last triggering.
 */
#define AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE 10

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Signature: \code void callback(uint32_t illuminance, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link ambient_light_v2_set_illuminance_callback_threshold} is reached.
 * The parameter is the illuminance of the ambient light sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link ambient_light_v2_set_debounce_period}.
 */
#define AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED 11


/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_UNLIMITED 6

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_64000LUX 0

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_32000LUX 1

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_16000LUX 2

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_8000LUX 3

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_1300LUX 4

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_ILLUMINANCE_RANGE_600LUX 5

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_50MS 0

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_100MS 1

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_150MS 2

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_200MS 3

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_250MS 4

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_300MS 5

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_350MS 6

/**
 * \ingroup BrickletAmbientLightV2
 */
#define AMBIENT_LIGHT_V2_INTEGRATION_TIME_400MS 7

/**
 * \ingroup BrickletAmbientLightV2
 *
 * This constant is used to identify a Ambient Light Bricklet 2.0.
 *
 * The {@link ambient_light_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define AMBIENT_LIGHT_V2_DEVICE_IDENTIFIER 259

/**
 * \ingroup BrickletAmbientLightV2
 *
 * This constant represents the display name of a Ambient Light Bricklet 2.0.
 */
#define AMBIENT_LIGHT_V2_DEVICE_DISPLAY_NAME "Ambient Light Bricklet 2.0"

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Creates the device object \c ambient_light_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void ambient_light_v2_create(AmbientLightV2 *ambient_light_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Removes the device object \c ambient_light_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void ambient_light_v2_destroy(AmbientLightV2 *ambient_light_v2);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the ambient_light_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int ambient_light_v2_get_response_expected(AmbientLightV2 *ambient_light_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletAmbientLightV2
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
int ambient_light_v2_set_response_expected(AmbientLightV2 *ambient_light_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int ambient_light_v2_set_response_expected_all(AmbientLightV2 *ambient_light_v2, bool response_expected);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void ambient_light_v2_register_callback(AmbientLightV2 *ambient_light_v2, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int ambient_light_v2_get_api_version(AmbientLightV2 *ambient_light_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the illuminance of the ambient light sensor. The measurement range goes
 * up to about 100000lux, but above 64000lux the precision starts to drop.
 * The illuminance is given in lux/100, i.e. a value of 450000 means that an
 * illuminance of 4500lux is measured.
 * 
 * .. versionchanged:: 2.0.2$nbsp;(Plugin)
 *   An illuminance of 0lux indicates that the sensor is saturated and the
 *   configuration should be modified, see {@link ambient_light_v2_set_configuration}.
 * 
 * If you want to get the illuminance periodically, it is recommended to use the
 * callback {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE} and set the period with 
 * {@link ambient_light_v2_set_illuminance_callback_period}.
 */
int ambient_light_v2_get_illuminance(AmbientLightV2 *ambient_light_v2, uint32_t *ret_illuminance);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Sets the period in ms with which the {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE} is only triggered if the illuminance has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int ambient_light_v2_set_illuminance_callback_period(AmbientLightV2 *ambient_light_v2, uint32_t period);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the period as set by {@link ambient_light_v2_set_illuminance_callback_period}.
 */
int ambient_light_v2_get_illuminance_callback_period(AmbientLightV2 *ambient_light_v2, uint32_t *ret_period);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Sets the thresholds for the {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the illuminance is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the illuminance is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the illuminance is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the illuminance is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int ambient_light_v2_set_illuminance_callback_threshold(AmbientLightV2 *ambient_light_v2, char option, uint32_t min, uint32_t max);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the threshold as set by {@link ambient_light_v2_set_illuminance_callback_threshold}.
 */
int ambient_light_v2_get_illuminance_callback_threshold(AmbientLightV2 *ambient_light_v2, char *ret_option, uint32_t *ret_min, uint32_t *ret_max);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE_REACHED},
 * 
 * are triggered, if the thresholds
 * 
 * * {@link ambient_light_v2_set_illuminance_callback_threshold},
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int ambient_light_v2_set_debounce_period(AmbientLightV2 *ambient_light_v2, uint32_t debounce);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the debounce period as set by {@link ambient_light_v2_set_debounce_period}.
 */
int ambient_light_v2_get_debounce_period(AmbientLightV2 *ambient_light_v2, uint32_t *ret_debounce);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Sets the configuration. It is possible to configure an illuminance range
 * between 0-600lux and 0-64000lux and an integration time between 50ms and 400ms.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Plugin)
 *   The unlimited illuminance range allows to measure up to about 100000lux, but
 *   above 64000lux the precision starts to drop.
 * 
 * A smaller illuminance range increases the resolution of the data. A longer
 * integration time will result in less noise on the data.
 * 
 * .. versionchanged:: 2.0.2$nbsp;(Plugin)
 *   If the actual measure illuminance is out-of-range then the current illuminance
 *   range maximum +0.01lux is reported by {@link ambient_light_v2_get_illuminance} and the
 *   {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE} callback. For example, 800001 for the 0-8000lux range.
 * 
 * .. versionchanged:: 2.0.2$nbsp;(Plugin)
 *   With a long integration time the sensor might be saturated before the measured
 *   value reaches the maximum of the selected illuminance range. In this case 0lux
 *   is reported by {@link ambient_light_v2_get_illuminance} and the {@link AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE} callback.
 * 
 * If the measurement is out-of-range or the sensor is saturated then you should
 * configure the next higher illuminance range. If the highest range is already
 * in use, then start to reduce the integration time.
 * 
 * The default values are 0-8000lux illuminance range and 200ms integration time.
 */
int ambient_light_v2_set_configuration(AmbientLightV2 *ambient_light_v2, uint8_t illuminance_range, uint8_t integration_time);

/**
 * \ingroup BrickletAmbientLightV2
 *
 * Returns the configuration as set by {@link ambient_light_v2_set_configuration}.
 */
int ambient_light_v2_get_configuration(AmbientLightV2 *ambient_light_v2, uint8_t *ret_illuminance_range, uint8_t *ret_integration_time);

/**
 * \ingroup BrickletAmbientLightV2
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
int ambient_light_v2_get_identity(AmbientLightV2 *ambient_light_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

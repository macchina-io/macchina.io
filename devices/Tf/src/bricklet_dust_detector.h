/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_DUST_DETECTOR_H
#define BRICKLET_DUST_DETECTOR_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletDustDetector Dust Detector Bricklet
 */

/**
 * \ingroup BrickletDustDetector
 *
 * Measures dust density
 */
typedef Device DustDetector;

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY 1

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_SET_DUST_DENSITY_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_SET_DUST_DENSITY_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_GET_DUST_DENSITY_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_SET_MOVING_AVERAGE 10

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_GET_MOVING_AVERAGE 11

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletDustDetector
 *
 * Signature: \code void callback(uint16_t dust_density, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link dust_detector_set_dust_density_callback_period}. The parameter is the 
 * dust density of the sensor.
 * 
 * {@link DUST_DETECTOR_CALLBACK_DUST_DENSITY} is only triggered if the dust density value has changed since the
 * last triggering.
 */
#define DUST_DETECTOR_CALLBACK_DUST_DENSITY 8

/**
 * \ingroup BrickletDustDetector
 *
 * Signature: \code void callback(uint16_t dust_density, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link dust_detector_set_dust_density_callback_threshold} is reached.
 * The parameter is the dust density of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link dust_detector_set_debounce_period}.
 */
#define DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED 9


/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletDustDetector
 */
#define DUST_DETECTOR_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletDustDetector
 *
 * This constant is used to identify a Dust Detector Bricklet.
 *
 * The {@link dust_detector_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define DUST_DETECTOR_DEVICE_IDENTIFIER 260

/**
 * \ingroup BrickletDustDetector
 *
 * This constant represents the display name of a Dust Detector Bricklet.
 */
#define DUST_DETECTOR_DEVICE_DISPLAY_NAME "Dust Detector Bricklet"

/**
 * \ingroup BrickletDustDetector
 *
 * Creates the device object \c dust_detector with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void dust_detector_create(DustDetector *dust_detector, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletDustDetector
 *
 * Removes the device object \c dust_detector from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void dust_detector_destroy(DustDetector *dust_detector);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the dust_detector_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int dust_detector_get_response_expected(DustDetector *dust_detector, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletDustDetector
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
int dust_detector_set_response_expected(DustDetector *dust_detector, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletDustDetector
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int dust_detector_set_response_expected_all(DustDetector *dust_detector, bool response_expected);

/**
 * \ingroup BrickletDustDetector
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void dust_detector_register_callback(DustDetector *dust_detector, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int dust_detector_get_api_version(DustDetector *dust_detector, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the dust density in µg/m³.
 * 
 * If you want to get the dust density periodically, it is recommended 
 * to use the callback {@link DUST_DETECTOR_CALLBACK_DUST_DENSITY} and set the period with 
 * {@link dust_detector_set_dust_density_callback_period}.
 */
int dust_detector_get_dust_density(DustDetector *dust_detector, uint16_t *ret_dust_density);

/**
 * \ingroup BrickletDustDetector
 *
 * Sets the period in ms with which the {@link DUST_DETECTOR_CALLBACK_DUST_DENSITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link DUST_DETECTOR_CALLBACK_DUST_DENSITY} is only triggered if the dust density has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int dust_detector_set_dust_density_callback_period(DustDetector *dust_detector, uint32_t period);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the period as set by {@link dust_detector_set_dust_density_callback_period}.
 */
int dust_detector_get_dust_density_callback_period(DustDetector *dust_detector, uint32_t *ret_period);

/**
 * \ingroup BrickletDustDetector
 *
 * Sets the thresholds for the {@link DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the dust density value is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the dust density value is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the dust density value is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the dust density value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int dust_detector_set_dust_density_callback_threshold(DustDetector *dust_detector, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the threshold as set by {@link dust_detector_set_dust_density_callback_threshold}.
 */
int dust_detector_get_dust_density_callback_threshold(DustDetector *dust_detector, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletDustDetector
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link DUST_DETECTOR_CALLBACK_DUST_DENSITY_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link dust_detector_set_dust_density_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int dust_detector_set_debounce_period(DustDetector *dust_detector, uint32_t debounce);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the debounce period as set by {@link dust_detector_set_debounce_period}.
 */
int dust_detector_get_debounce_period(DustDetector *dust_detector, uint32_t *ret_debounce);

/**
 * \ingroup BrickletDustDetector
 *
 * Sets the length of a `moving averaging <https://en.wikipedia.org/wiki/Moving_average>`__
 * for the dust_density.
 * 
 * Setting the length to 0 will turn the averaging completely off. With less
 * averaging, there is more noise on the data.
 * 
 * The range for the averaging is 0-100.
 * 
 * The default value is 100.
 */
int dust_detector_set_moving_average(DustDetector *dust_detector, uint8_t average);

/**
 * \ingroup BrickletDustDetector
 *
 * Returns the length moving average as set by {@link dust_detector_set_moving_average}.
 */
int dust_detector_get_moving_average(DustDetector *dust_detector, uint8_t *ret_average);

/**
 * \ingroup BrickletDustDetector
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
int dust_detector_get_identity(DustDetector *dust_detector, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

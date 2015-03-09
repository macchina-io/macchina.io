/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_DUAL_0_20MA_H
#define BRICKLET_INDUSTRIAL_DUAL_0_20MA_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialDual020mA IndustrialDual020mA Bricklet
 */

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Device for sensing two currents between 0 and 20mA (IEC 60381-1)
 */
typedef Device IndustrialDual020mA;

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_GET_CURRENT 1

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_SET_CURRENT_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_GET_CURRENT_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_SET_SAMPLE_RATE 8

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_GET_SAMPLE_RATE 9

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Signature: \code void callback(uint8_t sensor, int32_t current, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link industrial_dual_0_20ma_set_current_callback_period}. The parameter is the current of the
 * sensor.
 * 
 * {@link INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 */
#define INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT 10

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Signature: \code void callback(uint8_t sensor, int32_t current, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link industrial_dual_0_20ma_set_current_callback_threshold} is reached.
 * The parameter is the current of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link industrial_dual_0_20ma_set_debounce_period}.
 */
#define INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT_REACHED 11


/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_SAMPLE_RATE_240_SPS 0

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_SAMPLE_RATE_60_SPS 1

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_SAMPLE_RATE_15_SPS 2

/**
 * \ingroup BrickletIndustrialDual020mA
 */
#define INDUSTRIAL_DUAL_0_20MA_SAMPLE_RATE_4_SPS 3

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * This constant is used to identify a IndustrialDual020mA Bricklet.
 *
 * The {@link industrial_dual_0_20ma_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_DUAL_0_20MA_DEVICE_IDENTIFIER 228

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Creates the device object \c industrial_dual_0_20ma with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_dual_0_20ma_create(IndustrialDual020mA *industrial_dual_0_20ma, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Removes the device object \c industrial_dual_0_20ma from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_dual_0_20ma_destroy(IndustrialDual020mA *industrial_dual_0_20ma);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_dual_0_20ma_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_dual_0_20ma_get_response_expected(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialDual020mA
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
int industrial_dual_0_20ma_set_response_expected(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_dual_0_20ma_set_response_expected_all(IndustrialDual020mA *industrial_dual_0_20ma, bool response_expected);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void industrial_dual_0_20ma_register_callback(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_dual_0_20ma_get_api_version(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the current of the specified sensor (0 or 1). The value is in nA
 * and between 0nA and 22505322nA (22.5mA).
 * 
 * It is possible to detect if an IEC 60381-1 compatible sensor is connected
 * and if it works probably.
 * 
 * If the returned current is below 4mA, there is likely no sensor connected
 * or the sensor may be defect. If the returned current is over 20mA, there might
 * be a short circuit or the sensor may be defect.
 * 
 * If you want to get the current periodically, it is recommended to use the
 * callback {@link INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT} and set the period with 
 * {@link industrial_dual_0_20ma_set_current_callback_period}.
 */
int industrial_dual_0_20ma_get_current(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t sensor, int32_t *ret_current);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Sets the period in ms with which the {@link INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT} callback is triggered
 * periodically for the given sensor. A value of 0 turns the callback off.
 * 
 * {@link INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int industrial_dual_0_20ma_set_current_callback_period(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t sensor, uint32_t period);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the period as set by {@link industrial_dual_0_20ma_set_current_callback_period}.
 */
int industrial_dual_0_20ma_get_current_callback_period(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t sensor, uint32_t *ret_period);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Sets the thresholds for the {@link INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT_REACHED} callback for the given
 * sensor.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the current is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the current is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the current is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the current is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int industrial_dual_0_20ma_set_current_callback_threshold(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t sensor, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the threshold as set by {@link industrial_dual_0_20ma_set_current_callback_threshold}.
 */
int industrial_dual_0_20ma_get_current_callback_threshold(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t sensor, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link industrial_dual_0_20ma_set_current_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int industrial_dual_0_20ma_set_debounce_period(IndustrialDual020mA *industrial_dual_0_20ma, uint32_t debounce);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the debounce period as set by {@link industrial_dual_0_20ma_set_debounce_period}.
 */
int industrial_dual_0_20ma_get_debounce_period(IndustrialDual020mA *industrial_dual_0_20ma, uint32_t *ret_debounce);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Sets the sample rate to either 240, 60, 15 or 4 samples per second.
 * The resolution for the rates is 12, 14, 16 and 18 bit respectively.
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0",    "240 samples per second, 12 bit resolution"
 *  "1",    "60 samples per second, 14 bit resolution"
 *  "2",    "15 samples per second, 16 bit resolution"
 *  "3",    "4 samples per second, 18 bit resolution"
 * \endverbatim
 * 
 * The default value is 3: 4 samples per second with 18 bit resolution.
 */
int industrial_dual_0_20ma_set_sample_rate(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t rate);

/**
 * \ingroup BrickletIndustrialDual020mA
 *
 * Returns the sample rate as set by {@link industrial_dual_0_20ma_set_sample_rate}.
 */
int industrial_dual_0_20ma_get_sample_rate(IndustrialDual020mA *industrial_dual_0_20ma, uint8_t *ret_rate);

/**
 * \ingroup BrickletIndustrialDual020mA
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
int industrial_dual_0_20ma_get_identity(IndustrialDual020mA *industrial_dual_0_20ma, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

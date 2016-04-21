/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_DUAL_ANALOG_IN_H
#define BRICKLET_INDUSTRIAL_DUAL_ANALOG_IN_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialDualAnalogIn Industrial Dual Analog In Bricklet
 */

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Measures two DC voltages between -35V and +35V with 24bit resolution each
 */
typedef Device IndustrialDualAnalogIn;

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE 1

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_SAMPLE_RATE 8

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_SAMPLE_RATE 9

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_SET_CALIBRATION 10

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_CALIBRATION 11

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_ADC_VALUES 12

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Signature: \code void callback(uint8_t channel, int32_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link industrial_dual_analog_in_set_voltage_callback_period}. The parameter is the voltage of the
 * channel.
 * 
 * {@link INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE 13

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Signature: \code void callback(uint8_t channel, int32_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link industrial_dual_analog_in_set_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the channel.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link industrial_dual_analog_in_set_debounce_period}.
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED 14


/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_976_SPS 0

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_488_SPS 1

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_244_SPS 2

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_122_SPS 3

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_61_SPS 4

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_4_SPS 5

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_2_SPS 6

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_SAMPLE_RATE_1_SPS 7

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * This constant is used to identify a Industrial Dual Analog In Bricklet.
 *
 * The {@link industrial_dual_analog_in_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_DEVICE_IDENTIFIER 249

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * This constant represents the display name of a Industrial Dual Analog In Bricklet.
 */
#define INDUSTRIAL_DUAL_ANALOG_IN_DEVICE_DISPLAY_NAME "Industrial Dual Analog In Bricklet"

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Creates the device object \c industrial_dual_analog_in with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_dual_analog_in_create(IndustrialDualAnalogIn *industrial_dual_analog_in, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Removes the device object \c industrial_dual_analog_in from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_dual_analog_in_destroy(IndustrialDualAnalogIn *industrial_dual_analog_in);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_dual_analog_in_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_dual_analog_in_get_response_expected(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
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
int industrial_dual_analog_in_set_response_expected(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_dual_analog_in_set_response_expected_all(IndustrialDualAnalogIn *industrial_dual_analog_in, bool response_expected);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void industrial_dual_analog_in_register_callback(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_dual_analog_in_get_api_version(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the voltage for the given channel in mV.
 * 
 * If you want to get the voltage periodically, it is recommended to use the
 * callback {@link INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE} and set the period with 
 * {@link industrial_dual_analog_in_set_voltage_callback_period}.
 */
int industrial_dual_analog_in_get_voltage(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, int32_t *ret_voltage);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Sets the period in ms with which the {@link INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE} callback is triggered
 * periodically for the given channel. A value of 0 turns the callback off.
 * 
 * {@link INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int industrial_dual_analog_in_set_voltage_callback_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, uint32_t period);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the period as set by {@link industrial_dual_analog_in_set_voltage_callback_period}.
 */
int industrial_dual_analog_in_get_voltage_callback_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, uint32_t *ret_period);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Sets the thresholds for the {@link INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED} callback for the given
 * channel.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the voltage is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the voltage is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the voltage is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the voltage is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int industrial_dual_analog_in_set_voltage_callback_threshold(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the threshold as set by {@link industrial_dual_analog_in_set_voltage_callback_threshold}.
 */
int industrial_dual_analog_in_get_voltage_callback_threshold(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t channel, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link industrial_dual_analog_in_set_voltage_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int industrial_dual_analog_in_set_debounce_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint32_t debounce);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the debounce period as set by {@link industrial_dual_analog_in_set_debounce_period}.
 */
int industrial_dual_analog_in_get_debounce_period(IndustrialDualAnalogIn *industrial_dual_analog_in, uint32_t *ret_debounce);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Sets the sample rate. The sample rate can be between 1 sample per second
 * and 976 samples per second. Decreasing the sample rate will also decrease the
 * noise on the data.
 * 
 * The default value is 6 (2 samples per second).
 */
int industrial_dual_analog_in_set_sample_rate(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t rate);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the sample rate as set by {@link industrial_dual_analog_in_set_sample_rate}.
 */
int industrial_dual_analog_in_get_sample_rate(IndustrialDualAnalogIn *industrial_dual_analog_in, uint8_t *ret_rate);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Sets offset and gain of MCP3911 internal calibration registers.
 * 
 * See MCP3911 datasheet 7.7 and 7.8. The Industrial Dual Analog In Bricklet
 * is already factory calibrated by Tinkerforge. It should not be necessary
 * for you to use this function
 */
int industrial_dual_analog_in_set_calibration(IndustrialDualAnalogIn *industrial_dual_analog_in, int32_t offset[2], int32_t gain[2]);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the calibration as set by {@link industrial_dual_analog_in_set_calibration}.
 */
int industrial_dual_analog_in_get_calibration(IndustrialDualAnalogIn *industrial_dual_analog_in, int32_t ret_offset[2], int32_t ret_gain[2]);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
 *
 * Returns the ADC values as given by the MCP3911 IC. This function
 * is needed for proper calibration, see {@link industrial_dual_analog_in_set_calibration}.
 */
int industrial_dual_analog_in_get_adc_values(IndustrialDualAnalogIn *industrial_dual_analog_in, int32_t ret_value[2]);

/**
 * \ingroup BrickletIndustrialDualAnalogIn
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
int industrial_dual_analog_in_get_identity(IndustrialDualAnalogIn *industrial_dual_analog_in, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

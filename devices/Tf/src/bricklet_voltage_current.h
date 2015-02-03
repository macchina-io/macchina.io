/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_VOLTAGE_CURRENT_H
#define BRICKLET_VOLTAGE_CURRENT_H

#include "ip_connection.h"

/**
 * \defgroup BrickletVoltageCurrent VoltageCurrent Bricklet
 */

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Device for high precision sensing of voltage and current
 */
typedef Device VoltageCurrent;

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_CURRENT 1

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE 2

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_POWER 3

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_CONFIGURATION 4

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_CONFIGURATION 5

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_CALIBRATION 6

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_CALIBRATION 7

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_CURRENT_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_CURRENT_CALLBACK_PERIOD 9

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD 10

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD 11

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_POWER_CALLBACK_PERIOD 12

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_POWER_CALLBACK_PERIOD 13

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD 14

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD 15

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD 16

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD 17

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_POWER_CALLBACK_THRESHOLD 18

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_POWER_CALLBACK_THRESHOLD 19

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_SET_DEBOUNCE_PERIOD 20

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_DEBOUNCE_PERIOD 21

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Signature: \code void callback(int32_t current, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link voltage_current_set_current_callback_period}. The parameter is the current of the
 * sensor.
 * 
 * {@link VOLTAGE_CURRENT_CALLBACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 */
#define VOLTAGE_CURRENT_CALLBACK_CURRENT 22

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Signature: \code void callback(int32_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link voltage_current_set_voltage_callback_period}. The parameter is the voltage of the
 * sensor.
 * 
 * {@link VOLTAGE_CURRENT_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 */
#define VOLTAGE_CURRENT_CALLBACK_VOLTAGE 23

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Signature: \code void callback(int32_t power, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link voltage_current_set_power_callback_period}. The parameter is the power of the
 * sensor.
 * 
 * {@link VOLTAGE_CURRENT_CALLBACK_POWER} is only triggered if the power has changed since the
 * last triggering.
 */
#define VOLTAGE_CURRENT_CALLBACK_POWER 24

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Signature: \code void callback(int32_t current, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link voltage_current_set_current_callback_threshold} is reached.
 * The parameter is the current of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link voltage_current_set_debounce_period}.
 */
#define VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED 25

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Signature: \code void callback(int32_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link voltage_current_set_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link voltage_current_set_debounce_period}.
 */
#define VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED 26

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Signature: \code void callback(int32_t power, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link voltage_current_set_power_callback_threshold} is reached.
 * The parameter is the power of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link voltage_current_set_debounce_period}.
 */
#define VOLTAGE_CURRENT_CALLBACK_POWER_REACHED 27


/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_1 0

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_4 1

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_16 2

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_64 3

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_128 4

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_256 5

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_512 6

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_AVERAGING_1024 7

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletVoltageCurrent
 */
#define VOLTAGE_CURRENT_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletVoltageCurrent
 *
 * This constant is used to identify a VoltageCurrent Bricklet.
 *
 * The {@link voltage_current_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define VOLTAGE_CURRENT_DEVICE_IDENTIFIER 227

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Creates the device object \c voltage_current with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void voltage_current_create(VoltageCurrent *voltage_current, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Removes the device object \c voltage_current from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void voltage_current_destroy(VoltageCurrent *voltage_current);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the voltage_current_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int voltage_current_get_response_expected(VoltageCurrent *voltage_current, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletVoltageCurrent
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
int voltage_current_set_response_expected(VoltageCurrent *voltage_current, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int voltage_current_set_response_expected_all(VoltageCurrent *voltage_current, bool response_expected);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void voltage_current_register_callback(VoltageCurrent *voltage_current, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int voltage_current_get_api_version(VoltageCurrent *voltage_current, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the current. The value is in mA
 * and between -20000mA and 20000mA.
 * 
 * If you want to get the current periodically, it is recommended to use the
 * callback {@link VOLTAGE_CURRENT_CALLBACK_CURRENT} and set the period with 
 * {@link voltage_current_set_current_callback_period}.
 */
int voltage_current_get_current(VoltageCurrent *voltage_current, int32_t *ret_current);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the voltage. The value is in mV
 * and between 0mV and 36000mV.
 * 
 * If you want to get the voltage periodically, it is recommended to use the
 * callback {@link VOLTAGE_CURRENT_CALLBACK_VOLTAGE} and set the period with 
 * {@link voltage_current_set_voltage_callback_period}.
 */
int voltage_current_get_voltage(VoltageCurrent *voltage_current, int32_t *ret_voltage);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the power. The value is in mW
 * and between 0mV and 720000mW.
 * 
 * If you want to get the power periodically, it is recommended to use the
 * callback {@link VOLTAGE_CURRENT_CALLBACK_POWER} and set the period with 
 * {@link voltage_current_set_power_callback_period}.
 */
int voltage_current_get_power(VoltageCurrent *voltage_current, int32_t *ret_power);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the configuration of the Voltage/Current Bricklet. It is
 * possible to configure number of averages as well as
 * voltage and current conversion time.
 * 
 * Averaging:
 * 
 * \verbatim
 *  "Value", "Number of Averages"
 * 
 *  "0",    "1"
 *  "1",    "4"
 *  "2",    "16"
 *  "3",    "64"
 *  "4",    "128"
 *  "5",    "256"
 *  "6",    "512"
 *  ">=7",  "1024"
 * \endverbatim
 * 
 * Voltage/Current conversion:
 * 
 * \verbatim
 *  "Value", "Conversion time"
 * 
 *  "0",    "140µs"
 *  "1",    "204µs"
 *  "2",    "332µs"
 *  "3",    "588µs"
 *  "4",    "1.1ms"
 *  "5",    "2.116ms"
 *  "6",    "4.156ms"
 *  ">=7",  "8.244ms"
 * \endverbatim
 * 
 * The default values are 3, 4 and 4 (64, 1.1ms, 1.1ms) for averaging, voltage 
 * conversion and current conversion.
 */
int voltage_current_set_configuration(VoltageCurrent *voltage_current, uint8_t averaging, uint8_t voltage_conversion_time, uint8_t current_conversion_time);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the configuration as set by {@link voltage_current_set_configuration}.
 */
int voltage_current_get_configuration(VoltageCurrent *voltage_current, uint8_t *ret_averaging, uint8_t *ret_voltage_conversion_time, uint8_t *ret_current_conversion_time);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Since the shunt resistor that is used to measure the current is not
 * perfectly precise, it needs to be calibrated by a multiplier and
 * divisor if a very precise reading is needed.
 * 
 * For example, if you are expecting a measurement of 1000mA and you
 * are measuring 1023mA, you can calibrate the Voltage/Current Bricklet 
 * by setting the multiplier to 1000 and the divisor to 1023.
 */
int voltage_current_set_calibration(VoltageCurrent *voltage_current, uint16_t gain_multiplier, uint16_t gain_divisor);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the calibration as set by {@link voltage_current_set_calibration}.
 */
int voltage_current_get_calibration(VoltageCurrent *voltage_current, uint16_t *ret_gain_multiplier, uint16_t *ret_gain_divisor);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the period in ms with which the {@link VOLTAGE_CURRENT_CALLBACK_CURRENT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link VOLTAGE_CURRENT_CALLBACK_CURRENT} is only triggered if the current has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int voltage_current_set_current_callback_period(VoltageCurrent *voltage_current, uint32_t period);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the period as set by {@link voltage_current_set_current_callback_period}.
 */
int voltage_current_get_current_callback_period(VoltageCurrent *voltage_current, uint32_t *ret_period);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the period in ms with which the {@link VOLTAGE_CURRENT_CALLBACK_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link VOLTAGE_CURRENT_CALLBACK_VOLTAGE} is only triggered if the voltage has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int voltage_current_set_voltage_callback_period(VoltageCurrent *voltage_current, uint32_t period);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the period as set by {@link voltage_current_set_voltage_callback_period}.
 */
int voltage_current_get_voltage_callback_period(VoltageCurrent *voltage_current, uint32_t *ret_period);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the period in ms with which the {@link VOLTAGE_CURRENT_CALLBACK_POWER} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link VOLTAGE_CURRENT_CALLBACK_POWER} is only triggered if the power has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int voltage_current_set_power_callback_period(VoltageCurrent *voltage_current, uint32_t period);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the period as set by {@link voltage_current_get_power_callback_period}.
 */
int voltage_current_get_power_callback_period(VoltageCurrent *voltage_current, uint32_t *ret_period);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the thresholds for the {@link VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED} callback. 
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
int voltage_current_set_current_callback_threshold(VoltageCurrent *voltage_current, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the threshold as set by {@link voltage_current_set_current_callback_threshold}.
 */
int voltage_current_get_current_callback_threshold(VoltageCurrent *voltage_current, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the thresholds for the {@link VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED} callback. 
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
int voltage_current_set_voltage_callback_threshold(VoltageCurrent *voltage_current, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the threshold as set by {@link voltage_current_set_voltage_callback_threshold}.
 */
int voltage_current_get_voltage_callback_threshold(VoltageCurrent *voltage_current, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the thresholds for the {@link VOLTAGE_CURRENT_CALLBACK_POWER_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the power is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the power is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the power is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the power is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int voltage_current_set_power_callback_threshold(VoltageCurrent *voltage_current, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the threshold as set by {@link voltage_current_set_power_callback_threshold}.
 */
int voltage_current_get_power_callback_threshold(VoltageCurrent *voltage_current, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link VOLTAGE_CURRENT_CALLBACK_CURRENT_REACHED},
 * * {@link VOLTAGE_CURRENT_CALLBACK_VOLTAGE_REACHED},
 * * {@link VOLTAGE_CURRENT_CALLBACK_POWER_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link voltage_current_set_current_callback_threshold},
 * * {@link voltage_current_set_voltage_callback_threshold},
 * * {@link voltage_current_set_power_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int voltage_current_set_debounce_period(VoltageCurrent *voltage_current, uint32_t debounce);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the debounce period as set by {@link voltage_current_set_debounce_period}.
 */
int voltage_current_get_debounce_period(VoltageCurrent *voltage_current, uint32_t *ret_debounce);

/**
 * \ingroup BrickletVoltageCurrent
 *
 * Returns the UID, the UID where the Bricklet is connected to, 
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position can be 'a', 'b', 'c' or 'd'.
 * 
 * The device identifiers can be found :ref:`here <device_identifier>`.
 * 
 * .. versionadded:: 2.0.0~(Plugin)
 */
int voltage_current_get_identity(VoltageCurrent *voltage_current, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_THERMOCOUPLE_H
#define BRICKLET_THERMOCOUPLE_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletThermocouple Thermocouple Bricklet
 */

/**
 * \ingroup BrickletThermocouple
 *
 * Measures temperature with thermocouples
 */
typedef Device Thermocouple;

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_TEMPERATURE 1

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_SET_CONFIGURATION 10

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_CONFIGURATION 11

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_ERROR_STATE 12

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletThermocouple
 *
 * Signature: \code void callback(int32_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * :func:`SetThermocoupleCallbackPeriod`. The parameter is the temperature
 * of the thermocouple.
 * 
 * {@link THERMOCOUPLE_CALLBACK_TEMPERATURE} is only triggered if the temperature has changed since the
 * last triggering.
 */
#define THERMOCOUPLE_CALLBACK_TEMPERATURE 8

/**
 * \ingroup BrickletThermocouple
 *
 * Signature: \code void callback(int32_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link thermocouple_set_temperature_callback_threshold} is reached.
 * The parameter is the temperature of the thermocouple.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link thermocouple_set_debounce_period}.
 */
#define THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED 9

/**
 * \ingroup BrickletThermocouple
 *
 * Signature: \code void callback(bool over_under, bool open_circuit, void *user_data) \endcode
 * 
 * This Callback is triggered every time the error state changes 
 * (see func:`GetErrorStatus`).
 */
#define THERMOCOUPLE_CALLBACK_ERROR_STATE 13


/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_AVERAGING_1 1

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_AVERAGING_2 2

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_AVERAGING_4 4

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_AVERAGING_8 8

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_AVERAGING_16 16

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_B 0

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_E 1

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_J 2

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_K 3

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_N 4

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_R 5

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_S 6

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_T 7

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_G8 8

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_TYPE_G32 9

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FILTER_OPTION_50HZ 0

/**
 * \ingroup BrickletThermocouple
 */
#define THERMOCOUPLE_FILTER_OPTION_60HZ 1

/**
 * \ingroup BrickletThermocouple
 *
 * This constant is used to identify a Thermocouple Bricklet.
 *
 * The {@link thermocouple_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define THERMOCOUPLE_DEVICE_IDENTIFIER 266

/**
 * \ingroup BrickletThermocouple
 *
 * This constant represents the display name of a Thermocouple Bricklet.
 */
#define THERMOCOUPLE_DEVICE_DISPLAY_NAME "Thermocouple Bricklet"

/**
 * \ingroup BrickletThermocouple
 *
 * Creates the device object \c thermocouple with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void thermocouple_create(Thermocouple *thermocouple, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletThermocouple
 *
 * Removes the device object \c thermocouple from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void thermocouple_destroy(Thermocouple *thermocouple);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the thermocouple_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int thermocouple_get_response_expected(Thermocouple *thermocouple, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletThermocouple
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
int thermocouple_set_response_expected(Thermocouple *thermocouple, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletThermocouple
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int thermocouple_set_response_expected_all(Thermocouple *thermocouple, bool response_expected);

/**
 * \ingroup BrickletThermocouple
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void thermocouple_register_callback(Thermocouple *thermocouple, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int thermocouple_get_api_version(Thermocouple *thermocouple, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the temperature of the thermocouple. The value is given in °C/100,
 * e.g. a value of 4223 means that a temperature of 42.23 °C is measured.
 * 
 * If you want to get the temperature periodically, it is recommended 
 * to use the callback {@link THERMOCOUPLE_CALLBACK_TEMPERATURE} and set the period with 
 * {@link thermocouple_set_temperature_callback_period}.
 */
int thermocouple_get_temperature(Thermocouple *thermocouple, int32_t *ret_temperature);

/**
 * \ingroup BrickletThermocouple
 *
 * Sets the period in ms with which the {@link THERMOCOUPLE_CALLBACK_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link THERMOCOUPLE_CALLBACK_TEMPERATURE} is only triggered if the temperature has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int thermocouple_set_temperature_callback_period(Thermocouple *thermocouple, uint32_t period);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the period as set by {@link thermocouple_set_temperature_callback_period}.
 */
int thermocouple_get_temperature_callback_period(Thermocouple *thermocouple, uint32_t *ret_period);

/**
 * \ingroup BrickletThermocouple
 *
 * Sets the thresholds for the {@link THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED} callback. 
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
 * The default value is ('x', 0, 0).
 */
int thermocouple_set_temperature_callback_threshold(Thermocouple *thermocouple, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the threshold as set by {@link thermocouple_set_temperature_callback_threshold}.
 */
int thermocouple_get_temperature_callback_threshold(Thermocouple *thermocouple, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletThermocouple
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link thermocouple_set_temperature_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int thermocouple_set_debounce_period(Thermocouple *thermocouple, uint32_t debounce);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the debounce period as set by {@link thermocouple_set_debounce_period}.
 */
int thermocouple_get_debounce_period(Thermocouple *thermocouple, uint32_t *ret_debounce);

/**
 * \ingroup BrickletThermocouple
 *
 * You can configure averaging size, thermocouple type and frequency
 * filtering.
 * 
 * Available averaging sizes are 1, 2, 4, 8 and 16 samples.
 * 
 * As thermocouple type you can use B, E, J, K, N, R, S and T. If you have a
 * different thermocouple or a custom thermocouple you can also use
 * G8 and G32. With these types the returned value will not be in °C/100,
 * it will be calculated by the following formulas:
 * 
 * * G8: ``value = 8 * 1.6 * 2^17 * Vin``
 * * G32: ``value = 32 * 1.6 * 2^17 * Vin``
 * 
 * where Vin is the thermocouple input voltage.
 * 
 * The frequency filter can be either configured to 50Hz or to 60Hz. You should
 * configure it according to your utility frequency.
 * 
 * The conversion time depends on the averaging and filter configuration, it can
 * be calculated as follows:
 * 
 * * 60Hz: ``time = 82 + (samples - 1) * 16.67``
 * * 50Hz: ``time = 98 + (samples - 1) * 20``
 * 
 * The default configuration is 16 samples, K type and 50Hz.
 */
int thermocouple_set_configuration(Thermocouple *thermocouple, uint8_t averaging, uint8_t thermocouple_type, uint8_t filter);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the configuration as set by {@link thermocouple_set_configuration}.
 */
int thermocouple_get_configuration(Thermocouple *thermocouple, uint8_t *ret_averaging, uint8_t *ret_thermocouple_type, uint8_t *ret_filter);

/**
 * \ingroup BrickletThermocouple
 *
 * Returns the current error state. There are two possible errors:
 * 
 * * Over/Under Voltage and
 * * Open Circuit.
 * 
 * Over/Under Voltage happens for voltages below 0V or above 3.3V. In this case
 * it is very likely that your thermocouple is defective. An Open Circuit error
 * indicates that there is no thermocouple connected.
 * 
 * You can use the func:`ErrorState` callback to automatically get triggered
 * when the error state changes.
 */
int thermocouple_get_error_state(Thermocouple *thermocouple, bool *ret_over_under, bool *ret_open_circuit);

/**
 * \ingroup BrickletThermocouple
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
int thermocouple_get_identity(Thermocouple *thermocouple, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_PTC_H
#define BRICKLET_PTC_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletPTC PTC Bricklet
 */

/**
 * \ingroup BrickletPTC
 *
 * Device for reading temperatures from Pt100 or Pt1000 sensors
 */
typedef Device PTC;

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_TEMPERATURE 1

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_RESISTANCE 2

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_RESISTANCE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_RESISTANCE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_RESISTANCE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_RESISTANCE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_NOISE_REJECTION_FILTER 17

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_NOISE_REJECTION_FILTER 18

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_IS_SENSOR_CONNECTED 19

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_SET_WIRE_MODE 20

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_WIRE_MODE 21

/**
 * \ingroup BrickletPTC
 */
#define PTC_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletPTC
 *
 * Signature: \code void callback(int32_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link ptc_set_temperature_callback_period}. The parameter is the temperature
 * of the connected sensor.
 * 
 * {@link PTC_CALLBACK_TEMPERATURE} is only triggered if the temperature has changed since the
 * last triggering.
 */
#define PTC_CALLBACK_TEMPERATURE 13

/**
 * \ingroup BrickletPTC
 *
 * Signature: \code void callback(int32_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link ptc_set_temperature_callback_threshold} is reached.
 * The parameter is the temperature of the connected sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link ptc_set_debounce_period}.
 */
#define PTC_CALLBACK_TEMPERATURE_REACHED 14

/**
 * \ingroup BrickletPTC
 *
 * Signature: \code void callback(uint16_t resistance, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link ptc_set_resistance_callback_period}. The parameter is the resistance
 * of the connected sensor.
 * 
 * {@link PTC_CALLBACK_RESISTANCE} is only triggered if the resistance has changed since the
 * last triggering.
 */
#define PTC_CALLBACK_RESISTANCE 15

/**
 * \ingroup BrickletPTC
 *
 * Signature: \code void callback(uint16_t resistance, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link ptc_set_resistance_callback_threshold} is reached.
 * The parameter is the resistance of the connected sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link ptc_set_debounce_period}.
 */
#define PTC_CALLBACK_RESISTANCE_REACHED 16


/**
 * \ingroup BrickletPTC
 */
#define PTC_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletPTC
 */
#define PTC_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletPTC
 */
#define PTC_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletPTC
 */
#define PTC_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletPTC
 */
#define PTC_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletPTC
 */
#define PTC_FILTER_OPTION_50HZ 0

/**
 * \ingroup BrickletPTC
 */
#define PTC_FILTER_OPTION_60HZ 1

/**
 * \ingroup BrickletPTC
 */
#define PTC_WIRE_MODE_2 2

/**
 * \ingroup BrickletPTC
 */
#define PTC_WIRE_MODE_3 3

/**
 * \ingroup BrickletPTC
 */
#define PTC_WIRE_MODE_4 4

/**
 * \ingroup BrickletPTC
 *
 * This constant is used to identify a PTC Bricklet.
 *
 * The {@link ptc_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define PTC_DEVICE_IDENTIFIER 226

/**
 * \ingroup BrickletPTC
 *
 * Creates the device object \c ptc with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void ptc_create(PTC *ptc, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletPTC
 *
 * Removes the device object \c ptc from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void ptc_destroy(PTC *ptc);

/**
 * \ingroup BrickletPTC
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the ptc_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int ptc_get_response_expected(PTC *ptc, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletPTC
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
int ptc_set_response_expected(PTC *ptc, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletPTC
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int ptc_set_response_expected_all(PTC *ptc, bool response_expected);

/**
 * \ingroup BrickletPTC
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void ptc_register_callback(PTC *ptc, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletPTC
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int ptc_get_api_version(PTC *ptc, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletPTC
 *
 * Returns the temperature of connected sensor. The value
 * has a range of -246 to 849 °C and is given in °C/100,
 * e.g. a value of 4223 means that a temperature of 42.23 °C is measured.
 * 
 * If you want to get the temperature periodically, it is recommended 
 * to use the callback {@link PTC_CALLBACK_TEMPERATURE} and set the period with 
 * {@link ptc_set_temperature_callback_period}.
 */
int ptc_get_temperature(PTC *ptc, int32_t *ret_temperature);

/**
 * \ingroup BrickletPTC
 *
 * Returns the value as measured by the MAX31865 precision delta-sigma ADC.
 * 
 * The value can be converted with the following formulas:
 * 
 * * Pt100:  resistance = (value * 390) / 32768
 * * Pt1000: resistance = (value * 3900) / 32768
 * 
 * If you want to get the resistance periodically, it is recommended 
 * to use the callback {@link PTC_CALLBACK_RESISTANCE} and set the period with 
 * {@link ptc_set_resistance_callback_period}.
 */
int ptc_get_resistance(PTC *ptc, uint16_t *ret_resistance);

/**
 * \ingroup BrickletPTC
 *
 * Sets the period in ms with which the {@link PTC_CALLBACK_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link PTC_CALLBACK_TEMPERATURE} is only triggered if the temperature has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int ptc_set_temperature_callback_period(PTC *ptc, uint32_t period);

/**
 * \ingroup BrickletPTC
 *
 * Returns the period as set by {@link ptc_set_temperature_callback_period}.
 */
int ptc_get_temperature_callback_period(PTC *ptc, uint32_t *ret_period);

/**
 * \ingroup BrickletPTC
 *
 * Sets the period in ms with which the {@link PTC_CALLBACK_RESISTANCE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link PTC_CALLBACK_RESISTANCE} is only triggered if the resistance has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int ptc_set_resistance_callback_period(PTC *ptc, uint32_t period);

/**
 * \ingroup BrickletPTC
 *
 * Returns the period as set by {@link ptc_set_resistance_callback_period}.
 */
int ptc_get_resistance_callback_period(PTC *ptc, uint32_t *ret_period);

/**
 * \ingroup BrickletPTC
 *
 * Sets the thresholds for the {@link PTC_CALLBACK_TEMPERATURE_REACHED} callback. 
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
int ptc_set_temperature_callback_threshold(PTC *ptc, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletPTC
 *
 * Returns the threshold as set by {@link ptc_set_temperature_callback_threshold}.
 */
int ptc_get_temperature_callback_threshold(PTC *ptc, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletPTC
 *
 * Sets the thresholds for the {@link PTC_CALLBACK_RESISTANCE_REACHED} callback. 
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
int ptc_set_resistance_callback_threshold(PTC *ptc, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletPTC
 *
 * Returns the threshold as set by {@link ptc_set_resistance_callback_threshold}.
 */
int ptc_get_resistance_callback_threshold(PTC *ptc, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletPTC
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link PTC_CALLBACK_TEMPERATURE_REACHED},
 * * {@link PTC_CALLBACK_RESISTANCE_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link ptc_set_temperature_callback_threshold},
 * * {@link ptc_set_resistance_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int ptc_set_debounce_period(PTC *ptc, uint32_t debounce);

/**
 * \ingroup BrickletPTC
 *
 * Returns the debounce period as set by {@link ptc_set_debounce_period}.
 */
int ptc_get_debounce_period(PTC *ptc, uint32_t *ret_debounce);

/**
 * \ingroup BrickletPTC
 *
 * Sets the noise rejection filter to either 50Hz (0) or 60Hz (1).
 * Noise from 50Hz or 60Hz power sources (including
 * harmonics of the AC power's fundamental frequency) is
 * attenuated by 82dB.
 * 
 * Default value is 0 = 50Hz.
 */
int ptc_set_noise_rejection_filter(PTC *ptc, uint8_t filter);

/**
 * \ingroup BrickletPTC
 *
 * Returns the noise rejection filter option as set by 
 * {@link ptc_set_noise_rejection_filter}
 */
int ptc_get_noise_rejection_filter(PTC *ptc, uint8_t *ret_filter);

/**
 * \ingroup BrickletPTC
 *
 * Returns *true* if the sensor is connected correctly. 
 * 
 * If this function
 * returns *false*, there is either no Pt100 or Pt1000 sensor connected,
 * the sensor is connected incorrectly or the sensor itself is faulty.
 */
int ptc_is_sensor_connected(PTC *ptc, bool *ret_connected);

/**
 * \ingroup BrickletPTC
 *
 * Sets the wire mode of the sensor. Possible values are 2, 3 and 4 which
 * correspond to 2-, 3- and 4-wire sensors. The value has to match the jumper
 * configuration on the Bricklet.
 * 
 * The default value is 2 = 2-wire.
 */
int ptc_set_wire_mode(PTC *ptc, uint8_t mode);

/**
 * \ingroup BrickletPTC
 *
 * Returns the wire mode as set by {@link ptc_set_wire_mode}
 */
int ptc_get_wire_mode(PTC *ptc, uint8_t *ret_mode);

/**
 * \ingroup BrickletPTC
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
int ptc_get_identity(PTC *ptc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

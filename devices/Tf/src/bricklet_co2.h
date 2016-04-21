/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_CO2_H
#define BRICKLET_CO2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletCO2 CO2 Bricklet
 */

/**
 * \ingroup BrickletCO2
 *
 * Measures CO2 concentration in ppm
 */
typedef Device CO2;

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_GET_CO2_CONCENTRATION 1

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletCO2
 */
#define CO2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletCO2
 *
 * Signature: \code void callback(uint16_t co2_concentration, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link co2_set_co2_concentration_callback_period}. The parameter is the CO2 concentration of the
 * sensor.
 * 
 * {@link CO2_CALLBACK_CO2_CONCENTRATION} is only triggered if the CO2 concentration has changed since the
 * last triggering.
 */
#define CO2_CALLBACK_CO2_CONCENTRATION 8

/**
 * \ingroup BrickletCO2
 *
 * Signature: \code void callback(uint16_t co2_concentration, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link co2_set_co2_concentration_callback_threshold} is reached.
 * The parameter is the CO2 concentration.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link co2_set_debounce_period}.
 */
#define CO2_CALLBACK_CO2_CONCENTRATION_REACHED 9


/**
 * \ingroup BrickletCO2
 */
#define CO2_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletCO2
 */
#define CO2_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletCO2
 */
#define CO2_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletCO2
 */
#define CO2_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletCO2
 */
#define CO2_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletCO2
 *
 * This constant is used to identify a CO2 Bricklet.
 *
 * The {@link co2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define CO2_DEVICE_IDENTIFIER 262

/**
 * \ingroup BrickletCO2
 *
 * This constant represents the display name of a CO2 Bricklet.
 */
#define CO2_DEVICE_DISPLAY_NAME "CO2 Bricklet"

/**
 * \ingroup BrickletCO2
 *
 * Creates the device object \c co2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void co2_create(CO2 *co2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletCO2
 *
 * Removes the device object \c co2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void co2_destroy(CO2 *co2);

/**
 * \ingroup BrickletCO2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the co2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int co2_get_response_expected(CO2 *co2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletCO2
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
int co2_set_response_expected(CO2 *co2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletCO2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int co2_set_response_expected_all(CO2 *co2, bool response_expected);

/**
 * \ingroup BrickletCO2
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void co2_register_callback(CO2 *co2, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletCO2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int co2_get_api_version(CO2 *co2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletCO2
 *
 * Returns the measured CO2 concentration. The value is in 
 * `ppm (parts per million) <https://en.wikipedia.org/wiki/Parts-per_notation>`__
 * and between 0 to 10000.
 * 
 * If you want to get the CO2 concentration periodically, it is recommended to use the
 * callback {@link CO2_CALLBACK_CO2_CONCENTRATION} and set the period with
 * {@link co2_set_co2_concentration_callback_period}.
 */
int co2_get_co2_concentration(CO2 *co2, uint16_t *ret_co2_concentration);

/**
 * \ingroup BrickletCO2
 *
 * Sets the period in ms with which the {@link CO2_CALLBACK_CO2_CONCENTRATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link CO2_CALLBACK_CO2_CONCENTRATION} is only triggered if the CO2 concentration has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int co2_set_co2_concentration_callback_period(CO2 *co2, uint32_t period);

/**
 * \ingroup BrickletCO2
 *
 * Returns the period as set by {@link co2_set_co2_concentration_callback_period}.
 */
int co2_get_co2_concentration_callback_period(CO2 *co2, uint32_t *ret_period);

/**
 * \ingroup BrickletCO2
 *
 * Sets the thresholds for the {@link CO2_CALLBACK_CO2_CONCENTRATION_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the CO2 concentration is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the CO2 concentration is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the CO2 concentration is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the CO2 concentration is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int co2_set_co2_concentration_callback_threshold(CO2 *co2, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletCO2
 *
 * Returns the threshold as set by {@link co2_set_co2_concentration_callback_threshold}.
 */
int co2_get_co2_concentration_callback_threshold(CO2 *co2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletCO2
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link CO2_CALLBACK_CO2_CONCENTRATION_REACHED},
 * 
 * are triggered, if the thresholds
 * 
 * * {@link co2_set_co2_concentration_callback_threshold},
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int co2_set_debounce_period(CO2 *co2, uint32_t debounce);

/**
 * \ingroup BrickletCO2
 *
 * Returns the debounce period as set by {@link co2_set_debounce_period}.
 */
int co2_get_debounce_period(CO2 *co2, uint32_t *ret_debounce);

/**
 * \ingroup BrickletCO2
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
int co2_get_identity(CO2 *co2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

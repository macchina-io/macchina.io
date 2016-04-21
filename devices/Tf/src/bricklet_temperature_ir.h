/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_TEMPERATURE_IR_H
#define BRICKLET_TEMPERATURE_IR_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletTemperatureIR Temperature IR Bricklet
 */

/**
 * \ingroup BrickletTemperatureIR
 *
 * Measures contactless object temperature between -70°C and +380°C
 */
typedef Device TemperatureIR;

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_AMBIENT_TEMPERATURE 1

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_OBJECT_TEMPERATURE 2

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_SET_EMISSIVITY 3

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_EMISSIVITY 4

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_SET_AMBIENT_TEMPERATURE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_AMBIENT_TEMPERATURE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_SET_OBJECT_TEMPERATURE_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_OBJECT_TEMPERATURE_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_SET_AMBIENT_TEMPERATURE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_AMBIENT_TEMPERATURE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_SET_OBJECT_TEMPERATURE_CALLBACK_THRESHOLD 11

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_OBJECT_TEMPERATURE_CALLBACK_THRESHOLD 12

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_SET_DEBOUNCE_PERIOD 13

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_DEBOUNCE_PERIOD 14

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletTemperatureIR
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link temperature_ir_set_ambient_temperature_callback_period}. The parameter is the ambient
 * temperature of the sensor.
 * 
 * {@link TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE} is only triggered if the ambient temperature
 * has changed since the last triggering.
 */
#define TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE 15

/**
 * \ingroup BrickletTemperatureIR
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link temperature_ir_set_object_temperature_callback_period}. The parameter is the object
 * temperature of the sensor.
 * 
 * {@link TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE} is only triggered if the object temperature
 * has changed since the last triggering.
 */
#define TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE 16

/**
 * \ingroup BrickletTemperatureIR
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link temperature_ir_set_ambient_temperature_callback_threshold} is reached.
 * The parameter is the ambient temperature of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link temperature_ir_set_debounce_period}.
 */
#define TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE_REACHED 17

/**
 * \ingroup BrickletTemperatureIR
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link temperature_ir_set_object_temperature_callback_threshold} is reached.
 * The parameter is the object temperature of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link temperature_ir_set_debounce_period}.
 */
#define TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE_REACHED 18


/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletTemperatureIR
 */
#define TEMPERATURE_IR_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletTemperatureIR
 *
 * This constant is used to identify a Temperature IR Bricklet.
 *
 * The {@link temperature_ir_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define TEMPERATURE_IR_DEVICE_IDENTIFIER 217

/**
 * \ingroup BrickletTemperatureIR
 *
 * This constant represents the display name of a Temperature IR Bricklet.
 */
#define TEMPERATURE_IR_DEVICE_DISPLAY_NAME "Temperature IR Bricklet"

/**
 * \ingroup BrickletTemperatureIR
 *
 * Creates the device object \c temperature_ir with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void temperature_ir_create(TemperatureIR *temperature_ir, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Removes the device object \c temperature_ir from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void temperature_ir_destroy(TemperatureIR *temperature_ir);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the temperature_ir_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int temperature_ir_get_response_expected(TemperatureIR *temperature_ir, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletTemperatureIR
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
int temperature_ir_set_response_expected(TemperatureIR *temperature_ir, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int temperature_ir_set_response_expected_all(TemperatureIR *temperature_ir, bool response_expected);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void temperature_ir_register_callback(TemperatureIR *temperature_ir, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int temperature_ir_get_api_version(TemperatureIR *temperature_ir, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the ambient temperature of the sensor. The value
 * has a range of -400 to 1250 and is given in °C/10,
 * e.g. a value of 423 means that an ambient temperature of 42.3 °C is 
 * measured.
 * 
 * If you want to get the ambient temperature periodically, it is recommended 
 * to use the callback {@link TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE} and set the period with 
 * {@link temperature_ir_set_ambient_temperature_callback_period}.
 */
int temperature_ir_get_ambient_temperature(TemperatureIR *temperature_ir, int16_t *ret_temperature);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the object temperature of the sensor, i.e. the temperature
 * of the surface of the object the sensor is aimed at. The value
 * has a range of -700 to 3800 and is given in °C/10,
 * e.g. a value of 3001 means that a temperature of 300.1 °C is measured
 * on the surface of the object.
 * 
 * The temperature of different materials is dependent on their `emissivity 
 * <https://en.wikipedia.org/wiki/Emissivity>`__. The emissivity of the material
 * can be set with {@link temperature_ir_set_emissivity}.
 * 
 * If you want to get the object temperature periodically, it is recommended 
 * to use the callback {@link TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE} and set the period with 
 * {@link temperature_ir_set_object_temperature_callback_period}.
 */
int temperature_ir_get_object_temperature(TemperatureIR *temperature_ir, int16_t *ret_temperature);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Sets the `emissivity <https://en.wikipedia.org/wiki/Emissivity>`__ that is
 * used to calculate the surface temperature as returned by 
 * {@link temperature_ir_get_object_temperature}. 
 * 
 * The emissivity is usually given as a value between 0.0 and 1.0. A list of
 * emissivities of different materials can be found 
 * `here <http://www.infrared-thermography.com/material.htm>`__.
 * 
 * The parameter of {@link temperature_ir_set_emissivity} has to be given with a factor of
 * 65535 (16-bit). For example: An emissivity of 0.1 can be set with the
 * value 6553, an emissivity of 0.5 with the value 32767 and so on.
 * 
 * \note
 *  If you need a precise measurement for the object temperature, it is
 *  absolutely crucial that you also provide a precise emissivity.
 * 
 * The default emissivity is 1.0 (value of 65535) and the minimum emissivity the
 * sensor can handle is 0.1 (value of 6553).
 */
int temperature_ir_set_emissivity(TemperatureIR *temperature_ir, uint16_t emissivity);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the emissivity as set by {@link temperature_ir_set_emissivity}.
 */
int temperature_ir_get_emissivity(TemperatureIR *temperature_ir, uint16_t *ret_emissivity);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Sets the period in ms with which the {@link TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE} is only triggered if the temperature has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int temperature_ir_set_ambient_temperature_callback_period(TemperatureIR *temperature_ir, uint32_t period);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the period as set by {@link temperature_ir_set_ambient_temperature_callback_period}.
 */
int temperature_ir_get_ambient_temperature_callback_period(TemperatureIR *temperature_ir, uint32_t *ret_period);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Sets the period in ms with which the {@link TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE} is only triggered if the temperature has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int temperature_ir_set_object_temperature_callback_period(TemperatureIR *temperature_ir, uint32_t period);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the period as set by {@link temperature_ir_set_object_temperature_callback_period}.
 */
int temperature_ir_get_object_temperature_callback_period(TemperatureIR *temperature_ir, uint32_t *ret_period);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Sets the thresholds for the {@link TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the ambient temperature is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the ambient temperature is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the ambient temperature is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the ambient temperature is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int temperature_ir_set_ambient_temperature_callback_threshold(TemperatureIR *temperature_ir, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the threshold as set by {@link temperature_ir_set_ambient_temperature_callback_threshold}.
 */
int temperature_ir_get_ambient_temperature_callback_threshold(TemperatureIR *temperature_ir, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Sets the thresholds for the {@link TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the object temperature is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the object temperature is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the object temperature is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the object temperature is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int temperature_ir_set_object_temperature_callback_threshold(TemperatureIR *temperature_ir, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the threshold as set by {@link temperature_ir_set_object_temperature_callback_threshold}.
 */
int temperature_ir_get_object_temperature_callback_threshold(TemperatureIR *temperature_ir, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link TEMPERATURE_IR_CALLBACK_AMBIENT_TEMPERATURE_REACHED},
 * * {@link TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link temperature_ir_set_ambient_temperature_callback_threshold},
 * * {@link temperature_ir_set_object_temperature_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int temperature_ir_set_debounce_period(TemperatureIR *temperature_ir, uint32_t debounce);

/**
 * \ingroup BrickletTemperatureIR
 *
 * Returns the debounce period as set by {@link temperature_ir_set_debounce_period}.
 */
int temperature_ir_get_debounce_period(TemperatureIR *temperature_ir, uint32_t *ret_debounce);

/**
 * \ingroup BrickletTemperatureIR
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
int temperature_ir_get_identity(TemperatureIR *temperature_ir, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

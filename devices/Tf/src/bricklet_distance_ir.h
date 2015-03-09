/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_DISTANCE_IR_H
#define BRICKLET_DISTANCE_IR_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletDistanceIR DistanceIR Bricklet
 */

/**
 * \ingroup BrickletDistanceIR
 *
 * Device for sensing distance via infrared
 */
typedef Device DistanceIR;

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_DISTANCE 1

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_ANALOG_VALUE 2

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_SET_SAMPLING_POINT 3

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_SAMPLING_POINT 4

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 11

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 12

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_SET_DEBOUNCE_PERIOD 13

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_DEBOUNCE_PERIOD 14

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletDistanceIR
 *
 * Signature: \code void callback(uint16_t distance, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link distance_ir_set_distance_callback_period}. The parameter is the distance of the
 * sensor.
 * 
 * {@link DISTANCE_IR_CALLBACK_DISTANCE} is only triggered if the distance has changed since the
 * last triggering.
 */
#define DISTANCE_IR_CALLBACK_DISTANCE 15

/**
 * \ingroup BrickletDistanceIR
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link distance_ir_set_analog_value_callback_period}. The parameter is the analog value of the
 * sensor.
 * 
 * {@link DISTANCE_IR_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 */
#define DISTANCE_IR_CALLBACK_ANALOG_VALUE 16

/**
 * \ingroup BrickletDistanceIR
 *
 * Signature: \code void callback(uint16_t distance, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link distance_ir_set_distance_callback_threshold} is reached.
 * The parameter is the distance of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link distance_ir_set_debounce_period}.
 */
#define DISTANCE_IR_CALLBACK_DISTANCE_REACHED 17

/**
 * \ingroup BrickletDistanceIR
 *
 * Signature: \code void callback(uint16_t value, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link distance_ir_set_analog_value_callback_threshold} is reached.
 * The parameter is the analog value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link distance_ir_set_debounce_period}.
 */
#define DISTANCE_IR_CALLBACK_ANALOG_VALUE_REACHED 18


/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletDistanceIR
 */
#define DISTANCE_IR_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletDistanceIR
 *
 * This constant is used to identify a DistanceIR Bricklet.
 *
 * The {@link distance_ir_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define DISTANCE_IR_DEVICE_IDENTIFIER 25

/**
 * \ingroup BrickletDistanceIR
 *
 * Creates the device object \c distance_ir with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void distance_ir_create(DistanceIR *distance_ir, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletDistanceIR
 *
 * Removes the device object \c distance_ir from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void distance_ir_destroy(DistanceIR *distance_ir);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the distance_ir_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int distance_ir_get_response_expected(DistanceIR *distance_ir, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletDistanceIR
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
int distance_ir_set_response_expected(DistanceIR *distance_ir, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletDistanceIR
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int distance_ir_set_response_expected_all(DistanceIR *distance_ir, bool response_expected);

/**
 * \ingroup BrickletDistanceIR
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void distance_ir_register_callback(DistanceIR *distance_ir, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int distance_ir_get_api_version(DistanceIR *distance_ir, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the distance measured by the sensor. The value is in mm and possible
 * distance ranges are 40 to 300, 100 to 800 and 200 to 1500, depending on the
 * selected IR sensor.
 * 
 * If you want to get the distance periodically, it is recommended to use the
 * callback {@link DISTANCE_IR_CALLBACK_DISTANCE} and set the period with 
 * {@link distance_ir_set_distance_callback_period}.
 */
int distance_ir_get_distance(DistanceIR *distance_ir, uint16_t *ret_distance);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the value as read by a 12-bit analog-to-digital converter.
 * The value is between 0 and 4095.
 * 
 * \note
 *  The value returned by {@link distance_ir_get_distance} is averaged over several samples
 *  to yield less noise, while {@link distance_ir_get_analog_value} gives back raw
 *  unfiltered analog values. The only reason to use {@link distance_ir_get_analog_value} is,
 *  if you need the full resolution of the analog-to-digital converter.
 * 
 * If you want the analog value periodically, it is recommended to use the 
 * callback {@link DISTANCE_IR_CALLBACK_ANALOG_VALUE} and set the period with 
 * {@link distance_ir_set_analog_value_callback_period}.
 */
int distance_ir_get_analog_value(DistanceIR *distance_ir, uint16_t *ret_value);

/**
 * \ingroup BrickletDistanceIR
 *
 * Sets a sampling point value to a specific position of the lookup table.
 * The lookup table comprises 128 equidistant analog values with
 * corresponding distances.
 * 
 * If you measure a distance of 50cm at the analog value 2048, you
 * should call this function with (64, 5000). The utilized analog-to-digital
 * converter has a resolution of 12 bit. With 128 sampling points on the
 * whole range, this means that every sampling point has a size of 32
 * analog values. Thus the analog value 2048 has the corresponding sampling
 * point 64 = 2048/32.
 * 
 * Sampling points are saved on the EEPROM of the Distance IR Bricklet and
 * loaded again on startup.
 * 
 * \note
 *  An easy way to calibrate the sampling points of the Distance IR Bricklet is
 *  implemented in the Brick Viewer. If you want to calibrate your Bricklet it is
 *  highly recommended to use this implementation.
 */
int distance_ir_set_sampling_point(DistanceIR *distance_ir, uint8_t position, uint16_t distance);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the distance to a sampling point position as set by
 * {@link distance_ir_set_sampling_point}.
 */
int distance_ir_get_sampling_point(DistanceIR *distance_ir, uint8_t position, uint16_t *ret_distance);

/**
 * \ingroup BrickletDistanceIR
 *
 * Sets the period in ms with which the {@link DISTANCE_IR_CALLBACK_DISTANCE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link DISTANCE_IR_CALLBACK_DISTANCE} is only triggered if the distance has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int distance_ir_set_distance_callback_period(DistanceIR *distance_ir, uint32_t period);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the period as set by {@link distance_ir_set_distance_callback_period}.
 */
int distance_ir_get_distance_callback_period(DistanceIR *distance_ir, uint32_t *ret_period);

/**
 * \ingroup BrickletDistanceIR
 *
 * Sets the period in ms with which the {@link DISTANCE_IR_CALLBACK_ANALOG_VALUE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link DISTANCE_IR_CALLBACK_ANALOG_VALUE} is only triggered if the analog value has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int distance_ir_set_analog_value_callback_period(DistanceIR *distance_ir, uint32_t period);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the period as set by {@link distance_ir_set_analog_value_callback_period}.
 */
int distance_ir_get_analog_value_callback_period(DistanceIR *distance_ir, uint32_t *ret_period);

/**
 * \ingroup BrickletDistanceIR
 *
 * Sets the thresholds for the {@link DISTANCE_IR_CALLBACK_DISTANCE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the distance is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the distance is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the distance is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the distance is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int distance_ir_set_distance_callback_threshold(DistanceIR *distance_ir, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the threshold as set by {@link distance_ir_set_distance_callback_threshold}.
 */
int distance_ir_get_distance_callback_threshold(DistanceIR *distance_ir, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletDistanceIR
 *
 * Sets the thresholds for the {@link DISTANCE_IR_CALLBACK_ANALOG_VALUE_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the analog value is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the analog value is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the analog value is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the analog value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int distance_ir_set_analog_value_callback_threshold(DistanceIR *distance_ir, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the threshold as set by {@link distance_ir_set_analog_value_callback_threshold}.
 */
int distance_ir_get_analog_value_callback_threshold(DistanceIR *distance_ir, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletDistanceIR
 *
 * Sets the period in ms with which the threshold callbacks
 * 
 * * {@link DISTANCE_IR_CALLBACK_DISTANCE_REACHED},
 * * {@link DISTANCE_IR_CALLBACK_ANALOG_VALUE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link distance_ir_set_distance_callback_threshold},
 * * {@link distance_ir_set_analog_value_callback_threshold}
 * 
 * keep being reached.
 * 
 * The default value is 100.
 */
int distance_ir_set_debounce_period(DistanceIR *distance_ir, uint32_t debounce);

/**
 * \ingroup BrickletDistanceIR
 *
 * Returns the debounce period as set by {@link distance_ir_set_debounce_period}.
 */
int distance_ir_get_debounce_period(DistanceIR *distance_ir, uint32_t *ret_debounce);

/**
 * \ingroup BrickletDistanceIR
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
int distance_ir_get_identity(DistanceIR *distance_ir, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

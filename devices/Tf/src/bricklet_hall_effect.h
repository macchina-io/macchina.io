/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_HALL_EFFECT_H
#define BRICKLET_HALL_EFFECT_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletHallEffect Hall Effect Bricklet
 */

/**
 * \ingroup BrickletHallEffect
 *
 * Detects presence of magnetic field
 */
typedef Device HallEffect;

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_GET_VALUE 1

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_GET_EDGE_COUNT 2

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CONFIG 3

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CONFIG 4

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_SET_EDGE_INTERRUPT 5

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_GET_EDGE_INTERRUPT 6

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_EDGE_INTERRUPT 9

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletHallEffect
 *
 * Signature: \code void callback(uint32_t count, bool value, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link hall_effect_set_edge_count_callback_period}. The parameters are the
 * current count and the current value (see {@link hall_effect_get_value} and {@link hall_effect_get_edge_count}).
 * 
 * {@link HALL_EFFECT_CALLBACK_EDGE_COUNT} is only triggered if the count or value changed since the
 * last triggering.
 */
#define HALL_EFFECT_CALLBACK_EDGE_COUNT 10


/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_EDGE_TYPE_RISING 0

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_EDGE_TYPE_FALLING 1

/**
 * \ingroup BrickletHallEffect
 */
#define HALL_EFFECT_EDGE_TYPE_BOTH 2

/**
 * \ingroup BrickletHallEffect
 *
 * This constant is used to identify a Hall Effect Bricklet.
 *
 * The {@link hall_effect_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define HALL_EFFECT_DEVICE_IDENTIFIER 240

/**
 * \ingroup BrickletHallEffect
 *
 * This constant represents the display name of a Hall Effect Bricklet.
 */
#define HALL_EFFECT_DEVICE_DISPLAY_NAME "Hall Effect Bricklet"

/**
 * \ingroup BrickletHallEffect
 *
 * Creates the device object \c hall_effect with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void hall_effect_create(HallEffect *hall_effect, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletHallEffect
 *
 * Removes the device object \c hall_effect from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void hall_effect_destroy(HallEffect *hall_effect);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the hall_effect_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int hall_effect_get_response_expected(HallEffect *hall_effect, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletHallEffect
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
int hall_effect_set_response_expected(HallEffect *hall_effect, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletHallEffect
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int hall_effect_set_response_expected_all(HallEffect *hall_effect, bool response_expected);

/**
 * \ingroup BrickletHallEffect
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void hall_effect_register_callback(HallEffect *hall_effect, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int hall_effect_get_api_version(HallEffect *hall_effect, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns *true* if a magnetic field of 35 Gauss (3.5mT) or greater is detected.
 */
int hall_effect_get_value(HallEffect *hall_effect, bool *ret_value);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns the current value of the edge counter. You can configure
 * edge type (rising, falling, both) that is counted with
 * {@link hall_effect_set_edge_count_config}.
 * 
 * If you set the reset counter to *true*, the count is set back to 0
 * directly after it is read.
 */
int hall_effect_get_edge_count(HallEffect *hall_effect, bool reset_counter, uint32_t *ret_count);

/**
 * \ingroup BrickletHallEffect
 *
 * The edge type parameter configures if rising edges, falling edges or 
 * both are counted. Possible edge types are:
 * 
 * * 0 = rising (default)
 * * 1 = falling
 * * 2 = both
 * 
 * A magnetic field of 35 Gauss (3.5mT) or greater causes a falling edge and a
 * magnetic field of 25 Gauss (2.5mT) or smaller causes a rising edge.
 * 
 * If a magnet comes near the Bricklet the signal goes low (falling edge), if
 * a magnet is removed from the vicinity the signal goes high (rising edge).
 * 
 * The debounce time is given in ms.
 * 
 * Configuring an edge counter resets its value to 0.
 * 
 * If you don't know what any of this means, just leave it at default. The
 * default configuration is very likely OK for you.
 * 
 * Default values: 0 (edge type) and 100ms (debounce time)
 */
int hall_effect_set_edge_count_config(HallEffect *hall_effect, uint8_t edge_type, uint8_t debounce);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns the edge type and debounce time as set by {@link hall_effect_set_edge_count_config}.
 */
int hall_effect_get_edge_count_config(HallEffect *hall_effect, uint8_t *ret_edge_type, uint8_t *ret_debounce);

/**
 * \ingroup BrickletHallEffect
 *
 * Sets the number of edges until an interrupt is invoked.
 * 
 * If *edges* is set to n, an interrupt is invoked for every n-th detected edge.
 * 
 * If *edges* is set to 0, the interrupt is disabled.
 * 
 * Default value is 0.
 */
int hall_effect_set_edge_interrupt(HallEffect *hall_effect, uint32_t edges);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns the edges as set by {@link hall_effect_set_edge_interrupt}.
 */
int hall_effect_get_edge_interrupt(HallEffect *hall_effect, uint32_t *ret_edges);

/**
 * \ingroup BrickletHallEffect
 *
 * Sets the period in ms with which the {@link HALL_EFFECT_CALLBACK_EDGE_COUNT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link HALL_EFFECT_CALLBACK_EDGE_COUNT} is only triggered if the edge count has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int hall_effect_set_edge_count_callback_period(HallEffect *hall_effect, uint32_t period);

/**
 * \ingroup BrickletHallEffect
 *
 * Returns the period as set by {@link hall_effect_set_edge_count_callback_period}.
 */
int hall_effect_get_edge_count_callback_period(HallEffect *hall_effect, uint32_t *ret_period);

/**
 * \ingroup BrickletHallEffect
 *
 * This callback is triggered every n-th count, as configured with
 * {@link hall_effect_set_edge_interrupt}. The parameters are the
 * current count and the current value (see {@link hall_effect_get_value} and {@link hall_effect_get_edge_count}).
 */
int hall_effect_edge_interrupt(HallEffect *hall_effect, uint32_t *ret_count, bool *ret_value);

/**
 * \ingroup BrickletHallEffect
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
int hall_effect_get_identity(HallEffect *hall_effect, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

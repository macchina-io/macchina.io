/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_QUAD_RELAY_H
#define BRICKLET_INDUSTRIAL_QUAD_RELAY_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialQuadRelay Industrial Quad Relay Bricklet
 */

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * 4 galvanically isolated solid state relays
 */
typedef Device IndustrialQuadRelay;

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_SET_VALUE 1

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_GET_VALUE 2

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_SET_MONOFLOP 3

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_GET_MONOFLOP 4

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_SET_GROUP 5

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_GET_GROUP 6

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_GET_AVAILABLE_FOR_GROUP 7

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_SET_SELECTED_VALUES 9

/**
 * \ingroup BrickletIndustrialQuadRelay
 */
#define INDUSTRIAL_QUAD_RELAY_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Signature: \code void callback(uint16_t selection_mask, uint16_t value_mask, void *user_data) \endcode
 * 
 * This callback is triggered whenever a monoflop timer reaches 0. The
 * parameters contain the involved pins and the current value of the pins
 * (the value after the monoflop).
 */
#define INDUSTRIAL_QUAD_RELAY_CALLBACK_MONOFLOP_DONE 8


/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * This constant is used to identify a Industrial Quad Relay Bricklet.
 *
 * The {@link industrial_quad_relay_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_QUAD_RELAY_DEVICE_IDENTIFIER 225

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * This constant represents the display name of a Industrial Quad Relay Bricklet.
 */
#define INDUSTRIAL_QUAD_RELAY_DEVICE_DISPLAY_NAME "Industrial Quad Relay Bricklet"

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Creates the device object \c industrial_quad_relay with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_quad_relay_create(IndustrialQuadRelay *industrial_quad_relay, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Removes the device object \c industrial_quad_relay from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_quad_relay_destroy(IndustrialQuadRelay *industrial_quad_relay);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_quad_relay_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_quad_relay_get_response_expected(IndustrialQuadRelay *industrial_quad_relay, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialQuadRelay
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
int industrial_quad_relay_set_response_expected(IndustrialQuadRelay *industrial_quad_relay, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_quad_relay_set_response_expected_all(IndustrialQuadRelay *industrial_quad_relay, bool response_expected);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void industrial_quad_relay_register_callback(IndustrialQuadRelay *industrial_quad_relay, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_quad_relay_get_api_version(IndustrialQuadRelay *industrial_quad_relay, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Sets the output value with a bitmask (16bit). A 1 in the bitmask means relay
 * closed and a 0 means relay open.
 * 
 * For example: The value 3 or 0b0011 will close the relay of pins 0-1 and open
 * the other pins.
 * 
 * If no groups are used (see {@link industrial_quad_relay_set_group}), the pins correspond to the
 * markings on the Quad Relay Bricklet.
 * 
 * If groups are used, the pins correspond to the element in the group.
 * Element 1 in the group will get pins 0-3, element 2 pins 4-7, element 3
 * pins 8-11 and element 4 pins 12-15.
 */
int industrial_quad_relay_set_value(IndustrialQuadRelay *industrial_quad_relay, uint16_t value_mask);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Returns the bitmask as set by {@link industrial_quad_relay_set_value}.
 */
int industrial_quad_relay_get_value(IndustrialQuadRelay *industrial_quad_relay, uint16_t *ret_value_mask);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Configures a monoflop of the pins specified by the first parameter
 * bitmask.
 * 
 * The second parameter is a bitmask with the desired value of the specified
 * pins. A 1 in the bitmask means relay closed and a 0 means relay open.
 * 
 * The third parameter indicates the time (in ms) that the pins should hold
 * the value.
 * 
 * If this function is called with the parameters (9, 1, 1500) or
 * (0b1001, 0b0001, 1500): Pin 0 will close and pin 3 will open. In 1.5s pin 0
 * will open and pin 3 will close again.
 * 
 * A monoflop can be used as a fail-safe mechanism. For example: Lets assume you
 * have a RS485 bus and a Quad Relay Bricklet connected to one of the slave
 * stacks. You can now call this function every second, with a time parameter
 * of two seconds and pin 0 closed. Pin 0 will be closed all the time. If now
 * the RS485 connection is lost, then pin 0 will be opened in at most two seconds.
 */
int industrial_quad_relay_set_monoflop(IndustrialQuadRelay *industrial_quad_relay, uint16_t selection_mask, uint16_t value_mask, uint32_t time);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Returns (for the given pin) the current value and the time as set by
 * {@link industrial_quad_relay_set_monoflop} as well as the remaining time until the value flips.
 * 
 * If the timer is not running currently, the remaining time will be returned
 * as 0.
 */
int industrial_quad_relay_get_monoflop(IndustrialQuadRelay *industrial_quad_relay, uint8_t pin, uint16_t *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Sets a group of Quad Relay Bricklets that should work together. You can
 * find Bricklets that can be grouped together with {@link industrial_quad_relay_get_available_for_group}.
 * 
 * The group consists of 4 elements. Element 1 in the group will get pins 0-3,
 * element 2 pins 4-7, element 3 pins 8-11 and element 4 pins 12-15.
 * 
 * Each element can either be one of the ports ('a' to 'd') or 'n' if it should
 * not be used.
 * 
 * For example: If you have two Quad Relay Bricklets connected to port A and
 * port B respectively, you could call with ``['a', 'b', 'n', 'n']``.
 * 
 * Now the pins on the Quad Relay on port A are assigned to 0-3 and the
 * pins on the Quad Relay on port B are assigned to 4-7. It is now possible
 * to call {@link industrial_quad_relay_set_value} and control two Bricklets at the same time.
 */
int industrial_quad_relay_set_group(IndustrialQuadRelay *industrial_quad_relay, char group[4]);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Returns the group as set by {@link industrial_quad_relay_set_group}
 */
int industrial_quad_relay_get_group(IndustrialQuadRelay *industrial_quad_relay, char ret_group[4]);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Returns a bitmask of ports that are available for grouping. For example the
 * value 5 or 0b0101 means: Port A and port C are connected to Bricklets that
 * can be grouped together.
 */
int industrial_quad_relay_get_available_for_group(IndustrialQuadRelay *industrial_quad_relay, uint8_t *ret_available);

/**
 * \ingroup BrickletIndustrialQuadRelay
 *
 * Sets the output value with a bitmask, according to the selection mask. 
 * The bitmask is 16 bit long, *true* refers to a closed relay and 
 * *false* refers to an open relay.
 * 
 * For example: The values (3, 1) or (0b0011, 0b0001) will close the relay of
 * pin 0, open the relay of pin 1 and leave the others untouched.
 * 
 * If no groups are used (see {@link industrial_quad_relay_set_group}), the pins correspond to the
 * markings on the Quad Relay Bricklet.
 * 
 * If groups are used, the pins correspond to the element in the group.
 * Element 1 in the group will get pins 0-3, element 2 pins 4-7, element 3
 * pins 8-11 and element 4 pins 12-15.
 */
int industrial_quad_relay_set_selected_values(IndustrialQuadRelay *industrial_quad_relay, uint16_t selection_mask, uint16_t value_mask);

/**
 * \ingroup BrickletIndustrialQuadRelay
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
int industrial_quad_relay_get_identity(IndustrialQuadRelay *industrial_quad_relay, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

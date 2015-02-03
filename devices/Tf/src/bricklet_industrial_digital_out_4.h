/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_DIGITAL_OUT_4_H
#define BRICKLET_INDUSTRIAL_DIGITAL_OUT_4_H

#include "ip_connection.h"

/**
 * \defgroup BrickletIndustrialDigitalOut4 IndustrialDigitalOut4 Bricklet
 */

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Device for controlling up to 4 optically coupled digital outputs
 */
typedef Device IndustrialDigitalOut4;

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_VALUE 1

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_VALUE 2

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_MONOFLOP 3

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_MONOFLOP 4

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_GROUP 5

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_GROUP 6

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_AVAILABLE_FOR_GROUP 7

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_SET_SELECTED_VALUES 9

/**
 * \ingroup BrickletIndustrialDigitalOut4
 */
#define INDUSTRIAL_DIGITAL_OUT_4_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Signature: \code void callback(uint16_t selection_mask, uint16_t value_mask, void *user_data) \endcode
 * 
 * This callback is triggered whenever a monoflop timer reaches 0. The
 * parameters contain the involved pins and the current value of the pins
 * (the value after the monoflop).
 */
#define INDUSTRIAL_DIGITAL_OUT_4_CALLBACK_MONOFLOP_DONE 8


/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * This constant is used to identify a IndustrialDigitalOut4 Bricklet.
 *
 * The {@link industrial_digital_out_4_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_DIGITAL_OUT_4_DEVICE_IDENTIFIER 224

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Creates the device object \c industrial_digital_out_4 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_digital_out_4_create(IndustrialDigitalOut4 *industrial_digital_out_4, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Removes the device object \c industrial_digital_out_4 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_digital_out_4_destroy(IndustrialDigitalOut4 *industrial_digital_out_4);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_digital_out_4_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_digital_out_4_get_response_expected(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialDigitalOut4
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
int industrial_digital_out_4_set_response_expected(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_digital_out_4_set_response_expected_all(IndustrialDigitalOut4 *industrial_digital_out_4, bool response_expected);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void industrial_digital_out_4_register_callback(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_digital_out_4_get_api_version(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Sets the output value with a bitmask. The bitmask
 * is 16 bit long, *true* refers to high and *false* refers to 
 * low.
 * 
 * For example: The value 3 or 0b0011 will turn pins 0-1 high and the other pins
 * low.
 * 
 * If no groups are used (see {@link industrial_digital_out_4_set_group}), the pins correspond to the
 * markings on the Digital Out 4 Bricklet.
 * 
 * If groups are used, the pins correspond to the element in the group.
 * Element 1 in the group will get pins 0-3, element 2 pins 4-7, element 3
 * pins 8-11 and element 4 pins 12-15.
 */
int industrial_digital_out_4_set_value(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t value_mask);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Returns the bitmask as set by {@link industrial_digital_out_4_set_value}.
 */
int industrial_digital_out_4_get_value(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t *ret_value_mask);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Configures a monoflop of the pins specified by the first parameter
 * bitmask.
 * 
 * The second parameter is a bitmask with the desired value of the specified
 * pins (*true* means high and *false* means low).
 * 
 * The third parameter indicates the time (in ms) that the pins should hold
 * the value.
 * 
 * If this function is called with the parameters (9, 1, 1500) or
 * (0b1001, 0b0001, 1500): Pin 0 will get high and pin 3 will get low. In 1.5s
 * pin 0 will get low and pin 3 will get high again.
 * 
 * A monoflop can be used as a fail-safe mechanism. For example: Lets assume you
 * have a RS485 bus and a Digital Out 4 Bricklet connected to one of the slave
 * stacks. You can now call this function every second, with a time parameter
 * of two seconds and pin 0 high. Pin 0 will be high all the time. If now
 * the RS485 connection is lost, then pin 0 will turn low in at most two seconds.
 */
int industrial_digital_out_4_set_monoflop(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t selection_mask, uint16_t value_mask, uint32_t time);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Returns (for the given pin) the current value and the time as set by
 * {@link industrial_digital_out_4_set_monoflop} as well as the remaining time until the value flips.
 * 
 * If the timer is not running currently, the remaining time will be returned
 * as 0.
 */
int industrial_digital_out_4_get_monoflop(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t pin, uint16_t *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Sets a group of Digital Out 4 Bricklets that should work together. You can
 * find Bricklets that can be grouped together with {@link industrial_digital_out_4_get_available_for_group}.
 * 
 * The group consists of 4 elements. Element 1 in the group will get pins 0-3,
 * element 2 pins 4-7, element 3 pins 8-11 and element 4 pins 12-15.
 * 
 * Each element can either be one of the ports ('a' to 'd') or 'n' if it should
 * not be used.
 * 
 * For example: If you have two Digital Out 4 Bricklets connected to port A and
 * port B respectively, you could call with ``['a', 'b', 'n', 'n']``.
 * 
 * Now the pins on the Digital Out 4 on port A are assigned to 0-3 and the
 * pins on the Digital Out 4 on port B are assigned to 4-7. It is now possible
 * to call {@link industrial_digital_out_4_set_value} and control two Bricklets at the same time.
 */
int industrial_digital_out_4_set_group(IndustrialDigitalOut4 *industrial_digital_out_4, char group[4]);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Returns the group as set by {@link industrial_digital_out_4_set_group}
 */
int industrial_digital_out_4_get_group(IndustrialDigitalOut4 *industrial_digital_out_4, char ret_group[4]);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Returns a bitmask of ports that are available for grouping. For example the
 * value 5 or 0b0101 means: Port A and port C are connected to Bricklets that
 * can be grouped together.
 */
int industrial_digital_out_4_get_available_for_group(IndustrialDigitalOut4 *industrial_digital_out_4, uint8_t *ret_available);

/**
 * \ingroup BrickletIndustrialDigitalOut4
 *
 * Sets the output value with a bitmask, according to the selection mask.
 * The bitmask is 16 bit long, *true* refers to high and *false* refers to 
 * low.
 * 
 * For example: The values (3, 1) or (0b0011, 0b0001) will turn pin 0 high, pin 1
 * low the other pins remain untouched.
 * 
 * If no groups are used (see {@link industrial_digital_out_4_set_group}), the pins correspond to the
 * markings on the Digital Out 4 Bricklet.
 * 
 * If groups are used, the pins correspond to the element in the group.
 * Element 1 in the group will get pins 0-3, element 2 pins 4-7, element 3
 * pins 8-11 and element 4 pins 12-15.
 * 
 * .. versionadded:: 2.0.0~(Plugin)
 */
int industrial_digital_out_4_set_selected_values(IndustrialDigitalOut4 *industrial_digital_out_4, uint16_t selection_mask, uint16_t value_mask);

/**
 * \ingroup BrickletIndustrialDigitalOut4
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
int industrial_digital_out_4_get_identity(IndustrialDigitalOut4 *industrial_digital_out_4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

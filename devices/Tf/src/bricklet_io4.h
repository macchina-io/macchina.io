/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_IO4_H
#define BRICKLET_IO4_H

#include "ip_connection.h"

/**
 * \defgroup BrickletIO4 IO4 Bricklet
 */

/**
 * \ingroup BrickletIO4
 *
 * Device for controlling up to 4 general purpose input/output pins
 */
typedef Device IO4;

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_VALUE 1

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_VALUE 2

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_CONFIGURATION 3

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_CONFIGURATION 4

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_DEBOUNCE_PERIOD 5

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_INTERRUPT 7

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_INTERRUPT 8

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_MONOFLOP 10

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_MONOFLOP 11

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_SELECTED_VALUES 13

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_EDGE_COUNT 14

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_SET_EDGE_COUNT_CONFIG 15

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_EDGE_COUNT_CONFIG 16

/**
 * \ingroup BrickletIO4
 */
#define IO4_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIO4
 *
 * Signature: \code void callback(uint8_t interrupt_mask, uint8_t value_mask, void *user_data) \endcode
 * 
 * This callback is triggered whenever a change of the voltage level is detected
 * on pins where the interrupt was activated with {@link io4_set_interrupt}.
 * 
 * The values are a bitmask that specifies which interrupts occurred
 * and the current value bitmask.
 * 
 * For example:
 * 
 * * (1, 1) or (0b0001, 0b0001) means that an interrupt on pin 0 occurred and
 *   currently pin 0 is high and pins 1-3 are low.
 * * (9, 14) or (0b1001, 0b1110) means that interrupts on pins 0 and 3
 *   occurred and currently pin 0 is low and pins 1-3 are high.
 */
#define IO4_CALLBACK_INTERRUPT 9

/**
 * \ingroup BrickletIO4
 *
 * Signature: \code void callback(uint8_t selection_mask, uint8_t value_mask, void *user_data) \endcode
 * 
 * This callback is triggered whenever a monoflop timer reaches 0. The
 * parameters contain the involved pins and the current value of the pins
 * (the value after the monoflop).
 * 
 * .. versionadded:: 1.1.1~(Plugin)
 */
#define IO4_CALLBACK_MONOFLOP_DONE 12


/**
 * \ingroup BrickletIO4
 */
#define IO4_DIRECTION_IN 'i'

/**
 * \ingroup BrickletIO4
 */
#define IO4_DIRECTION_OUT 'o'

/**
 * \ingroup BrickletIO4
 */
#define IO4_EDGE_TYPE_RISING 0

/**
 * \ingroup BrickletIO4
 */
#define IO4_EDGE_TYPE_FALLING 1

/**
 * \ingroup BrickletIO4
 */
#define IO4_EDGE_TYPE_BOTH 2

/**
 * \ingroup BrickletIO4
 *
 * This constant is used to identify a IO4 Bricklet.
 *
 * The {@link io4_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define IO4_DEVICE_IDENTIFIER 29

/**
 * \ingroup BrickletIO4
 *
 * Creates the device object \c io4 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void io4_create(IO4 *io4, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIO4
 *
 * Removes the device object \c io4 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void io4_destroy(IO4 *io4);

/**
 * \ingroup BrickletIO4
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the io4_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int io4_get_response_expected(IO4 *io4, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIO4
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
int io4_set_response_expected(IO4 *io4, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIO4
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int io4_set_response_expected_all(IO4 *io4, bool response_expected);

/**
 * \ingroup BrickletIO4
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void io4_register_callback(IO4 *io4, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletIO4
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int io4_get_api_version(IO4 *io4, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIO4
 *
 * Sets the output value (high or low) with a bitmask. The bitmask
 * is 4bit long, *true* refers to high and *false* refers to low.
 * 
 * For example: The value 3 or 0b0011 will turn the pins 0-1 high and the
 * pins 2-3 low.
 * 
 * \note
 *  This function does nothing for pins that are configured as input.
 *  Pull-up resistors can be switched on with {@link io4_set_configuration}.
 */
int io4_set_value(IO4 *io4, uint8_t value_mask);

/**
 * \ingroup BrickletIO4
 *
 * Returns a bitmask of the values that are currently measured.
 * This function works if the pin is configured to input
 * as well as if it is configured to output.
 */
int io4_get_value(IO4 *io4, uint8_t *ret_value_mask);

/**
 * \ingroup BrickletIO4
 *
 * Configures the value and direction of the specified pins. Possible directions
 * are 'i' and 'o' for input and output.
 * 
 * If the direction is configured as output, the value is either high or low
 * (set as *true* or *false*).
 * 
 * If the direction is configured as input, the value is either pull-up or
 * default (set as *true* or *false*).
 * 
 * For example:
 * 
 * * (15, 'i', true) or (0b1111, 'i', true) will set all pins of as input pull-up.
 * * (8, 'i', false) or (0b1000, 'i', false) will set pin 3 of as input default (floating if nothing is connected).
 * * (3, 'o', false) or (0b0011, 'o', false) will set pins 0 and 1 as output low.
 * * (4, 'o', true) or (0b0100, 'o', true) will set pin 2 of as output high.
 */
int io4_set_configuration(IO4 *io4, uint8_t selection_mask, char direction, bool value);

/**
 * \ingroup BrickletIO4
 *
 * Returns a value bitmask and a direction bitmask.
 * 
 * For example: A return value of (3, 5) or (0b0011, 0b0101) for direction and
 * value means that:
 * 
 * * pin 0 is configured as input pull-up,
 * * pin 1 is configured as input default,
 * * pin 2 is configured as output high and
 * * pin 3 is are configured as output low.
 */
int io4_get_configuration(IO4 *io4, uint8_t *ret_direction_mask, uint8_t *ret_value_mask);

/**
 * \ingroup BrickletIO4
 *
 * Sets the debounce period of the {@link IO4_CALLBACK_INTERRUPT} callback in ms.
 * 
 * For example: If you set this value to 100, you will get the interrupt
 * maximal every 100ms. This is necessary if something that bounces is
 * connected to the IO-4 Bricklet, such as a button.
 * 
 * The default value is 100.
 */
int io4_set_debounce_period(IO4 *io4, uint32_t debounce);

/**
 * \ingroup BrickletIO4
 *
 * Returns the debounce period as set by {@link io4_set_debounce_period}.
 */
int io4_get_debounce_period(IO4 *io4, uint32_t *ret_debounce);

/**
 * \ingroup BrickletIO4
 *
 * Sets the pins on which an interrupt is activated with a bitmask.
 * Interrupts are triggered on changes of the voltage level of the pin,
 * i.e. changes from high to low and low to high.
 * 
 * For example: An interrupt bitmask of 10 or 0b1010 will enable the interrupt for
 * pins 1 and 3.
 * 
 * The interrupt is delivered with the callback {@link IO4_CALLBACK_INTERRUPT}.
 */
int io4_set_interrupt(IO4 *io4, uint8_t interrupt_mask);

/**
 * \ingroup BrickletIO4
 *
 * Returns the interrupt bitmask as set by {@link io4_set_interrupt}.
 */
int io4_get_interrupt(IO4 *io4, uint8_t *ret_interrupt_mask);

/**
 * \ingroup BrickletIO4
 *
 * Configures a monoflop of the pins specified by the first parameter as 4 bit
 * long bitmask. The specified pins must be configured for output. Non-output
 * pins will be ignored.
 * 
 * The second parameter is a bitmask with the desired value of the specified
 * output pins (*true* means high and *false* means low).
 * 
 * The third parameter indicates the time (in ms) that the pins should hold
 * the value.
 * 
 * If this function is called with the parameters (9, 1, 1500) or
 * (0b1001, 0b0001, 1500): Pin 0 will get high and pin 3 will get low. In 1.5s pin
 * 0 will get low and pin 3 will get high again.
 * 
 * A monoflop can be used as a fail-safe mechanism. For example: Lets assume you
 * have a RS485 bus and an IO-4 Bricklet connected to one of the slave
 * stacks. You can now call this function every second, with a time parameter
 * of two seconds and pin 0 set to high. Pin 0 will be high all the time. If now
 * the RS485 connection is lost, then pin 0 will get low in at most two seconds.
 * 
 * .. versionadded:: 1.1.1~(Plugin)
 */
int io4_set_monoflop(IO4 *io4, uint8_t selection_mask, uint8_t value_mask, uint32_t time);

/**
 * \ingroup BrickletIO4
 *
 * Returns (for the given pin) the current value and the time as set by
 * {@link io4_set_monoflop} as well as the remaining time until the value flips.
 * 
 * If the timer is not running currently, the remaining time will be returned
 * as 0.
 * 
 * .. versionadded:: 1.1.1~(Plugin)
 */
int io4_get_monoflop(IO4 *io4, uint8_t pin, uint8_t *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining);

/**
 * \ingroup BrickletIO4
 *
 * Sets the output value (high or low) with a bitmask, according to
 * the selection mask. The bitmask is 4 bit long, *true* refers to high 
 * and *false* refers to low.
 * 
 * For example: The parameters (9, 4) or (0b0110, 0b0100) will turn
 * pin 1 low and pin 2 high, pin 0 and 3 will remain untouched.
 * 
 * \note
 *  This function does nothing for pins that are configured as input.
 *  Pull-up resistors can be switched on with {@link io4_set_configuration}.
 * 
 * .. versionadded:: 2.0.0~(Plugin)
 */
int io4_set_selected_values(IO4 *io4, uint8_t selection_mask, uint8_t value_mask);

/**
 * \ingroup BrickletIO4
 *
 * Returns the current value of the edge counter for the selected pin. You can
 * configure the edges that are counted with {@link io4_set_edge_count_config}.
 * 
 * If you set the reset counter to *true*, the count is set back to 0
 * directly after it is read.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int io4_get_edge_count(IO4 *io4, uint8_t pin, bool reset_counter, uint32_t *ret_count);

/**
 * \ingroup BrickletIO4
 *
 * Configures the edge counter for the selected pins.
 * 
 * The edge type parameter configures if rising edges, falling edges or
 * both are counted if the pin is configured for input. Possible edge types are:
 * 
 * * 0 = rising (default)
 * * 1 = falling
 * * 2 = both
 * 
 * The debounce time is given in ms.
 * 
 * If you don't know what any of this means, just leave it at default. The
 * default configuration is very likely OK for you.
 * 
 * Default values: 0 (edge type) and 100ms (debounce time)
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int io4_set_edge_count_config(IO4 *io4, uint8_t selection_mask, uint8_t edge_type, uint8_t debounce);

/**
 * \ingroup BrickletIO4
 *
 * Returns the edge type and debounce time for the selected pin as set by
 * {@link io4_set_edge_count_config}.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int io4_get_edge_count_config(IO4 *io4, uint8_t pin, uint8_t *ret_edge_type, uint8_t *ret_debounce);

/**
 * \ingroup BrickletIO4
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
int io4_get_identity(IO4 *io4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

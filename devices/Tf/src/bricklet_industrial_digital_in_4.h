/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_DIGITAL_IN_4_H
#define BRICKLET_INDUSTRIAL_DIGITAL_IN_4_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialDigitalIn4 IndustrialDigitalIn4 Bricklet
 */

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Device for controlling up to 4 optically coupled digital inputs
 */
typedef Device IndustrialDigitalIn4;

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_VALUE 1

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_GROUP 2

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_GROUP 3

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_AVAILABLE_FOR_GROUP 4

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_DEBOUNCE_PERIOD 5

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_INTERRUPT 7

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_INTERRUPT 8

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_EDGE_COUNT 10

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_EDGE_COUNT_CONFIG 11

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_EDGE_COUNT_CONFIG 12

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Signature: \code void callback(uint16_t interrupt_mask, uint16_t value_mask, void *user_data) \endcode
 * 
 * This callback is triggered whenever a change of the voltage level is detected
 * on pins where the interrupt was activated with {@link industrial_digital_in_4_set_interrupt}.
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
#define INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT 9


/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_EDGE_TYPE_RISING 0

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_EDGE_TYPE_FALLING 1

/**
 * \ingroup BrickletIndustrialDigitalIn4
 */
#define INDUSTRIAL_DIGITAL_IN_4_EDGE_TYPE_BOTH 2

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * This constant is used to identify a IndustrialDigitalIn4 Bricklet.
 *
 * The {@link industrial_digital_in_4_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_DIGITAL_IN_4_DEVICE_IDENTIFIER 223

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Creates the device object \c industrial_digital_in_4 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_digital_in_4_create(IndustrialDigitalIn4 *industrial_digital_in_4, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Removes the device object \c industrial_digital_in_4 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_digital_in_4_destroy(IndustrialDigitalIn4 *industrial_digital_in_4);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_digital_in_4_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_digital_in_4_get_response_expected(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialDigitalIn4
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
int industrial_digital_in_4_set_response_expected(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_digital_in_4_set_response_expected_all(IndustrialDigitalIn4 *industrial_digital_in_4, bool response_expected);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void industrial_digital_in_4_register_callback(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_digital_in_4_get_api_version(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the input value with a bitmask. The bitmask is 16bit long, *true*
 * refers to high and *false* refers to low.
 * 
 * For example: The value 3 or 0b0011 means that pins 0-1 are high and the other
 * pins are low.
 * 
 * If no groups are used (see {@link industrial_digital_in_4_set_group}), the pins correspond to the
 * markings on the Digital In 4 Bricklet.
 * 
 * If groups are used, the pins correspond to the element in the group.
 * Element 1 in the group will get pins 0-3, element 2 pins 4-7, element 3
 * pins 8-11 and element 4 pins 12-15.
 */
int industrial_digital_in_4_get_value(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t *ret_value_mask);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Sets a group of Digital In 4 Bricklets that should work together. You can
 * find Bricklets that can be grouped together with {@link industrial_digital_in_4_get_available_for_group}.
 * 
 * The group consists of 4 elements. Element 1 in the group will get pins 0-3,
 * element 2 pins 4-7, element 3 pins 8-11 and element 4 pins 12-15.
 * 
 * Each element can either be one of the ports ('a' to 'd') or 'n' if it should
 * not be used.
 * 
 * For example: If you have two Digital In 4 Bricklets connected to port A and
 * port B respectively, you could call with ``['a', 'b', 'n', 'n']``.
 * 
 * Now the pins on the Digital In 4 on port A are assigned to 0-3 and the
 * pins on the Digital In 4 on port B are assigned to 4-7. It is now possible
 * to call {@link industrial_digital_in_4_get_value} and read out two Bricklets at the same time.
 * 
 * Changing the group configuration resets all edge counter configurations
 * and values.
 */
int industrial_digital_in_4_set_group(IndustrialDigitalIn4 *industrial_digital_in_4, char group[4]);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the group as set by {@link industrial_digital_in_4_set_group}
 */
int industrial_digital_in_4_get_group(IndustrialDigitalIn4 *industrial_digital_in_4, char ret_group[4]);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns a bitmask of ports that are available for grouping. For example the
 * value 5 or 0b0101 means: Port A and port C are connected to Bricklets that
 * can be grouped together.
 */
int industrial_digital_in_4_get_available_for_group(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t *ret_available);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Sets the debounce period of the {@link INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT} callback in ms.
 * 
 * For example: If you set this value to 100, you will get the interrupt
 * maximal every 100ms. This is necessary if something that bounces is
 * connected to the Digital In 4 Bricklet, such as a button.
 * 
 * The default value is 100.
 */
int industrial_digital_in_4_set_debounce_period(IndustrialDigitalIn4 *industrial_digital_in_4, uint32_t debounce);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the debounce period as set by {@link industrial_digital_in_4_set_debounce_period}.
 */
int industrial_digital_in_4_get_debounce_period(IndustrialDigitalIn4 *industrial_digital_in_4, uint32_t *ret_debounce);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Sets the pins on which an interrupt is activated with a bitmask.
 * Interrupts are triggered on changes of the voltage level of the pin,
 * i.e. changes from high to low and low to high.
 * 
 * For example: An interrupt bitmask of 9 or 0b1001 will enable the interrupt for
 * pins 0 and 3.
 * 
 * The interrupts use the grouping as set by {@link industrial_digital_in_4_set_group}.
 * 
 * The interrupt is delivered with the callback {@link INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT}.
 */
int industrial_digital_in_4_set_interrupt(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t interrupt_mask);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the interrupt bitmask as set by {@link industrial_digital_in_4_set_interrupt}.
 */
int industrial_digital_in_4_get_interrupt(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t *ret_interrupt_mask);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the current value of the edge counter for the selected pin. You can
 * configure the edges that are counted with {@link industrial_digital_in_4_set_edge_count_config}.
 * 
 * If you set the reset counter to *true*, the count is set back to 0
 * directly after it is read.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int industrial_digital_in_4_get_edge_count(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t pin, bool reset_counter, uint32_t *ret_count);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Configures the edge counter for the selected pins. A bitmask of 9 or 0b1001 will
 * enable the edge counter for pins 0 and 3.
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
 * Configuring an edge counter resets its value to 0.
 * 
 * If you don't know what any of this means, just leave it at default. The
 * default configuration is very likely OK for you.
 * 
 * Default values: 0 (edge type) and 100ms (debounce time)
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int industrial_digital_in_4_set_edge_count_config(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t selection_mask, uint8_t edge_type, uint8_t debounce);

/**
 * \ingroup BrickletIndustrialDigitalIn4
 *
 * Returns the edge type and debounce time for the selected pin as set by
 * {@link industrial_digital_in_4_set_edge_count_config}.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int industrial_digital_in_4_get_edge_count_config(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t pin, uint8_t *ret_edge_type, uint8_t *ret_debounce);

/**
 * \ingroup BrickletIndustrialDigitalIn4
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
int industrial_digital_in_4_get_identity(IndustrialDigitalIn4 *industrial_digital_in_4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

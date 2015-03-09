/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_DUAL_RELAY_H
#define BRICKLET_DUAL_RELAY_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletDualRelay DualRelay Bricklet
 */

/**
 * \ingroup BrickletDualRelay
 *
 * Device for controlling two relays
 */
typedef Device DualRelay;

/**
 * \ingroup BrickletDualRelay
 */
#define DUAL_RELAY_FUNCTION_SET_STATE 1

/**
 * \ingroup BrickletDualRelay
 */
#define DUAL_RELAY_FUNCTION_GET_STATE 2

/**
 * \ingroup BrickletDualRelay
 */
#define DUAL_RELAY_FUNCTION_SET_MONOFLOP 3

/**
 * \ingroup BrickletDualRelay
 */
#define DUAL_RELAY_FUNCTION_GET_MONOFLOP 4

/**
 * \ingroup BrickletDualRelay
 */
#define DUAL_RELAY_FUNCTION_SET_SELECTED_STATE 6

/**
 * \ingroup BrickletDualRelay
 */
#define DUAL_RELAY_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletDualRelay
 *
 * Signature: \code void callback(uint8_t relay, bool state, void *user_data) \endcode
 * 
 * This callback is triggered whenever a monoflop timer reaches 0. The 
 * parameter contain the relay (1 or 2) and the current state of the relay 
 * (the state after the monoflop).
 */
#define DUAL_RELAY_CALLBACK_MONOFLOP_DONE 5


/**
 * \ingroup BrickletDualRelay
 *
 * This constant is used to identify a DualRelay Bricklet.
 *
 * The {@link dual_relay_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define DUAL_RELAY_DEVICE_IDENTIFIER 26

/**
 * \ingroup BrickletDualRelay
 *
 * Creates the device object \c dual_relay with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void dual_relay_create(DualRelay *dual_relay, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletDualRelay
 *
 * Removes the device object \c dual_relay from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void dual_relay_destroy(DualRelay *dual_relay);

/**
 * \ingroup BrickletDualRelay
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the dual_relay_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int dual_relay_get_response_expected(DualRelay *dual_relay, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletDualRelay
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
int dual_relay_set_response_expected(DualRelay *dual_relay, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletDualRelay
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int dual_relay_set_response_expected_all(DualRelay *dual_relay, bool response_expected);

/**
 * \ingroup BrickletDualRelay
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void dual_relay_register_callback(DualRelay *dual_relay, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletDualRelay
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int dual_relay_get_api_version(DualRelay *dual_relay, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletDualRelay
 *
 * Sets the state of the relays, *true* means on and *false* means off. 
 * For example: (true, false) turns relay 1 on and relay 2 off.
 * 
 * If you just want to set one of the relays and don't know the current state
 * of the other relay, you can get the state with {@link dual_relay_get_state} or you
 * can use {@link dual_relay_set_selected_state}.
 * 
 * Running monoflop timers will be overwritten if this function is called.
 * 
 * The default value is (*false*, *false*).
 */
int dual_relay_set_state(DualRelay *dual_relay, bool relay1, bool relay2);

/**
 * \ingroup BrickletDualRelay
 *
 * Returns the state of the relays, *true* means on and *false* means off.
 */
int dual_relay_get_state(DualRelay *dual_relay, bool *ret_relay1, bool *ret_relay2);

/**
 * \ingroup BrickletDualRelay
 *
 * The first parameter can be 1 or 2 (relay 1 or relay 2). The second parameter 
 * is the desired state of the relay (*true* means on and *false* means off).
 * The third parameter indicates the time (in ms) that the relay should hold 
 * the state.
 * 
 * If this function is called with the parameters (1, true, 1500):
 * Relay 1 will turn on and in 1.5s it will turn off again.
 * 
 * A monoflop can be used as a failsafe mechanism. For example: Lets assume you 
 * have a RS485 bus and a Dual Relay Bricklet connected to one of the slave 
 * stacks. You can now call this function every second, with a time parameter
 * of two seconds. The relay will be on all the time. If now the RS485 
 * connection is lost, the relay will turn off in at most two seconds.
 */
int dual_relay_set_monoflop(DualRelay *dual_relay, uint8_t relay, bool state, uint32_t time);

/**
 * \ingroup BrickletDualRelay
 *
 * Returns (for the given relay) the current state and the time as set by 
 * {@link dual_relay_set_monoflop} as well as the remaining time until the state flips.
 * 
 * If the timer is not running currently, the remaining time will be returned
 * as 0.
 */
int dual_relay_get_monoflop(DualRelay *dual_relay, uint8_t relay, bool *ret_state, uint32_t *ret_time, uint32_t *ret_time_remaining);

/**
 * \ingroup BrickletDualRelay
 *
 * Sets the state of the selected relay (1 or 2), *true* means on and *false* means off. 
 * 
 * The other relay remains untouched.
 */
int dual_relay_set_selected_state(DualRelay *dual_relay, uint8_t relay, bool state);

/**
 * \ingroup BrickletDualRelay
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
int dual_relay_get_identity(DualRelay *dual_relay, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_SOLID_STATE_RELAY_H
#define BRICKLET_SOLID_STATE_RELAY_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletSolidStateRelay Solid State Relay Bricklet
 */

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Controls AC and DC Solid State Relays
 */
typedef Device SolidStateRelay;

/**
 * \ingroup BrickletSolidStateRelay
 */
#define SOLID_STATE_RELAY_FUNCTION_SET_STATE 1

/**
 * \ingroup BrickletSolidStateRelay
 */
#define SOLID_STATE_RELAY_FUNCTION_GET_STATE 2

/**
 * \ingroup BrickletSolidStateRelay
 */
#define SOLID_STATE_RELAY_FUNCTION_SET_MONOFLOP 3

/**
 * \ingroup BrickletSolidStateRelay
 */
#define SOLID_STATE_RELAY_FUNCTION_GET_MONOFLOP 4

/**
 * \ingroup BrickletSolidStateRelay
 */
#define SOLID_STATE_RELAY_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Signature: \code void callback(bool state, void *user_data) \endcode
 * 
 * This callback is triggered whenever the monoflop timer reaches 0. 
 * The parameter is the current state of the relay 
 * (the state after the monoflop).
 */
#define SOLID_STATE_RELAY_CALLBACK_MONOFLOP_DONE 5


/**
 * \ingroup BrickletSolidStateRelay
 *
 * This constant is used to identify a Solid State Relay Bricklet.
 *
 * The {@link solid_state_relay_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define SOLID_STATE_RELAY_DEVICE_IDENTIFIER 244

/**
 * \ingroup BrickletSolidStateRelay
 *
 * This constant represents the display name of a Solid State Relay Bricklet.
 */
#define SOLID_STATE_RELAY_DEVICE_DISPLAY_NAME "Solid State Relay Bricklet"

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Creates the device object \c solid_state_relay with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void solid_state_relay_create(SolidStateRelay *solid_state_relay, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Removes the device object \c solid_state_relay from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void solid_state_relay_destroy(SolidStateRelay *solid_state_relay);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the solid_state_relay_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int solid_state_relay_get_response_expected(SolidStateRelay *solid_state_relay, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletSolidStateRelay
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
int solid_state_relay_set_response_expected(SolidStateRelay *solid_state_relay, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int solid_state_relay_set_response_expected_all(SolidStateRelay *solid_state_relay, bool response_expected);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void solid_state_relay_register_callback(SolidStateRelay *solid_state_relay, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int solid_state_relay_get_api_version(SolidStateRelay *solid_state_relay, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Sets the state of the relays *true* means on and *false* means off. 
 * 
 * Running monoflop timers will be overwritten if this function is called.
 * 
 * The default value is *false*.
 */
int solid_state_relay_set_state(SolidStateRelay *solid_state_relay, bool state);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Returns the state of the relay, *true* means on and *false* means off.
 */
int solid_state_relay_get_state(SolidStateRelay *solid_state_relay, bool *ret_state);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * The first parameter  is the desired state of the relay (*true* means on 
 * and *false* means off). The second parameter indicates the time (in ms) that 
 * the relay should hold the state.
 * 
 * If this function is called with the parameters (true, 1500):
 * The relay will turn on and in 1.5s it will turn off again.
 * 
 * A monoflop can be used as a failsafe mechanism. For example: Lets assume you 
 * have a RS485 bus and a Solid State Relay Bricklet connected to one of the slave 
 * stacks. You can now call this function every second, with a time parameter
 * of two seconds. The relay will be on all the time. If now the RS485 
 * connection is lost, the relay will turn off in at most two seconds.
 */
int solid_state_relay_set_monoflop(SolidStateRelay *solid_state_relay, bool state, uint32_t time);

/**
 * \ingroup BrickletSolidStateRelay
 *
 * Returns the current state and the time as set by 
 * {@link solid_state_relay_set_monoflop} as well as the remaining time until the state flips.
 * 
 * If the timer is not running currently, the remaining time will be returned
 * as 0.
 */
int solid_state_relay_get_monoflop(SolidStateRelay *solid_state_relay, bool *ret_state, uint32_t *ret_time, uint32_t *ret_time_remaining);

/**
 * \ingroup BrickletSolidStateRelay
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
int solid_state_relay_get_identity(SolidStateRelay *solid_state_relay, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

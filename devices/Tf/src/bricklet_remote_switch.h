/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_REMOTE_SWITCH_H
#define BRICKLET_REMOTE_SWITCH_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRemoteSwitch Remote Switch Bricklet
 */

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Controls remote mains switches
 */
typedef Device RemoteSwitch;

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET 1

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_GET_SWITCHING_STATE 2

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_SET_REPEATS 4

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_GET_REPEATS 5

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_A 6

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_B 7

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_DIM_SOCKET_B 8

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_C 9

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is called whenever the switching state changes
 * from busy to ready, see {@link remote_switch_get_switching_state}.
 */
#define REMOTE_SWITCH_CALLBACK_SWITCHING_DONE 3


/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_SWITCH_TO_OFF 0

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_SWITCH_TO_ON 1

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_SWITCHING_STATE_READY 0

/**
 * \ingroup BrickletRemoteSwitch
 */
#define REMOTE_SWITCH_SWITCHING_STATE_BUSY 1

/**
 * \ingroup BrickletRemoteSwitch
 *
 * This constant is used to identify a Remote Switch Bricklet.
 *
 * The {@link remote_switch_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define REMOTE_SWITCH_DEVICE_IDENTIFIER 235

/**
 * \ingroup BrickletRemoteSwitch
 *
 * This constant represents the display name of a Remote Switch Bricklet.
 */
#define REMOTE_SWITCH_DEVICE_DISPLAY_NAME "Remote Switch Bricklet"

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Creates the device object \c remote_switch with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void remote_switch_create(RemoteSwitch *remote_switch, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Removes the device object \c remote_switch from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void remote_switch_destroy(RemoteSwitch *remote_switch);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the remote_switch_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int remote_switch_get_response_expected(RemoteSwitch *remote_switch, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRemoteSwitch
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
int remote_switch_set_response_expected(RemoteSwitch *remote_switch, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int remote_switch_set_response_expected_all(RemoteSwitch *remote_switch, bool response_expected);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void remote_switch_register_callback(RemoteSwitch *remote_switch, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int remote_switch_get_api_version(RemoteSwitch *remote_switch, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * This function is deprecated, use {@link remote_switch_switch_socket_a} instead.
 */
int remote_switch_switch_socket(RemoteSwitch *remote_switch, uint8_t house_code, uint8_t receiver_code, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Returns the current switching state. If the current state is busy, the
 * Bricklet is currently sending a code to switch a socket. It will not
 * accept any calls of {@link remote_switch_switch_socket} until the state changes to ready.
 * 
 * How long the switching takes is dependent on the number of repeats, see
 * {@link remote_switch_set_repeats}.
 */
int remote_switch_get_switching_state(RemoteSwitch *remote_switch, uint8_t *ret_state);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Sets the number of times the code is send when of the {@link remote_switch_switch_socket}
 * functions is called. The repeats basically correspond to the amount of time
 * that a button of the remote is pressed.
 * 
 * Some dimmers are controlled by the length of a button pressed,
 * this can be simulated by increasing the repeats.
 * 
 * The default value is 5.
 */
int remote_switch_set_repeats(RemoteSwitch *remote_switch, uint8_t repeats);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * Returns the number of repeats as set by {@link remote_switch_set_repeats}.
 */
int remote_switch_get_repeats(RemoteSwitch *remote_switch, uint8_t *ret_repeats);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * To switch a type A socket you have to give the house code, receiver code and the
 * state (on or off) you want to switch to.
 * 
 * The house code and receiver code have a range of 0 to 31 (5bit).
 * 
 * A detailed description on how you can figure out the house and receiver code
 * can be found :ref:`here <remote_switch_bricklet_type_a_house_and_receiver_code>`.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int remote_switch_switch_socket_a(RemoteSwitch *remote_switch, uint8_t house_code, uint8_t receiver_code, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * To switch a type B socket you have to give the address, unit and the state
 * (on or off) you want to switch to.
 * 
 * The address has a range of 0 to 67108863 (26bit) and the unit has a range
 * of 0 to 15 (4bit). To switch all devices with the same address use 255 for
 * the unit.
 * 
 * A detailed description on how you can teach a socket the address and unit can
 * be found :ref:`here <remote_switch_bricklet_type_b_address_and_unit>`.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int remote_switch_switch_socket_b(RemoteSwitch *remote_switch, uint32_t address, uint8_t unit, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * To control a type B dimmer you have to give the address, unit and the
 * dim value you want to set the dimmer to.
 * 
 * The address has a range of 0 to 67108863 (26bit), the unit and the dim value
 * has a range of 0 to 15 (4bit).
 * 
 * A detailed description on how you can teach a dimmer the address and unit can
 * be found :ref:`here <remote_switch_bricklet_type_b_address_and_unit>`.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int remote_switch_dim_socket_b(RemoteSwitch *remote_switch, uint32_t address, uint8_t unit, uint8_t dim_value);

/**
 * \ingroup BrickletRemoteSwitch
 *
 * To switch a type C socket you have to give the system code, device code and the
 * state (on or off) you want to switch to.
 * 
 * The system code has a range of 'A' to 'P' (4bit) and the device code has a
 * range of 1 to 16 (4bit).
 * 
 * A detailed description on how you can figure out the system and device code
 * can be found :ref:`here <remote_switch_bricklet_type_c_system_and_device_code>`.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int remote_switch_switch_socket_c(RemoteSwitch *remote_switch, char system_code, uint8_t device_code, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitch
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
int remote_switch_get_identity(RemoteSwitch *remote_switch, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

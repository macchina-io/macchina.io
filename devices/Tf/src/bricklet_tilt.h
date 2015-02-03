/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_TILT_H
#define BRICKLET_TILT_H

#include "ip_connection.h"

/**
 * \defgroup BrickletTilt Tilt Bricklet
 */

/**
 * \ingroup BrickletTilt
 *
 * Device for sensing tilt and vibration
 */
typedef Device Tilt;

/**
 * \ingroup BrickletTilt
 */
#define TILT_FUNCTION_GET_TILT_STATE 1

/**
 * \ingroup BrickletTilt
 */
#define TILT_FUNCTION_ENABLE_TILT_STATE_CALLBACK 2

/**
 * \ingroup BrickletTilt
 */
#define TILT_FUNCTION_DISABLE_TILT_STATE_CALLBACK 3

/**
 * \ingroup BrickletTilt
 */
#define TILT_FUNCTION_IS_TILT_STATE_CALLBACK_ENABLED 4

/**
 * \ingroup BrickletTilt
 */
#define TILT_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletTilt
 *
 * Signature: \code void callback(uint8_t state, void *user_data) \endcode
 * 
 * This callback provides the current tilt state. It is called every time the
 * state changes.
 * 
 * See {@link tilt_get_tilt_state} for a description of the states.
 */
#define TILT_CALLBACK_TILT_STATE 5


/**
 * \ingroup BrickletTilt
 */
#define TILT_TILT_STATE_CLOSED 0

/**
 * \ingroup BrickletTilt
 */
#define TILT_TILT_STATE_OPEN 1

/**
 * \ingroup BrickletTilt
 */
#define TILT_TILT_STATE_CLOSED_VIBRATING 2

/**
 * \ingroup BrickletTilt
 *
 * This constant is used to identify a Tilt Bricklet.
 *
 * The {@link tilt_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define TILT_DEVICE_IDENTIFIER 239

/**
 * \ingroup BrickletTilt
 *
 * Creates the device object \c tilt with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void tilt_create(Tilt *tilt, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletTilt
 *
 * Removes the device object \c tilt from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void tilt_destroy(Tilt *tilt);

/**
 * \ingroup BrickletTilt
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the tilt_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int tilt_get_response_expected(Tilt *tilt, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletTilt
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
int tilt_set_response_expected(Tilt *tilt, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletTilt
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int tilt_set_response_expected_all(Tilt *tilt, bool response_expected);

/**
 * \ingroup BrickletTilt
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void tilt_register_callback(Tilt *tilt, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletTilt
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int tilt_get_api_version(Tilt *tilt, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletTilt
 *
 * Returns the current tilt state. The state can either be
 * 
 * * 0 = Closed: The ball in the tilt switch closes the circuit.
 * * 1 = Open: The ball in the tilt switch does not close the circuit.
 * * 2 = Closed Vibrating: The tilt switch is in motion (rapid change between open and close).
 * 
 * .. image:: /Images/Bricklets/bricklet_tilt_mechanics.jpg
 *    :scale: 100 %
 *    :alt: Tilt states
 *    :align: center
 *    :target: ../../_images/Bricklets/bricklet_tilt_mechanics.jpg
 */
int tilt_get_tilt_state(Tilt *tilt, uint8_t *ret_state);

/**
 * \ingroup BrickletTilt
 *
 * Enables the {@link TILT_CALLBACK_TILT_STATE} callback.
 */
int tilt_enable_tilt_state_callback(Tilt *tilt);

/**
 * \ingroup BrickletTilt
 *
 * Disables the {@link TILT_CALLBACK_TILT_STATE} callback.
 */
int tilt_disable_tilt_state_callback(Tilt *tilt);

/**
 * \ingroup BrickletTilt
 *
 * Returns *true* if the {@link TILT_CALLBACK_TILT_STATE} callback is enabled.
 */
int tilt_is_tilt_state_callback_enabled(Tilt *tilt, bool *ret_enabled);

/**
 * \ingroup BrickletTilt
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
int tilt_get_identity(Tilt *tilt, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

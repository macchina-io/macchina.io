/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_DUAL_BUTTON_H
#define BRICKLET_DUAL_BUTTON_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletDualButton DualButton Bricklet
 */

/**
 * \ingroup BrickletDualButton
 *
 * Device with two buttons and two LEDs
 */
typedef Device DualButton;

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_FUNCTION_SET_LED_STATE 1

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_FUNCTION_GET_LED_STATE 2

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_FUNCTION_GET_BUTTON_STATE 3

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_FUNCTION_SET_SELECTED_LED_STATE 5

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletDualButton
 *
 * Signature: \code void callback(uint8_t button_l, uint8_t button_r, uint8_t led_l, uint8_t led_r, void *user_data) \endcode
 * 
 * This callback is called whenever a button is pressed. 
 * 
 * Possible states for buttons are:
 * 
 * * 0 = pressed
 * * 1 = released
 * 
 * Possible states for LEDs are:
 * 
 * * 0 = AutoToggleOn: Auto toggle enabled and LED on.
 * * 1 = AutoToggleOff: Auto toggle enabled and LED off.
 * * 2 = On: LED on (auto toggle is disabled).
 * * 3 = Off: LED off (auto toggle is disabled).
 */
#define DUAL_BUTTON_CALLBACK_STATE_CHANGED 4


/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_LED_STATE_AUTO_TOGGLE_ON 0

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_LED_STATE_AUTO_TOGGLE_OFF 1

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_LED_STATE_ON 2

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_LED_STATE_OFF 3

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_BUTTON_STATE_PRESSED 0

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_BUTTON_STATE_RELEASED 1

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_LED_LEFT 0

/**
 * \ingroup BrickletDualButton
 */
#define DUAL_BUTTON_LED_RIGHT 1

/**
 * \ingroup BrickletDualButton
 *
 * This constant is used to identify a DualButton Bricklet.
 *
 * The {@link dual_button_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define DUAL_BUTTON_DEVICE_IDENTIFIER 230

/**
 * \ingroup BrickletDualButton
 *
 * Creates the device object \c dual_button with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void dual_button_create(DualButton *dual_button, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletDualButton
 *
 * Removes the device object \c dual_button from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void dual_button_destroy(DualButton *dual_button);

/**
 * \ingroup BrickletDualButton
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the dual_button_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int dual_button_get_response_expected(DualButton *dual_button, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletDualButton
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
int dual_button_set_response_expected(DualButton *dual_button, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletDualButton
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int dual_button_set_response_expected_all(DualButton *dual_button, bool response_expected);

/**
 * \ingroup BrickletDualButton
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void dual_button_register_callback(DualButton *dual_button, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletDualButton
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int dual_button_get_api_version(DualButton *dual_button, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletDualButton
 *
 * Sets the state of the LEDs. Possible states are:
 * 
 * * 0 = AutoToggleOn: Enables auto toggle with initially enabled LED.
 * * 1 = AutoToggleOff: Activates auto toggle with initially disabled LED.
 * * 2 = On: Enables LED (auto toggle is disabled).
 * * 3 = Off: Disables LED (auto toggle is disabled).
 * 
 * In auto toggle mode the LED is toggled automatically at each press of a button.
 * 
 * If you just want to set one of the LEDs and don't know the current state
 * of the other LED, you can get the state with {@link dual_button_get_led_state} or you
 * can use {@link dual_button_set_selected_led_state}.
 * 
 * The default value is (1, 1).
 */
int dual_button_set_led_state(DualButton *dual_button, uint8_t led_l, uint8_t led_r);

/**
 * \ingroup BrickletDualButton
 *
 * Returns the current state of the LEDs, as set by {@link dual_button_set_led_state}.
 */
int dual_button_get_led_state(DualButton *dual_button, uint8_t *ret_led_l, uint8_t *ret_led_r);

/**
 * \ingroup BrickletDualButton
 *
 * Returns the current state for both buttons. Possible states are:
 * 
 * * 0 = pressed
 * * 1 = released
 */
int dual_button_get_button_state(DualButton *dual_button, uint8_t *ret_button_l, uint8_t *ret_button_r);

/**
 * \ingroup BrickletDualButton
 *
 * Sets the state of the selected LED (0 or 1). 
 * 
 * The other LED remains untouched.
 */
int dual_button_set_selected_led_state(DualButton *dual_button, uint8_t led, uint8_t state);

/**
 * \ingroup BrickletDualButton
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
int dual_button_get_identity(DualButton *dual_button, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

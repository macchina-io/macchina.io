/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_MULTI_TOUCH_H
#define BRICKLET_MULTI_TOUCH_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletMultiTouch Multi Touch Bricklet
 */

/**
 * \ingroup BrickletMultiTouch
 *
 * Capacitive touch sensor for 12 electrodes
 */
typedef Device MultiTouch;

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_GET_TOUCH_STATE 1

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_RECALIBRATE 2

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_SET_ELECTRODE_CONFIG 3

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_GET_ELECTRODE_CONFIG 4

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_SET_ELECTRODE_SENSITIVITY 6

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_GET_ELECTRODE_SENSITIVITY 7

/**
 * \ingroup BrickletMultiTouch
 */
#define MULTI_TOUCH_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletMultiTouch
 *
 * Signature: \code void callback(uint16_t state, void *user_data) \endcode
 * 
 * Returns the current touch state, see {@link multi_touch_get_touch_state} for
 * information about the state.
 * 
 * This callback is triggered every time the touch state changes.
 */
#define MULTI_TOUCH_CALLBACK_TOUCH_STATE 5


/**
 * \ingroup BrickletMultiTouch
 *
 * This constant is used to identify a Multi Touch Bricklet.
 *
 * The {@link multi_touch_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define MULTI_TOUCH_DEVICE_IDENTIFIER 234

/**
 * \ingroup BrickletMultiTouch
 *
 * This constant represents the display name of a Multi Touch Bricklet.
 */
#define MULTI_TOUCH_DEVICE_DISPLAY_NAME "Multi Touch Bricklet"

/**
 * \ingroup BrickletMultiTouch
 *
 * Creates the device object \c multi_touch with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void multi_touch_create(MultiTouch *multi_touch, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletMultiTouch
 *
 * Removes the device object \c multi_touch from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void multi_touch_destroy(MultiTouch *multi_touch);

/**
 * \ingroup BrickletMultiTouch
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the multi_touch_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int multi_touch_get_response_expected(MultiTouch *multi_touch, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletMultiTouch
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
int multi_touch_set_response_expected(MultiTouch *multi_touch, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletMultiTouch
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int multi_touch_set_response_expected_all(MultiTouch *multi_touch, bool response_expected);

/**
 * \ingroup BrickletMultiTouch
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void multi_touch_register_callback(MultiTouch *multi_touch, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletMultiTouch
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int multi_touch_get_api_version(MultiTouch *multi_touch, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletMultiTouch
 *
 * Returns the current touch state. The state is given as a bitfield.
 * 
 * Bits 0 to 11 represent the 12 electrodes and bit 12 represents
 * the proximity.
 * 
 * If an electrode is touched, the corresponding bit is true. If
 * a hand or similar is in proximity to the electrodes, bit 12 is
 * *true*.
 * 
 * Example: The state 4103 = 0x1007 = 0b1000000000111 means that
 * electrodes 0, 1 and 2 are touched and that something is in the
 * proximity of the electrodes.
 * 
 * The proximity is activated with a distance of 1-2cm. An electrode
 * is already counted as touched if a finger is nearly touching the
 * electrode. This means that you can put a piece of paper or foil
 * or similar on top of a electrode to build a touch panel with
 * a professional look.
 */
int multi_touch_get_touch_state(MultiTouch *multi_touch, uint16_t *ret_state);

/**
 * \ingroup BrickletMultiTouch
 *
 * Recalibrates the electrodes. Call this function whenever you changed
 * or moved you electrodes.
 */
int multi_touch_recalibrate(MultiTouch *multi_touch);

/**
 * \ingroup BrickletMultiTouch
 *
 * Enables/disables electrodes with a bitfield (see {@link multi_touch_get_touch_state}).
 * 
 * *True* enables the electrode, *false* disables the electrode. A
 * disabled electrode will always return *false* as its state. If you
 * don't need all electrodes you can disable the electrodes that are
 * not needed.
 * 
 * It is recommended that you disable the proximity bit (bit 12) if
 * the proximity feature is not needed. This will reduce the amount of
 * traffic that is produced by the {@link MULTI_TOUCH_CALLBACK_TOUCH_STATE} callback.
 * 
 * Disabling electrodes will also reduce power consumption.
 * 
 * Default: 8191 = 0x1FFF = 0b1111111111111 (all electrodes enabled)
 */
int multi_touch_set_electrode_config(MultiTouch *multi_touch, uint16_t enabled_electrodes);

/**
 * \ingroup BrickletMultiTouch
 *
 * Returns the electrode configuration, as set by {@link multi_touch_set_electrode_config}.
 */
int multi_touch_get_electrode_config(MultiTouch *multi_touch, uint16_t *ret_enabled_electrodes);

/**
 * \ingroup BrickletMultiTouch
 *
 * Sets the sensitivity of the electrodes. An electrode with a high sensitivity
 * will register a touch earlier then an electrode with a low sensitivity.
 * 
 * If you build a big electrode you might need to decrease the sensitivity, since
 * the area that can be charged will get bigger. If you want to be able to
 * activate an electrode from further away you need to increase the sensitivity.
 * 
 * After a new sensitivity is set, you likely want to call {@link multi_touch_recalibrate}
 * to calibrate the electrodes with the newly defined sensitivity.
 * 
 * The valid sensitivity value range is 5-201.
 * 
 * The default sensitivity value is 181.
 */
int multi_touch_set_electrode_sensitivity(MultiTouch *multi_touch, uint8_t sensitivity);

/**
 * \ingroup BrickletMultiTouch
 *
 * Returns the current sensitivity, as set by {@link multi_touch_set_electrode_sensitivity}.
 */
int multi_touch_get_electrode_sensitivity(MultiTouch *multi_touch, uint8_t *ret_sensitivity);

/**
 * \ingroup BrickletMultiTouch
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
int multi_touch_get_identity(MultiTouch *multi_touch, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_PIEZO_BUZZER_H
#define BRICKLET_PIEZO_BUZZER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletPiezoBuzzer PiezoBuzzer Bricklet
 */

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Device for controlling a piezo buzzer
 */
typedef Device PiezoBuzzer;

/**
 * \ingroup BrickletPiezoBuzzer
 */
#define PIEZO_BUZZER_FUNCTION_BEEP 1

/**
 * \ingroup BrickletPiezoBuzzer
 */
#define PIEZO_BUZZER_FUNCTION_MORSE_CODE 2

/**
 * \ingroup BrickletPiezoBuzzer
 */
#define PIEZO_BUZZER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if a beep set by {@link piezo_buzzer_beep} is finished
 */
#define PIEZO_BUZZER_CALLBACK_BEEP_FINISHED 3

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if the playback of the morse code set by
 * {@link piezo_buzzer_morse_code} is finished.
 */
#define PIEZO_BUZZER_CALLBACK_MORSE_CODE_FINISHED 4


/**
 * \ingroup BrickletPiezoBuzzer
 *
 * This constant is used to identify a PiezoBuzzer Bricklet.
 *
 * The {@link piezo_buzzer_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define PIEZO_BUZZER_DEVICE_IDENTIFIER 214

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Creates the device object \c piezo_buzzer with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void piezo_buzzer_create(PiezoBuzzer *piezo_buzzer, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Removes the device object \c piezo_buzzer from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void piezo_buzzer_destroy(PiezoBuzzer *piezo_buzzer);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the piezo_buzzer_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int piezo_buzzer_get_response_expected(PiezoBuzzer *piezo_buzzer, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletPiezoBuzzer
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
int piezo_buzzer_set_response_expected(PiezoBuzzer *piezo_buzzer, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int piezo_buzzer_set_response_expected_all(PiezoBuzzer *piezo_buzzer, bool response_expected);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void piezo_buzzer_register_callback(PiezoBuzzer *piezo_buzzer, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int piezo_buzzer_get_api_version(PiezoBuzzer *piezo_buzzer, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Beeps with the duration in ms. For example: If you set a value of 1000,
 * the piezo buzzer will beep for one second.
 */
int piezo_buzzer_beep(PiezoBuzzer *piezo_buzzer, uint32_t duration);

/**
 * \ingroup BrickletPiezoBuzzer
 *
 * Sets morse code that will be played by the piezo buzzer. The morse code
 * is given as a string consisting of "." (dot), "-" (minus) and " " (space)
 * for *dits*, *dahs* and *pauses*. Every other character is ignored.
 * 
 * For example: If you set the string "...---...", the piezo buzzer will beep
 * nine times with the durations "short short short long long long short 
 * short short".
 * 
 * The maximum string size is 60.
 */
int piezo_buzzer_morse_code(PiezoBuzzer *piezo_buzzer, const char morse[60]);

/**
 * \ingroup BrickletPiezoBuzzer
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
int piezo_buzzer_get_identity(PiezoBuzzer *piezo_buzzer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

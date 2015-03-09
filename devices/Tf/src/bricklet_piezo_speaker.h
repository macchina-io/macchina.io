/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_PIEZO_SPEAKER_H
#define BRICKLET_PIEZO_SPEAKER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletPiezoSpeaker PiezoSpeaker Bricklet
 */

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Device for controlling a piezo buzzer with configurable frequencies
 */
typedef Device PiezoSpeaker;

/**
 * \ingroup BrickletPiezoSpeaker
 */
#define PIEZO_SPEAKER_FUNCTION_BEEP 1

/**
 * \ingroup BrickletPiezoSpeaker
 */
#define PIEZO_SPEAKER_FUNCTION_MORSE_CODE 2

/**
 * \ingroup BrickletPiezoSpeaker
 */
#define PIEZO_SPEAKER_FUNCTION_CALIBRATE 3

/**
 * \ingroup BrickletPiezoSpeaker
 */
#define PIEZO_SPEAKER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if a beep set by {@link piezo_speaker_beep} is finished
 */
#define PIEZO_SPEAKER_CALLBACK_BEEP_FINISHED 4

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if the playback of the morse code set by
 * {@link piezo_speaker_morse_code} is finished.
 */
#define PIEZO_SPEAKER_CALLBACK_MORSE_CODE_FINISHED 5


/**
 * \ingroup BrickletPiezoSpeaker
 */
#define PIEZO_SPEAKER_BEEP_DURATION_OFF 0

/**
 * \ingroup BrickletPiezoSpeaker
 */
#define PIEZO_SPEAKER_BEEP_DURATION_INFINITE 4294967295

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * This constant is used to identify a PiezoSpeaker Bricklet.
 *
 * The {@link piezo_speaker_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define PIEZO_SPEAKER_DEVICE_IDENTIFIER 242

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Creates the device object \c piezo_speaker with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void piezo_speaker_create(PiezoSpeaker *piezo_speaker, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Removes the device object \c piezo_speaker from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void piezo_speaker_destroy(PiezoSpeaker *piezo_speaker);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the piezo_speaker_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int piezo_speaker_get_response_expected(PiezoSpeaker *piezo_speaker, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletPiezoSpeaker
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
int piezo_speaker_set_response_expected(PiezoSpeaker *piezo_speaker, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int piezo_speaker_set_response_expected_all(PiezoSpeaker *piezo_speaker, bool response_expected);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void piezo_speaker_register_callback(PiezoSpeaker *piezo_speaker, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int piezo_speaker_get_api_version(PiezoSpeaker *piezo_speaker, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Beeps with the given frequency for the duration in ms. For example: 
 * If you set a duration of 1000, with a frequency value of 2000
 * the piezo buzzer will beep for one second with a frequency of
 * approximately 2 kHz.
 * 
 * .. versionchanged:: 2.0.2~(Plugin)
 *    A duration of 0 stops the current beep if any, the frequency parameter is
 *    ignored. A duration of 4294967295 results in an infinite beep.
 * 
 * The *frequency* parameter can be set between 585 and 7100.
 * 
 * The Piezo Speaker Bricklet can only approximate the frequency, it will play
 * the best possible match by applying the calibration (see {@link piezo_speaker_calibrate}).
 */
int piezo_speaker_beep(PiezoSpeaker *piezo_speaker, uint32_t duration, uint16_t frequency);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * Sets morse code that will be played by the piezo buzzer. The morse code
 * is given as a string consisting of "." (dot), "-" (minus) and " " (space)
 * for *dits*, *dahs* and *pauses*. Every other character is ignored.
 * The second parameter is the frequency (see {@link piezo_speaker_beep}).
 * 
 * For example: If you set the string "...---...", the piezo buzzer will beep
 * nine times with the durations "short short short long long long short 
 * short short".
 * 
 * The maximum string size is 60.
 */
int piezo_speaker_morse_code(PiezoSpeaker *piezo_speaker, const char morse[60], uint16_t frequency);

/**
 * \ingroup BrickletPiezoSpeaker
 *
 * The Piezo Speaker Bricklet can play 512 different tones. This function
 * plays each tone and measures the exact frequency back. The result is a
 * mapping between setting value and frequency. This mapping is stored
 * in the EEPROM and loaded on startup.
 * 
 * The Bricklet should come calibrated, you only need to call this
 * function (once) every time you reflash the Bricklet plugin.
 * 
 * Returns *true* after the calibration finishes.
 */
int piezo_speaker_calibrate(PiezoSpeaker *piezo_speaker, bool *ret_calibration);

/**
 * \ingroup BrickletPiezoSpeaker
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
int piezo_speaker_get_identity(PiezoSpeaker *piezo_speaker, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

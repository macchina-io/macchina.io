/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_SOUND_INTENSITY_H
#define BRICKLET_SOUND_INTENSITY_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletSoundIntensity SoundIntensity Bricklet
 */

/**
 * \ingroup BrickletSoundIntensity
 *
 * Device for sensing sound intensity
 */
typedef Device SoundIntensity;

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_GET_INTENSITY 1

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_SET_INTENSITY_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_GET_INTENSITY_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_SET_INTENSITY_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_GET_INTENSITY_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletSoundIntensity
 *
 * Signature: \code void callback(uint16_t intensity, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link sound_intensity_set_intensity_callback_period}. The parameter is the intensity of
 * the encoder.
 * 
 * {@link SOUND_INTENSITY_CALLBACK_INTENSITY} is only triggered if the intensity has changed since the
 * last triggering.
 */
#define SOUND_INTENSITY_CALLBACK_INTENSITY 8

/**
 * \ingroup BrickletSoundIntensity
 *
 * Signature: \code void callback(uint16_t intensity, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link sound_intensity_set_intensity_callback_threshold} is reached.
 * The parameter is the intensity of the encoder.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link sound_intensity_set_debounce_period}.
 */
#define SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED 9


/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletSoundIntensity
 */
#define SOUND_INTENSITY_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletSoundIntensity
 *
 * This constant is used to identify a SoundIntensity Bricklet.
 *
 * The {@link sound_intensity_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define SOUND_INTENSITY_DEVICE_IDENTIFIER 238

/**
 * \ingroup BrickletSoundIntensity
 *
 * Creates the device object \c sound_intensity with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void sound_intensity_create(SoundIntensity *sound_intensity, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Removes the device object \c sound_intensity from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void sound_intensity_destroy(SoundIntensity *sound_intensity);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the sound_intensity_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int sound_intensity_get_response_expected(SoundIntensity *sound_intensity, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletSoundIntensity
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
int sound_intensity_set_response_expected(SoundIntensity *sound_intensity, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int sound_intensity_set_response_expected_all(SoundIntensity *sound_intensity, bool response_expected);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void sound_intensity_register_callback(SoundIntensity *sound_intensity, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int sound_intensity_get_api_version(SoundIntensity *sound_intensity, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Returns the current sound intensity. The value has a range of
 * 0 to 4095.
 * 
 * The value corresponds to the `upper envelop <http://en.wikipedia.org/wiki/Envelope_(waves)>`__
 * of the signal of the microphone capsule.
 * 
 * If you want to get the intensity periodically, it is recommended to use the
 * callback {@link SOUND_INTENSITY_CALLBACK_INTENSITY} and set the period with 
 * {@link sound_intensity_set_intensity_callback_period}.
 */
int sound_intensity_get_intensity(SoundIntensity *sound_intensity, uint16_t *ret_intensity);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Sets the period in ms with which the {@link SOUND_INTENSITY_CALLBACK_INTENSITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link SOUND_INTENSITY_CALLBACK_INTENSITY} is only triggered if the intensity has changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int sound_intensity_set_intensity_callback_period(SoundIntensity *sound_intensity, uint32_t period);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Returns the period as set by {@link sound_intensity_set_intensity_callback_period}.
 */
int sound_intensity_get_intensity_callback_period(SoundIntensity *sound_intensity, uint32_t *ret_period);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Sets the thresholds for the {@link SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED} callback. 
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the intensity is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the intensity is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the intensity is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the intensity is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * The default value is ('x', 0, 0).
 */
int sound_intensity_set_intensity_callback_threshold(SoundIntensity *sound_intensity, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Returns the threshold as set by {@link sound_intensity_set_intensity_callback_threshold}.
 */
int sound_intensity_get_intensity_callback_threshold(SoundIntensity *sound_intensity, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Sets the period in ms with which the threshold callback
 * 
 * * {@link SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED}
 * 
 * is triggered, if the thresholds
 * 
 * * {@link sound_intensity_set_intensity_callback_threshold}
 * 
 * keeps being reached.
 * 
 * The default value is 100.
 */
int sound_intensity_set_debounce_period(SoundIntensity *sound_intensity, uint32_t debounce);

/**
 * \ingroup BrickletSoundIntensity
 *
 * Returns the debounce period as set by {@link sound_intensity_set_debounce_period}.
 */
int sound_intensity_get_debounce_period(SoundIntensity *sound_intensity, uint32_t *ret_debounce);

/**
 * \ingroup BrickletSoundIntensity
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
int sound_intensity_get_identity(SoundIntensity *sound_intensity, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

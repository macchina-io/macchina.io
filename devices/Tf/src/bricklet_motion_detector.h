/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_MOTION_DETECTOR_H
#define BRICKLET_MOTION_DETECTOR_H

#include "ip_connection.h"

/**
 * \defgroup BrickletMotionDetector MotionDetector Bricklet
 */

/**
 * \ingroup BrickletMotionDetector
 *
 * Device that reads out PIR motion detector
 */
typedef Device MotionDetector;

/**
 * \ingroup BrickletMotionDetector
 */
#define MOTION_DETECTOR_FUNCTION_GET_MOTION_DETECTED 1

/**
 * \ingroup BrickletMotionDetector
 */
#define MOTION_DETECTOR_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletMotionDetector
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is called after a motion was detected.
 */
#define MOTION_DETECTOR_CALLBACK_MOTION_DETECTED 2

/**
 * \ingroup BrickletMotionDetector
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is called when the detection cycle ended. When this
 * callback is called, a new motion can be detected again after approximately 2
 * seconds.
 */
#define MOTION_DETECTOR_CALLBACK_DETECTION_CYCLE_ENDED 3


/**
 * \ingroup BrickletMotionDetector
 */
#define MOTION_DETECTOR_MOTION_NOT_DETECTED 0

/**
 * \ingroup BrickletMotionDetector
 */
#define MOTION_DETECTOR_MOTION_DETECTED 1

/**
 * \ingroup BrickletMotionDetector
 *
 * This constant is used to identify a MotionDetector Bricklet.
 *
 * The {@link motion_detector_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define MOTION_DETECTOR_DEVICE_IDENTIFIER 233

/**
 * \ingroup BrickletMotionDetector
 *
 * Creates the device object \c motion_detector with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void motion_detector_create(MotionDetector *motion_detector, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletMotionDetector
 *
 * Removes the device object \c motion_detector from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void motion_detector_destroy(MotionDetector *motion_detector);

/**
 * \ingroup BrickletMotionDetector
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the motion_detector_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int motion_detector_get_response_expected(MotionDetector *motion_detector, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletMotionDetector
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
int motion_detector_set_response_expected(MotionDetector *motion_detector, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletMotionDetector
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int motion_detector_set_response_expected_all(MotionDetector *motion_detector, bool response_expected);

/**
 * \ingroup BrickletMotionDetector
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void motion_detector_register_callback(MotionDetector *motion_detector, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletMotionDetector
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int motion_detector_get_api_version(MotionDetector *motion_detector, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletMotionDetector
 *
 * Returns 1 if a motion was detected. How long this returns 1 after a motion
 * was detected can be adjusted with one of the small potentiometers on the
 * Motion Detector Bricklet, see :ref:`here
 * <motion_detector_bricklet_sensitivity_delay_block_time>`.
 * 
 * There is also a blue LED on the Bricklet that is on as long as the Bricklet is
 * in the "motion detected" state.
 */
int motion_detector_get_motion_detected(MotionDetector *motion_detector, uint8_t *ret_motion);

/**
 * \ingroup BrickletMotionDetector
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
int motion_detector_get_identity(MotionDetector *motion_detector, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

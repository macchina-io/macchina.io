/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_SEGMENT_DISPLAY_4X7_H
#define BRICKLET_SEGMENT_DISPLAY_4X7_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletSegmentDisplay4x7 Segment Display 4x7 Bricklet
 */

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Four 7-segment displays with switchable colon
 */
typedef Device SegmentDisplay4x7;

/**
 * \ingroup BrickletSegmentDisplay4x7
 */
#define SEGMENT_DISPLAY_4X7_FUNCTION_SET_SEGMENTS 1

/**
 * \ingroup BrickletSegmentDisplay4x7
 */
#define SEGMENT_DISPLAY_4X7_FUNCTION_GET_SEGMENTS 2

/**
 * \ingroup BrickletSegmentDisplay4x7
 */
#define SEGMENT_DISPLAY_4X7_FUNCTION_START_COUNTER 3

/**
 * \ingroup BrickletSegmentDisplay4x7
 */
#define SEGMENT_DISPLAY_4X7_FUNCTION_GET_COUNTER_VALUE 4

/**
 * \ingroup BrickletSegmentDisplay4x7
 */
#define SEGMENT_DISPLAY_4X7_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered when the counter (see {@link segment_display_4x7_start_counter}) is
 * finished.
 */
#define SEGMENT_DISPLAY_4X7_CALLBACK_COUNTER_FINISHED 5


/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * This constant is used to identify a Segment Display 4x7 Bricklet.
 *
 * The {@link segment_display_4x7_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define SEGMENT_DISPLAY_4X7_DEVICE_IDENTIFIER 237

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * This constant represents the display name of a Segment Display 4x7 Bricklet.
 */
#define SEGMENT_DISPLAY_4X7_DEVICE_DISPLAY_NAME "Segment Display 4x7 Bricklet"

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Creates the device object \c segment_display_4x7 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void segment_display_4x7_create(SegmentDisplay4x7 *segment_display_4x7, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Removes the device object \c segment_display_4x7 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void segment_display_4x7_destroy(SegmentDisplay4x7 *segment_display_4x7);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the segment_display_4x7_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int segment_display_4x7_get_response_expected(SegmentDisplay4x7 *segment_display_4x7, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletSegmentDisplay4x7
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
int segment_display_4x7_set_response_expected(SegmentDisplay4x7 *segment_display_4x7, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int segment_display_4x7_set_response_expected_all(SegmentDisplay4x7 *segment_display_4x7, bool response_expected);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void segment_display_4x7_register_callback(SegmentDisplay4x7 *segment_display_4x7, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int segment_display_4x7_get_api_version(SegmentDisplay4x7 *segment_display_4x7, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * The 7-segment display can be set with bitmaps. Every bit controls one
 * segment:
 * 
 * .. image:: /Images/Bricklets/bricklet_segment_display_4x7_bit_order.png
 *    :scale: 100 %
 *    :alt: Bit order of one segment
 *    :align: center
 * 
 * For example to set a "5" you would want to activate segments 0, 2, 3, 5 and 6.
 * This is represented by the number 0b01101101 = 0x6d = 109.
 * 
 * The brightness can be set between 0 (dark) and 7 (bright). The colon
 * parameter turns the colon of the display on or off.
 */
int segment_display_4x7_set_segments(SegmentDisplay4x7 *segment_display_4x7, uint8_t segments[4], uint8_t brightness, bool colon);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Returns the segment, brightness and color data as set by 
 * {@link segment_display_4x7_set_segments}.
 */
int segment_display_4x7_get_segments(SegmentDisplay4x7 *segment_display_4x7, uint8_t ret_segments[4], uint8_t *ret_brightness, bool *ret_colon);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Starts a counter with the *from* value that counts to the *to*
 * value with the each step incremented by *increment*.
 * The *length* of the increment is given in ms.
 * 
 * Example: If you set *from* to 0, *to* to 100, *increment* to 1 and
 * *length* to 1000, a counter that goes from 0 to 100 with one second
 * pause between each increment will be started.
 * 
 * The maximum values for *from*, *to* and *increment* is 9999, 
 * the minimum value is -999.
 * 
 * Using a negative increment allows to count backwards.
 * 
 * You can stop the counter at every time by calling {@link segment_display_4x7_set_segments}.
 */
int segment_display_4x7_start_counter(SegmentDisplay4x7 *segment_display_4x7, int16_t value_from, int16_t value_to, int16_t increment, uint32_t length);

/**
 * \ingroup BrickletSegmentDisplay4x7
 *
 * Returns the counter value that is currently shown on the display.
 * 
 * If there is no counter running a 0 will be returned.
 */
int segment_display_4x7_get_counter_value(SegmentDisplay4x7 *segment_display_4x7, uint16_t *ret_value);

/**
 * \ingroup BrickletSegmentDisplay4x7
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
int segment_display_4x7_get_identity(SegmentDisplay4x7 *segment_display_4x7, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_OLED_128X64_H
#define BRICKLET_OLED_128X64_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletOLED128x64 OLED 128x64 Bricklet
 */

/**
 * \ingroup BrickletOLED128x64
 *
 * 3.3cm (1.3") OLED with 128x64 pixels
 */
typedef Device OLED128x64;

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_WRITE 1

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_NEW_WINDOW 2

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_CLEAR_DISPLAY 3

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION 4

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION 5

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_WRITE_LINE 6

/**
 * \ingroup BrickletOLED128x64
 */
#define OLED_128X64_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletOLED128x64
 *
 * This constant is used to identify a OLED 128x64 Bricklet.
 *
 * The {@link oled_128x64_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define OLED_128X64_DEVICE_IDENTIFIER 263

/**
 * \ingroup BrickletOLED128x64
 *
 * This constant represents the display name of a OLED 128x64 Bricklet.
 */
#define OLED_128X64_DEVICE_DISPLAY_NAME "OLED 128x64 Bricklet"

/**
 * \ingroup BrickletOLED128x64
 *
 * Creates the device object \c oled_128x64 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void oled_128x64_create(OLED128x64 *oled_128x64, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletOLED128x64
 *
 * Removes the device object \c oled_128x64 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void oled_128x64_destroy(OLED128x64 *oled_128x64);

/**
 * \ingroup BrickletOLED128x64
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the oled_128x64_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int oled_128x64_get_response_expected(OLED128x64 *oled_128x64, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletOLED128x64
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
int oled_128x64_set_response_expected(OLED128x64 *oled_128x64, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletOLED128x64
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int oled_128x64_set_response_expected_all(OLED128x64 *oled_128x64, bool response_expected);


/**
 * \ingroup BrickletOLED128x64
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int oled_128x64_get_api_version(OLED128x64 *oled_128x64, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletOLED128x64
 *
 * Appends 64 byte of data to the window as set by {@link oled_128x64_new_window}.
 * 
 * Each row has a height of 8 pixels which corresponds to one byte of data.
 * 
 * Example: if you call {@link oled_128x64_new_window} with column from 0 to 127 and row
 * from 0 to 7 (the whole display) each call of {@link oled_128x64_write} (red arrow) will
 * write half of a row.
 * 
 * .. image:: /Images/Bricklets/bricklet_oled_128x64_display.png
 *    :scale: 100 %
 *    :alt: Display pixel order
 *    :align: center
 *    :target: ../../_images/Bricklets/bricklet_oled_128x64_display.png
 * 
 * The LSB (D0) of each data byte is at the top and the MSB (D7) is at the 
 * bottom of the row.
 * 
 * The next call of {@link oled_128x64_write} will write the second half of the row
 * and the next two the second row and so on. To fill the whole display 
 * you need to call {@link oled_128x64_write} 16 times.
 */
int oled_128x64_write(OLED128x64 *oled_128x64, uint8_t data[64]);

/**
 * \ingroup BrickletOLED128x64
 *
 * Sets the window in which you can write with {@link oled_128x64_write}. One row
 * has a height of 8 pixels.
 * 
 * The columns have a range of 0 to 127 and the rows have a range of 0 to 7.
 */
int oled_128x64_new_window(OLED128x64 *oled_128x64, uint8_t column_from, uint8_t column_to, uint8_t row_from, uint8_t row_to);

/**
 * \ingroup BrickletOLED128x64
 *
 * Clears the current content of the window as set by {@link oled_128x64_new_window}.
 */
int oled_128x64_clear_display(OLED128x64 *oled_128x64);

/**
 * \ingroup BrickletOLED128x64
 *
 * Sets the configuration of the display.
 * 
 * You can set a contrast value from 0 to 255 and you can invert the color
 * (black/white) of the display.
 * 
 * The default values are contrast 143 and inverting off.
 */
int oled_128x64_set_display_configuration(OLED128x64 *oled_128x64, uint8_t contrast, bool invert);

/**
 * \ingroup BrickletOLED128x64
 *
 * Returns the configuration as set by {@link oled_128x64_set_display_configuration}.
 */
int oled_128x64_get_display_configuration(OLED128x64 *oled_128x64, uint8_t *ret_contrast, bool *ret_invert);

/**
 * \ingroup BrickletOLED128x64
 *
 * Writes text to a specific line (0 to 7) with a specific position 
 * (0 to 25). The text can have a maximum of 26 characters.
 * 
 * For example: (1, 10, "Hello") will write *Hello* in the middle of the
 * second line of the display.
 * 
 * You can draw to the display with {@link oled_128x64_write} and then add text to it
 * afterwards.
 * 
 * The display uses a special 5x7 pixel charset. You can view the characters 
 * of the charset in Brick Viewer.
 */
int oled_128x64_write_line(OLED128x64 *oled_128x64, uint8_t line, uint8_t position, const char text[26]);

/**
 * \ingroup BrickletOLED128x64
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
int oled_128x64_get_identity(OLED128x64 *oled_128x64, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

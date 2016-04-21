/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_OLED_64X48_H
#define BRICKLET_OLED_64X48_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletOLED64x48 OLED 64x48 Bricklet
 */

/**
 * \ingroup BrickletOLED64x48
 *
 * 1.68cm (0.66") OLED with 64x48 pixels
 */
typedef Device OLED64x48;

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_WRITE 1

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_NEW_WINDOW 2

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_CLEAR_DISPLAY 3

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_SET_DISPLAY_CONFIGURATION 4

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_GET_DISPLAY_CONFIGURATION 5

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_WRITE_LINE 6

/**
 * \ingroup BrickletOLED64x48
 */
#define OLED_64X48_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletOLED64x48
 *
 * This constant is used to identify a OLED 64x48 Bricklet.
 *
 * The {@link oled_64x48_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define OLED_64X48_DEVICE_IDENTIFIER 264

/**
 * \ingroup BrickletOLED64x48
 *
 * This constant represents the display name of a OLED 64x48 Bricklet.
 */
#define OLED_64X48_DEVICE_DISPLAY_NAME "OLED 64x48 Bricklet"

/**
 * \ingroup BrickletOLED64x48
 *
 * Creates the device object \c oled_64x48 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void oled_64x48_create(OLED64x48 *oled_64x48, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletOLED64x48
 *
 * Removes the device object \c oled_64x48 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void oled_64x48_destroy(OLED64x48 *oled_64x48);

/**
 * \ingroup BrickletOLED64x48
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the oled_64x48_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int oled_64x48_get_response_expected(OLED64x48 *oled_64x48, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletOLED64x48
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
int oled_64x48_set_response_expected(OLED64x48 *oled_64x48, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletOLED64x48
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int oled_64x48_set_response_expected_all(OLED64x48 *oled_64x48, bool response_expected);


/**
 * \ingroup BrickletOLED64x48
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int oled_64x48_get_api_version(OLED64x48 *oled_64x48, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletOLED64x48
 *
 * Appends 64 byte of data to the window as set by {@link oled_64x48_new_window}.
 * 
 * Each row has a height of 8 pixels which corresponds to one byte of data.
 * 
 * Example: if you call {@link oled_64x48_new_window} with column from 0 to 63 and row
 * from 0 to 5 (the whole display) each call of {@link oled_64x48_write} (red arrow) will
 * write one row.
 * 
 * .. image:: /Images/Bricklets/bricklet_oled_64x48_display.png
 *    :scale: 100 %
 *    :alt: Display pixel order
 *    :align: center
 *    :target: ../../_images/Bricklets/bricklet_oled_64x48_display.png
 * 
 * The LSB (D0) of each data byte is at the top and the MSB (D7) is at the 
 * bottom of the row.
 * 
 * The next call of {@link oled_64x48_write} will write the second row and so on. To
 * fill the whole display you need to call {@link oled_64x48_write} 6 times.
 */
int oled_64x48_write(OLED64x48 *oled_64x48, uint8_t data[64]);

/**
 * \ingroup BrickletOLED64x48
 *
 * Sets the window in which you can write with {@link oled_64x48_write}. One row
 * has a height of 8 pixels.
 * 
 * The columns have a range of 0 to 63 and the rows have a range of 0 to 5.
 */
int oled_64x48_new_window(OLED64x48 *oled_64x48, uint8_t column_from, uint8_t column_to, uint8_t row_from, uint8_t row_to);

/**
 * \ingroup BrickletOLED64x48
 *
 * Clears the current content of the window as set by {@link oled_64x48_new_window}.
 */
int oled_64x48_clear_display(OLED64x48 *oled_64x48);

/**
 * \ingroup BrickletOLED64x48
 *
 * Sets the configuration of the display.
 * 
 * You can set a contrast value from 0 to 255 and you can invert the color
 * (black/white) of the display.
 * 
 * The default values are contrast 143 and inverting off.
 */
int oled_64x48_set_display_configuration(OLED64x48 *oled_64x48, uint8_t contrast, bool invert);

/**
 * \ingroup BrickletOLED64x48
 *
 * Returns the configuration as set by {@link oled_64x48_set_display_configuration}.
 */
int oled_64x48_get_display_configuration(OLED64x48 *oled_64x48, uint8_t *ret_contrast, bool *ret_invert);

/**
 * \ingroup BrickletOLED64x48
 *
 * Writes text to a specific line (0 to 5) with a specific position 
 * (0 to 12). The text can have a maximum of 13 characters.
 * 
 * For example: (1, 4, "Hello") will write *Hello* in the middle of the
 * second line of the display.
 * 
 * You can draw to the display with {@link oled_64x48_write} and then add text to it
 * afterwards.
 * 
 * The display uses a special 5x7 pixel charset. You can view the characters 
 * of the charset in Brick Viewer.
 */
int oled_64x48_write_line(OLED64x48 *oled_64x48, uint8_t line, uint8_t position, const char text[13]);

/**
 * \ingroup BrickletOLED64x48
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
int oled_64x48_get_identity(OLED64x48 *oled_64x48, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

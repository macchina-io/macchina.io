/* ***********************************************************
 * This file was automatically generated on 2013-12-19.      *
 *                                                           *
 * Bindings Version 2.0.13                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_LCD_16X2_H
#define BRICKLET_LCD_16X2_H

#include "ip_connection.h"

/**
 * \defgroup BrickletLCD16x2 LCD16x2 Bricklet
 */

/**
 * \ingroup BrickletLCD16x2
 *
 * Device for controlling a LCD with 2 lines a 16 characters
 */
typedef Device LCD16x2;

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_WRITE_LINE 1

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_CLEAR_DISPLAY 2

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_BACKLIGHT_ON 3

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_BACKLIGHT_OFF 4

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_IS_BACKLIGHT_ON 5

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_SET_CONFIG 6

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_GET_CONFIG 7

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_IS_BUTTON_PRESSED 8

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_SET_CUSTOM_CHARACTER 11

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_GET_CUSTOM_CHARACTER 12

/**
 * \ingroup BrickletLCD16x2
 */
#define LCD_16X2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletLCD16x2
 *
 * Signature: \code void callback(uint8_t button, void *user_data) \endcode
 * 
 * This callback is triggered when a button is pressed. The parameter is
 * the number of the button (0 to 2).
 */
#define LCD_16X2_CALLBACK_BUTTON_PRESSED 9

/**
 * \ingroup BrickletLCD16x2
 *
 * Signature: \code void callback(uint8_t button, void *user_data) \endcode
 * 
 * This callback is triggered when a button is released. The parameter is
 * the number of the button (0 to 2).
 */
#define LCD_16X2_CALLBACK_BUTTON_RELEASED 10


/**
 * \ingroup BrickletLCD16x2
 *
 * This constant is used to identify a LCD16x2 Bricklet.
 *
 * The {@link lcd_16x2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define LCD_16X2_DEVICE_IDENTIFIER 211

/**
 * \ingroup BrickletLCD16x2
 *
 * Creates the device object \c lcd_16x2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void lcd_16x2_create(LCD16x2 *lcd_16x2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletLCD16x2
 *
 * Removes the device object \c lcd_16x2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void lcd_16x2_destroy(LCD16x2 *lcd_16x2);

/**
 * \ingroup BrickletLCD16x2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the lcd_16x2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int lcd_16x2_get_response_expected(LCD16x2 *lcd_16x2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletLCD16x2
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
int lcd_16x2_set_response_expected(LCD16x2 *lcd_16x2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletLCD16x2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int lcd_16x2_set_response_expected_all(LCD16x2 *lcd_16x2, bool response_expected);

/**
 * \ingroup BrickletLCD16x2
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void lcd_16x2_register_callback(LCD16x2 *lcd_16x2, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletLCD16x2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int lcd_16x2_get_api_version(LCD16x2 *lcd_16x2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletLCD16x2
 *
 * Writes text to a specific line (0 to 1) with a specific position 
 * (0 to 15). The text can have a maximum of 16 characters.
 * 
 * For example: (0, 5, "Hello") will write *Hello* in the middle of the
 * first line of the display.
 * 
 * The display uses a special charset that includes all ASCII characters except
 * backslash and tilde. The LCD charset also includes several other non-ASCII characters, see
 * the `charset specification <https://github.com/Tinkerforge/lcd-16x2-bricklet/raw/master/datasheets/standard_charset.pdf>`__
 * for details. The Unicode example above shows how to specify non-ASCII characters
 * and how to translate from Unicode to the LCD charset.
 */
int lcd_16x2_write_line(LCD16x2 *lcd_16x2, uint8_t line, uint8_t position, const char text[16]);

/**
 * \ingroup BrickletLCD16x2
 *
 * Deletes all characters from the display.
 */
int lcd_16x2_clear_display(LCD16x2 *lcd_16x2);

/**
 * \ingroup BrickletLCD16x2
 *
 * Turns the backlight on.
 */
int lcd_16x2_backlight_on(LCD16x2 *lcd_16x2);

/**
 * \ingroup BrickletLCD16x2
 *
 * Turns the backlight off.
 */
int lcd_16x2_backlight_off(LCD16x2 *lcd_16x2);

/**
 * \ingroup BrickletLCD16x2
 *
 * Returns *true* if the backlight is on and *false* otherwise.
 */
int lcd_16x2_is_backlight_on(LCD16x2 *lcd_16x2, bool *ret_backlight);

/**
 * \ingroup BrickletLCD16x2
 *
 * Configures if the cursor (shown as "_") should be visible and if it
 * should be blinking (shown as a blinking block). The cursor position
 * is one character behind the the last text written with 
 * {@link lcd_16x2_write_line}.
 * 
 * The default is (false, false).
 */
int lcd_16x2_set_config(LCD16x2 *lcd_16x2, bool cursor, bool blinking);

/**
 * \ingroup BrickletLCD16x2
 *
 * Returns the configuration as set by {@link lcd_16x2_set_config}.
 */
int lcd_16x2_get_config(LCD16x2 *lcd_16x2, bool *ret_cursor, bool *ret_blinking);

/**
 * \ingroup BrickletLCD16x2
 *
 * Returns *true* if the button (0 to 2) is pressed. If you want to react
 * on button presses and releases it is recommended to use the
 * {@link LCD_16X2_CALLBACK_BUTTON_PRESSED} and {@link LCD_16X2_CALLBACK_BUTTON_RELEASED} callbacks.
 */
int lcd_16x2_is_button_pressed(LCD16x2 *lcd_16x2, uint8_t button, bool *ret_pressed);

/**
 * \ingroup BrickletLCD16x2
 *
 * The LCD 16x2 Bricklet can store up to 8 custom characters. The characters
 * consist of 5x8 pixels and can be addressed with the index 0-7. To describe
 * the pixels, the first 5 bits of 8 bytes are used. For example, to make
 * a custom character "H", you should transfer the following:
 * 
 * * ``character[0] = 0b00010001`` (decimal value 17)
 * * ``character[1] = 0b00010001`` (decimal value 17)
 * * ``character[2] = 0b00010001`` (decimal value 17)
 * * ``character[3] = 0b00011111`` (decimal value 31)
 * * ``character[4] = 0b00010001`` (decimal value 17)
 * * ``character[5] = 0b00010001`` (decimal value 17)
 * * ``character[6] = 0b00010001`` (decimal value 17)
 * * ``character[7] = 0b00000000`` (decimal value 0)
 * 
 * The characters can later be written with {@link lcd_16x2_write_line} by using the
 * characters with the byte representation 8 to 15.
 * 
 * You can play around with the custom characters in Brick Viewer since
 * version 2.0.1.
 * 
 * Custom characters are stored by the LCD in RAM, so they have to be set
 * after each startup.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int lcd_16x2_set_custom_character(LCD16x2 *lcd_16x2, uint8_t index, uint8_t character[8]);

/**
 * \ingroup BrickletLCD16x2
 *
 * Returns the custom character for a given index, as set with
 * {@link lcd_16x2_set_custom_character}.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int lcd_16x2_get_custom_character(LCD16x2 *lcd_16x2, uint8_t index, uint8_t ret_character[8]);

/**
 * \ingroup BrickletLCD16x2
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
int lcd_16x2_get_identity(LCD16x2 *lcd_16x2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#endif

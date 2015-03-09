/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_LCD_20X4_H
#define BRICKLET_LCD_20X4_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletLCD20x4 LCD20x4 Bricklet
 */

/**
 * \ingroup BrickletLCD20x4
 *
 * Device for controlling a LCD with 4 lines a 20 characters
 */
typedef Device LCD20x4;

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_WRITE_LINE 1

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_CLEAR_DISPLAY 2

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_BACKLIGHT_ON 3

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_BACKLIGHT_OFF 4

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_IS_BACKLIGHT_ON 5

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_SET_CONFIG 6

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_GET_CONFIG 7

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_IS_BUTTON_PRESSED 8

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_SET_CUSTOM_CHARACTER 11

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_GET_CUSTOM_CHARACTER 12

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_SET_DEFAULT_TEXT 13

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_GET_DEFAULT_TEXT 14

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_SET_DEFAULT_TEXT_COUNTER 15

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_GET_DEFAULT_TEXT_COUNTER 16

/**
 * \ingroup BrickletLCD20x4
 */
#define LCD_20X4_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletLCD20x4
 *
 * Signature: \code void callback(uint8_t button, void *user_data) \endcode
 * 
 * This callback is triggered when a button is pressed. The parameter is
 * the number of the button (0 to 2 or 0 to 3 since hardware version 1.2).
 */
#define LCD_20X4_CALLBACK_BUTTON_PRESSED 9

/**
 * \ingroup BrickletLCD20x4
 *
 * Signature: \code void callback(uint8_t button, void *user_data) \endcode
 * 
 * This callback is triggered when a button is released. The parameter is
 * the number of the button (0 to 2 or 0 to 3 since hardware version 1.2).
 */
#define LCD_20X4_CALLBACK_BUTTON_RELEASED 10


/**
 * \ingroup BrickletLCD20x4
 *
 * This constant is used to identify a LCD20x4 Bricklet.
 *
 * The {@link lcd_20x4_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define LCD_20X4_DEVICE_IDENTIFIER 212

/**
 * \ingroup BrickletLCD20x4
 *
 * Creates the device object \c lcd_20x4 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void lcd_20x4_create(LCD20x4 *lcd_20x4, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletLCD20x4
 *
 * Removes the device object \c lcd_20x4 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void lcd_20x4_destroy(LCD20x4 *lcd_20x4);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the lcd_20x4_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int lcd_20x4_get_response_expected(LCD20x4 *lcd_20x4, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletLCD20x4
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
int lcd_20x4_set_response_expected(LCD20x4 *lcd_20x4, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletLCD20x4
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int lcd_20x4_set_response_expected_all(LCD20x4 *lcd_20x4, bool response_expected);

/**
 * \ingroup BrickletLCD20x4
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void lcd_20x4_register_callback(LCD20x4 *lcd_20x4, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int lcd_20x4_get_api_version(LCD20x4 *lcd_20x4, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletLCD20x4
 *
 * Writes text to a specific line (0 to 3) with a specific position 
 * (0 to 19). The text can have a maximum of 20 characters.
 * 
 * For example: (0, 7, "Hello") will write *Hello* in the middle of the
 * first line of the display.
 * 
 * The display uses a special charset that includes all ASCII characters except
 * backslash and tilde. The LCD charset also includes several other non-ASCII characters, see
 * the `charset specification <https://github.com/Tinkerforge/lcd-20x4-bricklet/raw/master/datasheets/standard_charset.pdf>`__
 * for details. The Unicode example above shows how to specify non-ASCII characters
 * and how to translate from Unicode to the LCD charset.
 */
int lcd_20x4_write_line(LCD20x4 *lcd_20x4, uint8_t line, uint8_t position, const char text[20]);

/**
 * \ingroup BrickletLCD20x4
 *
 * Deletes all characters from the display.
 */
int lcd_20x4_clear_display(LCD20x4 *lcd_20x4);

/**
 * \ingroup BrickletLCD20x4
 *
 * Turns the backlight on.
 */
int lcd_20x4_backlight_on(LCD20x4 *lcd_20x4);

/**
 * \ingroup BrickletLCD20x4
 *
 * Turns the backlight off.
 */
int lcd_20x4_backlight_off(LCD20x4 *lcd_20x4);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns *true* if the backlight is on and *false* otherwise.
 */
int lcd_20x4_is_backlight_on(LCD20x4 *lcd_20x4, bool *ret_backlight);

/**
 * \ingroup BrickletLCD20x4
 *
 * Configures if the cursor (shown as "_") should be visible and if it
 * should be blinking (shown as a blinking block). The cursor position
 * is one character behind the the last text written with 
 * {@link lcd_20x4_write_line}.
 * 
 * The default is (*false*, *false*).
 */
int lcd_20x4_set_config(LCD20x4 *lcd_20x4, bool cursor, bool blinking);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns the configuration as set by {@link lcd_20x4_set_config}.
 */
int lcd_20x4_get_config(LCD20x4 *lcd_20x4, bool *ret_cursor, bool *ret_blinking);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns *true* if the button (0 to 2 or 0 to 3 since hardware version 1.2)
 * is pressed. If you want to react
 * on button presses and releases it is recommended to use the
 * {@link LCD_20X4_CALLBACK_BUTTON_PRESSED} and {@link LCD_20X4_CALLBACK_BUTTON_RELEASED} callbacks.
 */
int lcd_20x4_is_button_pressed(LCD20x4 *lcd_20x4, uint8_t button, bool *ret_pressed);

/**
 * \ingroup BrickletLCD20x4
 *
 * The LCD 20x4 Bricklet can store up to 8 custom characters. The characters
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
 * The characters can later be written with {@link lcd_20x4_write_line} by using the
 * characters with the byte representation 8 ("\x08") to 15 ("\x0F").
 * 
 * You can play around with the custom characters in Brick Viewer version
 * since 2.0.1.
 * 
 * Custom characters are stored by the LCD in RAM, so they have to be set
 * after each startup.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int lcd_20x4_set_custom_character(LCD20x4 *lcd_20x4, uint8_t index, uint8_t character[8]);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns the custom character for a given index, as set with
 * {@link lcd_20x4_set_custom_character}.
 * 
 * .. versionadded:: 2.0.1~(Plugin)
 */
int lcd_20x4_get_custom_character(LCD20x4 *lcd_20x4, uint8_t index, uint8_t ret_character[8]);

/**
 * \ingroup BrickletLCD20x4
 *
 * Sets the default text for lines 0-3. The max number of characters
 * per line is 20.
 * 
 * The default text is shown on the LCD, if the default text counter
 * expires, see {@link lcd_20x4_set_default_text_counter}.
 * 
 * .. versionadded:: 2.0.2~(Plugin)
 */
int lcd_20x4_set_default_text(LCD20x4 *lcd_20x4, uint8_t line, const char text[20]);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns the default text for a given line (0-3) as set by
 * {@link lcd_20x4_set_default_text}.
 * 
 * .. versionadded:: 2.0.2~(Plugin)
 */
int lcd_20x4_get_default_text(LCD20x4 *lcd_20x4, uint8_t line, char ret_text[20]);

/**
 * \ingroup BrickletLCD20x4
 *
 * Sets the default text counter in ms. This counter is decremented each
 * ms by the LCD firmware. If the counter reaches 0, the default text
 * (see {@link lcd_20x4_set_default_text}) is shown on the LCD.
 * 
 * This functionality can be used to show a default text if the controlling
 * program crashes or the connection is interrupted.
 * 
 * A possible approach is to call {@link lcd_20x4_set_default_text_counter} every
 * minute with the parameter 1000*60*2 (2 minutes). In this case the
 * default text will be shown no later than 2 minutes after the
 * controlling program crashes.
 * 
 * A negative counter turns the default text functionality off.
 * 
 * The default is -1.
 * 
 * .. versionadded:: 2.0.2~(Plugin)
 */
int lcd_20x4_set_default_text_counter(LCD20x4 *lcd_20x4, int32_t counter);

/**
 * \ingroup BrickletLCD20x4
 *
 * Returns the current value of the default text counter.
 * 
 * .. versionadded:: 2.0.2~(Plugin)
 */
int lcd_20x4_get_default_text_counter(LCD20x4 *lcd_20x4, int32_t *ret_counter);

/**
 * \ingroup BrickletLCD20x4
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
int lcd_20x4_get_identity(LCD20x4 *lcd_20x4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

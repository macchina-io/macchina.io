/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_REAL_TIME_CLOCK_H
#define BRICKLET_REAL_TIME_CLOCK_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRealTimeClock Real-Time Clock Bricklet
 */

/**
 * \ingroup BrickletRealTimeClock
 *
 * Battery-backed real-time clock
 */
typedef Device RealTimeClock;

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME 1

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME 2

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_TIMESTAMP 3

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_SET_OFFSET 4

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_OFFSET 5

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_MONDAY 1

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_TUESDAY 2

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_WEDNESDAY 3

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_THURSDAY 4

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_FRIDAY 5

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_SATURDAY 6

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_SUNDAY 7

/**
 * \ingroup BrickletRealTimeClock
 *
 * This constant is used to identify a Real-Time Clock Bricklet.
 *
 * The {@link real_time_clock_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define REAL_TIME_CLOCK_DEVICE_IDENTIFIER 268

/**
 * \ingroup BrickletRealTimeClock
 *
 * This constant represents the display name of a Real-Time Clock Bricklet.
 */
#define REAL_TIME_CLOCK_DEVICE_DISPLAY_NAME "Real-Time Clock Bricklet"

/**
 * \ingroup BrickletRealTimeClock
 *
 * Creates the device object \c real_time_clock with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void real_time_clock_create(RealTimeClock *real_time_clock, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Removes the device object \c real_time_clock from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void real_time_clock_destroy(RealTimeClock *real_time_clock);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the real_time_clock_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int real_time_clock_get_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRealTimeClock
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
int real_time_clock_set_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int real_time_clock_set_response_expected_all(RealTimeClock *real_time_clock, bool response_expected);


/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int real_time_clock_get_api_version(RealTimeClock *real_time_clock, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Sets the current date (including weekday) and the current time with hundredths
 * of a second resolution.
 * 
 * Possible value ranges:
 * 
 * * Year: 2000 to 2099
 * * Month: 1 to 12 (January to December)
 * * Day: 1 to 31
 * * Hour: 0 to 23
 * * Minute: 0 to 59
 * * Second: 0 to 59
 * * Centisecond: 0 to 99
 * * Weekday: 1 to 7 (Monday to Sunday)
 * 
 * If the backup battery is installed then the real-time clock keeps date and
 * time even if the Bricklet is not powered by a Brick.
 * 
 * The real-time clock handles leap year and inserts the 29th of February
 * accordingly. But leap seconds, time zones and daylight saving time are not
 * handled.
 */
int real_time_clock_set_date_time(RealTimeClock *real_time_clock, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the current date (including weekday) and the current time of the
 * real-time clock with hundredths of a second resolution.
 */
int real_time_clock_get_date_time(RealTimeClock *real_time_clock, uint16_t *ret_year, uint8_t *ret_month, uint8_t *ret_day, uint8_t *ret_hour, uint8_t *ret_minute, uint8_t *ret_second, uint8_t *ret_centisecond, uint8_t *ret_weekday);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the current date and the time of the real-time clock converted to
 * milliseconds. The timestamp has an effective resolution of hundredths of a
 * second.
 */
int real_time_clock_get_timestamp(RealTimeClock *real_time_clock, int64_t *ret_timestamp);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Sets the offset the real-time clock should compensate for in 2.17 ppm steps
 * between -277.76 ppm (-128) and +275.59 ppm (127).
 * 
 * The real-time clock time can deviate from the actual time due to the frequency
 * deviation of its 32.768 kHz crystal. Even without compensation (factory
 * default) the resulting time deviation should be at most ±20 ppm (±52.6
 * seconds per month).
 * 
 * This deviation can be calculated by comparing the same duration measured by the
 * real-time clock (``rtc_duration``) an accurate reference clock
 * (``ref_duration``).
 * 
 * For best results the configured offset should be set to 0 ppm first and then a
 * duration of at least 6 hours should be measured.
 * 
 * The new offset (``new_offset``) can be calculated from the currently configured
 * offset (``current_offset``) and the measured durations as follow::
 * 
 *   new_offset = current_offset - round(1000000 * (rtc_duration - ref_duration) / rtc_duration / 2.17)
 * 
 * If you want to calculate the offset, then we recommend using the calibration
 * dialog in Brick Viewer, instead of doing it manually.
 * 
 * The offset is saved in the EEPROM of the Bricklet and only needs to be
 * configured once.
 */
int real_time_clock_set_offset(RealTimeClock *real_time_clock, int8_t offset);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the offset as set by {@link real_time_clock_set_offset}.
 */
int real_time_clock_get_offset(RealTimeClock *real_time_clock, int8_t *ret_offset);

/**
 * \ingroup BrickletRealTimeClock
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
int real_time_clock_get_identity(RealTimeClock *real_time_clock, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

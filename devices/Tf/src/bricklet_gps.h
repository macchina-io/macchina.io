/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_GPS_H
#define BRICKLET_GPS_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletGPS GPS Bricklet
 */

/**
 * \ingroup BrickletGPS
 *
 * Device for receiving GPS position
 */
typedef Device GPS;

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_COORDINATES 1

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_STATUS 2

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_ALTITUDE 3

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_MOTION 4

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_DATE_TIME 5

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_RESTART 6

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_SET_COORDINATES_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_COORDINATES_CALLBACK_PERIOD 8

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_SET_STATUS_CALLBACK_PERIOD 9

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_STATUS_CALLBACK_PERIOD 10

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD 11

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD 12

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_SET_MOTION_CALLBACK_PERIOD 13

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_MOTION_CALLBACK_PERIOD 14

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_SET_DATE_TIME_CALLBACK_PERIOD 15

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_DATE_TIME_CALLBACK_PERIOD 16

/**
 * \ingroup BrickletGPS
 */
#define GPS_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletGPS
 *
 * Signature: \code void callback(uint32_t latitude, char ns, uint32_t longitude, char ew, uint16_t pdop, uint16_t hdop, uint16_t vdop, uint16_t epe, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link gps_set_coordinates_callback_period}. The parameters are the same
 * as for {@link gps_get_coordinates}.
 * 
 * {@link GPS_CALLBACK_COORDINATES} is only triggered if the coordinates changed since the
 * last triggering and if there is currently a fix as indicated by
 * {@link gps_get_status}.
 */
#define GPS_CALLBACK_COORDINATES 17

/**
 * \ingroup BrickletGPS
 *
 * Signature: \code void callback(uint8_t fix, uint8_t satellites_view, uint8_t satellites_used, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link gps_set_status_callback_period}. The parameters are the same
 * as for {@link gps_get_status}.
 * 
 * {@link GPS_CALLBACK_STATUS} is only triggered if the status changed since the
 * last triggering.
 */
#define GPS_CALLBACK_STATUS 18

/**
 * \ingroup BrickletGPS
 *
 * Signature: \code void callback(uint32_t altitude, uint32_t geoidal_separation, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link gps_set_altitude_callback_period}. The parameters are the same
 * as for {@link gps_get_altitude}.
 * 
 * {@link GPS_CALLBACK_ALTITUDE} is only triggered if the altitude changed since the
 * last triggering and if there is currently a fix as indicated by
 * {@link gps_get_status}.
 */
#define GPS_CALLBACK_ALTITUDE 19

/**
 * \ingroup BrickletGPS
 *
 * Signature: \code void callback(uint32_t course, uint32_t speed, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link gps_set_motion_callback_period}. The parameters are the same
 * as for {@link gps_get_motion}.
 * 
 * {@link GPS_CALLBACK_MOTION} is only triggered if the motion changed since the
 * last triggering and if there is currently a fix as indicated by
 * {@link gps_get_status}.
 */
#define GPS_CALLBACK_MOTION 20

/**
 * \ingroup BrickletGPS
 *
 * Signature: \code void callback(uint32_t date, uint32_t time, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link gps_set_date_time_callback_period}. The parameters are the same
 * as for {@link gps_get_date_time}.
 * 
 * {@link GPS_CALLBACK_DATE_TIME} is only triggered if the date or time changed since the
 * last triggering.
 */
#define GPS_CALLBACK_DATE_TIME 21


/**
 * \ingroup BrickletGPS
 */
#define GPS_FIX_NO_FIX 1

/**
 * \ingroup BrickletGPS
 */
#define GPS_FIX_2D_FIX 2

/**
 * \ingroup BrickletGPS
 */
#define GPS_FIX_3D_FIX 3

/**
 * \ingroup BrickletGPS
 */
#define GPS_RESTART_TYPE_HOT_START 0

/**
 * \ingroup BrickletGPS
 */
#define GPS_RESTART_TYPE_WARM_START 1

/**
 * \ingroup BrickletGPS
 */
#define GPS_RESTART_TYPE_COLD_START 2

/**
 * \ingroup BrickletGPS
 */
#define GPS_RESTART_TYPE_FACTORY_RESET 3

/**
 * \ingroup BrickletGPS
 *
 * This constant is used to identify a GPS Bricklet.
 *
 * The {@link gps_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define GPS_DEVICE_IDENTIFIER 222

/**
 * \ingroup BrickletGPS
 *
 * Creates the device object \c gps with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void gps_create(GPS *gps, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletGPS
 *
 * Removes the device object \c gps from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void gps_destroy(GPS *gps);

/**
 * \ingroup BrickletGPS
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the gps_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int gps_get_response_expected(GPS *gps, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletGPS
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
int gps_set_response_expected(GPS *gps, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletGPS
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int gps_set_response_expected_all(GPS *gps, bool response_expected);

/**
 * \ingroup BrickletGPS
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void gps_register_callback(GPS *gps, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletGPS
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int gps_get_api_version(GPS *gps, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletGPS
 *
 * Returns the GPS coordinates. Latitude and longitude are given in the
 * ``DD.dddddd°`` format, the value 57123468 means 57.123468°.
 * The parameter ``ns`` and ``ew`` are the cardinal directions for
 * latitude and longitude. Possible values for ``ns`` and ``ew`` are 'N', 'S', 'E'
 * and 'W' (north, south, east and west).
 * 
 * PDOP, HDOP and VDOP are the dilution of precision (DOP) values. They specify
 * the additional multiplicative effect of GPS satellite geometry on GPS 
 * precision. See 
 * `here <http://en.wikipedia.org/wiki/Dilution_of_precision_(GPS)>`__
 * for more information. The values are give in hundredths.
 * 
 * EPE is the "Estimated Position Error". The EPE is given in cm. This is not the
 * absolute maximum error, it is the error with a specific confidence. See
 * `here <http://www.nps.gov/gis/gps/WhatisEPE.html>`__ for more information.
 * 
 * This data is only valid if there is currently a fix as indicated by
 * {@link gps_get_status}.
 */
int gps_get_coordinates(GPS *gps, uint32_t *ret_latitude, char *ret_ns, uint32_t *ret_longitude, char *ret_ew, uint16_t *ret_pdop, uint16_t *ret_hdop, uint16_t *ret_vdop, uint16_t *ret_epe);

/**
 * \ingroup BrickletGPS
 *
 * Returns the current fix status, the number of satellites that are in view and
 * the number of satellites that are currently used.
 * 
 * Possible fix status values can be:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "1", "No Fix, {@link gps_get_coordinates} and {@link gps_get_altitude} return invalid data"
 *  "2", "2D Fix, only {@link gps_get_coordinates} returns valid data"
 *  "3", "3D Fix, {@link gps_get_coordinates} and {@link gps_get_altitude} return valid data"
 * \endverbatim
 * 
 * There is also a :ref:`blue LED <gps_bricklet_fix_led>` on the Bricklet that
 * indicates the fix status.
 */
int gps_get_status(GPS *gps, uint8_t *ret_fix, uint8_t *ret_satellites_view, uint8_t *ret_satellites_used);

/**
 * \ingroup BrickletGPS
 *
 * Returns the current altitude and corresponding geoidal separation.
 * 
 * Both values are given in cm.
 * 
 * This data is only valid if there is currently a fix as indicated by
 * {@link gps_get_status}.
 */
int gps_get_altitude(GPS *gps, uint32_t *ret_altitude, uint32_t *ret_geoidal_separation);

/**
 * \ingroup BrickletGPS
 *
 * Returns the current course and speed. Course is given in hundredths degree
 * and speed is given in hundredths km/h. A course of 0° means the Bricklet is
 * traveling north bound and 90° means it is traveling east bound.
 * 
 * Please note that this only returns useful values if an actual movement
 * is present.
 * 
 * This data is only valid if there is currently a fix as indicated by
 * {@link gps_get_status}.
 */
int gps_get_motion(GPS *gps, uint32_t *ret_course, uint32_t *ret_speed);

/**
 * \ingroup BrickletGPS
 *
 * Returns the current date and time. The date is
 * given in the format ``ddmmyy`` and the time is given
 * in the format ``hhmmss.sss``. For example, 140713 means
 * 14.05.13 as date and 195923568 means 19:59:23.568 as time.
 */
int gps_get_date_time(GPS *gps, uint32_t *ret_date, uint32_t *ret_time);

/**
 * \ingroup BrickletGPS
 *
 * Restarts the GPS Bricklet, the following restart types are available:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "Hot start (use all available data in the NV store)"
 *  "1", "Warm start (don't use ephemeris at restart)"
 *  "2", "Cold start (don't use time, position, almanacs and ephemeris at restart)"
 *  "3", "Factory reset (clear all system/user configurations at restart)"
 * \endverbatim
 */
int gps_restart(GPS *gps, uint8_t restart_type);

/**
 * \ingroup BrickletGPS
 *
 * Sets the period in ms with which the {@link GPS_CALLBACK_COORDINATES} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link GPS_CALLBACK_COORDINATES} is only triggered if the coordinates changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int gps_set_coordinates_callback_period(GPS *gps, uint32_t period);

/**
 * \ingroup BrickletGPS
 *
 * Returns the period as set by {@link gps_set_coordinates_callback_period}.
 */
int gps_get_coordinates_callback_period(GPS *gps, uint32_t *ret_period);

/**
 * \ingroup BrickletGPS
 *
 * Sets the period in ms with which the {@link GPS_CALLBACK_STATUS} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link GPS_CALLBACK_STATUS} is only triggered if the status changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int gps_set_status_callback_period(GPS *gps, uint32_t period);

/**
 * \ingroup BrickletGPS
 *
 * Returns the period as set by {@link gps_set_status_callback_period}.
 */
int gps_get_status_callback_period(GPS *gps, uint32_t *ret_period);

/**
 * \ingroup BrickletGPS
 *
 * Sets the period in ms with which the {@link GPS_CALLBACK_ALTITUDE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link GPS_CALLBACK_ALTITUDE} is only triggered if the altitude changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int gps_set_altitude_callback_period(GPS *gps, uint32_t period);

/**
 * \ingroup BrickletGPS
 *
 * Returns the period as set by {@link gps_set_altitude_callback_period}.
 */
int gps_get_altitude_callback_period(GPS *gps, uint32_t *ret_period);

/**
 * \ingroup BrickletGPS
 *
 * Sets the period in ms with which the {@link GPS_CALLBACK_MOTION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link GPS_CALLBACK_MOTION} is only triggered if the motion changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int gps_set_motion_callback_period(GPS *gps, uint32_t period);

/**
 * \ingroup BrickletGPS
 *
 * Returns the period as set by {@link gps_set_motion_callback_period}.
 */
int gps_get_motion_callback_period(GPS *gps, uint32_t *ret_period);

/**
 * \ingroup BrickletGPS
 *
 * Sets the period in ms with which the {@link GPS_CALLBACK_DATE_TIME} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * {@link GPS_CALLBACK_DATE_TIME} is only triggered if the date or time changed since the
 * last triggering.
 * 
 * The default value is 0.
 */
int gps_set_date_time_callback_period(GPS *gps, uint32_t period);

/**
 * \ingroup BrickletGPS
 *
 * Returns the period as set by {@link gps_set_date_time_callback_period}.
 */
int gps_get_date_time_callback_period(GPS *gps, uint32_t *ret_period);

/**
 * \ingroup BrickletGPS
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
int gps_get_identity(GPS *gps, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

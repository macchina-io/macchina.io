/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICK_IMU_V2_H
#define BRICK_IMU_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickIMUV2 IMU Brick 2.0
 */

/**
 * \ingroup BrickIMUV2
 *
 * Full fledged AHRS with 9 degrees of freedom
 */
typedef Device IMUV2;

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ACCELERATION 1

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_MAGNETIC_FIELD 2

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ANGULAR_VELOCITY 3

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_TEMPERATURE 4

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ORIENTATION 5

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_LINEAR_ACCELERATION 6

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_GRAVITY_VECTOR 7

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_QUATERNION 8

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ALL_DATA 9

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_LEDS_ON 10

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_LEDS_OFF 11

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_ARE_LEDS_ON 12

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SAVE_CALIBRATION 13

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_ACCELERATION_PERIOD 14

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ACCELERATION_PERIOD 15

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_MAGNETIC_FIELD_PERIOD 16

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_MAGNETIC_FIELD_PERIOD 17

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_ANGULAR_VELOCITY_PERIOD 18

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ANGULAR_VELOCITY_PERIOD 19

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_TEMPERATURE_PERIOD 20

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_TEMPERATURE_PERIOD 21

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_ORIENTATION_PERIOD 22

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ORIENTATION_PERIOD 23

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_LINEAR_ACCELERATION_PERIOD 24

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_LINEAR_ACCELERATION_PERIOD 25

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_GRAVITY_VECTOR_PERIOD 26

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_GRAVITY_VECTOR_PERIOD 27

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_QUATERNION_PERIOD 28

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_QUATERNION_PERIOD 29

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_SET_ALL_DATA_PERIOD 30

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_ALL_DATA_PERIOD 31

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_ENABLE_STATUS_LED 238

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_DISABLE_STATUS_LED 239

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_IS_STATUS_LED_ENABLED 240

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME 241

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickIMUV2
 */
#define IMU_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_acceleration_period}. The parameters are the acceleration
 * for the x, y and z axis.
 */
#define IMU_V2_CALLBACK_ACCELERATION 32

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_magnetic_field_period}. The parameters are the magnetic field
 * for the x, y and z axis.
 */
#define IMU_V2_CALLBACK_MAGNETIC_FIELD 33

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_angular_velocity_period}. The parameters are the angular velocity
 * for the x, y and z axis.
 */
#define IMU_V2_CALLBACK_ANGULAR_VELOCITY 34

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int8_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_temperature_period}. The parameter is the temperature.
 */
#define IMU_V2_CALLBACK_TEMPERATURE 35

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_linear_acceleration_period}. The parameters are the 
 * linear acceleration for the x, y and z axis.
 */
#define IMU_V2_CALLBACK_LINEAR_ACCELERATION 36

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_gravity_vector_period}. The parameters gravity vector
 * for the x, y and z axis.
 */
#define IMU_V2_CALLBACK_GRAVITY_VECTOR 37

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t heading, int16_t roll, int16_t pitch, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_orientation_period}. The parameters are the orientation
 * (heading (yaw), roll, pitch) of the IMU Brick in Euler angles. See
 * {@link imu_v2_get_orientation} for details.
 */
#define IMU_V2_CALLBACK_ORIENTATION 38

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t w, int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_quaternion_period}. The parameters are the orientation
 * (x, y, z, w) of the IMU Brick in quaternions. See {@link imu_v2_get_quaternion}
 * for details.
 */
#define IMU_V2_CALLBACK_QUATERNION 39

/**
 * \ingroup BrickIMUV2
 *
 * Signature: \code void callback(int16_t ret_acceleration[3], int16_t ret_magnetic_field[3], int16_t ret_angular_velocity[3], int16_t ret_euler_angle[3], int16_t ret_quaternion[4], int16_t ret_linear_acceleration[3], int16_t ret_gravity_vector[3], int8_t temperature, uint8_t calibration_status, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_v2_set_all_data_period}. The parameters are as for {@link imu_v2_get_all_data}.
 */
#define IMU_V2_CALLBACK_ALL_DATA 40


/**
 * \ingroup BrickIMUV2
 *
 * This constant is used to identify a IMU Brick 2.0.
 *
 * The {@link imu_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define IMU_V2_DEVICE_IDENTIFIER 18

/**
 * \ingroup BrickIMUV2
 *
 * This constant represents the display name of a IMU Brick 2.0.
 */
#define IMU_V2_DEVICE_DISPLAY_NAME "IMU Brick 2.0"

/**
 * \ingroup BrickIMUV2
 *
 * Creates the device object \c imu_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void imu_v2_create(IMUV2 *imu_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickIMUV2
 *
 * Removes the device object \c imu_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void imu_v2_destroy(IMUV2 *imu_v2);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the imu_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int imu_v2_get_response_expected(IMUV2 *imu_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickIMUV2
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
int imu_v2_set_response_expected(IMUV2 *imu_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickIMUV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int imu_v2_set_response_expected_all(IMUV2 *imu_v2, bool response_expected);

/**
 * \ingroup BrickIMUV2
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void imu_v2_register_callback(IMUV2 *imu_v2, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int imu_v2_get_api_version(IMUV2 *imu_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the calibrated acceleration from the accelerometer for the 
 * x, y and z axis in 1/100 m/s².
 * 
 * If you want to get the acceleration periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_ACCELERATION} and set the period with 
 * {@link imu_v2_set_acceleration_period}.
 */
int imu_v2_get_acceleration(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the calibrated magnetic field from the magnetometer for the 
 * x, y and z axis in 1/16 µT (Microtesla).
 * 
 * If you want to get the magnetic field periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_MAGNETIC_FIELD} and set the period with 
 * {@link imu_v2_set_magnetic_field_period}.
 */
int imu_v2_get_magnetic_field(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the calibrated angular velocity from the gyroscope for the 
 * x, y and z axis in 1/16 °/s.
 * 
 * If you want to get the angular velocity periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_ANGULAR_VELOCITY} and set the period with 
 * {@link imu_v2_set_angular_velocity_period}.
 */
int imu_v2_get_angular_velocity(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the temperature of the IMU Brick. The temperature is given in 
 * °C. The temperature is measured in the core of the BNO055 IC, it is not the
 * ambient temperature
 */
int imu_v2_get_temperature(IMUV2 *imu_v2, int8_t *ret_temperature);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the current orientation (heading, roll, pitch) of the IMU Brick as
 * independent Euler angles in 1/16 degree. Note that Euler angles always
 * experience a `gimbal lock <https://en.wikipedia.org/wiki/Gimbal_lock>`__. We
 * recommend that you use quaternions instead, if you need the absolute orientation.
 * 
 * The rotation angle has the following ranges:
 * 
 * * heading: 0° to 360°
 * * roll: -90° to +90°
 * * pitch: -180° to +180°
 * 
 * If you want to get the orientation periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_ORIENTATION} and set the period with 
 * {@link imu_v2_set_orientation_period}.
 */
int imu_v2_get_orientation(IMUV2 *imu_v2, int16_t *ret_heading, int16_t *ret_roll, int16_t *ret_pitch);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the linear acceleration of the IMU Brick for the
 * x, y and z axis in 1/100 m/s².
 * 
 * The linear acceleration is the acceleration in each of the three
 * axis of the IMU Brick with the influences of gravity removed.
 * 
 * It is also possible to get the gravity vector with the influence of linear
 * acceleration removed, see {@link imu_v2_get_gravity_vector}.
 * 
 * If you want to get the linear acceleration periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_LINEAR_ACCELERATION} and set the period with 
 * {@link imu_v2_set_linear_acceleration_period}.
 */
int imu_v2_get_linear_acceleration(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the current gravity vector of the IMU Brick for the
 * x, y and z axis in 1/100 m/s².
 * 
 * The gravity vector is the acceleration that occurs due to gravity.
 * Influences of additional linear acceleration are removed.
 * 
 * It is also possible to get the linear acceleration with the influence 
 * of gravity removed, see {@link imu_v2_get_linear_acceleration}.
 * 
 * If you want to get the gravity vector periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_GRAVITY_VECTOR} and set the period with 
 * {@link imu_v2_set_gravity_vector_period}.
 */
int imu_v2_get_gravity_vector(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the current orientation (w, x, y, z) of the IMU Brick as
 * `quaternions <https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation>`__.
 * 
 * You have to divide the returns values by 16383 (14 bit) to get
 * the usual range of -1.0 to +1.0 for quaternions.
 * 
 * If you want to get the quaternions periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_QUATERNION} and set the period with 
 * {@link imu_v2_set_quaternion_period}.
 */
int imu_v2_get_quaternion(IMUV2 *imu_v2, int16_t *ret_w, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMUV2
 *
 * Return all of the available data of the IMU Brick.
 * 
 * * acceleration in 1/100 m/s² (see {@link imu_v2_get_acceleration})
 * * magnetic field in 1/16 µT (see {@link imu_v2_get_magnetic_field})
 * * angular velocity in 1/16 °/s (see {@link imu_v2_get_angular_velocity})
 * * Euler angles in 1/16 ° (see {@link imu_v2_get_orientation})
 * * quaternion 1/16383 (see {@link imu_v2_get_quaternion})
 * * linear acceleration 1/100 m/s² (see {@link imu_v2_get_linear_acceleration})
 * * gravity vector 1/100 m/s² (see {@link imu_v2_get_gravity_vector})
 * * temperature in 1 °C (see {@link imu_v2_get_temperature})
 * * calibration status (see below)
 * 
 * The calibration status consists of four pairs of two bits. Each pair
 * of bits represents the status of the current calibration.
 * 
 * * bit 0-1: Magnetometer
 * * bit 2-3: Accelerometer
 * * bit 4-5: Gyroscope
 * * bit 6-7: System
 * 
 * A value of 0 means for "not calibrated" and a value of 3 means
 * "fully calibrated". In your program you should always be able to
 * ignore the calibration status, it is used by the calibration
 * window of the Brick Viewer and it can be ignored after the first
 * calibration. See the documentation in the calibration window for
 * more information regarding the calibration of the IMU Brick.
 * 
 * If you want to get the data periodically, it is recommended 
 * to use the callback {@link IMU_V2_CALLBACK_ALL_DATA} and set the period with 
 * {@link imu_v2_set_all_data_period}.
 */
int imu_v2_get_all_data(IMUV2 *imu_v2, int16_t ret_acceleration[3], int16_t ret_magnetic_field[3], int16_t ret_angular_velocity[3], int16_t ret_euler_angle[3], int16_t ret_quaternion[4], int16_t ret_linear_acceleration[3], int16_t ret_gravity_vector[3], int8_t *ret_temperature, uint8_t *ret_calibration_status);

/**
 * \ingroup BrickIMUV2
 *
 * Turns the orientation and direction LEDs of the IMU Brick on.
 */
int imu_v2_leds_on(IMUV2 *imu_v2);

/**
 * \ingroup BrickIMUV2
 *
 * Turns the orientation and direction LEDs of the IMU Brick off.
 */
int imu_v2_leds_off(IMUV2 *imu_v2);

/**
 * \ingroup BrickIMUV2
 *
 * Returns *true* if the orientation and direction LEDs of the IMU Brick
 * are on, *false* otherwise.
 */
int imu_v2_are_leds_on(IMUV2 *imu_v2, bool *ret_leds);

/**
 * \ingroup BrickIMUV2
 *
 * A call of this function saves the current calibration to be used
 * as a starting point for the next restart of continuous calibration
 * of the IMU Brick.
 * 
 * A return value of *true* means that the calibration could be used and
 * *false* means that it could not be used (this happens if the calibration 
 * status is not "fully calibrated").
 * 
 * This function is used by the calibration window of the Brick Viewer, you
 * should not need to call it in your program.
 */
int imu_v2_save_calibration(IMUV2 *imu_v2, bool *ret_calibration_done);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_ACCELERATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The default value is 0.
 */
int imu_v2_set_acceleration_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_acceleration_period}.
 */
int imu_v2_get_acceleration_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_MAGNETIC_FIELD} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_magnetic_field_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_magnetic_field_period}.
 */
int imu_v2_get_magnetic_field_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_ANGULAR_VELOCITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_angular_velocity_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_angular_velocity_period}.
 */
int imu_v2_get_angular_velocity_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_temperature_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_temperature_period}.
 */
int imu_v2_get_temperature_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_ORIENTATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_orientation_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_orientation_period}.
 */
int imu_v2_get_orientation_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_LINEAR_ACCELERATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_linear_acceleration_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_linear_acceleration_period}.
 */
int imu_v2_get_linear_acceleration_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_GRAVITY_VECTOR} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_gravity_vector_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_gravity_vector_period}.
 */
int imu_v2_get_gravity_vector_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_QUATERNION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_quaternion_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_quaternion_period}.
 */
int imu_v2_get_quaternion_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Sets the period in ms with which the {@link IMU_V2_CALLBACK_ALL_DATA} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_v2_set_all_data_period(IMUV2 *imu_v2, uint32_t period);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the period as set by {@link imu_v2_set_all_data_period}.
 */
int imu_v2_get_all_data_period(IMUV2 *imu_v2, uint32_t *ret_period);

/**
 * \ingroup BrickIMUV2
 *
 * Enables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 */
int imu_v2_enable_status_led(IMUV2 *imu_v2);

/**
 * \ingroup BrickIMUV2
 *
 * Disables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 */
int imu_v2_disable_status_led(IMUV2 *imu_v2);

/**
 * \ingroup BrickIMUV2
 *
 * Returns *true* if the status LED is enabled, *false* otherwise.
 */
int imu_v2_is_status_led_enabled(IMUV2 *imu_v2, bool *ret_enabled);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the firmware and protocol version and the name of the Bricklet for a
 * given port.
 * 
 * This functions sole purpose is to allow automatic flashing of v1.x.y Bricklet
 * plugins.
 */
int imu_v2_get_protocol1_bricklet_name(IMUV2 *imu_v2, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the temperature in °C/10 as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has an
 * accuracy of +-15%. Practically it is only useful as an indicator for
 * temperature changes.
 */
int imu_v2_get_chip_temperature(IMUV2 *imu_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickIMUV2
 *
 * Calling this function will reset the Brick. Calling this function
 * on a Brick inside of a stack will reset the whole stack.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int imu_v2_reset(IMUV2 *imu_v2);

/**
 * \ingroup BrickIMUV2
 *
 * Returns the UID, the UID where the Brick is connected to, 
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position can be '0'-'8' (stack position).
 * 
 * The device identifier numbers can be found :ref:`here <device_identifier>`.
 * |device_identifier_constant|
 */
int imu_v2_get_identity(IMUV2 *imu_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

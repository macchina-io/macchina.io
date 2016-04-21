/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICK_IMU_H
#define BRICK_IMU_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickIMU IMU Brick
 */

/**
 * \ingroup BrickIMU
 *
 * Full fledged AHRS with 9 degrees of freedom
 */
typedef Device IMU;

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ACCELERATION 1

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_MAGNETIC_FIELD 2

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ANGULAR_VELOCITY 3

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ALL_DATA 4

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ORIENTATION 5

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_QUATERNION 6

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_IMU_TEMPERATURE 7

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_LEDS_ON 8

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_LEDS_OFF 9

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_ARE_LEDS_ON 10

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_ACCELERATION_RANGE 11

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ACCELERATION_RANGE 12

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_MAGNETOMETER_RANGE 13

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_MAGNETOMETER_RANGE 14

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_CONVERGENCE_SPEED 15

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_CONVERGENCE_SPEED 16

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_CALIBRATION 17

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_CALIBRATION 18

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_ACCELERATION_PERIOD 19

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ACCELERATION_PERIOD 20

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_MAGNETIC_FIELD_PERIOD 21

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_MAGNETIC_FIELD_PERIOD 22

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_ANGULAR_VELOCITY_PERIOD 23

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ANGULAR_VELOCITY_PERIOD 24

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_ALL_DATA_PERIOD 25

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ALL_DATA_PERIOD 26

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_ORIENTATION_PERIOD 27

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_ORIENTATION_PERIOD 28

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_SET_QUATERNION_PERIOD 29

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_QUATERNION_PERIOD 30

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_ORIENTATION_CALCULATION_ON 37

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_ORIENTATION_CALCULATION_OFF 38

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_IS_ORIENTATION_CALCULATION_ON 39

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_ENABLE_STATUS_LED 238

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_DISABLE_STATUS_LED 239

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_IS_STATUS_LED_ENABLED 240

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME 241

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_RESET 243

/**
 * \ingroup BrickIMU
 */
#define IMU_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickIMU
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_set_acceleration_period}. The parameters are the acceleration
 * for the x, y and z axis.
 */
#define IMU_CALLBACK_ACCELERATION 31

/**
 * \ingroup BrickIMU
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_set_magnetic_field_period}. The parameters are the magnetic field
 * for the x, y and z axis.
 */
#define IMU_CALLBACK_MAGNETIC_FIELD 32

/**
 * \ingroup BrickIMU
 *
 * Signature: \code void callback(int16_t x, int16_t y, int16_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_set_angular_velocity_period}. The parameters are the angular velocity
 * for the x, y and z axis.
 */
#define IMU_CALLBACK_ANGULAR_VELOCITY 33

/**
 * \ingroup BrickIMU
 *
 * Signature: \code void callback(int16_t acc_x, int16_t acc_y, int16_t acc_z, int16_t mag_x, int16_t mag_y, int16_t mag_z, int16_t ang_x, int16_t ang_y, int16_t ang_z, int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_set_all_data_period}. The parameters are the acceleration,
 * the magnetic field and the angular velocity for the x, y and z axis as
 * well as the temperature of the IMU Brick.
 */
#define IMU_CALLBACK_ALL_DATA 34

/**
 * \ingroup BrickIMU
 *
 * Signature: \code void callback(int16_t roll, int16_t pitch, int16_t yaw, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_set_orientation_period}. The parameters are the orientation
 * (roll, pitch and yaw) of the IMU Brick in Euler angles. See
 * {@link imu_get_orientation} for details.
 */
#define IMU_CALLBACK_ORIENTATION 35

/**
 * \ingroup BrickIMU
 *
 * Signature: \code void callback(float x, float y, float z, float w, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link imu_set_quaternion_period}. The parameters are the orientation
 * (x, y, z, w) of the IMU Brick in quaternions. See {@link imu_get_quaternion}
 * for details.
 */
#define IMU_CALLBACK_QUATERNION 36


/**
 * \ingroup BrickIMU
 */
#define IMU_CALIBRATION_TYPE_ACCELEROMETER_GAIN 0

/**
 * \ingroup BrickIMU
 */
#define IMU_CALIBRATION_TYPE_ACCELEROMETER_BIAS 1

/**
 * \ingroup BrickIMU
 */
#define IMU_CALIBRATION_TYPE_MAGNETOMETER_GAIN 2

/**
 * \ingroup BrickIMU
 */
#define IMU_CALIBRATION_TYPE_MAGNETOMETER_BIAS 3

/**
 * \ingroup BrickIMU
 */
#define IMU_CALIBRATION_TYPE_GYROSCOPE_GAIN 4

/**
 * \ingroup BrickIMU
 */
#define IMU_CALIBRATION_TYPE_GYROSCOPE_BIAS 5

/**
 * \ingroup BrickIMU
 *
 * This constant is used to identify a IMU Brick.
 *
 * The {@link imu_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define IMU_DEVICE_IDENTIFIER 16

/**
 * \ingroup BrickIMU
 *
 * This constant represents the display name of a IMU Brick.
 */
#define IMU_DEVICE_DISPLAY_NAME "IMU Brick"

/**
 * \ingroup BrickIMU
 *
 * Creates the device object \c imu with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void imu_create(IMU *imu, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickIMU
 *
 * Removes the device object \c imu from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void imu_destroy(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the imu_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int imu_get_response_expected(IMU *imu, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickIMU
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
int imu_set_response_expected(IMU *imu, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickIMU
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int imu_set_response_expected_all(IMU *imu, bool response_expected);

/**
 * \ingroup BrickIMU
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void imu_register_callback(IMU *imu, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickIMU
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int imu_get_api_version(IMU *imu, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickIMU
 *
 * Returns the calibrated acceleration from the accelerometer for the 
 * x, y and z axis in g/1000 (1g = 9.80665m/s²).
 * 
 * If you want to get the acceleration periodically, it is recommended 
 * to use the callback {@link IMU_CALLBACK_ACCELERATION} and set the period with 
 * {@link imu_set_acceleration_period}.
 */
int imu_get_acceleration(IMU *imu, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMU
 *
 * Returns the calibrated magnetic field from the magnetometer for the 
 * x, y and z axis in mG (Milligauss or Nanotesla).
 * 
 * If you want to get the magnetic field periodically, it is recommended 
 * to use the callback {@link IMU_CALLBACK_MAGNETIC_FIELD} and set the period with 
 * {@link imu_set_magnetic_field_period}.
 */
int imu_get_magnetic_field(IMU *imu, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMU
 *
 * Returns the calibrated angular velocity from the gyroscope for the 
 * x, y and z axis in °/14.375s (you have to divide by 14.375 to
 * get the value in °/s).
 * 
 * If you want to get the angular velocity periodically, it is recommended 
 * to use the callback {@link IMU_CALLBACK_ANGULAR_VELOCITY} and set the period with 
 * {@link imu_set_angular_velocity_period}.
 */
int imu_get_angular_velocity(IMU *imu, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z);

/**
 * \ingroup BrickIMU
 *
 * Returns the data from {@link imu_get_acceleration}, {@link imu_get_magnetic_field} 
 * and {@link imu_get_angular_velocity} as well as the temperature of the IMU Brick.
 * 
 * The temperature is given in °C/100.
 * 
 * If you want to get the data periodically, it is recommended 
 * to use the callback {@link IMU_CALLBACK_ALL_DATA} and set the period with 
 * {@link imu_set_all_data_period}.
 */
int imu_get_all_data(IMU *imu, int16_t *ret_acc_x, int16_t *ret_acc_y, int16_t *ret_acc_z, int16_t *ret_mag_x, int16_t *ret_mag_y, int16_t *ret_mag_z, int16_t *ret_ang_x, int16_t *ret_ang_y, int16_t *ret_ang_z, int16_t *ret_temperature);

/**
 * \ingroup BrickIMU
 *
 * Returns the current orientation (roll, pitch, yaw) of the IMU Brick as Euler
 * angles in one-hundredth degree. Note that Euler angles always experience a
 * `gimbal lock <https://en.wikipedia.org/wiki/Gimbal_lock>`__.
 * 
 * We recommend that you use quaternions instead.
 * 
 * The order to sequence in which the orientation values should be applied is 
 * roll, yaw, pitch. 
 * 
 * If you want to get the orientation periodically, it is recommended 
 * to use the callback {@link IMU_CALLBACK_ORIENTATION} and set the period with 
 * {@link imu_set_orientation_period}.
 */
int imu_get_orientation(IMU *imu, int16_t *ret_roll, int16_t *ret_pitch, int16_t *ret_yaw);

/**
 * \ingroup BrickIMU
 *
 * Returns the current orientation (x, y, z, w) of the IMU as 
 * `quaternions <https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation>`__.
 * 
 * You can go from quaternions to Euler angles with the following formula::
 * 
 *  xAngle = atan2(2*y*w - 2*x*z, 1 - 2*y*y - 2*z*z)
 *  yAngle = atan2(2*x*w - 2*y*z, 1 - 2*x*x - 2*z*z)
 *  zAngle =  asin(2*x*y + 2*z*w)
 * 
 * This process is not reversible, because of the 
 * `gimbal lock <https://en.wikipedia.org/wiki/Gimbal_lock>`__.
 * 
 * It is also possible to calculate independent angles. You can calculate 
 * yaw, pitch and roll in a right-handed vehicle coordinate system according to DIN70000
 * with::
 * 
 *  yaw   =  atan2(2*x*y + 2*w*z, w*w + x*x - y*y - z*z)
 *  pitch = -asin(2*w*y - 2*x*z)
 *  roll  = -atan2(2*y*z + 2*w*x, -w*w + x*x + y*y - z*z))
 * 
 * Converting the quaternions to an OpenGL transformation matrix is
 * possible with the following formula::
 * 
 *  matrix = [[1 - 2*(y*y + z*z),     2*(x*y - w*z),     2*(x*z + w*y), 0],
 *            [    2*(x*y + w*z), 1 - 2*(x*x + z*z),     2*(y*z - w*x), 0],
 *            [    2*(x*z - w*y),     2*(y*z + w*x), 1 - 2*(x*x + y*y), 0],
 *            [                0,                 0,                 0, 1]]
 * 
 * If you want to get the quaternions periodically, it is recommended 
 * to use the callback {@link IMU_CALLBACK_QUATERNION} and set the period with 
 * {@link imu_set_quaternion_period}.
 */
int imu_get_quaternion(IMU *imu, float *ret_x, float *ret_y, float *ret_z, float *ret_w);

/**
 * \ingroup BrickIMU
 *
 * Returns the temperature of the IMU Brick. The temperature is given in 
 * °C/100.
 */
int imu_get_imu_temperature(IMU *imu, int16_t *ret_temperature);

/**
 * \ingroup BrickIMU
 *
 * Turns the orientation and direction LEDs of the IMU Brick on.
 */
int imu_leds_on(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Turns the orientation and direction LEDs of the IMU Brick off.
 */
int imu_leds_off(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Returns *true* if the orientation and direction LEDs of the IMU Brick
 * are on, *false* otherwise.
 */
int imu_are_leds_on(IMU *imu, bool *ret_leds);

/**
 * \ingroup BrickIMU
 *
 * Not implemented yet.
 */
int imu_set_acceleration_range(IMU *imu, uint8_t range);

/**
 * \ingroup BrickIMU
 *
 * Not implemented yet.
 */
int imu_get_acceleration_range(IMU *imu, uint8_t *ret_range);

/**
 * \ingroup BrickIMU
 *
 * Not implemented yet.
 */
int imu_set_magnetometer_range(IMU *imu, uint8_t range);

/**
 * \ingroup BrickIMU
 *
 * Not implemented yet.
 */
int imu_get_magnetometer_range(IMU *imu, uint8_t *ret_range);

/**
 * \ingroup BrickIMU
 *
 * Sets the convergence speed of the IMU Brick in °/s. The convergence speed 
 * determines how the different sensor measurements are fused.
 * 
 * If the orientation of the IMU Brick is off by 10° and the convergence speed is 
 * set to 20°/s, it will take 0.5s until the orientation is corrected. However,
 * if the correct orientation is reached and the convergence speed is too high,
 * the orientation will fluctuate with the fluctuations of the accelerometer and
 * the magnetometer.
 * 
 * If you set the convergence speed to 0, practically only the gyroscope is used
 * to calculate the orientation. This gives very smooth movements, but errors of the
 * gyroscope will not be corrected. If you set the convergence speed to something
 * above 500, practically only the magnetometer and the accelerometer are used to
 * calculate the orientation. In this case the movements are abrupt and the values
 * will fluctuate, but there won't be any errors that accumulate over time.
 * 
 * In an application with high angular velocities, we recommend a high convergence
 * speed, so the errors of the gyroscope can be corrected fast. In applications with
 * only slow movements we recommend a low convergence speed. You can change the
 * convergence speed on the fly. So it is possible (and recommended) to increase 
 * the convergence speed before an abrupt movement and decrease it afterwards 
 * again.
 * 
 * You might want to play around with the convergence speed in the Brick Viewer to
 * get a feeling for a good value for your application.
 * 
 * The default value is 30.
 */
int imu_set_convergence_speed(IMU *imu, uint16_t speed);

/**
 * \ingroup BrickIMU
 *
 * Returns the convergence speed as set by {@link imu_set_convergence_speed}.
 */
int imu_get_convergence_speed(IMU *imu, uint16_t *ret_speed);

/**
 * \ingroup BrickIMU
 *
 * There are several different types that can be calibrated:
 * 
 * \verbatim
 *  "Type", "Description", "Values"
 * 
 *  "0",    "Accelerometer Gain", "``[mul x, mul y, mul z, div x, div y, div z, 0, 0, 0, 0]``"
 *  "1",    "Accelerometer Bias", "``[bias x, bias y, bias z, 0, 0, 0, 0, 0, 0, 0]``"
 *  "2",    "Magnetometer Gain",  "``[mul x, mul y, mul z, div x, div y, div z, 0, 0, 0, 0]``"
 *  "3",    "Magnetometer Bias",  "``[bias x, bias y, bias z, 0, 0, 0, 0, 0, 0, 0]``"
 *  "4",    "Gyroscope Gain",     "``[mul x, mul y, mul z, div x, div y, div z, 0, 0, 0, 0]``"
 *  "5",    "Gyroscope Bias",     "``[bias xl, bias yl, bias zl, temp l, bias xh, bias yh, bias zh, temp h, 0, 0]``"
 * \endverbatim
 * 
 * The calibration via gain and bias is done with the following formula::
 * 
 *  new_value = (bias + orig_value) * gain_mul / gain_div
 * 
 * If you really want to write your own calibration software, please keep
 * in mind that you first have to undo the old calibration (set bias to 0 and
 * gain to 1/1) and that you have to average over several thousand values
 * to obtain a usable result in the end.
 * 
 * The gyroscope bias is highly dependent on the temperature, so you have to
 * calibrate the bias two times with different temperatures. The values ``xl``,
 * ``yl``, ``zl`` and ``temp l`` are the bias for ``x``, ``y``, ``z`` and the
 * corresponding temperature for a low temperature. The values ``xh``, ``yh``,
 * ``zh`` and ``temp h`` are the same for a high temperatures. The temperature
 * difference should be at least 5°C. If you have a temperature where the
 * IMU Brick is mostly used, you should use this temperature for one of the
 * sampling points.
 * 
 * \note
 *  We highly recommend that you use the Brick Viewer to calibrate your
 *  IMU Brick.
 */
int imu_set_calibration(IMU *imu, uint8_t typ, int16_t data[10]);

/**
 * \ingroup BrickIMU
 *
 * Returns the calibration for a given type as set by {@link imu_set_calibration}.
 */
int imu_get_calibration(IMU *imu, uint8_t typ, int16_t ret_data[10]);

/**
 * \ingroup BrickIMU
 *
 * Sets the period in ms with which the {@link IMU_CALLBACK_ACCELERATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The default value is 0.
 */
int imu_set_acceleration_period(IMU *imu, uint32_t period);

/**
 * \ingroup BrickIMU
 *
 * Returns the period as set by {@link imu_set_acceleration_period}.
 */
int imu_get_acceleration_period(IMU *imu, uint32_t *ret_period);

/**
 * \ingroup BrickIMU
 *
 * Sets the period in ms with which the {@link IMU_CALLBACK_MAGNETIC_FIELD} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_set_magnetic_field_period(IMU *imu, uint32_t period);

/**
 * \ingroup BrickIMU
 *
 * Returns the period as set by {@link imu_set_magnetic_field_period}.
 */
int imu_get_magnetic_field_period(IMU *imu, uint32_t *ret_period);

/**
 * \ingroup BrickIMU
 *
 * Sets the period in ms with which the {@link IMU_CALLBACK_ANGULAR_VELOCITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_set_angular_velocity_period(IMU *imu, uint32_t period);

/**
 * \ingroup BrickIMU
 *
 * Returns the period as set by {@link imu_set_angular_velocity_period}.
 */
int imu_get_angular_velocity_period(IMU *imu, uint32_t *ret_period);

/**
 * \ingroup BrickIMU
 *
 * Sets the period in ms with which the {@link IMU_CALLBACK_ALL_DATA} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_set_all_data_period(IMU *imu, uint32_t period);

/**
 * \ingroup BrickIMU
 *
 * Returns the period as set by {@link imu_set_all_data_period}.
 */
int imu_get_all_data_period(IMU *imu, uint32_t *ret_period);

/**
 * \ingroup BrickIMU
 *
 * Sets the period in ms with which the {@link IMU_CALLBACK_ORIENTATION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_set_orientation_period(IMU *imu, uint32_t period);

/**
 * \ingroup BrickIMU
 *
 * Returns the period as set by {@link imu_set_orientation_period}.
 */
int imu_get_orientation_period(IMU *imu, uint32_t *ret_period);

/**
 * \ingroup BrickIMU
 *
 * Sets the period in ms with which the {@link IMU_CALLBACK_QUATERNION} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int imu_set_quaternion_period(IMU *imu, uint32_t period);

/**
 * \ingroup BrickIMU
 *
 * Returns the period as set by {@link imu_set_quaternion_period}.
 */
int imu_get_quaternion_period(IMU *imu, uint32_t *ret_period);

/**
 * \ingroup BrickIMU
 *
 * Turns the orientation calculation of the IMU Brick on.
 * 
 * As default the calculation is on.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Firmware)
 */
int imu_orientation_calculation_on(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Turns the orientation calculation of the IMU Brick off.
 * 
 * If the calculation is off, {@link imu_get_orientation} will return
 * the last calculated value until the calculation is turned on again.
 * 
 * The trigonometric functions that are needed to calculate the orientation 
 * are very expensive. We recommend to turn the orientation calculation
 * off if the orientation is not needed, to free calculation time for the
 * sensor fusion algorithm.
 * 
 * As default the calculation is on.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Firmware)
 */
int imu_orientation_calculation_off(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Returns *true* if the orientation calculation of the IMU Brick
 * is on, *false* otherwise.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Firmware)
 */
int imu_is_orientation_calculation_on(IMU *imu, bool *ret_orientation_calculation_on);

/**
 * \ingroup BrickIMU
 *
 * Enables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 * 
 * .. versionadded:: 2.3.1$nbsp;(Firmware)
 */
int imu_enable_status_led(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Disables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 * 
 * .. versionadded:: 2.3.1$nbsp;(Firmware)
 */
int imu_disable_status_led(IMU *imu);

/**
 * \ingroup BrickIMU
 *
 * Returns *true* if the status LED is enabled, *false* otherwise.
 * 
 * .. versionadded:: 2.3.1$nbsp;(Firmware)
 */
int imu_is_status_led_enabled(IMU *imu, bool *ret_enabled);

/**
 * \ingroup BrickIMU
 *
 * Returns the firmware and protocol version and the name of the Bricklet for a
 * given port.
 * 
 * This functions sole purpose is to allow automatic flashing of v1.x.y Bricklet
 * plugins.
 */
int imu_get_protocol1_bricklet_name(IMU *imu, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]);

/**
 * \ingroup BrickIMU
 *
 * Returns the temperature in °C/10 as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has an
 * accuracy of +-15%. Practically it is only useful as an indicator for
 * temperature changes.
 */
int imu_get_chip_temperature(IMU *imu, int16_t *ret_temperature);

/**
 * \ingroup BrickIMU
 *
 * Calling this function will reset the Brick. Calling this function
 * on a Brick inside of a stack will reset the whole stack.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int imu_reset(IMU *imu);

/**
 * \ingroup BrickIMU
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
int imu_get_identity(IMU *imu, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

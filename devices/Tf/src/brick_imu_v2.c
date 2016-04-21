/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "brick_imu_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AccelerationCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*MagneticFieldCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*AngularVelocityCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*TemperatureCallbackFunction)(int8_t, void *);

typedef void (*LinearAccelerationCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*GravityVectorCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*OrientationCallbackFunction)(int16_t, int16_t, int16_t, void *);

typedef void (*QuaternionCallbackFunction)(int16_t, int16_t, int16_t, int16_t, void *);

typedef void (*AllDataCallbackFunction)(int16_t[3], int16_t[3], int16_t[3], int16_t[3], int16_t[4], int16_t[3], int16_t[3], int8_t, uint8_t, void *);

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(push)
	#pragma pack(1)
	#define ATTRIBUTE_PACKED
#elif defined __GNUC__
	#ifdef _WIN32
		// workaround struct packing bug in GCC 4.7 on Windows
		// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=52991
		#define ATTRIBUTE_PACKED __attribute__((gcc_struct, packed))
	#else
		#define ATTRIBUTE_PACKED __attribute__((packed))
	#endif
#else
	#error unknown compiler, do not know how to enable struct packing
#endif

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAcceleration_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetAccelerationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagneticField_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetMagneticFieldResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAngularVelocity_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetAngularVelocityResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperature_;

typedef struct {
	PacketHeader header;
	int8_t temperature;
} ATTRIBUTE_PACKED GetTemperatureResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOrientation_;

typedef struct {
	PacketHeader header;
	int16_t heading;
	int16_t roll;
	int16_t pitch;
} ATTRIBUTE_PACKED GetOrientationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLinearAcceleration_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetLinearAccelerationResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGravityVector_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetGravityVectorResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQuaternion_;

typedef struct {
	PacketHeader header;
	int16_t w;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetQuaternionResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllData_;

typedef struct {
	PacketHeader header;
	int16_t acceleration[3];
	int16_t magnetic_field[3];
	int16_t angular_velocity[3];
	int16_t euler_angle[3];
	int16_t quaternion[4];
	int16_t linear_acceleration[3];
	int16_t gravity_vector[3];
	int8_t temperature;
	uint8_t calibration_status;
} ATTRIBUTE_PACKED GetAllDataResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LedsOn_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LedsOff_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED AreLedsOn_;

typedef struct {
	PacketHeader header;
	bool leds;
} ATTRIBUTE_PACKED AreLedsOnResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED SaveCalibration_;

typedef struct {
	PacketHeader header;
	bool calibration_done;
} ATTRIBUTE_PACKED SaveCalibrationResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAccelerationPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAccelerationPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetMagneticFieldPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagneticFieldPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetMagneticFieldPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAngularVelocityPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAngularVelocityPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAngularVelocityPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetTemperaturePeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperaturePeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetTemperaturePeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetOrientationPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOrientationPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetOrientationPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetLinearAccelerationPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLinearAccelerationPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetLinearAccelerationPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetGravityVectorPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGravityVectorPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetGravityVectorPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetQuaternionPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQuaternionPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetQuaternionPeriodResponse_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAllDataPeriod_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllDataPeriod_;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAllDataPeriodResponse_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED AccelerationCallback_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED MagneticFieldCallback_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED AngularVelocityCallback_;

typedef struct {
	PacketHeader header;
	int8_t temperature;
} ATTRIBUTE_PACKED TemperatureCallback_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED LinearAccelerationCallback_;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GravityVectorCallback_;

typedef struct {
	PacketHeader header;
	int16_t heading;
	int16_t roll;
	int16_t pitch;
} ATTRIBUTE_PACKED OrientationCallback_;

typedef struct {
	PacketHeader header;
	int16_t w;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED QuaternionCallback_;

typedef struct {
	PacketHeader header;
	int16_t acceleration[3];
	int16_t magnetic_field[3];
	int16_t angular_velocity[3];
	int16_t euler_angle[3];
	int16_t quaternion[4];
	int16_t linear_acceleration[3];
	int16_t gravity_vector[3];
	int8_t temperature;
	uint8_t calibration_status;
} ATTRIBUTE_PACKED AllDataCallback_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableStatusLED_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableStatusLED_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_;

typedef struct {
	PacketHeader header;
	bool enabled;
} ATTRIBUTE_PACKED IsStatusLEDEnabledResponse_;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetProtocol1BrickletName_;

typedef struct {
	PacketHeader header;
	uint8_t protocol_version;
	uint8_t firmware_version[3];
	char name[40];
} ATTRIBUTE_PACKED GetProtocol1BrickletNameResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperatureResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Reset_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIdentity_;

typedef struct {
	PacketHeader header;
	char uid[8];
	char connected_uid[8];
	char position;
	uint8_t hardware_version[3];
	uint8_t firmware_version[3];
	uint16_t device_identifier;
} ATTRIBUTE_PACKED GetIdentityResponse_;

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(pop)
#endif
#undef ATTRIBUTE_PACKED

static void imu_v2_callback_wrapper_acceleration(DevicePrivate *device_p, Packet *packet) {
	AccelerationCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_ACCELERATION];
	AccelerationCallback_ *callback = (AccelerationCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_ACCELERATION];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v2_callback_wrapper_magnetic_field(DevicePrivate *device_p, Packet *packet) {
	MagneticFieldCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_MAGNETIC_FIELD];
	MagneticFieldCallback_ *callback = (MagneticFieldCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_MAGNETIC_FIELD];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v2_callback_wrapper_angular_velocity(DevicePrivate *device_p, Packet *packet) {
	AngularVelocityCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_ANGULAR_VELOCITY];
	AngularVelocityCallback_ *callback = (AngularVelocityCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_ANGULAR_VELOCITY];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v2_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	TemperatureCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_TEMPERATURE];
	TemperatureCallback_ *callback = (TemperatureCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_TEMPERATURE];

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->temperature, user_data);
}

static void imu_v2_callback_wrapper_linear_acceleration(DevicePrivate *device_p, Packet *packet) {
	LinearAccelerationCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_LINEAR_ACCELERATION];
	LinearAccelerationCallback_ *callback = (LinearAccelerationCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_LINEAR_ACCELERATION];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v2_callback_wrapper_gravity_vector(DevicePrivate *device_p, Packet *packet) {
	GravityVectorCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_GRAVITY_VECTOR];
	GravityVectorCallback_ *callback = (GravityVectorCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_GRAVITY_VECTOR];

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v2_callback_wrapper_orientation(DevicePrivate *device_p, Packet *packet) {
	OrientationCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_ORIENTATION];
	OrientationCallback_ *callback = (OrientationCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_ORIENTATION];

	if (callback_function == NULL) {
		return;
	}

	callback->heading = leconvert_int16_from(callback->heading);
	callback->roll = leconvert_int16_from(callback->roll);
	callback->pitch = leconvert_int16_from(callback->pitch);

	callback_function(callback->heading, callback->roll, callback->pitch, user_data);
}

static void imu_v2_callback_wrapper_quaternion(DevicePrivate *device_p, Packet *packet) {
	QuaternionCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_QUATERNION];
	QuaternionCallback_ *callback = (QuaternionCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_QUATERNION];

	if (callback_function == NULL) {
		return;
	}

	callback->w = leconvert_int16_from(callback->w);
	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->w, callback->x, callback->y, callback->z, user_data);
}

static void imu_v2_callback_wrapper_all_data(DevicePrivate *device_p, Packet *packet) {
	AllDataCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[IMU_V2_CALLBACK_ALL_DATA];
	int i;
	AllDataCallback_ *callback = (AllDataCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[IMU_V2_CALLBACK_ALL_DATA];

	if (callback_function == NULL) {
		return;
	}

	for (i = 0; i < 3; i++) callback->acceleration[i] = leconvert_int16_from(callback->acceleration[i]);
	for (i = 0; i < 3; i++) callback->magnetic_field[i] = leconvert_int16_from(callback->magnetic_field[i]);
	for (i = 0; i < 3; i++) callback->angular_velocity[i] = leconvert_int16_from(callback->angular_velocity[i]);
	for (i = 0; i < 3; i++) callback->euler_angle[i] = leconvert_int16_from(callback->euler_angle[i]);
	for (i = 0; i < 4; i++) callback->quaternion[i] = leconvert_int16_from(callback->quaternion[i]);
	for (i = 0; i < 3; i++) callback->linear_acceleration[i] = leconvert_int16_from(callback->linear_acceleration[i]);
	for (i = 0; i < 3; i++) callback->gravity_vector[i] = leconvert_int16_from(callback->gravity_vector[i]);

	callback_function(callback->acceleration, callback->magnetic_field, callback->angular_velocity, callback->euler_angle, callback->quaternion, callback->linear_acceleration, callback->gravity_vector, callback->temperature, callback->calibration_status, user_data);
}

void imu_v2_create(IMUV2 *imu_v2, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(imu_v2, uid, ipcon->p, 2, 0, 0);

	device_p = imu_v2->p;

	device_p->response_expected[IMU_V2_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_MAGNETIC_FIELD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ANGULAR_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ORIENTATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_LINEAR_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_GRAVITY_VECTOR] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_QUATERNION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ALL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_LEDS_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V2_FUNCTION_LEDS_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V2_FUNCTION_ARE_LEDS_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SAVE_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_ACCELERATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ACCELERATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_MAGNETIC_FIELD_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_MAGNETIC_FIELD_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_ANGULAR_VELOCITY_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ANGULAR_VELOCITY_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_TEMPERATURE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_TEMPERATURE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_ORIENTATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ORIENTATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_LINEAR_ACCELERATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_LINEAR_ACCELERATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_GRAVITY_VECTOR_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_GRAVITY_VECTOR_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_QUATERNION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_QUATERNION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_SET_ALL_DATA_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_ALL_DATA_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_CALLBACK_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_MAGNETIC_FIELD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_ANGULAR_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_LINEAR_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_GRAVITY_VECTOR] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_ORIENTATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_QUATERNION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_CALLBACK_ALL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[IMU_V2_FUNCTION_ENABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V2_FUNCTION_DISABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V2_FUNCTION_IS_STATUS_LED_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[IMU_V2_CALLBACK_ACCELERATION] = imu_v2_callback_wrapper_acceleration;
	device_p->callback_wrappers[IMU_V2_CALLBACK_MAGNETIC_FIELD] = imu_v2_callback_wrapper_magnetic_field;
	device_p->callback_wrappers[IMU_V2_CALLBACK_ANGULAR_VELOCITY] = imu_v2_callback_wrapper_angular_velocity;
	device_p->callback_wrappers[IMU_V2_CALLBACK_TEMPERATURE] = imu_v2_callback_wrapper_temperature;
	device_p->callback_wrappers[IMU_V2_CALLBACK_LINEAR_ACCELERATION] = imu_v2_callback_wrapper_linear_acceleration;
	device_p->callback_wrappers[IMU_V2_CALLBACK_GRAVITY_VECTOR] = imu_v2_callback_wrapper_gravity_vector;
	device_p->callback_wrappers[IMU_V2_CALLBACK_ORIENTATION] = imu_v2_callback_wrapper_orientation;
	device_p->callback_wrappers[IMU_V2_CALLBACK_QUATERNION] = imu_v2_callback_wrapper_quaternion;
	device_p->callback_wrappers[IMU_V2_CALLBACK_ALL_DATA] = imu_v2_callback_wrapper_all_data;
}

void imu_v2_destroy(IMUV2 *imu_v2) {
	device_release(imu_v2->p);
}

int imu_v2_get_response_expected(IMUV2 *imu_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(imu_v2->p, function_id, ret_response_expected);
}

int imu_v2_set_response_expected(IMUV2 *imu_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(imu_v2->p, function_id, response_expected);
}

int imu_v2_set_response_expected_all(IMUV2 *imu_v2, bool response_expected) {
	return device_set_response_expected_all(imu_v2->p, response_expected);
}

void imu_v2_register_callback(IMUV2 *imu_v2, uint8_t id, void *callback, void *user_data) {
	device_register_callback(imu_v2->p, id, callback, user_data);
}

int imu_v2_get_api_version(IMUV2 *imu_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(imu_v2->p, ret_api_version);
}

int imu_v2_get_acceleration(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v2->p;
	GetAcceleration_ request;
	GetAccelerationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int imu_v2_get_magnetic_field(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v2->p;
	GetMagneticField_ request;
	GetMagneticFieldResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_MAGNETIC_FIELD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int imu_v2_get_angular_velocity(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v2->p;
	GetAngularVelocity_ request;
	GetAngularVelocityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ANGULAR_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int imu_v2_get_temperature(IMUV2 *imu_v2, int8_t *ret_temperature) {
	DevicePrivate *device_p = imu_v2->p;
	GetTemperature_ request;
	GetTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_temperature = response.temperature;



	return ret;
}

int imu_v2_get_orientation(IMUV2 *imu_v2, int16_t *ret_heading, int16_t *ret_roll, int16_t *ret_pitch) {
	DevicePrivate *device_p = imu_v2->p;
	GetOrientation_ request;
	GetOrientationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ORIENTATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_heading = leconvert_int16_from(response.heading);
	*ret_roll = leconvert_int16_from(response.roll);
	*ret_pitch = leconvert_int16_from(response.pitch);



	return ret;
}

int imu_v2_get_linear_acceleration(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v2->p;
	GetLinearAcceleration_ request;
	GetLinearAccelerationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_LINEAR_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int imu_v2_get_gravity_vector(IMUV2 *imu_v2, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v2->p;
	GetGravityVector_ request;
	GetGravityVectorResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_GRAVITY_VECTOR, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int imu_v2_get_quaternion(IMUV2 *imu_v2, int16_t *ret_w, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v2->p;
	GetQuaternion_ request;
	GetQuaternionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_QUATERNION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_w = leconvert_int16_from(response.w);
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);



	return ret;
}

int imu_v2_get_all_data(IMUV2 *imu_v2, int16_t ret_acceleration[3], int16_t ret_magnetic_field[3], int16_t ret_angular_velocity[3], int16_t ret_euler_angle[3], int16_t ret_quaternion[4], int16_t ret_linear_acceleration[3], int16_t ret_gravity_vector[3], int8_t *ret_temperature, uint8_t *ret_calibration_status) {
	DevicePrivate *device_p = imu_v2->p;
	GetAllData_ request;
	GetAllDataResponse_ response;
	int ret;
	int i;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ALL_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	for (i = 0; i < 3; i++) ret_acceleration[i] = leconvert_int16_from(response.acceleration[i]);
	for (i = 0; i < 3; i++) ret_magnetic_field[i] = leconvert_int16_from(response.magnetic_field[i]);
	for (i = 0; i < 3; i++) ret_angular_velocity[i] = leconvert_int16_from(response.angular_velocity[i]);
	for (i = 0; i < 3; i++) ret_euler_angle[i] = leconvert_int16_from(response.euler_angle[i]);
	for (i = 0; i < 4; i++) ret_quaternion[i] = leconvert_int16_from(response.quaternion[i]);
	for (i = 0; i < 3; i++) ret_linear_acceleration[i] = leconvert_int16_from(response.linear_acceleration[i]);
	for (i = 0; i < 3; i++) ret_gravity_vector[i] = leconvert_int16_from(response.gravity_vector[i]);
	*ret_temperature = response.temperature;
	*ret_calibration_status = response.calibration_status;



	return ret;
}

int imu_v2_leds_on(IMUV2 *imu_v2) {
	DevicePrivate *device_p = imu_v2->p;
	LedsOn_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_LEDS_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_leds_off(IMUV2 *imu_v2) {
	DevicePrivate *device_p = imu_v2->p;
	LedsOff_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_LEDS_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_are_leds_on(IMUV2 *imu_v2, bool *ret_leds) {
	DevicePrivate *device_p = imu_v2->p;
	AreLedsOn_ request;
	AreLedsOnResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_ARE_LEDS_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_leds = response.leds;



	return ret;
}

int imu_v2_save_calibration(IMUV2 *imu_v2, bool *ret_calibration_done) {
	DevicePrivate *device_p = imu_v2->p;
	SaveCalibration_ request;
	SaveCalibrationResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SAVE_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_calibration_done = response.calibration_done;



	return ret;
}

int imu_v2_set_acceleration_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetAccelerationPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_ACCELERATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_acceleration_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetAccelerationPeriod_ request;
	GetAccelerationPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ACCELERATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_magnetic_field_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetMagneticFieldPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_MAGNETIC_FIELD_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_magnetic_field_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetMagneticFieldPeriod_ request;
	GetMagneticFieldPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_MAGNETIC_FIELD_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_angular_velocity_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetAngularVelocityPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_ANGULAR_VELOCITY_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_angular_velocity_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetAngularVelocityPeriod_ request;
	GetAngularVelocityPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ANGULAR_VELOCITY_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_temperature_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetTemperaturePeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_TEMPERATURE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_temperature_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetTemperaturePeriod_ request;
	GetTemperaturePeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_TEMPERATURE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_orientation_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetOrientationPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_ORIENTATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_orientation_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetOrientationPeriod_ request;
	GetOrientationPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ORIENTATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_linear_acceleration_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetLinearAccelerationPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_LINEAR_ACCELERATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_linear_acceleration_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetLinearAccelerationPeriod_ request;
	GetLinearAccelerationPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_LINEAR_ACCELERATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_gravity_vector_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetGravityVectorPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_GRAVITY_VECTOR_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_gravity_vector_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetGravityVectorPeriod_ request;
	GetGravityVectorPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_GRAVITY_VECTOR_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_quaternion_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetQuaternionPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_QUATERNION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_quaternion_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetQuaternionPeriod_ request;
	GetQuaternionPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_QUATERNION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_set_all_data_period(IMUV2 *imu_v2, uint32_t period) {
	DevicePrivate *device_p = imu_v2->p;
	SetAllDataPeriod_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_SET_ALL_DATA_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_all_data_period(IMUV2 *imu_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = imu_v2->p;
	GetAllDataPeriod_ request;
	GetAllDataPeriodResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_ALL_DATA_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_period = leconvert_uint32_from(response.period);



	return ret;
}

int imu_v2_enable_status_led(IMUV2 *imu_v2) {
	DevicePrivate *device_p = imu_v2->p;
	EnableStatusLED_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_ENABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_disable_status_led(IMUV2 *imu_v2) {
	DevicePrivate *device_p = imu_v2->p;
	DisableStatusLED_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_DISABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_is_status_led_enabled(IMUV2 *imu_v2, bool *ret_enabled) {
	DevicePrivate *device_p = imu_v2->p;
	IsStatusLEDEnabled_ request;
	IsStatusLEDEnabledResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_IS_STATUS_LED_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_enabled = response.enabled;



	return ret;
}

int imu_v2_get_protocol1_bricklet_name(IMUV2 *imu_v2, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]) {
	DevicePrivate *device_p = imu_v2->p;
	GetProtocol1BrickletName_ request;
	GetProtocol1BrickletNameResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_protocol_version = response.protocol_version;
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	strncpy(ret_name, response.name, 40);



	return ret;
}

int imu_v2_get_chip_temperature(IMUV2 *imu_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = imu_v2->p;
	GetChipTemperature_ request;
	GetChipTemperatureResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_temperature = leconvert_int16_from(response.temperature);



	return ret;
}

int imu_v2_reset(IMUV2 *imu_v2) {
	DevicePrivate *device_p = imu_v2->p;
	Reset_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int imu_v2_get_identity(IMUV2 *imu_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = imu_v2->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	strncpy(ret_uid, response.uid, 8);
	strncpy(ret_connected_uid, response.connected_uid, 8);
	*ret_position = response.position;
	memcpy(ret_hardware_version, response.hardware_version, 3 * sizeof(uint8_t));
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	*ret_device_identifier = leconvert_uint16_from(response.device_identifier);



	return ret;
}

#ifdef __cplusplus
}
#endif

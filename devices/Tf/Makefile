#
# Makefile
#
# Makefile for macchina.io Tinkerforge Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = \
	MasterConnection \
	MasterConnectionImpl \
	TemperatureSensor \
	HumiditySensor \
	AmbientLightSensor \
	AirPressureSensor \
	RotaryEncoder \
	MotionDetector \
	GNSSSensor \
	DCMotor \
	BundleActivator \
	brick_dc \
	brick_imu \
	brick_master \
	brick_servo \
	brick_stepper \
	bricklet_ambient_light \
	bricklet_analog_in \
	bricklet_analog_out \
	bricklet_barometer \
	bricklet_current12 \
	bricklet_current25 \
	bricklet_distance_ir \
	bricklet_distance_us \
	bricklet_dual_button \
	bricklet_dual_relay \
	bricklet_gps \
	bricklet_hall_effect \
	bricklet_humidity \
	bricklet_industrial_digital_in_4 \
	bricklet_industrial_digital_out_4 \
	bricklet_industrial_dual_0_20ma \
	bricklet_industrial_quad_relay \
	bricklet_io16 \
	bricklet_io4 \
	bricklet_joystick \
	bricklet_lcd_16x2 \
	bricklet_lcd_20x4 \
	bricklet_led_strip \
	bricklet_line \
	bricklet_linear_poti \
	bricklet_moisture \
	bricklet_motion_detector \
	bricklet_multi_touch \
	bricklet_piezo_buzzer \
	bricklet_piezo_speaker \
	bricklet_ptc \
	bricklet_remote_switch \
	bricklet_rotary_encoder \
	bricklet_rotary_poti \
	bricklet_segment_display_4x7 \
	bricklet_sound_intensity \
	bricklet_temperature \
	bricklet_temperature_ir \
	bricklet_tilt \
	bricklet_voltage \
	bricklet_voltage_current \
	ip_connection

target          = io.macchina.tf
target_includes = $(PROJECT_BASE)/devices/Devices/include
target_libs     = IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Tf.bndlspec

include $(POCO_BASE)/build/rules/dylib

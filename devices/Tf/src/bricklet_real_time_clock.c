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

#include "bricklet_real_time_clock.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



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
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t centisecond;
	uint8_t weekday;
} ATTRIBUTE_PACKED SetDateTime_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDateTime_;

typedef struct {
	PacketHeader header;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t centisecond;
	uint8_t weekday;
} ATTRIBUTE_PACKED GetDateTimeResponse_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTimestamp_;

typedef struct {
	PacketHeader header;
	int64_t timestamp;
} ATTRIBUTE_PACKED GetTimestampResponse_;

typedef struct {
	PacketHeader header;
	int8_t offset;
} ATTRIBUTE_PACKED SetOffset_;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOffset_;

typedef struct {
	PacketHeader header;
	int8_t offset;
} ATTRIBUTE_PACKED GetOffsetResponse_;

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

void real_time_clock_create(RealTimeClock *real_time_clock, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(real_time_clock, uid, ipcon->p, 2, 0, 0);

	device_p = real_time_clock->p;

	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_TIMESTAMP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_SET_OFFSET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_OFFSET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

}

void real_time_clock_destroy(RealTimeClock *real_time_clock) {
	device_release(real_time_clock->p);
}

int real_time_clock_get_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(real_time_clock->p, function_id, ret_response_expected);
}

int real_time_clock_set_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(real_time_clock->p, function_id, response_expected);
}

int real_time_clock_set_response_expected_all(RealTimeClock *real_time_clock, bool response_expected) {
	return device_set_response_expected_all(real_time_clock->p, response_expected);
}

void real_time_clock_register_callback(RealTimeClock *real_time_clock, uint8_t id, void *callback, void *user_data) {
	device_register_callback(real_time_clock->p, id, callback, user_data);
}

int real_time_clock_get_api_version(RealTimeClock *real_time_clock, uint8_t ret_api_version[3]) {
	return device_get_api_version(real_time_clock->p, ret_api_version);
}

int real_time_clock_set_date_time(RealTimeClock *real_time_clock, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday) {
	DevicePrivate *device_p = real_time_clock->p;
	SetDateTime_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.year = leconvert_uint16_to(year);
	request.month = month;
	request.day = day;
	request.hour = hour;
	request.minute = minute;
	request.second = second;
	request.centisecond = centisecond;
	request.weekday = weekday;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int real_time_clock_get_date_time(RealTimeClock *real_time_clock, uint16_t *ret_year, uint8_t *ret_month, uint8_t *ret_day, uint8_t *ret_hour, uint8_t *ret_minute, uint8_t *ret_second, uint8_t *ret_centisecond, uint8_t *ret_weekday) {
	DevicePrivate *device_p = real_time_clock->p;
	GetDateTime_ request;
	GetDateTimeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_year = leconvert_uint16_from(response.year);
	*ret_month = response.month;
	*ret_day = response.day;
	*ret_hour = response.hour;
	*ret_minute = response.minute;
	*ret_second = response.second;
	*ret_centisecond = response.centisecond;
	*ret_weekday = response.weekday;



	return ret;
}

int real_time_clock_get_timestamp(RealTimeClock *real_time_clock, int64_t *ret_timestamp) {
	DevicePrivate *device_p = real_time_clock->p;
	GetTimestamp_ request;
	GetTimestampResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_TIMESTAMP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_timestamp = leconvert_int64_from(response.timestamp);



	return ret;
}

int real_time_clock_set_offset(RealTimeClock *real_time_clock, int8_t offset) {
	DevicePrivate *device_p = real_time_clock->p;
	SetOffset_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_SET_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.offset = offset;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int real_time_clock_get_offset(RealTimeClock *real_time_clock, int8_t *ret_offset) {
	DevicePrivate *device_p = real_time_clock->p;
	GetOffset_ request;
	GetOffsetResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_offset = response.offset;



	return ret;
}

int real_time_clock_get_identity(RealTimeClock *real_time_clock, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = real_time_clock->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

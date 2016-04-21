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

#include "brick_red.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AsyncFileReadCallbackFunction)(uint16_t, uint8_t, uint8_t[60], uint8_t, void *);

typedef void (*AsyncFileWriteCallbackFunction)(uint16_t, uint8_t, uint8_t, void *);

typedef void (*FileEventsOccurredCallbackFunction)(uint16_t, uint16_t, void *);

typedef void (*ProcessStateChangedCallbackFunction)(uint16_t, uint8_t, uint64_t, uint8_t, void *);

typedef void (*ProgramSchedulerStateChangedCallbackFunction)(uint16_t, void *);

typedef void (*ProgramProcessSpawnedCallbackFunction)(uint16_t, void *);

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
	uint32_t lifetime;
} ATTRIBUTE_PACKED CreateSession_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t session_id;
} ATTRIBUTE_PACKED CreateSessionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t session_id;
} ATTRIBUTE_PACKED ExpireSession_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED ExpireSessionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t session_id;
} ATTRIBUTE_PACKED ExpireSessionUnchecked_;

typedef struct {
	PacketHeader header;
	uint16_t session_id;
	uint32_t lifetime;
} ATTRIBUTE_PACKED KeepSessionAlive_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED KeepSessionAliveResponse_;

typedef struct {
	PacketHeader header;
	uint16_t object_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED ReleaseObject_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED ReleaseObjectResponse_;

typedef struct {
	PacketHeader header;
	uint16_t object_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED ReleaseObjectUnchecked_;

typedef struct {
	PacketHeader header;
	uint32_t length_to_reserve;
	char buffer[58];
	uint16_t session_id;
} ATTRIBUTE_PACKED AllocateString_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t string_id;
} ATTRIBUTE_PACKED AllocateStringResponse_;

typedef struct {
	PacketHeader header;
	uint16_t string_id;
	uint32_t length;
} ATTRIBUTE_PACKED TruncateString_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED TruncateStringResponse_;

typedef struct {
	PacketHeader header;
	uint16_t string_id;
} ATTRIBUTE_PACKED GetStringLength_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint32_t length;
} ATTRIBUTE_PACKED GetStringLengthResponse_;

typedef struct {
	PacketHeader header;
	uint16_t string_id;
	uint32_t offset;
	char buffer[58];
} ATTRIBUTE_PACKED SetStringChunk_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED SetStringChunkResponse_;

typedef struct {
	PacketHeader header;
	uint16_t string_id;
	uint32_t offset;
} ATTRIBUTE_PACKED GetStringChunk_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	char buffer[63];
} ATTRIBUTE_PACKED GetStringChunkResponse_;

typedef struct {
	PacketHeader header;
	uint16_t length_to_reserve;
	uint16_t session_id;
} ATTRIBUTE_PACKED AllocateList_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t list_id;
} ATTRIBUTE_PACKED AllocateListResponse_;

typedef struct {
	PacketHeader header;
	uint16_t list_id;
} ATTRIBUTE_PACKED GetListLength_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t length;
} ATTRIBUTE_PACKED GetListLengthResponse_;

typedef struct {
	PacketHeader header;
	uint16_t list_id;
	uint16_t index;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetListItem_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t item_object_id;
	uint8_t type;
} ATTRIBUTE_PACKED GetListItemResponse_;

typedef struct {
	PacketHeader header;
	uint16_t list_id;
	uint16_t item_object_id;
} ATTRIBUTE_PACKED AppendToList_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED AppendToListResponse_;

typedef struct {
	PacketHeader header;
	uint16_t list_id;
	uint16_t index;
} ATTRIBUTE_PACKED RemoveFromList_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED RemoveFromListResponse_;

typedef struct {
	PacketHeader header;
	uint16_t name_string_id;
	uint32_t flags;
	uint16_t permissions;
	uint32_t uid;
	uint32_t gid;
	uint16_t session_id;
} ATTRIBUTE_PACKED OpenFile_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t file_id;
} ATTRIBUTE_PACKED OpenFileResponse_;

typedef struct {
	PacketHeader header;
	uint32_t flags;
	uint64_t length;
	uint16_t session_id;
} ATTRIBUTE_PACKED CreatePipe_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t file_id;
} ATTRIBUTE_PACKED CreatePipeResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetFileInfo_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t type;
	uint16_t name_string_id;
	uint32_t flags;
	uint16_t permissions;
	uint32_t uid;
	uint32_t gid;
	uint64_t length;
	uint64_t access_timestamp;
	uint64_t modification_timestamp;
	uint64_t status_change_timestamp;
} ATTRIBUTE_PACKED GetFileInfoResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint8_t length_to_read;
} ATTRIBUTE_PACKED ReadFile_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t buffer[62];
	uint8_t length_read;
} ATTRIBUTE_PACKED ReadFileResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint64_t length_to_read;
} ATTRIBUTE_PACKED ReadFileAsync_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
} ATTRIBUTE_PACKED AbortAsyncFileRead_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED AbortAsyncFileReadResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint8_t buffer[61];
	uint8_t length_to_write;
} ATTRIBUTE_PACKED WriteFile_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t length_written;
} ATTRIBUTE_PACKED WriteFileResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint8_t buffer[61];
	uint8_t length_to_write;
} ATTRIBUTE_PACKED WriteFileUnchecked_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint8_t buffer[61];
	uint8_t length_to_write;
} ATTRIBUTE_PACKED WriteFileAsync_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	int64_t offset;
	uint8_t origin;
} ATTRIBUTE_PACKED SetFilePosition_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint64_t position;
} ATTRIBUTE_PACKED SetFilePositionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
} ATTRIBUTE_PACKED GetFilePosition_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint64_t position;
} ATTRIBUTE_PACKED GetFilePositionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint16_t events;
} ATTRIBUTE_PACKED SetFileEvents_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED SetFileEventsResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
} ATTRIBUTE_PACKED GetFileEvents_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t events;
} ATTRIBUTE_PACKED GetFileEventsResponse_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint8_t error_code;
	uint8_t buffer[60];
	uint8_t length_read;
} ATTRIBUTE_PACKED AsyncFileReadCallback_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint8_t error_code;
	uint8_t length_written;
} ATTRIBUTE_PACKED AsyncFileWriteCallback_;

typedef struct {
	PacketHeader header;
	uint16_t file_id;
	uint16_t events;
} ATTRIBUTE_PACKED FileEventsOccurredCallback_;

typedef struct {
	PacketHeader header;
	uint16_t name_string_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED OpenDirectory_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t directory_id;
} ATTRIBUTE_PACKED OpenDirectoryResponse_;

typedef struct {
	PacketHeader header;
	uint16_t directory_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetDirectoryName_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t name_string_id;
} ATTRIBUTE_PACKED GetDirectoryNameResponse_;

typedef struct {
	PacketHeader header;
	uint16_t directory_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetNextDirectoryEntry_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t name_string_id;
	uint8_t type;
} ATTRIBUTE_PACKED GetNextDirectoryEntryResponse_;

typedef struct {
	PacketHeader header;
	uint16_t directory_id;
} ATTRIBUTE_PACKED RewindDirectory_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED RewindDirectoryResponse_;

typedef struct {
	PacketHeader header;
	uint16_t name_string_id;
	uint32_t flags;
	uint16_t permissions;
	uint32_t uid;
	uint32_t gid;
} ATTRIBUTE_PACKED CreateDirectory_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED CreateDirectoryResponse_;

typedef struct {
	PacketHeader header;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProcesses_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t processes_list_id;
} ATTRIBUTE_PACKED GetProcessesResponse_;

typedef struct {
	PacketHeader header;
	uint16_t executable_string_id;
	uint16_t arguments_list_id;
	uint16_t environment_list_id;
	uint16_t working_directory_string_id;
	uint32_t uid;
	uint32_t gid;
	uint16_t stdin_file_id;
	uint16_t stdout_file_id;
	uint16_t stderr_file_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED SpawnProcess_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t process_id;
} ATTRIBUTE_PACKED SpawnProcessResponse_;

typedef struct {
	PacketHeader header;
	uint16_t process_id;
	uint8_t signal;
} ATTRIBUTE_PACKED KillProcess_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED KillProcessResponse_;

typedef struct {
	PacketHeader header;
	uint16_t process_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProcessCommand_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t executable_string_id;
	uint16_t arguments_list_id;
	uint16_t environment_list_id;
	uint16_t working_directory_string_id;
} ATTRIBUTE_PACKED GetProcessCommandResponse_;

typedef struct {
	PacketHeader header;
	uint16_t process_id;
} ATTRIBUTE_PACKED GetProcessIdentity_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint32_t pid;
	uint32_t uid;
	uint32_t gid;
} ATTRIBUTE_PACKED GetProcessIdentityResponse_;

typedef struct {
	PacketHeader header;
	uint16_t process_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProcessStdio_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t stdin_file_id;
	uint16_t stdout_file_id;
	uint16_t stderr_file_id;
} ATTRIBUTE_PACKED GetProcessStdioResponse_;

typedef struct {
	PacketHeader header;
	uint16_t process_id;
} ATTRIBUTE_PACKED GetProcessState_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t state;
	uint64_t timestamp;
	uint8_t exit_code;
} ATTRIBUTE_PACKED GetProcessStateResponse_;

typedef struct {
	PacketHeader header;
	uint16_t process_id;
	uint8_t state;
	uint64_t timestamp;
	uint8_t exit_code;
} ATTRIBUTE_PACKED ProcessStateChangedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetPrograms_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t programs_list_id;
} ATTRIBUTE_PACKED GetProgramsResponse_;

typedef struct {
	PacketHeader header;
	uint16_t identifier_string_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED DefineProgram_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t program_id;
} ATTRIBUTE_PACKED DefineProgramResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint32_t cookie;
} ATTRIBUTE_PACKED PurgeProgram_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED PurgeProgramResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProgramIdentifier_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t identifier_string_id;
} ATTRIBUTE_PACKED GetProgramIdentifierResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProgramRootDirectory_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t root_directory_string_id;
} ATTRIBUTE_PACKED GetProgramRootDirectoryResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t executable_string_id;
	uint16_t arguments_list_id;
	uint16_t environment_list_id;
	uint16_t working_directory_string_id;
} ATTRIBUTE_PACKED SetProgramCommand_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED SetProgramCommandResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProgramCommand_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t executable_string_id;
	uint16_t arguments_list_id;
	uint16_t environment_list_id;
	uint16_t working_directory_string_id;
} ATTRIBUTE_PACKED GetProgramCommandResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint8_t stdin_redirection;
	uint16_t stdin_file_name_string_id;
	uint8_t stdout_redirection;
	uint16_t stdout_file_name_string_id;
	uint8_t stderr_redirection;
	uint16_t stderr_file_name_string_id;
} ATTRIBUTE_PACKED SetProgramStdioRedirection_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED SetProgramStdioRedirectionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProgramStdioRedirection_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t stdin_redirection;
	uint16_t stdin_file_name_string_id;
	uint8_t stdout_redirection;
	uint16_t stdout_file_name_string_id;
	uint8_t stderr_redirection;
	uint16_t stderr_file_name_string_id;
} ATTRIBUTE_PACKED GetProgramStdioRedirectionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint8_t start_mode;
	bool continue_after_error;
	uint32_t start_interval;
	uint16_t start_fields_string_id;
} ATTRIBUTE_PACKED SetProgramSchedule_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED SetProgramScheduleResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProgramSchedule_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t start_mode;
	bool continue_after_error;
	uint32_t start_interval;
	uint16_t start_fields_string_id;
} ATTRIBUTE_PACKED GetProgramScheduleResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetProgramSchedulerState_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint8_t state;
	uint64_t timestamp;
	uint16_t message_string_id;
} ATTRIBUTE_PACKED GetProgramSchedulerStateResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
} ATTRIBUTE_PACKED ContinueProgramSchedule_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED ContinueProgramScheduleResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
} ATTRIBUTE_PACKED StartProgram_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED StartProgramResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetLastSpawnedProgramProcess_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t process_id;
	uint64_t timestamp;
} ATTRIBUTE_PACKED GetLastSpawnedProgramProcessResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetCustomProgramOptionNames_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t names_list_id;
} ATTRIBUTE_PACKED GetCustomProgramOptionNamesResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t name_string_id;
	uint16_t value_string_id;
} ATTRIBUTE_PACKED SetCustomProgramOptionValue_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED SetCustomProgramOptionValueResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t name_string_id;
	uint16_t session_id;
} ATTRIBUTE_PACKED GetCustomProgramOptionValue_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
	uint16_t value_string_id;
} ATTRIBUTE_PACKED GetCustomProgramOptionValueResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
	uint16_t name_string_id;
} ATTRIBUTE_PACKED RemoveCustomProgramOption_;

typedef struct {
	PacketHeader header;
	uint8_t error_code;
} ATTRIBUTE_PACKED RemoveCustomProgramOptionResponse_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
} ATTRIBUTE_PACKED ProgramSchedulerStateChangedCallback_;

typedef struct {
	PacketHeader header;
	uint16_t program_id;
} ATTRIBUTE_PACKED ProgramProcessSpawnedCallback_;

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

static void red_callback_wrapper_async_file_read(DevicePrivate *device_p, Packet *packet) {
	AsyncFileReadCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RED_CALLBACK_ASYNC_FILE_READ];
	AsyncFileReadCallback_ *callback = (AsyncFileReadCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RED_CALLBACK_ASYNC_FILE_READ];

	if (callback_function == NULL) {
		return;
	}

	callback->file_id = leconvert_uint16_from(callback->file_id);

	callback_function(callback->file_id, callback->error_code, callback->buffer, callback->length_read, user_data);
}

static void red_callback_wrapper_async_file_write(DevicePrivate *device_p, Packet *packet) {
	AsyncFileWriteCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RED_CALLBACK_ASYNC_FILE_WRITE];
	AsyncFileWriteCallback_ *callback = (AsyncFileWriteCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RED_CALLBACK_ASYNC_FILE_WRITE];

	if (callback_function == NULL) {
		return;
	}

	callback->file_id = leconvert_uint16_from(callback->file_id);

	callback_function(callback->file_id, callback->error_code, callback->length_written, user_data);
}

static void red_callback_wrapper_file_events_occurred(DevicePrivate *device_p, Packet *packet) {
	FileEventsOccurredCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RED_CALLBACK_FILE_EVENTS_OCCURRED];
	FileEventsOccurredCallback_ *callback = (FileEventsOccurredCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RED_CALLBACK_FILE_EVENTS_OCCURRED];

	if (callback_function == NULL) {
		return;
	}

	callback->file_id = leconvert_uint16_from(callback->file_id);
	callback->events = leconvert_uint16_from(callback->events);

	callback_function(callback->file_id, callback->events, user_data);
}

static void red_callback_wrapper_process_state_changed(DevicePrivate *device_p, Packet *packet) {
	ProcessStateChangedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RED_CALLBACK_PROCESS_STATE_CHANGED];
	ProcessStateChangedCallback_ *callback = (ProcessStateChangedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RED_CALLBACK_PROCESS_STATE_CHANGED];

	if (callback_function == NULL) {
		return;
	}

	callback->process_id = leconvert_uint16_from(callback->process_id);
	callback->timestamp = leconvert_uint64_from(callback->timestamp);

	callback_function(callback->process_id, callback->state, callback->timestamp, callback->exit_code, user_data);
}

static void red_callback_wrapper_program_scheduler_state_changed(DevicePrivate *device_p, Packet *packet) {
	ProgramSchedulerStateChangedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RED_CALLBACK_PROGRAM_SCHEDULER_STATE_CHANGED];
	ProgramSchedulerStateChangedCallback_ *callback = (ProgramSchedulerStateChangedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RED_CALLBACK_PROGRAM_SCHEDULER_STATE_CHANGED];

	if (callback_function == NULL) {
		return;
	}

	callback->program_id = leconvert_uint16_from(callback->program_id);

	callback_function(callback->program_id, user_data);
}

static void red_callback_wrapper_program_process_spawned(DevicePrivate *device_p, Packet *packet) {
	ProgramProcessSpawnedCallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[RED_CALLBACK_PROGRAM_PROCESS_SPAWNED];
	ProgramProcessSpawnedCallback_ *callback = (ProgramProcessSpawnedCallback_ *)packet;
	*(void **)(&callback_function) = device_p->registered_callbacks[RED_CALLBACK_PROGRAM_PROCESS_SPAWNED];

	if (callback_function == NULL) {
		return;
	}

	callback->program_id = leconvert_uint16_from(callback->program_id);

	callback_function(callback->program_id, user_data);
}

void red_create(RED *red, const char *uid, IPConnection *ipcon) {
	DevicePrivate *device_p;

	device_create(red, uid, ipcon->p, 2, 0, 0);

	device_p = red->p;

	device_p->response_expected[RED_FUNCTION_CREATE_SESSION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_EXPIRE_SESSION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_EXPIRE_SESSION_UNCHECKED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RED_FUNCTION_KEEP_SESSION_ALIVE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_RELEASE_OBJECT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_RELEASE_OBJECT_UNCHECKED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RED_FUNCTION_ALLOCATE_STRING] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_TRUNCATE_STRING] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_STRING_LENGTH] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SET_STRING_CHUNK] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_STRING_CHUNK] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_ALLOCATE_LIST] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_LIST_LENGTH] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_LIST_ITEM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_APPEND_TO_LIST] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_REMOVE_FROM_LIST] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_OPEN_FILE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_CREATE_PIPE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_FILE_INFO] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_READ_FILE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_READ_FILE_ASYNC] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RED_FUNCTION_ABORT_ASYNC_FILE_READ] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_WRITE_FILE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_WRITE_FILE_UNCHECKED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RED_FUNCTION_WRITE_FILE_ASYNC] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RED_FUNCTION_SET_FILE_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_FILE_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SET_FILE_EVENTS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_FILE_EVENTS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_CALLBACK_ASYNC_FILE_READ] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RED_CALLBACK_ASYNC_FILE_WRITE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RED_CALLBACK_FILE_EVENTS_OCCURRED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RED_FUNCTION_OPEN_DIRECTORY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_DIRECTORY_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_NEXT_DIRECTORY_ENTRY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_REWIND_DIRECTORY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_CREATE_DIRECTORY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROCESSES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SPAWN_PROCESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_KILL_PROCESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROCESS_COMMAND] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROCESS_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROCESS_STDIO] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROCESS_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_CALLBACK_PROCESS_STATE_CHANGED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAMS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_DEFINE_PROGRAM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_PURGE_PROGRAM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAM_IDENTIFIER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAM_ROOT_DIRECTORY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SET_PROGRAM_COMMAND] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAM_COMMAND] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SET_PROGRAM_STDIO_REDIRECTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAM_STDIO_REDIRECTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SET_PROGRAM_SCHEDULE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAM_SCHEDULE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_PROGRAM_SCHEDULER_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_CONTINUE_PROGRAM_SCHEDULE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_START_PROGRAM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_LAST_SPAWNED_PROGRAM_PROCESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_CUSTOM_PROGRAM_OPTION_NAMES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_SET_CUSTOM_PROGRAM_OPTION_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_GET_CUSTOM_PROGRAM_OPTION_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_FUNCTION_REMOVE_CUSTOM_PROGRAM_OPTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RED_CALLBACK_PROGRAM_SCHEDULER_STATE_CHANGED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RED_CALLBACK_PROGRAM_PROCESS_SPAWNED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_FALSE;
	device_p->response_expected[RED_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[RED_CALLBACK_ASYNC_FILE_READ] = red_callback_wrapper_async_file_read;
	device_p->callback_wrappers[RED_CALLBACK_ASYNC_FILE_WRITE] = red_callback_wrapper_async_file_write;
	device_p->callback_wrappers[RED_CALLBACK_FILE_EVENTS_OCCURRED] = red_callback_wrapper_file_events_occurred;
	device_p->callback_wrappers[RED_CALLBACK_PROCESS_STATE_CHANGED] = red_callback_wrapper_process_state_changed;
	device_p->callback_wrappers[RED_CALLBACK_PROGRAM_SCHEDULER_STATE_CHANGED] = red_callback_wrapper_program_scheduler_state_changed;
	device_p->callback_wrappers[RED_CALLBACK_PROGRAM_PROCESS_SPAWNED] = red_callback_wrapper_program_process_spawned;
}

void red_destroy(RED *red) {
	device_release(red->p);
}

int red_get_response_expected(RED *red, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(red->p, function_id, ret_response_expected);
}

int red_set_response_expected(RED *red, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(red->p, function_id, response_expected);
}

int red_set_response_expected_all(RED *red, bool response_expected) {
	return device_set_response_expected_all(red->p, response_expected);
}

void red_register_callback(RED *red, uint8_t id, void *callback, void *user_data) {
	device_register_callback(red->p, id, callback, user_data);
}

int red_get_api_version(RED *red, uint8_t ret_api_version[3]) {
	return device_get_api_version(red->p, ret_api_version);
}

int red_create_session(RED *red, uint32_t lifetime, uint8_t *ret_error_code, uint16_t *ret_session_id) {
	DevicePrivate *device_p = red->p;
	CreateSession_ request;
	CreateSessionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_CREATE_SESSION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.lifetime = leconvert_uint32_to(lifetime);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_session_id = leconvert_uint16_from(response.session_id);



	return ret;
}

int red_expire_session(RED *red, uint16_t session_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	ExpireSession_ request;
	ExpireSessionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_EXPIRE_SESSION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_expire_session_unchecked(RED *red, uint16_t session_id) {
	DevicePrivate *device_p = red->p;
	ExpireSessionUnchecked_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_EXPIRE_SESSION_UNCHECKED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int red_keep_session_alive(RED *red, uint16_t session_id, uint32_t lifetime, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	KeepSessionAlive_ request;
	KeepSessionAliveResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_KEEP_SESSION_ALIVE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.session_id = leconvert_uint16_to(session_id);
	request.lifetime = leconvert_uint32_to(lifetime);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_release_object(RED *red, uint16_t object_id, uint16_t session_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	ReleaseObject_ request;
	ReleaseObjectResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_RELEASE_OBJECT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.object_id = leconvert_uint16_to(object_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_release_object_unchecked(RED *red, uint16_t object_id, uint16_t session_id) {
	DevicePrivate *device_p = red->p;
	ReleaseObjectUnchecked_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_RELEASE_OBJECT_UNCHECKED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.object_id = leconvert_uint16_to(object_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int red_allocate_string(RED *red, uint32_t length_to_reserve, const char buffer[58], uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_string_id) {
	DevicePrivate *device_p = red->p;
	AllocateString_ request;
	AllocateStringResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_ALLOCATE_STRING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.length_to_reserve = leconvert_uint32_to(length_to_reserve);
	strncpy(request.buffer, buffer, 58);

	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_string_id = leconvert_uint16_from(response.string_id);



	return ret;
}

int red_truncate_string(RED *red, uint16_t string_id, uint32_t length, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	TruncateString_ request;
	TruncateStringResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_TRUNCATE_STRING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.string_id = leconvert_uint16_to(string_id);
	request.length = leconvert_uint32_to(length);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_string_length(RED *red, uint16_t string_id, uint8_t *ret_error_code, uint32_t *ret_length) {
	DevicePrivate *device_p = red->p;
	GetStringLength_ request;
	GetStringLengthResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_STRING_LENGTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.string_id = leconvert_uint16_to(string_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_length = leconvert_uint32_from(response.length);



	return ret;
}

int red_set_string_chunk(RED *red, uint16_t string_id, uint32_t offset, const char buffer[58], uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	SetStringChunk_ request;
	SetStringChunkResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_STRING_CHUNK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.string_id = leconvert_uint16_to(string_id);
	request.offset = leconvert_uint32_to(offset);
	strncpy(request.buffer, buffer, 58);


	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_string_chunk(RED *red, uint16_t string_id, uint32_t offset, uint8_t *ret_error_code, char ret_buffer[63]) {
	DevicePrivate *device_p = red->p;
	GetStringChunk_ request;
	GetStringChunkResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_STRING_CHUNK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.string_id = leconvert_uint16_to(string_id);
	request.offset = leconvert_uint32_to(offset);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	strncpy(ret_buffer, response.buffer, 63);



	return ret;
}

int red_allocate_list(RED *red, uint16_t length_to_reserve, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_list_id) {
	DevicePrivate *device_p = red->p;
	AllocateList_ request;
	AllocateListResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_ALLOCATE_LIST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.length_to_reserve = leconvert_uint16_to(length_to_reserve);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_list_id = leconvert_uint16_from(response.list_id);



	return ret;
}

int red_get_list_length(RED *red, uint16_t list_id, uint8_t *ret_error_code, uint16_t *ret_length) {
	DevicePrivate *device_p = red->p;
	GetListLength_ request;
	GetListLengthResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_LIST_LENGTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.list_id = leconvert_uint16_to(list_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_length = leconvert_uint16_from(response.length);



	return ret;
}

int red_get_list_item(RED *red, uint16_t list_id, uint16_t index, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_item_object_id, uint8_t *ret_type) {
	DevicePrivate *device_p = red->p;
	GetListItem_ request;
	GetListItemResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_LIST_ITEM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.list_id = leconvert_uint16_to(list_id);
	request.index = leconvert_uint16_to(index);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_item_object_id = leconvert_uint16_from(response.item_object_id);
	*ret_type = response.type;



	return ret;
}

int red_append_to_list(RED *red, uint16_t list_id, uint16_t item_object_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	AppendToList_ request;
	AppendToListResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_APPEND_TO_LIST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.list_id = leconvert_uint16_to(list_id);
	request.item_object_id = leconvert_uint16_to(item_object_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_remove_from_list(RED *red, uint16_t list_id, uint16_t index, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	RemoveFromList_ request;
	RemoveFromListResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_REMOVE_FROM_LIST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.list_id = leconvert_uint16_to(list_id);
	request.index = leconvert_uint16_to(index);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_open_file(RED *red, uint16_t name_string_id, uint32_t flags, uint16_t permissions, uint32_t uid, uint32_t gid, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_file_id) {
	DevicePrivate *device_p = red->p;
	OpenFile_ request;
	OpenFileResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_OPEN_FILE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.name_string_id = leconvert_uint16_to(name_string_id);
	request.flags = leconvert_uint32_to(flags);
	request.permissions = leconvert_uint16_to(permissions);
	request.uid = leconvert_uint32_to(uid);
	request.gid = leconvert_uint32_to(gid);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_file_id = leconvert_uint16_from(response.file_id);



	return ret;
}

int red_create_pipe(RED *red, uint32_t flags, uint64_t length, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_file_id) {
	DevicePrivate *device_p = red->p;
	CreatePipe_ request;
	CreatePipeResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_CREATE_PIPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.flags = leconvert_uint32_to(flags);
	request.length = leconvert_uint64_to(length);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_file_id = leconvert_uint16_from(response.file_id);



	return ret;
}

int red_get_file_info(RED *red, uint16_t file_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_type, uint16_t *ret_name_string_id, uint32_t *ret_flags, uint16_t *ret_permissions, uint32_t *ret_uid, uint32_t *ret_gid, uint64_t *ret_length, uint64_t *ret_access_timestamp, uint64_t *ret_modification_timestamp, uint64_t *ret_status_change_timestamp) {
	DevicePrivate *device_p = red->p;
	GetFileInfo_ request;
	GetFileInfoResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_FILE_INFO, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_type = response.type;
	*ret_name_string_id = leconvert_uint16_from(response.name_string_id);
	*ret_flags = leconvert_uint32_from(response.flags);
	*ret_permissions = leconvert_uint16_from(response.permissions);
	*ret_uid = leconvert_uint32_from(response.uid);
	*ret_gid = leconvert_uint32_from(response.gid);
	*ret_length = leconvert_uint64_from(response.length);
	*ret_access_timestamp = leconvert_uint64_from(response.access_timestamp);
	*ret_modification_timestamp = leconvert_uint64_from(response.modification_timestamp);
	*ret_status_change_timestamp = leconvert_uint64_from(response.status_change_timestamp);



	return ret;
}

int red_read_file(RED *red, uint16_t file_id, uint8_t length_to_read, uint8_t *ret_error_code, uint8_t ret_buffer[62], uint8_t *ret_length_read) {
	DevicePrivate *device_p = red->p;
	ReadFile_ request;
	ReadFileResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_READ_FILE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	request.length_to_read = length_to_read;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	memcpy(ret_buffer, response.buffer, 62 * sizeof(uint8_t));
	*ret_length_read = response.length_read;



	return ret;
}

int red_read_file_async(RED *red, uint16_t file_id, uint64_t length_to_read) {
	DevicePrivate *device_p = red->p;
	ReadFileAsync_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_READ_FILE_ASYNC, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	request.length_to_read = leconvert_uint64_to(length_to_read);

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int red_abort_async_file_read(RED *red, uint16_t file_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	AbortAsyncFileRead_ request;
	AbortAsyncFileReadResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_ABORT_ASYNC_FILE_READ, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_write_file(RED *red, uint16_t file_id, uint8_t buffer[61], uint8_t length_to_write, uint8_t *ret_error_code, uint8_t *ret_length_written) {
	DevicePrivate *device_p = red->p;
	WriteFile_ request;
	WriteFileResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_WRITE_FILE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	memcpy(request.buffer, buffer, 61 * sizeof(uint8_t));
	request.length_to_write = length_to_write;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_length_written = response.length_written;



	return ret;
}

int red_write_file_unchecked(RED *red, uint16_t file_id, uint8_t buffer[61], uint8_t length_to_write) {
	DevicePrivate *device_p = red->p;
	WriteFileUnchecked_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_WRITE_FILE_UNCHECKED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	memcpy(request.buffer, buffer, 61 * sizeof(uint8_t));
	request.length_to_write = length_to_write;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int red_write_file_async(RED *red, uint16_t file_id, uint8_t buffer[61], uint8_t length_to_write) {
	DevicePrivate *device_p = red->p;
	WriteFileAsync_ request;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_WRITE_FILE_ASYNC, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	memcpy(request.buffer, buffer, 61 * sizeof(uint8_t));
	request.length_to_write = length_to_write;

	ret = device_send_request(device_p, (Packet *)&request, NULL);


	return ret;
}

int red_set_file_position(RED *red, uint16_t file_id, int64_t offset, uint8_t origin, uint8_t *ret_error_code, uint64_t *ret_position) {
	DevicePrivate *device_p = red->p;
	SetFilePosition_ request;
	SetFilePositionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_FILE_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	request.offset = leconvert_int64_to(offset);
	request.origin = origin;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_position = leconvert_uint64_from(response.position);



	return ret;
}

int red_get_file_position(RED *red, uint16_t file_id, uint8_t *ret_error_code, uint64_t *ret_position) {
	DevicePrivate *device_p = red->p;
	GetFilePosition_ request;
	GetFilePositionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_FILE_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_position = leconvert_uint64_from(response.position);



	return ret;
}

int red_set_file_events(RED *red, uint16_t file_id, uint8_t *ret_error_code, uint16_t events) {
	DevicePrivate *device_p = red->p;
	SetFileEvents_ request;
	SetFileEventsResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_FILE_EVENTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);
	request.events = leconvert_uint16_to(events);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_file_events(RED *red, uint16_t file_id, uint8_t *ret_error_code, uint16_t *ret_events) {
	DevicePrivate *device_p = red->p;
	GetFileEvents_ request;
	GetFileEventsResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_FILE_EVENTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.file_id = leconvert_uint16_to(file_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_events = leconvert_uint16_from(response.events);



	return ret;
}

int red_open_directory(RED *red, uint16_t name_string_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_directory_id) {
	DevicePrivate *device_p = red->p;
	OpenDirectory_ request;
	OpenDirectoryResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_OPEN_DIRECTORY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.name_string_id = leconvert_uint16_to(name_string_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_directory_id = leconvert_uint16_from(response.directory_id);



	return ret;
}

int red_get_directory_name(RED *red, uint16_t directory_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_name_string_id) {
	DevicePrivate *device_p = red->p;
	GetDirectoryName_ request;
	GetDirectoryNameResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_DIRECTORY_NAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.directory_id = leconvert_uint16_to(directory_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_name_string_id = leconvert_uint16_from(response.name_string_id);



	return ret;
}

int red_get_next_directory_entry(RED *red, uint16_t directory_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_name_string_id, uint8_t *ret_type) {
	DevicePrivate *device_p = red->p;
	GetNextDirectoryEntry_ request;
	GetNextDirectoryEntryResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_NEXT_DIRECTORY_ENTRY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.directory_id = leconvert_uint16_to(directory_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_name_string_id = leconvert_uint16_from(response.name_string_id);
	*ret_type = response.type;



	return ret;
}

int red_rewind_directory(RED *red, uint16_t directory_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	RewindDirectory_ request;
	RewindDirectoryResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_REWIND_DIRECTORY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.directory_id = leconvert_uint16_to(directory_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_create_directory(RED *red, uint16_t name_string_id, uint32_t flags, uint16_t permissions, uint32_t uid, uint32_t gid, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	CreateDirectory_ request;
	CreateDirectoryResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_CREATE_DIRECTORY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.name_string_id = leconvert_uint16_to(name_string_id);
	request.flags = leconvert_uint32_to(flags);
	request.permissions = leconvert_uint16_to(permissions);
	request.uid = leconvert_uint32_to(uid);
	request.gid = leconvert_uint32_to(gid);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_processes(RED *red, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_processes_list_id) {
	DevicePrivate *device_p = red->p;
	GetProcesses_ request;
	GetProcessesResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROCESSES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_processes_list_id = leconvert_uint16_from(response.processes_list_id);



	return ret;
}

int red_spawn_process(RED *red, uint16_t executable_string_id, uint16_t arguments_list_id, uint16_t environment_list_id, uint16_t working_directory_string_id, uint32_t uid, uint32_t gid, uint16_t stdin_file_id, uint16_t stdout_file_id, uint16_t stderr_file_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_process_id) {
	DevicePrivate *device_p = red->p;
	SpawnProcess_ request;
	SpawnProcessResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SPAWN_PROCESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.executable_string_id = leconvert_uint16_to(executable_string_id);
	request.arguments_list_id = leconvert_uint16_to(arguments_list_id);
	request.environment_list_id = leconvert_uint16_to(environment_list_id);
	request.working_directory_string_id = leconvert_uint16_to(working_directory_string_id);
	request.uid = leconvert_uint32_to(uid);
	request.gid = leconvert_uint32_to(gid);
	request.stdin_file_id = leconvert_uint16_to(stdin_file_id);
	request.stdout_file_id = leconvert_uint16_to(stdout_file_id);
	request.stderr_file_id = leconvert_uint16_to(stderr_file_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_process_id = leconvert_uint16_from(response.process_id);



	return ret;
}

int red_kill_process(RED *red, uint16_t process_id, uint8_t signal, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	KillProcess_ request;
	KillProcessResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_KILL_PROCESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.process_id = leconvert_uint16_to(process_id);
	request.signal = signal;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_process_command(RED *red, uint16_t process_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_executable_string_id, uint16_t *ret_arguments_list_id, uint16_t *ret_environment_list_id, uint16_t *ret_working_directory_string_id) {
	DevicePrivate *device_p = red->p;
	GetProcessCommand_ request;
	GetProcessCommandResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROCESS_COMMAND, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.process_id = leconvert_uint16_to(process_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_executable_string_id = leconvert_uint16_from(response.executable_string_id);
	*ret_arguments_list_id = leconvert_uint16_from(response.arguments_list_id);
	*ret_environment_list_id = leconvert_uint16_from(response.environment_list_id);
	*ret_working_directory_string_id = leconvert_uint16_from(response.working_directory_string_id);



	return ret;
}

int red_get_process_identity(RED *red, uint16_t process_id, uint8_t *ret_error_code, uint32_t *ret_pid, uint32_t *ret_uid, uint32_t *ret_gid) {
	DevicePrivate *device_p = red->p;
	GetProcessIdentity_ request;
	GetProcessIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROCESS_IDENTITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.process_id = leconvert_uint16_to(process_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_pid = leconvert_uint32_from(response.pid);
	*ret_uid = leconvert_uint32_from(response.uid);
	*ret_gid = leconvert_uint32_from(response.gid);



	return ret;
}

int red_get_process_stdio(RED *red, uint16_t process_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_stdin_file_id, uint16_t *ret_stdout_file_id, uint16_t *ret_stderr_file_id) {
	DevicePrivate *device_p = red->p;
	GetProcessStdio_ request;
	GetProcessStdioResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROCESS_STDIO, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.process_id = leconvert_uint16_to(process_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_stdin_file_id = leconvert_uint16_from(response.stdin_file_id);
	*ret_stdout_file_id = leconvert_uint16_from(response.stdout_file_id);
	*ret_stderr_file_id = leconvert_uint16_from(response.stderr_file_id);



	return ret;
}

int red_get_process_state(RED *red, uint16_t process_id, uint8_t *ret_error_code, uint8_t *ret_state, uint64_t *ret_timestamp, uint8_t *ret_exit_code) {
	DevicePrivate *device_p = red->p;
	GetProcessState_ request;
	GetProcessStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROCESS_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.process_id = leconvert_uint16_to(process_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_state = response.state;
	*ret_timestamp = leconvert_uint64_from(response.timestamp);
	*ret_exit_code = response.exit_code;



	return ret;
}

int red_get_programs(RED *red, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_programs_list_id) {
	DevicePrivate *device_p = red->p;
	GetPrograms_ request;
	GetProgramsResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAMS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_programs_list_id = leconvert_uint16_from(response.programs_list_id);



	return ret;
}

int red_define_program(RED *red, uint16_t identifier_string_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_program_id) {
	DevicePrivate *device_p = red->p;
	DefineProgram_ request;
	DefineProgramResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_DEFINE_PROGRAM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.identifier_string_id = leconvert_uint16_to(identifier_string_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_program_id = leconvert_uint16_from(response.program_id);



	return ret;
}

int red_purge_program(RED *red, uint16_t program_id, uint32_t cookie, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	PurgeProgram_ request;
	PurgeProgramResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_PURGE_PROGRAM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.cookie = leconvert_uint32_to(cookie);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_program_identifier(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_identifier_string_id) {
	DevicePrivate *device_p = red->p;
	GetProgramIdentifier_ request;
	GetProgramIdentifierResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAM_IDENTIFIER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_identifier_string_id = leconvert_uint16_from(response.identifier_string_id);



	return ret;
}

int red_get_program_root_directory(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_root_directory_string_id) {
	DevicePrivate *device_p = red->p;
	GetProgramRootDirectory_ request;
	GetProgramRootDirectoryResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAM_ROOT_DIRECTORY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_root_directory_string_id = leconvert_uint16_from(response.root_directory_string_id);



	return ret;
}

int red_set_program_command(RED *red, uint16_t program_id, uint16_t executable_string_id, uint16_t arguments_list_id, uint16_t environment_list_id, uint16_t working_directory_string_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	SetProgramCommand_ request;
	SetProgramCommandResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_PROGRAM_COMMAND, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.executable_string_id = leconvert_uint16_to(executable_string_id);
	request.arguments_list_id = leconvert_uint16_to(arguments_list_id);
	request.environment_list_id = leconvert_uint16_to(environment_list_id);
	request.working_directory_string_id = leconvert_uint16_to(working_directory_string_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_program_command(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_executable_string_id, uint16_t *ret_arguments_list_id, uint16_t *ret_environment_list_id, uint16_t *ret_working_directory_string_id) {
	DevicePrivate *device_p = red->p;
	GetProgramCommand_ request;
	GetProgramCommandResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAM_COMMAND, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_executable_string_id = leconvert_uint16_from(response.executable_string_id);
	*ret_arguments_list_id = leconvert_uint16_from(response.arguments_list_id);
	*ret_environment_list_id = leconvert_uint16_from(response.environment_list_id);
	*ret_working_directory_string_id = leconvert_uint16_from(response.working_directory_string_id);



	return ret;
}

int red_set_program_stdio_redirection(RED *red, uint16_t program_id, uint8_t stdin_redirection, uint16_t stdin_file_name_string_id, uint8_t stdout_redirection, uint16_t stdout_file_name_string_id, uint8_t stderr_redirection, uint16_t stderr_file_name_string_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	SetProgramStdioRedirection_ request;
	SetProgramStdioRedirectionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_PROGRAM_STDIO_REDIRECTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.stdin_redirection = stdin_redirection;
	request.stdin_file_name_string_id = leconvert_uint16_to(stdin_file_name_string_id);
	request.stdout_redirection = stdout_redirection;
	request.stdout_file_name_string_id = leconvert_uint16_to(stdout_file_name_string_id);
	request.stderr_redirection = stderr_redirection;
	request.stderr_file_name_string_id = leconvert_uint16_to(stderr_file_name_string_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_program_stdio_redirection(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_stdin_redirection, uint16_t *ret_stdin_file_name_string_id, uint8_t *ret_stdout_redirection, uint16_t *ret_stdout_file_name_string_id, uint8_t *ret_stderr_redirection, uint16_t *ret_stderr_file_name_string_id) {
	DevicePrivate *device_p = red->p;
	GetProgramStdioRedirection_ request;
	GetProgramStdioRedirectionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAM_STDIO_REDIRECTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_stdin_redirection = response.stdin_redirection;
	*ret_stdin_file_name_string_id = leconvert_uint16_from(response.stdin_file_name_string_id);
	*ret_stdout_redirection = response.stdout_redirection;
	*ret_stdout_file_name_string_id = leconvert_uint16_from(response.stdout_file_name_string_id);
	*ret_stderr_redirection = response.stderr_redirection;
	*ret_stderr_file_name_string_id = leconvert_uint16_from(response.stderr_file_name_string_id);



	return ret;
}

int red_set_program_schedule(RED *red, uint16_t program_id, uint8_t start_mode, bool continue_after_error, uint32_t start_interval, uint16_t start_fields_string_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	SetProgramSchedule_ request;
	SetProgramScheduleResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_PROGRAM_SCHEDULE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.start_mode = start_mode;
	request.continue_after_error = continue_after_error;
	request.start_interval = leconvert_uint32_to(start_interval);
	request.start_fields_string_id = leconvert_uint16_to(start_fields_string_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_program_schedule(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_start_mode, bool *ret_continue_after_error, uint32_t *ret_start_interval, uint16_t *ret_start_fields_string_id) {
	DevicePrivate *device_p = red->p;
	GetProgramSchedule_ request;
	GetProgramScheduleResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAM_SCHEDULE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_start_mode = response.start_mode;
	*ret_continue_after_error = response.continue_after_error;
	*ret_start_interval = leconvert_uint32_from(response.start_interval);
	*ret_start_fields_string_id = leconvert_uint16_from(response.start_fields_string_id);



	return ret;
}

int red_get_program_scheduler_state(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_state, uint64_t *ret_timestamp, uint16_t *ret_message_string_id) {
	DevicePrivate *device_p = red->p;
	GetProgramSchedulerState_ request;
	GetProgramSchedulerStateResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_PROGRAM_SCHEDULER_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_state = response.state;
	*ret_timestamp = leconvert_uint64_from(response.timestamp);
	*ret_message_string_id = leconvert_uint16_from(response.message_string_id);



	return ret;
}

int red_continue_program_schedule(RED *red, uint16_t program_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	ContinueProgramSchedule_ request;
	ContinueProgramScheduleResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_CONTINUE_PROGRAM_SCHEDULE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_start_program(RED *red, uint16_t program_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	StartProgram_ request;
	StartProgramResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_START_PROGRAM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_last_spawned_program_process(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_process_id, uint64_t *ret_timestamp) {
	DevicePrivate *device_p = red->p;
	GetLastSpawnedProgramProcess_ request;
	GetLastSpawnedProgramProcessResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_LAST_SPAWNED_PROGRAM_PROCESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_process_id = leconvert_uint16_from(response.process_id);
	*ret_timestamp = leconvert_uint64_from(response.timestamp);



	return ret;
}

int red_get_custom_program_option_names(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_names_list_id) {
	DevicePrivate *device_p = red->p;
	GetCustomProgramOptionNames_ request;
	GetCustomProgramOptionNamesResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_CUSTOM_PROGRAM_OPTION_NAMES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_names_list_id = leconvert_uint16_from(response.names_list_id);



	return ret;
}

int red_set_custom_program_option_value(RED *red, uint16_t program_id, uint16_t name_string_id, uint16_t value_string_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	SetCustomProgramOptionValue_ request;
	SetCustomProgramOptionValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_SET_CUSTOM_PROGRAM_OPTION_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.name_string_id = leconvert_uint16_to(name_string_id);
	request.value_string_id = leconvert_uint16_to(value_string_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_custom_program_option_value(RED *red, uint16_t program_id, uint16_t name_string_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_value_string_id) {
	DevicePrivate *device_p = red->p;
	GetCustomProgramOptionValue_ request;
	GetCustomProgramOptionValueResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_CUSTOM_PROGRAM_OPTION_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.name_string_id = leconvert_uint16_to(name_string_id);
	request.session_id = leconvert_uint16_to(session_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;
	*ret_value_string_id = leconvert_uint16_from(response.value_string_id);



	return ret;
}

int red_remove_custom_program_option(RED *red, uint16_t program_id, uint16_t name_string_id, uint8_t *ret_error_code) {
	DevicePrivate *device_p = red->p;
	RemoveCustomProgramOption_ request;
	RemoveCustomProgramOptionResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_REMOVE_CUSTOM_PROGRAM_OPTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.program_id = leconvert_uint16_to(program_id);
	request.name_string_id = leconvert_uint16_to(name_string_id);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response);

	if (ret < 0) {
		return ret;
	}
	*ret_error_code = response.error_code;



	return ret;
}

int red_get_identity(RED *red, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = red->p;
	GetIdentity_ request;
	GetIdentityResponse_ response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RED_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

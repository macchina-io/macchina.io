/* ***********************************************************
 * This file was automatically generated on 2014-12-10.      *
 *                                                           *
 * Bindings Version 2.1.6                                    *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICK_RED_H
#define BRICK_RED_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickRED RED Brick
 */

/**
 * \ingroup BrickRED
 *
 * Device for running user programs standalone on the stack
 */
typedef Device RED;

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_CREATE_SESSION 1

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_EXPIRE_SESSION 2

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_EXPIRE_SESSION_UNCHECKED 3

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_KEEP_SESSION_ALIVE 4

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_RELEASE_OBJECT 5

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_RELEASE_OBJECT_UNCHECKED 6

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_ALLOCATE_STRING 7

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_TRUNCATE_STRING 8

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_STRING_LENGTH 9

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_STRING_CHUNK 10

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_STRING_CHUNK 11

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_ALLOCATE_LIST 12

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_LIST_LENGTH 13

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_LIST_ITEM 14

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_APPEND_TO_LIST 15

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_REMOVE_FROM_LIST 16

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_OPEN_FILE 17

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_CREATE_PIPE 18

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_FILE_INFO 19

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_READ_FILE 20

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_READ_FILE_ASYNC 21

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_ABORT_ASYNC_FILE_READ 22

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_WRITE_FILE 23

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_WRITE_FILE_UNCHECKED 24

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_WRITE_FILE_ASYNC 25

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_FILE_POSITION 26

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_FILE_POSITION 27

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_FILE_EVENTS 28

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_FILE_EVENTS 29

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_OPEN_DIRECTORY 33

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_DIRECTORY_NAME 34

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_NEXT_DIRECTORY_ENTRY 35

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_REWIND_DIRECTORY 36

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_CREATE_DIRECTORY 37

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROCESSES 38

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SPAWN_PROCESS 39

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_KILL_PROCESS 40

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROCESS_COMMAND 41

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROCESS_IDENTITY 42

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROCESS_STDIO 43

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROCESS_STATE 44

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAMS 46

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_DEFINE_PROGRAM 47

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_PURGE_PROGRAM 48

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAM_IDENTIFIER 49

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAM_ROOT_DIRECTORY 50

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_PROGRAM_COMMAND 51

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAM_COMMAND 52

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_PROGRAM_STDIO_REDIRECTION 53

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAM_STDIO_REDIRECTION 54

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_PROGRAM_SCHEDULE 55

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAM_SCHEDULE 56

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_PROGRAM_SCHEDULER_STATE 57

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_CONTINUE_PROGRAM_SCHEDULE 58

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_START_PROGRAM 59

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_LAST_SPAWNED_PROGRAM_PROCESS 60

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_CUSTOM_PROGRAM_OPTION_NAMES 61

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_SET_CUSTOM_PROGRAM_OPTION_VALUE 62

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_CUSTOM_PROGRAM_OPTION_VALUE 63

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_REMOVE_CUSTOM_PROGRAM_OPTION 64

/**
 * \ingroup BrickRED
 */
#define RED_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickRED
 *
 * Signature: \code void callback(uint16_t file_id, uint8_t error_code, uint8_t ret_buffer[60], uint8_t length_read, void *user_data) \endcode
 * 
 * This callback reports the result of a call to the {@link red_read_file_async}
 * function.
 */
#define RED_CALLBACK_ASYNC_FILE_READ 30

/**
 * \ingroup BrickRED
 *
 * Signature: \code void callback(uint16_t file_id, uint8_t error_code, uint8_t length_written, void *user_data) \endcode
 * 
 * This callback reports the result of a call to the {@link red_write_file_async}
 * function.
 */
#define RED_CALLBACK_ASYNC_FILE_WRITE 31

/**
 * \ingroup BrickRED
 *
 * Signature: \code void callback(uint16_t file_id, uint16_t events, void *user_data) \endcode
 */
#define RED_CALLBACK_FILE_EVENTS_OCCURRED 32

/**
 * \ingroup BrickRED
 *
 * Signature: \code void callback(uint16_t process_id, uint8_t state, uint64_t timestamp, uint8_t exit_code, void *user_data) \endcode
 */
#define RED_CALLBACK_PROCESS_STATE_CHANGED 45

/**
 * \ingroup BrickRED
 *
 * Signature: \code void callback(uint16_t program_id, void *user_data) \endcode
 */
#define RED_CALLBACK_PROGRAM_SCHEDULER_STATE_CHANGED 65

/**
 * \ingroup BrickRED
 *
 * Signature: \code void callback(uint16_t program_id, void *user_data) \endcode
 */
#define RED_CALLBACK_PROGRAM_PROCESS_SPAWNED 66


/**
 * \ingroup BrickRED
 */
#define RED_OBJECT_TYPE_STRING 0

/**
 * \ingroup BrickRED
 */
#define RED_OBJECT_TYPE_LIST 1

/**
 * \ingroup BrickRED
 */
#define RED_OBJECT_TYPE_FILE 2

/**
 * \ingroup BrickRED
 */
#define RED_OBJECT_TYPE_DIRECTORY 3

/**
 * \ingroup BrickRED
 */
#define RED_OBJECT_TYPE_PROCESS 4

/**
 * \ingroup BrickRED
 */
#define RED_OBJECT_TYPE_PROGRAM 5

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_READ_ONLY 1

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_WRITE_ONLY 2

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_READ_WRITE 4

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_APPEND 8

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_CREATE 16

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_EXCLUSIVE 32

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_NON_BLOCKING 64

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_TRUNCATE 128

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_TEMPORARY 256

/**
 * \ingroup BrickRED
 */
#define RED_FILE_FLAG_REPLACE 512

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_USER_ALL 448

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_USER_READ 256

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_USER_WRITE 128

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_USER_EXECUTE 64

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_GROUP_ALL 56

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_GROUP_READ 32

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_GROUP_WRITE 16

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_GROUP_EXECUTE 8

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_OTHERS_ALL 7

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_OTHERS_READ 4

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_OTHERS_WRITE 2

/**
 * \ingroup BrickRED
 */
#define RED_FILE_PERMISSION_OTHERS_EXECUTE 1

/**
 * \ingroup BrickRED
 */
#define RED_PIPE_FLAG_NON_BLOCKING_READ 1

/**
 * \ingroup BrickRED
 */
#define RED_PIPE_FLAG_NON_BLOCKING_WRITE 2

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_UNKNOWN 0

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_REGULAR 1

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_DIRECTORY 2

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_CHARACTER 3

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_BLOCK 4

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_FIFO 5

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_SYMLINK 6

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_SOCKET 7

/**
 * \ingroup BrickRED
 */
#define RED_FILE_TYPE_PIPE 8

/**
 * \ingroup BrickRED
 */
#define RED_FILE_ORIGIN_BEGINNING 0

/**
 * \ingroup BrickRED
 */
#define RED_FILE_ORIGIN_CURRENT 1

/**
 * \ingroup BrickRED
 */
#define RED_FILE_ORIGIN_END 2

/**
 * \ingroup BrickRED
 */
#define RED_FILE_EVENT_READABLE 1

/**
 * \ingroup BrickRED
 */
#define RED_FILE_EVENT_WRITABLE 2

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_UNKNOWN 0

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_REGULAR 1

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_DIRECTORY 2

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_CHARACTER 3

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_BLOCK 4

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_FIFO 5

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_SYMLINK 6

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_ENTRY_TYPE_SOCKET 7

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_FLAG_RECURSIVE 1

/**
 * \ingroup BrickRED
 */
#define RED_DIRECTORY_FLAG_EXCLUSIVE 2

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_INTERRUPT 2

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_QUIT 3

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_ABORT 6

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_KILL 9

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_USER1 10

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_USER2 12

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_TERMINATE 15

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_CONTINUE 18

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_SIGNAL_STOP 19

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_STATE_UNKNOWN 0

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_STATE_RUNNING 1

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_STATE_ERROR 2

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_STATE_EXITED 3

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_STATE_KILLED 4

/**
 * \ingroup BrickRED
 */
#define RED_PROCESS_STATE_STOPPED 5

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_STDIO_REDIRECTION_DEV_NULL 0

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_STDIO_REDIRECTION_PIPE 1

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_STDIO_REDIRECTION_FILE 2

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_STDIO_REDIRECTION_INDIVIDUAL_LOG 3

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_STDIO_REDIRECTION_CONTINUOUS_LOG 4

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_STDIO_REDIRECTION_STDOUT 5

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_START_MODE_NEVER 0

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_START_MODE_ALWAYS 1

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_START_MODE_INTERVAL 2

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_START_MODE_CRON 3

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_SCHEDULER_STATE_STOPPED 0

/**
 * \ingroup BrickRED
 */
#define RED_PROGRAM_SCHEDULER_STATE_RUNNING 1

/**
 * \ingroup BrickRED
 *
 * This constant is used to identify a RED Brick.
 *
 * The {@link red_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define RED_DEVICE_IDENTIFIER 17

/**
 * \ingroup BrickRED
 *
 * Creates the device object \c red with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void red_create(RED *red, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickRED
 *
 * Removes the device object \c red from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void red_destroy(RED *red);

/**
 * \ingroup BrickRED
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the red_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int red_get_response_expected(RED *red, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickRED
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
int red_set_response_expected(RED *red, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickRED
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int red_set_response_expected_all(RED *red, bool response_expected);

/**
 * \ingroup BrickRED
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void red_register_callback(RED *red, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickRED
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int red_get_api_version(RED *red, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_create_session(RED *red, uint32_t lifetime, uint8_t *ret_error_code, uint16_t *ret_session_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_expire_session(RED *red, uint16_t session_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_expire_session_unchecked(RED *red, uint16_t session_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_keep_session_alive(RED *red, uint16_t session_id, uint32_t lifetime, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Decreases the reference count of an object by one and returns the resulting
 * error code. If the reference count reaches zero the object gets destroyed.
 */
int red_release_object(RED *red, uint16_t object_id, uint16_t session_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_release_object_unchecked(RED *red, uint16_t object_id, uint16_t session_id);

/**
 * \ingroup BrickRED
 *
 * Allocates a new string object, reserves ``length_to_reserve`` bytes memory
 * for it and sets up to the first 60 bytes. Set ``length_to_reserve`` to the
 * length of the string that should be stored in the string object.
 * 
 * Returns the object ID of the new string object and the resulting error code.
 */
int red_allocate_string(RED *red, uint32_t length_to_reserve, const char buffer[58], uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_string_id);

/**
 * \ingroup BrickRED
 *
 * Truncates a string object to ``length`` bytes and returns the resulting
 * error code.
 */
int red_truncate_string(RED *red, uint16_t string_id, uint32_t length, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Returns the length of a string object in bytes and the resulting error code.
 */
int red_get_string_length(RED *red, uint16_t string_id, uint8_t *ret_error_code, uint32_t *ret_length);

/**
 * \ingroup BrickRED
 *
 * Sets a chunk of up to 58 bytes in a string object beginning at ``offset``.
 * 
 * Returns the resulting error code.
 */
int red_set_string_chunk(RED *red, uint16_t string_id, uint32_t offset, const char buffer[58], uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Returns a chunk up to 63 bytes from a string object beginning at ``offset`` and
 * returns the resulting error code.
 */
int red_get_string_chunk(RED *red, uint16_t string_id, uint32_t offset, uint8_t *ret_error_code, char ret_buffer[63]);

/**
 * \ingroup BrickRED
 *
 * Allocates a new list object and reserves memory for ``length_to_reserve``
 * items. Set ``length_to_reserve`` to the number of items that should be stored
 * in the list object.
 * 
 * Returns the object ID of the new list object and the resulting error code.
 * 
 * When a list object gets destroyed then the reference count of each object in
 * the list object is decreased by one.
 */
int red_allocate_list(RED *red, uint16_t length_to_reserve, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_list_id);

/**
 * \ingroup BrickRED
 *
 * Returns the length of a list object in items and the resulting error code.
 */
int red_get_list_length(RED *red, uint16_t list_id, uint8_t *ret_error_code, uint16_t *ret_length);

/**
 * \ingroup BrickRED
 *
 * Returns the object ID and type of the object stored at ``index`` in a list
 * object and returns the resulting error code.
 * 
 * Possible object types are:
 * 
 * * String = 0
 * * List = 1
 * * File = 2
 * * Directory = 3
 * * Process = 4
 * * Program = 5
 */
int red_get_list_item(RED *red, uint16_t list_id, uint16_t index, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_item_object_id, uint8_t *ret_type);

/**
 * \ingroup BrickRED
 *
 * Appends an object to a list object and increases the reference count of the
 * appended object by one.
 * 
 * Returns the resulting error code.
 */
int red_append_to_list(RED *red, uint16_t list_id, uint16_t item_object_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Removes the object stored at ``index`` from a list object and decreases the
 * reference count of the removed object by one.
 * 
 * Returns the resulting error code.
 */
int red_remove_from_list(RED *red, uint16_t list_id, uint16_t index, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Opens an existing file or creates a new file and allocates a new file object
 * for it.
 * 
 * FIXME: name has to be absolute
 * 
 * The reference count of the name string object is increased by one. When the
 * file object gets destroyed then the reference count of the name string object is
 * decreased by one. Also the name string object is locked and cannot be modified
 * while the file object holds a reference to it.
 * 
 * The ``flags`` parameter takes a ORed combination of the following possible file
 * flags (in hexadecimal notation):
 * 
 * * ReadOnly = 0x0001 (O_RDONLY)
 * * WriteOnly = 0x0002 (O_WRONLY)
 * * ReadWrite = 0x0004 (O_RDWR)
 * * Append = 0x0008 (O_APPEND)
 * * Create = 0x0010 (O_CREAT)
 * * Exclusive = 0x0020 (O_EXCL)
 * * NonBlocking = 0x0040 (O_NONBLOCK)
 * * Truncate = 0x0080 (O_TRUNC)
 * * Temporary = 0x0100
 * * Replace = 0x0200
 * 
 * FIXME: explain *Temporary* and *Replace* flag
 * 
 * The ``permissions`` parameter takes a ORed combination of the following
 * possible file permissions (in octal notation) that match the common UNIX
 * permission bits:
 * 
 * * UserRead = 00400
 * * UserWrite = 00200
 * * UserExecute = 00100
 * * GroupRead = 00040
 * * GroupWrite = 00020
 * * GroupExecute = 00010
 * * OthersRead = 00004
 * * OthersWrite = 00002
 * * OthersExecute = 00001
 * 
 * Returns the object ID of the new file object and the resulting error code.
 */
int red_open_file(RED *red, uint16_t name_string_id, uint32_t flags, uint16_t permissions, uint32_t uid, uint32_t gid, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_file_id);

/**
 * \ingroup BrickRED
 *
 * Creates a new pipe and allocates a new file object for it.
 * 
 * The ``flags`` parameter takes a ORed combination of the following possible
 * pipe flags (in hexadecimal notation):
 * 
 * * NonBlockingRead = 0x0001
 * * NonBlockingWrite = 0x0002
 * 
 * The length of the pipe buffer can be specified with the ``length`` parameter
 * in bytes. If length is set to zero, then the default pipe buffer length is used.
 * 
 * Returns the object ID of the new file object and the resulting error code.
 */
int red_create_pipe(RED *red, uint32_t flags, uint64_t length, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_file_id);

/**
 * \ingroup BrickRED
 *
 * Returns various information about a file and the resulting error code.
 * 
 * Possible file types are:
 * 
 * * Unknown = 0
 * * Regular = 1
 * * Directory = 2
 * * Character = 3
 * * Block = 4
 * * FIFO = 5
 * * Symlink = 6
 * * Socket = 7
 * * Pipe = 8
 * 
 * If the file type is *Pipe* then the returned name string object is invalid,
 * because a pipe has no name. Otherwise the returned name string object was used
 * to open or create the file object, as passed to {@link red_open_file}.
 * 
 * The returned flags were used to open or create the file object, as passed to
 * {@link red_open_file} or {@link red_create_pipe}. See the respective function for a list
 * of possible file and pipe flags.
 * 
 * FIXME: everything except flags and length is invalid if file type is *Pipe*
 */
int red_get_file_info(RED *red, uint16_t file_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_type, uint16_t *ret_name_string_id, uint32_t *ret_flags, uint16_t *ret_permissions, uint32_t *ret_uid, uint32_t *ret_gid, uint64_t *ret_length, uint64_t *ret_access_timestamp, uint64_t *ret_modification_timestamp, uint64_t *ret_status_change_timestamp);

/**
 * \ingroup BrickRED
 *
 * Reads up to 62 bytes from a file object.
 * 
 * Returns the bytes read, the actual number of bytes read and the resulting
 * error code.
 * 
 * If there is not data to be read, either because the file position reached
 * end-of-file or because there is not data in the pipe, then zero bytes are
 * returned.
 * 
 * If the file object was created by {@link red_open_file} without the *NonBlocking*
 * flag or by {@link red_create_pipe} without the *NonBlockingRead* flag then the
 * error code *NotSupported* is returned.
 */
int red_read_file(RED *red, uint16_t file_id, uint8_t length_to_read, uint8_t *ret_error_code, uint8_t ret_buffer[62], uint8_t *ret_length_read);

/**
 * \ingroup BrickRED
 *
 * Reads up to 2\ :sup:`63`\  - 1 bytes from a file object asynchronously.
 * 
 * Reports the bytes read (in 60 byte chunks), the actual number of bytes read and
 * the resulting error code via the {@link RED_CALLBACK_ASYNC_FILE_READ} callback.
 * 
 * If there is not data to be read, either because the file position reached
 * end-of-file or because there is not data in the pipe, then zero bytes are
 * reported.
 * 
 * If the file object was created by {@link red_open_file} without the *NonBlocking*
 * flag or by {@link red_create_pipe} without the *NonBlockingRead* flag then the error
 * code *NotSupported* is reported via the {@link RED_CALLBACK_ASYNC_FILE_READ} callback.
 */
int red_read_file_async(RED *red, uint16_t file_id, uint64_t length_to_read);

/**
 * \ingroup BrickRED
 *
 * Aborts a {@link red_read_file_async} operation in progress.
 * 
 * Returns the resulting error code.
 * 
 * On success the {@link RED_CALLBACK_ASYNC_FILE_READ} callback will report *OperationAborted*.
 */
int red_abort_async_file_read(RED *red, uint16_t file_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Writes up to 61 bytes to a file object.
 * 
 * Returns the actual number of bytes written and the resulting error code.
 * 
 * If the file object was created by {@link red_open_file} without the *NonBlocking*
 * flag or by {@link red_create_pipe} without the *NonBlockingWrite* flag then the
 * error code *NotSupported* is returned.
 */
int red_write_file(RED *red, uint16_t file_id, uint8_t buffer[61], uint8_t length_to_write, uint8_t *ret_error_code, uint8_t *ret_length_written);

/**
 * \ingroup BrickRED
 *
 * Writes up to 61 bytes to a file object.
 * 
 * Does neither report the actual number of bytes written nor the resulting error
 * code.
 * 
 * If the file object was created by {@link red_open_file} without the *NonBlocking*
 * flag or by {@link red_create_pipe} without the *NonBlockingWrite* flag then the
 * write operation will fail silently.
 */
int red_write_file_unchecked(RED *red, uint16_t file_id, uint8_t buffer[61], uint8_t length_to_write);

/**
 * \ingroup BrickRED
 *
 * Writes up to 61 bytes to a file object.
 * 
 * Reports the actual number of bytes written and the resulting error code via the
 * {@link RED_CALLBACK_ASYNC_FILE_WRITE} callback.
 * 
 * If the file object was created by {@link red_open_file} without the *NonBlocking*
 * flag or by {@link red_create_pipe} without the *NonBlockingWrite* flag then the
 * error code *NotSupported* is reported via the {@link RED_CALLBACK_ASYNC_FILE_WRITE} callback.
 */
int red_write_file_async(RED *red, uint16_t file_id, uint8_t buffer[61], uint8_t length_to_write);

/**
 * \ingroup BrickRED
 *
 * Set the current seek position of a file object in bytes relative to ``origin``.
 * 
 * Possible file origins are:
 * 
 * * Beginning = 0
 * * Current = 1
 * * End = 2
 * 
 * Returns the resulting absolute seek position and error code.
 * 
 * If the file object was created by {@link red_create_pipe} then it has no seek
 * position and the error code *InvalidSeek* is returned.
 */
int red_set_file_position(RED *red, uint16_t file_id, int64_t offset, uint8_t origin, uint8_t *ret_error_code, uint64_t *ret_position);

/**
 * \ingroup BrickRED
 *
 * Returns the current seek position of a file object in bytes and returns the
 * resulting error code.
 * 
 * If the file object was created by {@link red_create_pipe} then it has no seek
 * position and the error code *InvalidSeek* is returned.
 */
int red_get_file_position(RED *red, uint16_t file_id, uint8_t *ret_error_code, uint64_t *ret_position);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_set_file_events(RED *red, uint16_t file_id, uint8_t *ret_error_code, uint16_t events);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_file_events(RED *red, uint16_t file_id, uint8_t *ret_error_code, uint16_t *ret_events);

/**
 * \ingroup BrickRED
 *
 * Opens an existing directory and allocates a new directory object for it.
 * 
 * FIXME: name has to be absolute
 * 
 * The reference count of the name string object is increased by one. When the
 * directory object is destroyed then the reference count of the name string
 * object is decreased by one. Also the name string object is locked and cannot be
 * modified while the directory object holds a reference to it.
 * 
 * Returns the object ID of the new directory object and the resulting error code.
 */
int red_open_directory(RED *red, uint16_t name_string_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_directory_id);

/**
 * \ingroup BrickRED
 *
 * Returns the name of a directory object, as passed to {@link red_open_directory}, and
 * the resulting error code.
 */
int red_get_directory_name(RED *red, uint16_t directory_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_name_string_id);

/**
 * \ingroup BrickRED
 *
 * Returns the next entry in a directory object and the resulting error code.
 * 
 * If there is not next entry then error code *NoMoreData* is returned. To rewind
 * a directory object call {@link red_rewind_directory}.
 * 
 * Possible directory entry types are:
 * 
 * * Unknown = 0
 * * Regular = 1
 * * Directory = 2
 * * Character = 3
 * * Block = 4
 * * FIFO = 5
 * * Symlink = 6
 * * Socket = 7
 */
int red_get_next_directory_entry(RED *red, uint16_t directory_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_name_string_id, uint8_t *ret_type);

/**
 * \ingroup BrickRED
 *
 * Rewinds a directory object and returns the resulting error code.
 */
int red_rewind_directory(RED *red, uint16_t directory_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * FIXME: name has to be absolute
 */
int red_create_directory(RED *red, uint16_t name_string_id, uint32_t flags, uint16_t permissions, uint32_t uid, uint32_t gid, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_processes(RED *red, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_processes_list_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_spawn_process(RED *red, uint16_t executable_string_id, uint16_t arguments_list_id, uint16_t environment_list_id, uint16_t working_directory_string_id, uint32_t uid, uint32_t gid, uint16_t stdin_file_id, uint16_t stdout_file_id, uint16_t stderr_file_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_process_id);

/**
 * \ingroup BrickRED
 *
 * Sends a UNIX signal to a process object and returns the resulting error code.
 * 
 * Possible UNIX signals are:
 * 
 * * Interrupt = 2
 * * Quit = 3
 * * Abort = 6
 * * Kill = 9
 * * User1 = 10
 * * User2 = 12
 * * Terminate = 15
 * * Continue =  18
 * * Stop = 19
 */
int red_kill_process(RED *red, uint16_t process_id, uint8_t signal, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * Returns the executable, arguments, environment and working directory used to
 * spawn a process object, as passed to {@link red_spawn_process}, and the resulting
 * error code.
 */
int red_get_process_command(RED *red, uint16_t process_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_executable_string_id, uint16_t *ret_arguments_list_id, uint16_t *ret_environment_list_id, uint16_t *ret_working_directory_string_id);

/**
 * \ingroup BrickRED
 *
 * Returns the process ID and the user and group ID used to spawn a process object,
 * as passed to {@link red_spawn_process}, and the resulting error code.
 * 
 * The process ID is only valid if the state is *Running* or *Stopped*, see
 * {@link red_get_process_state}.
 */
int red_get_process_identity(RED *red, uint16_t process_id, uint8_t *ret_error_code, uint32_t *ret_pid, uint32_t *ret_uid, uint32_t *ret_gid);

/**
 * \ingroup BrickRED
 *
 * Returns the stdin, stdout and stderr files used to spawn a process object, as
 * passed to {@link red_spawn_process}, and the resulting error code.
 */
int red_get_process_stdio(RED *red, uint16_t process_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_stdin_file_id, uint16_t *ret_stdout_file_id, uint16_t *ret_stderr_file_id);

/**
 * \ingroup BrickRED
 *
 * Returns the current state, timestamp and exit code of a process object, and
 * the resulting error code.
 * 
 * Possible process states are:
 * 
 * * Unknown = 0
 * * Running = 1
 * * Error = 2
 * * Exited = 3
 * * Killed = 4
 * * Stopped = 5
 * 
 * The timestamp represents the UNIX time since when the process is in its current
 * state.
 * 
 * The exit code is only valid if the state is *Error*, *Exited*, *Killed* or
 * *Stopped* and has different meanings depending on the state:
 * 
 * * Error: error code for error occurred while spawning the process (see below)
 * * Exited: exit status of the process
 * * Killed: UNIX signal number used to kill the process
 * * Stopped: UNIX signal number used to stop the process
 * 
 * Possible exit/error codes in *Error* state are:
 * 
 * * InternalError = 125
 * * CannotExecute = 126
 * * DoesNotExist = 127
 * 
 * The *CannotExecute* error can be caused by the executable being opened for
 * writing.
 */
int red_get_process_state(RED *red, uint16_t process_id, uint8_t *ret_error_code, uint8_t *ret_state, uint64_t *ret_timestamp, uint8_t *ret_exit_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_programs(RED *red, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_programs_list_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_define_program(RED *red, uint16_t identifier_string_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_program_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_purge_program(RED *red, uint16_t program_id, uint32_t cookie, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_program_identifier(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_identifier_string_id);

/**
 * \ingroup BrickRED
 *
 * FIXME: root directory is absolute: <home>/programs/<identifier>
 */
int red_get_program_root_directory(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_root_directory_string_id);

/**
 * \ingroup BrickRED
 *
 * FIXME: working directory is relative to <home>/programs/<identifier>/bin
 */
int red_set_program_command(RED *red, uint16_t program_id, uint16_t executable_string_id, uint16_t arguments_list_id, uint16_t environment_list_id, uint16_t working_directory_string_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * FIXME: working directory is relative to <home>/programs/<identifier>/bin
 */
int red_get_program_command(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_executable_string_id, uint16_t *ret_arguments_list_id, uint16_t *ret_environment_list_id, uint16_t *ret_working_directory_string_id);

/**
 * \ingroup BrickRED
 *
 * FIXME: stdio file names are relative to <home>/programs/<identifier>/bin
 */
int red_set_program_stdio_redirection(RED *red, uint16_t program_id, uint8_t stdin_redirection, uint16_t stdin_file_name_string_id, uint8_t stdout_redirection, uint16_t stdout_file_name_string_id, uint8_t stderr_redirection, uint16_t stderr_file_name_string_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * FIXME: stdio file names are relative to <home>/programs/<identifier>/bin
 */
int red_get_program_stdio_redirection(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_stdin_redirection, uint16_t *ret_stdin_file_name_string_id, uint8_t *ret_stdout_redirection, uint16_t *ret_stdout_file_name_string_id, uint8_t *ret_stderr_redirection, uint16_t *ret_stderr_file_name_string_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_set_program_schedule(RED *red, uint16_t program_id, uint8_t start_mode, bool continue_after_error, uint32_t start_interval, uint16_t start_fields_string_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_program_schedule(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_start_mode, bool *ret_continue_after_error, uint32_t *ret_start_interval, uint16_t *ret_start_fields_string_id);

/**
 * \ingroup BrickRED
 *
 * FIXME: message is currently vaild in error-occurred state only
 */
int red_get_program_scheduler_state(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint8_t *ret_state, uint64_t *ret_timestamp, uint16_t *ret_message_string_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_continue_program_schedule(RED *red, uint16_t program_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_start_program(RED *red, uint16_t program_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_last_spawned_program_process(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_process_id, uint64_t *ret_timestamp);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_custom_program_option_names(RED *red, uint16_t program_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_names_list_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_set_custom_program_option_value(RED *red, uint16_t program_id, uint16_t name_string_id, uint16_t value_string_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_get_custom_program_option_value(RED *red, uint16_t program_id, uint16_t name_string_id, uint16_t session_id, uint8_t *ret_error_code, uint16_t *ret_value_string_id);

/**
 * \ingroup BrickRED
 *
 * 
 */
int red_remove_custom_program_option(RED *red, uint16_t program_id, uint16_t name_string_id, uint8_t *ret_error_code);

/**
 * \ingroup BrickRED
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
int red_get_identity(RED *red, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

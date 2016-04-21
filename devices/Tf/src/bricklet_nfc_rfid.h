/* ***********************************************************
 * This file was automatically generated on 2016-02-10.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.10                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_NFC_RFID_H
#define BRICKLET_NFC_RFID_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletNFCRFID NFC/RFID Bricklet
 */

/**
 * \ingroup BrickletNFCRFID
 *
 * Reads and writes NFC and RFID tags
 */
typedef Device NFCRFID;

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_REQUEST_TAG_ID 1

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_GET_TAG_ID 2

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_GET_STATE 3

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_AUTHENTICATE_MIFARE_CLASSIC_PAGE 4

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_WRITE_PAGE 5

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_REQUEST_PAGE 6

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_GET_PAGE 7

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletNFCRFID
 *
 * Signature: \code void callback(uint8_t state, bool idle, void *user_data) \endcode
 * 
 * This callback is called if the state of the NFC/RFID Bricklet changes.
 * See {@link nfc_rfid_get_state} for more information about the possible states.
 */
#define NFC_RFID_CALLBACK_STATE_CHANGED 8


/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_TAG_TYPE_MIFARE_CLASSIC 0

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_TAG_TYPE_TYPE1 1

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_TAG_TYPE_TYPE2 2

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_INITIALIZATION 0

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_IDLE 128

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_ERROR 192

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_REQUEST_TAG_ID 2

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_REQUEST_TAG_ID_READY 130

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_REQUEST_TAG_ID_ERROR 194

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_AUTHENTICATING_MIFARE_CLASSIC_PAGE 3

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_AUTHENTICATING_MIFARE_CLASSIC_PAGE_READY 131

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_AUTHENTICATING_MIFARE_CLASSIC_PAGE_ERROR 195

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_WRITE_PAGE 4

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_WRITE_PAGE_READY 132

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_WRITE_PAGE_ERROR 196

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_REQUEST_PAGE 5

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_REQUEST_PAGE_READY 133

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_STATE_REQUEST_PAGE_ERROR 197

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_KEY_A 0

/**
 * \ingroup BrickletNFCRFID
 */
#define NFC_RFID_KEY_B 1

/**
 * \ingroup BrickletNFCRFID
 *
 * This constant is used to identify a NFC/RFID Bricklet.
 *
 * The {@link nfc_rfid_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define NFC_RFID_DEVICE_IDENTIFIER 246

/**
 * \ingroup BrickletNFCRFID
 *
 * This constant represents the display name of a NFC/RFID Bricklet.
 */
#define NFC_RFID_DEVICE_DISPLAY_NAME "NFC/RFID Bricklet"

/**
 * \ingroup BrickletNFCRFID
 *
 * Creates the device object \c nfc_rfid with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void nfc_rfid_create(NFCRFID *nfc_rfid, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletNFCRFID
 *
 * Removes the device object \c nfc_rfid from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void nfc_rfid_destroy(NFCRFID *nfc_rfid);

/**
 * \ingroup BrickletNFCRFID
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the nfc_rfid_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is send and errors are
 * silently ignored, because they cannot be detected.
 */
int nfc_rfid_get_response_expected(NFCRFID *nfc_rfid, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletNFCRFID
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
int nfc_rfid_set_response_expected(NFCRFID *nfc_rfid, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletNFCRFID
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int nfc_rfid_set_response_expected_all(NFCRFID *nfc_rfid, bool response_expected);

/**
 * \ingroup BrickletNFCRFID
 *
 * Registers a callback with ID \c id to the function \c callback. The
 * \c user_data will be given as a parameter of the callback.
 */
void nfc_rfid_register_callback(NFCRFID *nfc_rfid, uint8_t id, void *callback, void *user_data);

/**
 * \ingroup BrickletNFCRFID
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int nfc_rfid_get_api_version(NFCRFID *nfc_rfid, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletNFCRFID
 *
 * To read or write a tag that is in proximity of the NFC/RFID Bricklet you 
 * first have to call this function with the expected tag type as parameter.
 * It is no problem if you don't know the tag type. You can cycle through 
 * the available tag types until the tag gives an answer to the request.
 * 
 * Current the following tag types are supported:
 * 
 * * Mifare Classic
 * * NFC Forum Type 1
 * * NFC Forum Type 2
 * 
 * After you call {@link nfc_rfid_request_tag_id} the NFC/RFID Bricklet will try to read 
 * the tag ID from the tag. After this process is done the state will change.
 * You can either register the {@link NFC_RFID_CALLBACK_STATE_CHANGED} callback or you can poll
 * {@link nfc_rfid_get_state} to find out about the state change.
 * 
 * If the state changes to *RequestTagIDError* it means that either there was 
 * no tag present or that the tag is of an incompatible type. If the state 
 * changes to *RequestTagIDReady* it means that a compatible tag was found 
 * and that the tag ID could be read out. You can now get the tag ID by
 * calling {@link nfc_rfid_get_tag_id}.
 * 
 * If two tags are in the proximity of the NFC/RFID Bricklet, this
 * function will cycle through the tags. To select a specific tag you have
 * to call {@link nfc_rfid_request_tag_id} until the correct tag id is found.
 * 
 * In case of any *Error* state the selection is lost and you have to
 * start again by calling {@link nfc_rfid_request_tag_id}.
 */
int nfc_rfid_request_tag_id(NFCRFID *nfc_rfid, uint8_t tag_type);

/**
 * \ingroup BrickletNFCRFID
 *
 * Returns the tag type, tag ID and the length of the tag ID 
 * (4 or 7 bytes are possible length). This function can only be called if the
 * NFC/RFID is currently in one of the *Ready* states. The returned ID
 * is the ID that was saved through the last call of {@link nfc_rfid_request_tag_id}.
 * 
 * To get the tag ID of a tag the approach is as follows:
 * 
 * 1. Call {@link nfc_rfid_request_tag_id}
 * 2. Wait for state to change to *RequestTagIDReady* (see {@link nfc_rfid_get_state} or
 *    {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 3. Call {@link nfc_rfid_get_tag_id}
 */
int nfc_rfid_get_tag_id(NFCRFID *nfc_rfid, uint8_t *ret_tag_type, uint8_t *ret_tid_length, uint8_t ret_tid[7]);

/**
 * \ingroup BrickletNFCRFID
 *
 * Returns the current state of the NFC/RFID Bricklet.
 * 
 * On startup the Bricklet will be in the *Initialization* state. The
 * initialization will only take about 20ms. After that it changes to *Idle*.
 * 
 * The functions of this Bricklet can be called in the *Idle* state and all of
 * the *Ready* and *Error* states.
 * 
 * Example: If you call {@link nfc_rfid_request_page}, the state will change to 
 * *RequestPage* until the reading of the page is finished. Then it will change
 * to either *RequestPageReady* if it worked or to *RequestPageError* if it
 * didn't. If the request worked you can get the page by calling {@link nfc_rfid_get_page}.
 * 
 * The same approach is used analogously for the other API functions.
 */
int nfc_rfid_get_state(NFCRFID *nfc_rfid, uint8_t *ret_state, bool *ret_idle);

/**
 * \ingroup BrickletNFCRFID
 *
 * Mifare Classic tags use authentication. If you want to read from or write to
 * a Mifare Classic page you have to authenticate it beforehand.
 * Each page can be authenticated with two keys: A (``key_number`` = 0) and B
 * (``key_number`` = 1). A new Mifare Classic
 * tag that has not yet been written to can can be accessed with key A
 * and the default key ``[0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF]``.
 * 
 * The approach to read or write a Mifare Classic page is as follows:
 * 
 * 1. Call {@link nfc_rfid_request_tag_id}
 * 2. Wait for state to change to *RequestTagIDReady* (see {@link nfc_rfid_get_state}
 *    or {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 3. If looking for a specific tag then call {@link nfc_rfid_get_tag_id} and check if the
 *    expected tag was found, if it was not found got back to step 1
 * 4. Call {@link nfc_rfid_authenticate_mifare_classic_page} with page and key for the page
 * 5. Wait for state to change to *AuthenticatingMifareClassicPageReady* (see
 *    {@link nfc_rfid_get_state} or {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 6. Call {@link nfc_rfid_request_page} or {@link nfc_rfid_write_page} to read/write page
 */
int nfc_rfid_authenticate_mifare_classic_page(NFCRFID *nfc_rfid, uint16_t page, uint8_t key_number, uint8_t key[6]);

/**
 * \ingroup BrickletNFCRFID
 *
 * Writes 16 bytes starting from the given page. How many pages are written
 * depends on the tag type. The page sizes are as follows:
 * 
 * * Mifare Classic page size: 16 byte (one page is written)
 * * NFC Forum Type 1 page size: 8 byte (two pages are written)
 * * NFC Forum Type 2 page size: 4 byte (four pages are written)
 * 
 * The general approach for writing to a tag is as follows:
 * 
 * 1. Call {@link nfc_rfid_request_tag_id}
 * 2. Wait for state to change to *RequestTagIDReady* (see {@link nfc_rfid_get_state} or
 *    {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 3. If looking for a specific tag then call {@link nfc_rfid_get_tag_id} and check if the
 *    expected tag was found, if it was not found got back to step 1
 * 4. Call {@link nfc_rfid_write_page} with page number and data
 * 5. Wait for state to change to *WritePageReady* (see {@link nfc_rfid_get_state} or
 *    {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 
 * If you use a Mifare Classic tag you have to authenticate a page before you
 * can write to it. See {@link nfc_rfid_authenticate_mifare_classic_page}.
 */
int nfc_rfid_write_page(NFCRFID *nfc_rfid, uint16_t page, uint8_t data[16]);

/**
 * \ingroup BrickletNFCRFID
 *
 * Reads 16 bytes starting from the given page and stores them into a buffer. 
 * The buffer can then be read out with {@link nfc_rfid_get_page}.
 * How many pages are read depends on the tag type. The page sizes are 
 * as follows:
 * 
 * * Mifare Classic page size: 16 byte (one page is read)
 * * NFC Forum Type 1 page size: 8 byte (two pages are read)
 * * NFC Forum Type 2 page size: 4 byte (four pages are read)
 * 
 * The general approach for reading a tag is as follows:
 * 
 * 1. Call {@link nfc_rfid_request_tag_id}
 * 2. Wait for state to change to *RequestTagIDReady* (see {@link nfc_rfid_get_state}
 *    or {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 3. If looking for a specific tag then call {@link nfc_rfid_get_tag_id} and check if the
 *    expected tag was found, if it was not found got back to step 1
 * 4. Call {@link nfc_rfid_request_page} with page number
 * 5. Wait for state to change to *RequestPageReady* (see {@link nfc_rfid_get_state}
 *    or {@link NFC_RFID_CALLBACK_STATE_CHANGED})
 * 6. Call {@link nfc_rfid_get_page} to retrieve the page from the buffer
 * 
 * If you use a Mifare Classic tag you have to authenticate a page before you
 * can read it. See {@link nfc_rfid_authenticate_mifare_classic_page}.
 */
int nfc_rfid_request_page(NFCRFID *nfc_rfid, uint16_t page);

/**
 * \ingroup BrickletNFCRFID
 *
 * Returns 16 bytes of data from an internal buffer. To fill the buffer
 * with specific pages you have to call {@link nfc_rfid_request_page} beforehand.
 */
int nfc_rfid_get_page(NFCRFID *nfc_rfid, uint8_t ret_data[16]);

/**
 * \ingroup BrickletNFCRFID
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
int nfc_rfid_get_identity(NFCRFID *nfc_rfid, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif

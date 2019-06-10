/* ----------------------------------------------------------------------------
 * Copyright (c) 2019 Semiconductor Components Industries, LLC (d/b/a
 * ON Semiconductor), All Rights Reserved
 *
 * This code is the property of ON Semiconductor and may not be redistributed
 * in any form without prior written permission from ON Semiconductor.
 * The terms of use and warranty for this code are covered by contractual
 * agreements between ON Semiconductor and the licensee.
 *
 * This is Reusable Code.
 *
 * ----------------------------------------------------------------------------
 */

#include "ble_gap.h"
#include "ble_gatt.h"
#include "ble_dfus.h"
#include "msg_handler.h"
#include "sys_fota.h"
#include "sys_boot.h"

#include "app_att_db.h"
#include "app_customss.h"
#include "app_sockets.h"
#include "ble_dfus.h"

/* ----------------------------------------------------------------------------
 * Defines
 * ------------------------------------------------------------------------- */

const struct att_db_desc app_att_db[APP_ATT_NB] =
{
	/**** Service 0 ****/
	CS_SERVICE_UUID_128(CS_SERVICE0, CS_SVC_UUID),

	/* To the BLE transfer */
	CS_CHAR_UUID_128(CS_TX_VALUE_CHAR0,             // attidx_char
			CS_TX_VALUE_VAL0,                       // attidx_val
			CS_CHAR_RX_UUID,                        // uuid
			PERM(RD, ENABLE) | PERM(NTF, ENABLE),   // perm
			sizeof(app_env_cs.to_air_buffer),       // length
			app_env_cs.to_air_buffer,               // data
			NULL),                                  // callback
	// Client Characteristic Configuration descriptor
	CS_CHAR_CCC(CS_TX_VALUE_CCC0,                   // attidx
			app_env_cs.to_air_cccd_value,           // data
			NULL),                                  // callback
	// Characteristic User Description descriptor
	CS_CHAR_USER_DESC(CS_TX_VALUE_USR_DSCP0,        // attidx
			sizeof(CS_RX_CHAR_NAME) - 1,            // length
			CS_RX_CHAR_NAME,                        // data
			NULL),                                  // callback

	/* From the BLE transfer */
	CS_CHAR_UUID_128(CS_RX_VALUE_CHAR0,             // attidx_char
			CS_RX_VALUE_VAL0,                       // attidx_val
			CS_CHAR_TX_UUID,                        // uuid
			PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),// perm
			sizeof(app_env_cs.from_air_buffer),     // length
			app_env_cs.from_air_buffer,             // data
			CUSTOMSS_RXCharCallback),               // callback
	// Client Characteristic Configuration descriptor
	CS_CHAR_CCC(CS_RX_VALUE_CCC0,                   // attidx
			app_env_cs.from_air_cccd_value,         // data
			NULL),                                  // callback
	// Characteristic User Description descriptor
	CS_CHAR_USER_DESC(CS_RX_VALUE_USR_DSCP0,        // attidx
			sizeof(CS_TX_CHAR_NAME) - 1,            // length
			CS_TX_CHAR_NAME,                        // data
			NULL),                                  // callback

	/* To the BLE long transfer */
	CS_CHAR_UUID_128(CS_TX_LONG_VALUE_CHAR0,        // attidx_char
			CS_TX_LONG_VALUE_VAL0,                  // attidx_val
			CS_CHAR_LONG_RX_UUID,                   // uuid
#ifdef TX_VALUE_LONG_INDICATION
			PERM(RD, ENABLE) | PERM(IND, ENABLE),   // perm
#else
			PERM(RD, ENABLE) | PERM(NTF, ENABLE),   // perm
#endif /* TX_VALUE_LONG_INDICATION */
			sizeof(app_env_cs.to_air_buffer_long),  // length
			app_env_cs.to_air_buffer_long,          // data
			NULL),                                  // callback
	// Client Characteristic Configuration descriptor
	CS_CHAR_CCC(CS_TX_LONG_VALUE_CCC0,              // attidx
			app_env_cs.to_air_cccd_value_long,      // data
			NULL),                                  // callback
	// Characteristic User Description descriptor
	CS_CHAR_USER_DESC(CS_TX_LONG_VALUE_USR_DSCP0,   // attidx
			sizeof(CS_RX_CHAR_LONG_NAME) - 1,       // length
			CS_RX_CHAR_LONG_NAME,                   // data
			NULL),                                  // callback

	/* From the BLE long transfer */
	CS_CHAR_UUID_128(CS_RX_LONG_VALUE_CHAR0,        // attidx_char
			CS_RX_LONG_VALUE_VAL0,                  // attidx_val
			CS_CHAR_LONG_TX_UUID,                   // uuid
			PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE)| PERM(WRITE_COMMAND, ENABLE),// perm
			sizeof(app_env_cs.from_air_buffer_long),// length
			app_env_cs.from_air_buffer_long,        // data
			CUSTOMSS_RXLongCharCallback),           // callback
	// Client Characteristic Configuration descriptor
	CS_CHAR_CCC(CS_RX_LONG_VALUE_CCC0,              // attidx
			app_env_cs.from_air_cccd_value_long,    // data
			NULL),                                  // callback
	// Characteristic User Description descriptor
	CS_CHAR_USER_DESC(CS_RX_LONG_VALUE_USR_DSCP0,   // attidx
			sizeof(CS_TX_CHAR_LONG_NAME)- 1,        // length
			CS_TX_CHAR_LONG_NAME,                   // data
			NULL),                                  // callback


	/* Service DFU */
	CS_SERVICE_UUID_128(DFU_SVC, SYS_FOTA_DFU_SVC_UUID),
#if (SHOW_DEVID)
	/* Device ID Characteristic in Service DFU */
	CS_CHAR_UUID_128(DFU_DEVID_CHAR, DFU_DEVID_VAL,
			SYS_FOTA_DFU_DEVID_UUID, PERM(RD, ENABLE), 16,
			NULL, DfusCallback),
	CS_CHAR_USER_DESC(DFU_DEVID_NAME,                // attidx
			sizeof("Device ID") - 1,                 // length
			"Device ID",                             // data
			NULL),                                   // callback
#endif
#if (SHOW_BOOTVER)
	/* BootLoader Version Characteristic in Service DFU */
	CS_CHAR_UUID_128(DFU_BOOTVER_CHAR, DFU_BOOTVER_VAL, SYS_FOTA_DFU_BOOTVER_UUID,
			PERM(RD, ENABLE),
			sizeof(Sys_Boot_app_version_t), NULL, DfusCallback),
	CS_CHAR_USER_DESC(DFU_BOOTVER_NAME,                 // attidx
			sizeof("Bootloader Version") - 1,// length
			"Bootloader Version",// data
			NULL),// callback
#endif
#if (SHOW_STACKVER)
	/* BLE Stack Version Characteristic in Service DFU */
			CS_CHAR_UUID_128(DFU_STACKVER_CHAR, DFU_STACKVER_VAL,
					SYS_FOTA_DFU_STACKVER_UUID, PERM(RD, ENABLE),
					sizeof(Sys_Boot_app_version_t), NULL,
					DfusCallback),
	CS_CHAR_USER_DESC(DFU_STACKVER_NAME,                 // attidx
			sizeof("BLE Stack Version") - 1,// length
			"BLE Stack Version",// data
			NULL),// callback
#endif
#if (SHOW_APPVER)
	/* Application Version Characteristic in Service DFU */
			CS_CHAR_UUID_128(DFU_APPVER_CHAR, DFU_APPVER_VAL,
					SYS_FOTA_DFU_APPVER_UUID, PERM(RD, ENABLE),
					sizeof(Sys_Boot_app_version_t), NULL,
					DfusCallback),
	CS_CHAR_USER_DESC(DFU_APPVER_NAME,                   // attidx
			sizeof("Application Version") - 1,// length
			"Application Version",// data
			NULL),// callback
#endif
#if (SHOW_BUILDID)
	/* Build ID Characteristic in Service DFU */
	CS_CHAR_UUID_128(DFU_BUILDID_CHAR, DFU_BUILDID_VAL, SYS_FOTA_DFU_BUILDID_UUID,
			PERM(RD, ENABLE),
			32, NULL, DfusCallback),
	CS_CHAR_USER_DESC(DFU_BUILDID_NAME,                  // attidx
			sizeof("BLE Stack Build ID") - 1,// length
			"BLE Stack Build ID",// data
			NULL),// callback
#endif
	/* Enter mode Characteristic in Service DFU */
			CS_CHAR_UUID_128(DFU_ENTER_CHAR, DFU_ENTER_VAL,
					SYS_FOTA_DFU_ENTER_UUID,
					PERM(WRITE_REQ, ENABLE), 1, NULL, DfusCallback),
	CS_CHAR_USER_DESC(DFU_ENTER_NAME,                   // attidx
			sizeof("Enter DFU mode") - 1,// length
			"Enter DFU mode",// data
			NULL),// callback

	/* SOCKET Service */
	CS_SERVICE_UUID_128(SOCKETS_SVC, SOCKETS_SVC_UUID),

	/* SOCKET Status Characteristic */
	CS_CHAR_UUID_128(SOCKETS_STATUS_CHAR,           // attidx_char
			SOCKETS_STATUS_VAL,                     // attidx_val
			SOCKETS_STATUS_UUID,                    // uuid
			PERM(RD, ENABLE) | PERM(NTF, ENABLE),   // perm
			sizeof(app_env_sockets.status_att_val), // length
			&app_env_sockets.status_att_val,        // data
			NULL),                                  // callback
	// Client Characteristic Configuration descriptor
	CS_CHAR_CCC(SOCKETS_STATUS_CCCD,                // attidx
			app_env_sockets.status_cccd_val,        // data
			NULL),                                  // callback
	// Characteristic User Description descriptor
	CS_CHAR_USER_DESC(SOCKETS_STATUS_USR_DSCP,      // attidx
			sizeof(SOCKETS_STATUS_CHAR_NAME) - 1,   // length
			SOCKETS_STATUS_CHAR_NAME,               // data
			NULL),

	/* SOCKET Command Characteristic */
	CS_CHAR_UUID_128(SOCKETS_COMMAND_CHAR,          // attidx_char
			SOCKETS_COMMAND_VAL,                    // attidx_val
			SOCKETS_COMMAND_UUID,                   // uuid
			PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),// perm
			SOCKETS_COMMAND_VALUE_LENGTH,           // length
			NULL,                                   // data
			SOCKETS_CommandCallback),               // callback

	// Characteristic User Description descriptor
	CS_CHAR_USER_DESC(SOCKETS_COMMAND_USR_DSCP,     // attidx
			sizeof(SOCKETS_COMMAND_CHAR_NAME) - 1,  // length
			SOCKETS_COMMAND_CHAR_NAME,              // data
			NULL),                                  // callback


};

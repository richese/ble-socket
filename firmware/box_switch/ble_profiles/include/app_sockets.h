/* ----------------------------------------------------------------------------
 * Copyright (c) 2018 Semiconductor Components Industries, LLC (d/b/a
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
 * app_customss.h
 * - Application-specific Bluetooth custom service server header file
 * ------------------------------------------------------------------------- */

#ifndef BLE_SOCKETS_H
#define BLE_SOCKETS_H

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include <rsl10_ke.h>
#include <gattc_task.h>

#include <app_att_db.h>

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

/* Custom service UUIDs and characteristics
 *
 * uuidgen --sha1 --namespace @dns --name "socket_switch.service.richese.eu"
 * 75ee98e2-e726-52c4-a138-7900d5391b5c
 */

/* Custom service UUIDs */
#define SOCKETS_SVC_UUID                { 0x5c, 0x1b, 0x39, 0xd5, 0x01, 0x79, \
                                          0x38, 0xa1, 0xc4, 0x52, 0x26, 0xe7, \
                                          0xe2, 0x98, 0xee, 0x75 }
#define SOCKETS_STATUS_UUID             { 0x5c, 0x1b, 0x39, 0xd5, 0x02, 0x79, \
                                          0x38, 0xa1, 0xc4, 0x52, 0x26, 0xe7, \
                                          0xe2, 0x98, 0xee, 0x75 }
#define SOCKETS_COMMAND_UUID            { 0x5c, 0x1b, 0x39, 0xd5, 0x03, 0x79, \
                                          0x38, 0xa1, 0xc4, 0x52, 0x26, 0xe7, \
                                          0xe2, 0x98, 0xee, 0x75 }

#define SOCKETS_COMMAND_VALUE_LENGTH      (1)

#define SOCKETS_STATUS_CHAR_NAME          "Status Value"
#define SOCKETS_COMMAND_CHAR_NAME         "Command Value"

#define SOCKETS_CMD_ON                 "\x11"
#define SOCKETS_CMD_OFF                "\x00"

/* Pin Mappings */
#define SOCKETS_PIN_RELAY_1            (0)
#define SOCKETS_PIN_RELAY_2            (1)
#define SOCKETS_PIN_RELAY_3            (2)
#define SOCKETS_PIN_RELAY_4            (3)

#define SOCKETS_PIN_SOCKET             SOCKETS_PIN_RELAY_4
#define SOCKETS_PIN_LED_BTN            SOCKETS_PIN_RELAY_1
#define SOCKETS_PIN_BTN                (13)

// kernel timeout x * 10ms
#define SOCKETS_BTN_TIMEOUT_VAL        (100) /* 1000 ms */

struct app_env_tag_sockets
{
	uint8_t status_att_val;
	uint8_t status_cccd_val[2];

	bool conn_encrypted[BLE_CONNECTION_MAX];

	bool btn_evt;
};

enum sockets_app_msg_id
{
    SOCKETS_UPDATE = TASK_FIRST_MSG(TASK_ID_APP) + 70,
	SOCKETS_NOTIFY,
	SOCKETS_BTN_TIMEOUT
};

/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/

extern struct app_env_tag_sockets app_env_sockets;

/* ----------------------------------------------------------------------------
 * Function prototype definitions
 * --------------------------------------------------------------------------*/
void SOCKETS_Initialize(void);

void SOCKETS_Poll(void);

//void CUSTOMSS_NotifyOnTimeout(uint32_t timeout);

void SOCKETS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id);

uint8_t SOCKETS_CommandCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *toData, const uint8_t *fromData, uint16_t lenData,
                                uint16_t operation);
//
//uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
//                                    uint8_t *toData, const uint8_t *fromData, uint16_t lenData,
//                                    uint16_t operation);


/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* BLE_SOCKETS_H */

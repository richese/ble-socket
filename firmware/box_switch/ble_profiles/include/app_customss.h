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

#ifndef BLE_CUSTOMSS_H
#define BLE_CUSTOMSS_H

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

/* Custom service UUIDs and characteristics */

/* Custom service UUIDs */
#define CS_SVC_UUID                     { 0x24, 0xdc, 0x0e, 0x6e, 0x01, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_TX_UUID                 { 0x24, 0xdc, 0x0e, 0x6e, 0x02, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_RX_UUID                 { 0x24, 0xdc, 0x0e, 0x6e, 0x03, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_LONG_RX_UUID            { 0x24, 0xdc, 0x0e, 0x6e, 0x04, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_LONG_TX_UUID            { 0x24, 0xdc, 0x0e, 0x6e, 0x05, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }

#define CS_VALUE_MAX_LENGTH          20
#define CS_LONG_VALUE_MAX_LENGTH     40

#define CS_TX_CHAR_NAME            "TX_VALUE"
#define CS_RX_CHAR_NAME            "RX_VALUE"
#define CS_TX_CHAR_LONG_NAME       "TX_VALUE_LONG"
#define CS_RX_CHAR_LONG_NAME       "RX_VALUE_LONG"

/* Uncomment to use indications in the RX_VALUE_LONG characteristic */
//#define TX_VALUE_LONG_INDICATION


struct app_env_tag_cs
{
    /* To BLE transfer buffer */
    uint8_t to_air_buffer[CS_VALUE_MAX_LENGTH];
    uint8_t to_air_cccd_value[2];

    /* From BLE transfer buffer */
    uint8_t from_air_buffer[CS_VALUE_MAX_LENGTH];
    uint8_t from_air_cccd_value[2];

    /* To BLE long transfer buffer */
    uint8_t to_air_buffer_long[CS_LONG_VALUE_MAX_LENGTH];
    uint8_t to_air_cccd_value_long[2];

    /* From BLE long transfer buffer */
    uint8_t from_air_buffer_long[CS_LONG_VALUE_MAX_LENGTH];
    uint8_t from_air_cccd_value_long[2];
};

enum custom_app_msg_id
{
    CUSTOMSS_NTF_TIMEOUT = TASK_FIRST_MSG(TASK_ID_APP) + 60
};

/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/

extern struct app_env_tag_cs app_env_cs;

/* ----------------------------------------------------------------------------
 * Function prototype definitions
 * --------------------------------------------------------------------------*/
void CUSTOMSS_Initialize(void);

void CUSTOMSS_NotifyOnTimeout(uint32_t timeout);

void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id);

uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *toData, const uint8_t *fromData, uint16_t lenData,
                                uint16_t operation);

uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                    uint8_t *toData, const uint8_t *fromData, uint16_t lenData,
                                    uint16_t operation);


/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* BLE_CUSTOMSS_H */

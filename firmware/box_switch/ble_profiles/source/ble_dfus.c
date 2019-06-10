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
 * ble_dfus.c
 * - Custom Bluetooth DFU server source file
 * ----------------------------------------------------------------------------
 * $Revision: 1.2 $
 * $Date: 2019/03/15 21:19:15 $
 * ------------------------------------------------------------------------- */

#include "ble_gap.h"
#include "ble_gatt.h"
#include "ble_dfus.h"
#include "msg_handler.h"
#include "sys_fota.h"
#include "sys_boot.h"

/* ----------------------------------------------------------------------------
 * Defines
 * ------------------------------------------------------------------------- */

/* switches on/off optional DFU characteristics */
#define SHOW_DEVID                  1
#define SHOW_BOOTVER                0
#define SHOW_STACKVER               1
#define SHOW_APPVER                 1
#define SHOW_BUILDID                0

#define DFU_ENTER_DELAY             0.1

extern const Sys_Fota_version_t Sys_Boot_app_version;

/* ----------------------------------------------------------------------------
 * Local variables and types
 * --------------------------------------------------------------------------*/

typedef enum
{
    DFU_ENTER_TIMEOUT = TASK_FIRST_MSG(TASK_ID_APP) + 250,
    DFU_DISCONNECT
} dfu_msg_id_t;

/* ----------------------------------------------------------------------------
 * Function      : uint8_t DfusCallback(uint8_t conidx, uint16_t attidx,
 *                       uint16_t handle, uint8_t *toData,
 *                       const uint8_t *fromData, uint16_t lenData,
 *                       uint16_t operation)
 * ----------------------------------------------------------------------------
 * Description   : User callback data access function for the DFU
 *                 characteristics. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 * Inputs        : - conidx    - connection index
 *                 - attidx    - attribute index in the user defined database
 *                 - handle    - attribute handle allocated in the BLE stack
 *                 - to        - pointer to destination buffer
 *                 - from      - pointer to source buffer
 *                               "to" and "from" may be a pointer to the
 *                               'att_db' characteristic buffer or the BLE
 *                               stack buffer, depending if the "operation" is
 *                               a write or a read.
 *                 - length    - length of data to be copied
 *                 - operation - GATTC_READ_REQ_IND or GATTC_WRITE_REQ_IND
 * Outputs       : return value - read or write  status (one of enum hl_err)
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
uint8_t DfusCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                            uint8_t *toData, const uint8_t *fromData,
                            uint16_t lenData,  uint16_t operation)
{
    if (operation == GATTC_WRITE_REQ_IND)
    {
        switch (attidx)
        {
            case DFU_ENTER_VAL:
            {
               if (*fromData != 1)
               {
                   return GATT_ERR_WRITE;
               }
               ke_msg_send_basic(DFU_DISCONNECT,
                                 KE_BUILD_ID(TASK_APP, conidx),
                                 KE_BUILD_ID(TASK_APP, conidx));
            }
            break;
        }
    }
    else if (operation == GATTC_READ_REQ_IND)
    {
        switch (attidx)
        {
        #if (SHOW_DEVID)
            case DFU_DEVID_VAL:
            {
                const Sys_Fota_version_t *version;
                version = (const Sys_Fota_version_t *)Sys_Boot_GetVersion(APP_BASE_ADR);
                memcpy(toData, &version->dev_id, lenData);
            }
            break;
        #endif
        #if (SHOW_BOOTVER)
            case DFU_BOOTVER_VAL:
            {
                memcpy(toData, Sys_Boot_GetVersion(BOOT_BASE_ADR), lenData);
            }
            break;
        #endif
        #if (SHOW_STACKVER)
            case DFU_STACKVER_VAL:
            {
                memcpy(toData, Sys_Boot_GetVersion(APP_BASE_ADR), lenData);
            }
            break;
        #endif
        #if (SHOW_APPVER)
            case DFU_APPVER_VAL:
            {
                memcpy(toData, &Sys_Boot_app_version.app_id, lenData);
            }
            break;
        #endif
        #if (SHOW_BUILDID)
            case DFU_BUILDID_VAL:
            {
                memcpy(toData,
                       Sys_Boot_GetDscr(APP_BASE_ADR)->build_id_a, lenData);
            }
            break;
        #endif
        }
    }
    return ATT_ERR_NO_ERROR;
}

/* ----------------------------------------------------------------------------
 * Function      : void DFUS_Start(void)
 * ----------------------------------------------------------------------------
 * Description   : Start the DFU Server
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
static void DFUS_Start(void)
{

}

/* ----------------------------------------------------------------------------
 * Function      : void Dfus_MsgHandler(ke_msg_id_t const msg_id,
 *                                      void const *param,
 *                                      ke_task_id_t const dest_id,
 *                                      ke_task_id_t const src_id)
 * ----------------------------------------------------------------------------
 * Description   : Handle all events related to the DFU service
 * Inputs        : - msg_id     - Kernel message ID number
 *                 - param      - Message parameter
 *                 - dest_id    - Destination task ID number
 *                 - src_id     - Source task ID number
 * Outputs       : return value - Indicate if the message was consumed;
 *                                compare with KE_MSG_CONSUMED
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
static void Dfus_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                            ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    switch (msg_id)
    {
        case GAPM_CMP_EVT:
        {
            const struct gapm_cmp_evt *p = param;

//            if (p->operation == GATTM_ADD_SVC_RSP && GATTM_GetServiceAddedCount() == 1)
//            {
//                DFUS_Start();
//            }s
        }
        break;
        case DFU_DISCONNECT:
        {
            GAPC_DisconnectAll(CO_ERROR_REMOTE_USER_TERM_CON);
            ke_timer_set(DFU_ENTER_TIMEOUT, dest_id,
                         KE_TIME_IN_SEC(DFU_ENTER_DELAY));
        }
        break;
        case DFU_ENTER_TIMEOUT:
        {
            Sys_Fota_StartDfu(1);
        }
        break;

        case GATTM_ADD_SVC_RSP:
        {
        	if (GATTM_GetServiceAddedCount() == 1)
        	{
        		DFUS_Start();
        	}
        }
        break;
    }
}

/* ----------------------------------------------------------------------------
 * Function      : void DFUS_Initialize(void)
 * ----------------------------------------------------------------------------
 * Description   : Initialize the DFU Server
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void DFUS_Initialize(void)
{
    MsgHandler_Add(GATTM_ADD_SVC_RSP, Dfus_MsgHandler);
    MsgHandler_Add(DFU_ENTER_TIMEOUT, Dfus_MsgHandler);
    MsgHandler_Add(DFU_DISCONNECT, Dfus_MsgHandler);
}

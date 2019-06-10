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
 * app_customss.c
 * - Application-specific Bluetooth custom service server source file
 * ------------------------------------------------------------------------- */

#include <ble_gap.h>
#include <ble_gatt.h>
#include <msg_handler.h>
#include <app_trace.h>
#include <app_sockets.h>

/* Global variable definition */
struct app_env_tag_sockets app_env_sockets;


/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_Initialize(void)
 * ----------------------------------------------------------------------------
 * Description   : Initialize custom service environment
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void SOCKETS_Initialize(void)
{
	memset(&app_env_sockets, 0, sizeof(struct app_env_tag_sockets));

	app_env_sockets.status_cccd_val[0] = ATT_CCC_START_NTF;
	app_env_sockets.status_cccd_val[1] = 0x00;

	MsgHandler_Add(GAPC_CONNECTION_REQ_IND, SOCKETS_MsgHandler);
	MsgHandler_Add(GAPC_PAIRING_SUCCEED, SOCKETS_MsgHandler);
	MsgHandler_Add(GAPC_ENCRYPT_IND, SOCKETS_MsgHandler);
    MsgHandler_Add(SOCKETS_UPDATE, SOCKETS_MsgHandler);
    MsgHandler_Add(SOCKETS_NOTIFY, SOCKETS_MsgHandler);
    MsgHandler_Add(SOCKETS_BTN_TIMEOUT, SOCKETS_MsgHandler);


    /* --------------------------------------
     *  Board specific configuration.
     * -------------------------------------- */

    // Relay Pads
    Sys_DIO_Config(SOCKETS_PIN_RELAY_1, DIO_MODE_GPIO_OUT_1 | DIO_NO_PULL);
    Sys_DIO_Config(SOCKETS_PIN_RELAY_2, DIO_MODE_GPIO_OUT_1 | DIO_NO_PULL);
    Sys_DIO_Config(SOCKETS_PIN_RELAY_3, DIO_MODE_GPIO_OUT_1 | DIO_NO_PULL);
    Sys_DIO_Config(SOCKETS_PIN_RELAY_4, DIO_MODE_GPIO_OUT_1 | DIO_NO_PULL);

    // Button input
    Sys_DIO_Config(SOCKETS_PIN_BTN, DIO_MODE_GPIO_IN_0 | DIO_STRONG_PULL_UP | DIO_LPF_ENABLE);
	Sys_DIO_IntConfig(0,
			DIO_DEBOUNCE_ENABLE | DIO_EVENT_FALLING_EDGE | SOCKETS_PIN_BTN,
			DIO_DEBOUNCE_SLOWCLK_DIV32, 100);
	NVIC_ClearPendingIRQ(DIO0_IRQn);
	NVIC_EnableIRQ(DIO0_IRQn);
}

void SOCKETS_Poll(void)
{
	if (app_env_sockets.btn_evt == true)
	{
		app_env_sockets.btn_evt = false;

		PRINTF("\r\n%s : Button pressed\r\n", __FUNCTION__);

		if (app_env_sockets.status_att_val)
		{
			app_env_sockets.status_att_val = 0;
		}
		else
		{
			app_env_sockets.status_att_val = 1;
		}

		ke_msg_send_basic(SOCKETS_UPDATE, TASK_APP, TASK_APP);

		ke_timer_set(SOCKETS_BTN_TIMEOUT, TASK_APP, SOCKETS_BTN_TIMEOUT_VAL);
	}
}

void DIO0_IRQHandler(void)
{
	app_env_sockets.btn_evt = true;

	NVIC_DisableIRQ(DIO0_IRQn);
}

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id,
 *                                          void const *param,
 *                                          ke_task_id_t const dest_id,
 *                                          ke_task_id_t const src_id)
 * ----------------------------------------------------------------------------
 * Description   : Handle all events related to the custom service
 * Inputs        : - msg_id     - Kernel message ID number
 *                 - param      - Message parameter
 *                 - dest_id    - Destination task ID number
 *                 - src_id     - Source task ID number
 * Outputs       : return value - Indicate if the message was consumed;
 *                                compare with KE_MSG_CONSUMED
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void SOCKETS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    switch (msg_id)
    {
    	/* Reset state of associated connection when new connection request is
    	 * received.
    	 */
    	case GAPC_CONNECTION_REQ_IND:
    	{
    		uint8_t conidx = KE_IDX_GET(src_id);

    		app_env_sockets.conn_encrypted[conidx] = false;
    	}
    	break;

    	/* Listen for connection encrypted indication to allow writing to
    	 * command char.
    	 */
    	case GAPC_PAIRING_SUCCEED:
    	case GAPC_ENCRYPT_IND:
    	{
    		uint8_t conidx = KE_IDX_GET(src_id);

    		app_env_sockets.conn_encrypted[conidx] = true;

    		PRINTF("\r\n%s : Encryption established\r\n", __FUNCTION__);

    		/* Send initial notification after connection is established. */
    		ke_msg_send_basic(SOCKETS_NOTIFY, TASK_APP, TASK_APP);
    	}
    	break;

        case SOCKETS_UPDATE:
        {
		PRINTF("\r\n%s : SOCKETS_UPDATE : status=%d", __FUNCTION__,
				app_env_sockets.status_att_val);

        	if (app_env_sockets.status_att_val)
        	{
        		Sys_GPIO_Set_Low(SOCKETS_PIN_SOCKET);
        		Sys_GPIO_Set_Low(SOCKETS_PIN_LED_BTN);
        	}
        	else
        	{
        		Sys_GPIO_Set_High(SOCKETS_PIN_SOCKET);
				Sys_GPIO_Set_High(SOCKETS_PIN_LED_BTN);
        	}

        	ke_msg_send_basic(SOCKETS_NOTIFY, TASK_APP, TASK_APP);
        }
        break;

        /* Notify all connected devices with current status. */
        case SOCKETS_NOTIFY:
        {
        	for (int i = 0; i < BLE_CONNECTION_MAX; ++i)
        	{
        		if (GAPC_IsConnectionActive(i) == true)
        		{
        			GATTC_SendEvtCmd(i, GATTC_NOTIFY, 0,
        					GATTM_GetHandle(SOCKETS_STATUS_VAL), 1,
							&app_env_sockets.status_att_val);

        			PRINTF(
						"\r\n%s : SOCKETS_NOTIFY(%d) : notification status=%d \r\n",
						__FUNCTION__, i, app_env_sockets.status_att_val);
        		}
        	}
        }
        break;

        /* Re-enable button interrupt after some delay. */
        case SOCKETS_BTN_TIMEOUT:
        {
        	PRINTF("\r\n%s : SOCKETS_BTN_TIMEOUT\r\n", __FUNCTION__);

        	NVIC_ClearPendingIRQ(DIO0_IRQn);
        	NVIC_EnableIRQ(DIO0_IRQn);
        }
        break;
    }
}

uint8_t SOCKETS_CommandCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *toData, const uint8_t *fromData, uint16_t lenData,
                                uint16_t operation)
{
	uint8_t retval = ATT_ERR_NO_ERROR;

	if (app_env_sockets.conn_encrypted[conidx] == false)
	{
		return ATT_ERR_INSUFF_AUTHEN;
	}

	if (operation != GATTC_WRITE_REQ_IND)
	{
		return ATT_ERR_REQUEST_NOT_SUPPORTED;
	}

	if (lenData == SOCKETS_COMMAND_VALUE_LENGTH)
	{
		if (memcmp(fromData, SOCKETS_CMD_ON, SOCKETS_COMMAND_VALUE_LENGTH) == 0)
		{
			// ON command
			app_env_sockets.status_att_val = 1;

			PRINTF("\r\n%s : ON\r\n", __FUNCTION__);

			ke_msg_send_basic(SOCKETS_UPDATE, KE_BUILD_ID(TASK_APP, conidx), KE_BUILD_ID(TASK_APP, conidx));
		}
		else if (memcmp(fromData, SOCKETS_CMD_OFF, SOCKETS_COMMAND_VALUE_LENGTH) == 0)
		{
			// OFF command
			app_env_sockets.status_att_val = 0;

			PRINTF("\r\n%s : OFF\r\n", __FUNCTION__);

			ke_msg_send_basic(SOCKETS_UPDATE, KE_BUILD_ID(TASK_APP, conidx), KE_BUILD_ID(TASK_APP, conidx));
		}
		else
		{
			// UNKNOWN command
			retval = ATT_ERR_REQUEST_NOT_SUPPORTED;
		}
	}
	else
	{
		retval = ATT_ERR_INVALID_ATTRIBUTE_VAL_LEN;
	}

	return retval;
}

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_RXCharCallback(uint8_t conidx,
 *                         uint16_t attidx, uint16_t handle, uint8_t *toData,
 *                         uint8_t *fromData, uint16_t lenData,
 *                         uint16_t operation)
 * ----------------------------------------------------------------------------
 * Description   : User callback data access function for the RX
 *                 characteristic. This function is called by the BLE
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
 *                 - operation - GATTC_ReadReqInd or GATTC_WriteReqInd
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
//uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
//                                uint8_t *to, const uint8_t *from, uint16_t length,
//                                uint16_t operation)
//{
//    memcpy(to, from, length);
//#if RSL10_DEBUG
//    PRINTF("\n\rRXCharCallback (%d): ", conidx, length);
//    for (int i = 0; i < length; i++)
//    {
//        PRINTF("%02x ", app_env_cs.from_air_buffer[i]);
//    }
//#endif    /* if RSL10_DEBUG */
//    return ATT_ERR_NO_ERROR;
//}

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_RXLongCharCallback(uint8_t conidx,
 *                          uint16_t attidx, uint16_t handle, uint8_t *to,
 *                          uint8_t *from, uint16_t length, uint16_t operation)
 * ----------------------------------------------------------------------------
 * Description   : User callback data access function for the RX Long
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction. See att_db.
 *                 When a write occurs in the RX long characteristic, besides
 *                 updating the database value, this function updates the TX
 *                 Long characteristic value with the complement if the written
 *                 value.
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
 *                 - operation - GATTC_ReadReqInd or GATTC_WriteReqInd
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
//uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
//                                    uint8_t *to, const uint8_t *from, uint16_t length,
//                                    uint16_t operation)
//{
//    memcpy(to, from, length);
//#if RSL10_DEBUG
//    PRINTF("\n\rRXLongCharCallback (%d): ", conidx, length);
//    for (int i = 0; i < length; i++)
//    {
//        PRINTF("%02x ", app_env_cs.from_air_buffer_long[i]);
//    }
//#endif  /* if RSL10_DEBUG */
//    PRINTF("\r\n");
//
//    /* Update TX long characteristic with the inverted version of
//     * RX long characteristic just received */
//    if(operation == GATTC_WRITE_REQ_IND)
//    {
//        for (uint8_t i = 0; i < CS_LONG_VALUE_MAX_LENGTH; i++)
//        {
//            app_env_cs.to_air_buffer_long[i] = 0xFF ^ app_env_cs.from_air_buffer_long[i];
//        }
//    }
//    return ATT_ERR_NO_ERROR;
//}


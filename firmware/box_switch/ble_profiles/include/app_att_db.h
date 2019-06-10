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

#ifndef APP_ATT_DB_H
#define APP_ATT_DB_H

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

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

/* switches on/off optional DFU characteristics */
#define SHOW_DEVID                  1
#define SHOW_BOOTVER                0
#define SHOW_STACKVER               1
#define SHOW_APPVER                 1
#define SHOW_BUILDID                0


enum app_atts
{
    /* Service 0 */
    CS_SERVICE0,

    /* TX Characteristic in Service 0 */
    CS_TX_VALUE_CHAR0,
    CS_TX_VALUE_VAL0,
    CS_TX_VALUE_CCC0,
    CS_TX_VALUE_USR_DSCP0,

    /* RX Characteristic in Service 0 */
    CS_RX_VALUE_CHAR0,
    CS_RX_VALUE_VAL0,
    CS_RX_VALUE_CCC0,
    CS_RX_VALUE_USR_DSCP0,

    /* TX Long Characteristic in Service 0 */
    CS_TX_LONG_VALUE_CHAR0,
    CS_TX_LONG_VALUE_VAL0,
    CS_TX_LONG_VALUE_CCC0,
    CS_TX_LONG_VALUE_USR_DSCP0,

    /* RX Long Characteristic in Service 0 */
    CS_RX_LONG_VALUE_CHAR0,
    CS_RX_LONG_VALUE_VAL0,
    CS_RX_LONG_VALUE_CCC0,
    CS_RX_LONG_VALUE_USR_DSCP0,

    /* Service DFU */
    DFU_SVC,
#if (SHOW_DEVID)
    /* Device ID Characteristic in Service DFU */
    DFU_DEVID_CHAR,
    DFU_DEVID_VAL,
    DFU_DEVID_NAME,
#endif
#if (SHOW_BOOTVER)
    /* BootLoader Version Characteristic in Service DFU */
    DFU_BOOTVER_CHAR,
    DFU_BOOTVER_VAL,
    DFU_BOOTVER_NAME,
#endif
#if (SHOW_STACKVER)
    /* BLE Stack Version Characteristic in Service DFU */
    DFU_STACKVER_CHAR,
    DFU_STACKVER_VAL,
    DFU_STACKVER_NAME,
#endif
#if (SHOW_APPVER)
    /* Application Version Characteristic in Service DFU */
    DFU_APPVER_CHAR,
    DFU_APPVER_VAL,
    DFU_APPVER_NAME,
#endif
#if (SHOW_BUILDID)
    /* Build ID Characteristic in Service DFU */
    DFU_BUILDID_CHAR,
    DFU_BUILDID_VAL,
    DFU_BUILDID_NAME,
#endif
    /* Enter mode Characteristic in Service DFU */
    DFU_ENTER_CHAR,
    DFU_ENTER_VAL,
    DFU_ENTER_NAME,

	/* SOCKET Service */
	SOCKETS_SVC,

	/* SOCKET Status Characteristic */
	SOCKETS_STATUS_CHAR,
	SOCKETS_STATUS_VAL,
	SOCKETS_STATUS_CCCD,
	SOCKETS_STATUS_USR_DSCP,

	/* SOCKET Command Characteristic */
	SOCKETS_COMMAND_CHAR,
	SOCKETS_COMMAND_VAL,
	SOCKETS_COMMAND_USR_DSCP,

    /* Max number of services and characteristics */
    APP_ATT_NB,
};


/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/

extern const struct att_db_desc app_att_db[APP_ATT_NB];

/* ----------------------------------------------------------------------------
 * Function prototype definitions
 * --------------------------------------------------------------------------*/


/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_ATT_DB_H */

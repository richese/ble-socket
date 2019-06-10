/* ----------------------------------------------------------------------------
 * Copyright (c) 2015-2018 Semiconductor Components Industries, LLC (d/b/a
 * ON Semiconductor), All Rights Reserved
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 * This module is derived in part from example code provided by RivieraWaves
 * and as such the underlying code is the property of RivieraWaves [a member
 * of the CEVA, Inc. group of companies], together with additional code which
 * is the property of ON Semiconductor. The code (in whole or any part) may not
 * be redistributed in any form without prior written permission from
 * ON Semiconductor.
 *
 * The terms of use and warranty for this code are covered by contractual
 * agreements between ON Semiconductor and the licensee.
 *
 * This is Reusable Code.
 *
 * ----------------------------------------------------------------------------
 * ble_dfu.h
 * - Custom Bluetooth DFU service header
 * ----------------------------------------------------------------------------
 * $Revision: 1.2 $
 * $Date: 2019/03/15 21:19:15 $
 * ------------------------------------------------------------------------- */

#ifndef BLE_DFUS_H
#define BLE_DFUS_H

#include <app_att_db.h>

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/* ----------------------------------------------------------------------------
 * Function prototype definitions
 * --------------------------------------------------------------------------*/
void DFUS_Initialize(void);

uint8_t DfusCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                            uint8_t *toData, const uint8_t *fromData,
                            uint16_t lenData,  uint16_t operation);
/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* BLE_DFUS_H */

/* PRQA S 3108++ */
/**
 * Copyright (C) 2024 Isoft Infrastructure Software Co., Ltd.
 * SPDX-License-Identifier: LGPL-2.1-only-with-exception OR  LicenseRef-Commercial-License
 *
 * This library is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation; version 2.1.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with this library;
 * if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * or see <https://www.gnu.org/licenses/>.
 *
 * Alternatively, this file may be used under the terms of the Isoft Infrastructure Software Co., Ltd.
 * Commercial License, in which case the provisions of the Isoft Infrastructure Software Co., Ltd.
 * Commercial License shall apply instead of those of the GNU Lesser General Public License.
 *
 * You should have received a copy of the Isoft Infrastructure Software Co., Ltd.  Commercial License
 * along with this program. If not, please find it at <https://EasyXMen.com/xy/reference/permissions.html>
 *
 ********************************************************************************
 **                                                                            **
 **  FILENAME    : Arch_Trap.c                                                 **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Trap manager                                                **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/*=======[I N C L U D E S]====================================================*/
#include "Os_Internal.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Exception handling.>
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_TrapHandler(void)
{
    #if ((OS_SC2 == CFG_SC) || (OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
    #if (TRUE == CFG_PROTECTIONHOOK)
    VAR(uint32,OS_VAR) WhoHook = OS_TMPROT_HOOK_OSAPP;

    if (OS_LEVEL_TASK == Os_SCB.sysOsLevel)
    {
        WhoHook = OS_TMPROT_HOOK_TASK;
    }
    else if (OS_LEVEL_ISR2 == Os_SCB.sysOsLevel)
    {
        WhoHook = OS_TMPROT_HOOK_ISR;
    }
    else
    {
        /* Do nothing. */
    }
    #endif /* TRUE == CFG_PROTECTIONHOOK */

    #if (TRUE == CFG_ERRORHOOK)
    (void)ErrorHook(E_OS_PROTECTION_MEMORY);
    #endif /* TRUE == CFG_ERRORHOOK */
    /* OS245:  protection exception hook. */
    #if (TRUE == CFG_PROTECTIONHOOK)
    (void)Os_CallProtectionHook(E_OS_PROTECTION_MEMORY, WhoHook);
    #endif /* TRUE == CFG_PROTECTIONHOOK */
    #else /* CFG_SC ==  OS_SC1 */
    #if (TRUE == CFG_ERRORHOOK)
    (void)ErrorHook(E_OS_PROTECTION_MEMORY);
    #endif /* TRUE == CFG_ERRORHOOK */
    while(1)
    {
        /* nothing to do. */
    }
    #endif /* (OS_SC2 == CFG_SC) || (OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC)*/
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"



/*=======[E N D   O F   F I L E]==============================================*/

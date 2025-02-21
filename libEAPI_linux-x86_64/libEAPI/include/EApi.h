/*
 *<KHeader>
 *+=========================================================================
 *I  Project Name: EApiDK Embedded Application Development Kit
 *+=========================================================================
 *I  $HeadURL: https://svn.code.sf.net/p/eapidk/code/trunk/include/EApi.h $
 *+=========================================================================
 *I   Copyright: Copyright (c) 2009-2010, PICMG
 *I      Author: John Kearney,                  John.Kearney@kontron.com
 *I
 *I     License: All rights reserved. This program and the accompanying 
 *I              materials are licensed and made available under the 
 *I              terms and conditions of the BSD License which 
 *I              accompanies this distribution. The full text of the 
 *I              license may be found at 
 *I              http://opensource.org/licenses/bsd-license.php
 *I              
 *I              THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "
 *I              AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS OF 
 *I              ANY KIND, EITHER EXPRESS OR IMPLIED.
 *I
 *I Description: Auto Created for EApi.h
 *I
 *+-------------------------------------------------------------------------
 *I
 *I  File Name            : EApi.h
 *I  File Location        : include
 *I  Last committed       : $Revision: 74 $
 *I  Last changed by      : $Author: dethrophes $
 *I  Last changed date    : $Date: 2010-06-24 03:26:50 +0800 (Thu, 24 Jun 2010) $
 *I  ID                   : $Id: EApi.h 74 2010-06-23 19:26:50Z dethrophes $
 *I
 *+=========================================================================
 *</KHeader>
 */

#ifndef _EAPI_H_        
#define _EAPI_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************/

#ifndef __IN
#  define __IN 
/* __IN
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Immediate value | Input value that must be specified and is essential 
 *                 | to function operation.
 *                 | 
 * Pointer         | Valid pointer to initialized buffer/variable.
 *                 | 
 */
#endif
#ifndef __INOPT
#  define __INOPT
/* __INOPT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to initialized buffer/variable, or
 *                 | NULL Pointer.
 *                 | Note: refer to function specification for specifics.
 */
#endif
#ifndef __OUT
#  define __OUT
/* __OUT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to destination buffer/variable
 */
#endif
#ifndef __OUTOPT
#  define __OUTOPT

/* __OUTOPT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to destination buffer/variable, or
 *                 | NULL Pointer. 
 *                 | Note: refer to function specification for specifics.
 */
#endif
#ifndef __INOUT
#  define __INOUT
/* __INOUT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to initialized buffer/variable
 *                 | Contents of buffer/variable updated before return.
 */
#endif
#ifndef EAPI_CALLTYPE
#  define EAPI_CALLTYPE
#endif
#ifndef EAPI_UINT32_C
#  define EAPI_UINT8_C(x)  ((uint8_t)(x))
#  define EAPI_UINT16_C(x) ((uint16_t)(x))
#  define EAPI_UINT32_C(x) ((uint32_t)(x))
#endif
/************************************************************************
 * All version numbers 
 * +=========+===============================+
 * | Bits    | Descriptions                  |
 * +=========+===============================+
 * | 24 - 31 | Version Number                |
 * +---------+-------------------------------+
 * | 16 - 23 | Revision Number               |
 * +---------+-------------------------------+
 * | 0  - 15 | Build Number                  |
 * +=========+===============================+
 */
#define EAPI_VER_MASK_VER     EAPI_UINT32_C(0xFF000000)
#define EAPI_VER_MASK_REV     EAPI_UINT32_C(0x00FF0000)
#define EAPI_VER_MASK_BUILD   EAPI_UINT32_C(0x0000FFFF)
#define EAPI_VER_GET_VER(x)   EAPI_UINT8_C (((x)>>24)&UINT8_MAX )
#define EAPI_VER_GET_REV(x)   EAPI_UINT8_C (((x)>>16)&UINT8_MAX )
#define EAPI_VER_GET_BUILD(x) EAPI_UINT16_C(((x)>> 0)&UINT16_MAX)
#define EAPI_VER_CREATE(Version,Revision,Build) (\
                      EAPI_UINT32_C(\
                        (((Version )&UINT8_MAX )<<24)|\
                        (((Revision)&UINT8_MAX )<<16)|\
                        (((Build   )&UINT16_MAX)<< 0) \
                      )\
                    )

/* Embedded API Standard Revision */
#define EAPI_VER      1
#define EAPI_REVISION 0
#define EAPI_VERSION EAPI_VER_CREATE(EAPI_VER, EAPI_REVISION, 0)


/************************************************************************
 */


/* Embedded Application System Interface */

/*
 *  EApi Types
 */
typedef uint32_t EApiStatus_t;
typedef uint32_t EApiId_t;

/*
 *
 *
 *  S T A T U S   C O D E S
 *
 *
 */
/* Description
 *   The EAPI library is not yet or unsuccessfully initialized. 
 *   EApiLibInitialize needs to be called prior to the first access of any 
 *   other EAPI function.
 * Actions
 *   Call EApiLibInitialize..
 */
#define EAPI_STATUS_NOT_INITIALIZED   EAPI_UINT32_C(0xFFFFFFFF)

/* Description
 *   Library is initialized.
 * Actions
 *   none.
 */
#define EAPI_STATUS_INITIALIZED       EAPI_UINT32_C(0xFFFFFFFE)

/* Description
 *   Memory Allocation Error.
 * Actions
 *   Free memory and try again..
 */
#define EAPI_STATUS_ALLOC_ERROR       EAPI_UINT32_C(0xFFFFFFFD)

/* Description 
 *   Time out in driver. This is Normally caused by hardware/software 
 *   semaphore timeout. 
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_DRIVER_TIMEOUT    EAPI_UINT32_C(0xFFFFFFFC)

/* Description 
 *  One or more of the EAPI function call parameters are out of the 
 *  defined range.
 *
 *  Possible Reasons include be
 *  NULL Pointer
 *  Invalid Offset
 *  Invalid Length
 *  Undefined Value
 *  
 *   Storage Write
 *    Incorrectly Aligned Offset
 *    Invalid Write Length
 * Actions
 *   Verify Function Parameters.
 */
#define EAPI_STATUS_INVALID_PARAMETER EAPI_UINT32_C(0xFFFFFEFF)

/* Description
 *   The Block Alignment is incorrect.
 * Actions
 *   Use pInputs and pOutputs to correctly select input and outputs. 
 */
#define EAPI_STATUS_INVALID_BLOCK_ALIGNMENT EAPI_UINT32_C(0xFFFFFEFE)

/* Description
 *   This means that the Block length is too long.
 * Actions
 *   Use Alignment Capabilities information to correctly align write access.
 */
#define EAPI_STATUS_INVALID_BLOCK_LENGTH    EAPI_UINT32_C(0xFFFFFEFD)

/* Description
 *   The current Direction Argument attempts to set GPIOs to a unsupported 
 *   directions. I.E. Setting GPI to Output.
 * Actions
 *   Use pInputs and pOutputs to correctly select input and outputs. 
 */
#define EAPI_STATUS_INVALID_DIRECTION       EAPI_UINT32_C(0xFFFFFEFC)

/* Description
 *   The Bitmask Selects bits/GPIOs which are not supported for the current ID.
 * Actions
 *   Use pInputs and pOutputs to probe supported bits..
 */
#define EAPI_STATUS_INVALID_BITMASK         EAPI_UINT32_C(0xFFFFFEFB)

/* Description
 *   Watchdog timer already started.
 * Actions
 *   Call EApiWDogStop, before retrying.
 */
#define EAPI_STATUS_RUNNING                 EAPI_UINT32_C(0xFFFFFEFA)

/* Description
 *   This function or ID is not supported at the actual hardware environment.
 * Actions
 *   none.
 */
#define EAPI_STATUS_UNSUPPORTED       EAPI_UINT32_C(0xFFFFFCFF)

/* Description
 *   I2C Device Error
 *   No Acknowledge For Device Address, 7Bit Address Only
 *   10Bit Address may cause Write error if 2 10Bit addressed devices 
 *   present on the bus.
 * Actions
 *   none.
 */
#define EAPI_STATUS_NOT_FOUND         EAPI_UINT32_C(0xFFFFFBFF)

/* Description
 *   I2C Time-out
 *   Device Clock stretching time-out, Clock pulled low by device 
 *   for too long
 * Actions
 *   none.
 */
#define EAPI_STATUS_TIMEOUT           EAPI_UINT32_C(0xFFFFFBFE)

/* Description
 *   EApi  I2C functions specific. The addressed I2C bus is busy or there 
 *   is a bus collision.
 *   The I2C bus is in use. Either CLK or DAT are low.
 *   Arbitration loss or bus Collision, data remains low when writing a 1
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_BUSY_COLLISION    EAPI_UINT32_C(0xFFFFFBFD)

/* Description
 *   I2C Read Error
 *    Not Possible to detect.
 *   Storage Read Error
 *    ....
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_READ_ERROR        EAPI_UINT32_C(0xFFFFFAFf)

/* Description
 *   I2C Write Error
 *     No Acknowledge received after writing any Byte after the First Address 
 *     Byte.
 *     Can be caused by 
 *     unsupported Device Command/Index
 *     Ext Command/Index used on Standard Command/Index Device
 *     10Bit Address Device Not Present
 *   Storage Write Error
 *    ...
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_WRITE_ERROR       EAPI_UINT32_C(0xFFFFFAFE)


/* Description
 *   The amount of available data exceeds the buffer size.
 *   Storage buffer overflow was prevented. Read count was larger then 
 *   the defined buffer length.
 *   Read Count > Buffer Length
 * Actions
 *   Either increase the buffer size or reduce the block length.
 */
#define EAPI_STATUS_MORE_DATA         EAPI_UINT32_C(0xFFFFF9FF)

/* Description
 *   Advantech EAPI ETP API type define.
 *   Get ETP lock status failed.
 * Actions
 *   none.
 */
#define EAPI_STATUS_GET_STATUS_ERROR  EAPI_UINT32_C(0xFFFFF8FF)

/* Description
 *   Advantech EAPI ETP API type define.
 *   Current ETP was locked (read only).
 * Actions
 *   none.
 */
#define EAPI_STATUS_LOCKED			  EAPI_UINT32_C(0xFFFFF8FE)

/* Description
 *   Generic error message. No further error details are available.
 * Actions
 *   none.
 */
#define EAPI_STATUS_ERROR             EAPI_UINT32_C(0xFFFFF0FF)

/* Description
 *   The operation was successful.
 * Actions
 *   none.
 */
#define EAPI_STATUS_SUCCESS           EAPI_UINT32_C(0)
#define EAPI_TEST_SUCCESS(x)        (!(x))

/* Library */
/* 
 * EApiLibInitialize
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Already initialized            | EAPI_STATUS_INITIALIZED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiLibInitialize(void)   ; /* Should be called before 
                             * calling any other API 
                             * function is called
                             */
/* 
 * EApiLibUnInitialize
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE 
EApiLibUnInitialize(void) ; /* Should be called before 
                             * program exit 
                             */ 


/* 
 *
 * Plug and Play Identifiers
 *
 *
 *
 */
/* 
 * The following MACROS are for Creating OEM IDs
 * OEM ID macros should be named
 * EAPI_[PNPID]_ID_[TYPE]_[NAME] 
 * E.G.
 * EAPI_PMG_ID_BOARD_CUSTOMERID
 */
#define EAPI_BYTE_SWAP_W(a) EAPI_UINT16_C(\
      (((a)<<8)&0xFF00)|\
      (((a)>>8)&0x00FF) \
      )

#define EAPI_CREATE_PNPID(a, b, c) \
  EAPI_BYTE_SWAP_W(((( a -'A'+1)&0x1F)<<10)|\
              ((( b -'A'+1)&0x1F)<< 5)|\
              ((( c -'A'+1)&0x1F)<< 0) \
             )
#define EAPI_CREATE_CUST_ID(a, b, c, Id)\
      EAPI_UINT32_C((0xF<<28)|(EAPI_CREATE_PNPID(a, b, c)<<12)|(Id&0xFFF))

#define EAPI_PNPID_PICMG EAPI_CREATE_PNPID('P', 'M', 'G')  /* PICMG Should
                                                            * register this. 
                                                            */

/*
 *
 *      B O A R D   I N F O M A T I O N   S T R I N G S 
 *
 */
/* IDS */


/* Board information string */
#define EAPI_ID_GET_NAME_MASK							EAPI_UINT32_C(0xF0000000)
#define EAPI_ID_GET_NAME_BASE(Id)						EAPI_UINT32_C(Id & EAPI_ID_GET_NAME_MASK)

#define EAPI_ID_BASE_GET_NAME_INFO           EAPI_UINT32_C(0x00000000)
#define EAPI_ID_BASE_GET_NAME_HWMON          EAPI_UINT32_C(0x10000000)

#define EAPI_ID_BASE_GET_NAME_I2C						(0x20000000)
#define EAPI_ID_BASE_GET_NAME_SMB						(0x30000000)
#define EAPI_ID_BASE_GET_NAME_GPIO						(0x40000000)
#define EAPI_ID_BASE_GET_NAME_WDT						(0x50000000)
#define EAPI_ID_BASE_GET_NAME_VGA_BACKLIGHT				(0x60000000)
#define EAPI_ID_BASE_GET_NAME_STORAGE					(0x70000000)
#define EAPI_ID_BASE_GET_NAME_TML						(0x80000000)



#define EAPI_ID_MAPPING_GET_NAME_HWMON(Id)				((EApiId_t)(Id | EAPI_ID_BA SE_GET_NAME_HWMON))
#define EAPI_ID_MAPPING_GET_NAME_HWMON_FANCONTROL(Id)	((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_HWMON_FANCONTROL))
#define EAPI_ID_MAPPING_GET_NAME_I2C(Id)				((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_I2C))
#define EAPI_ID_MAPPING_GET_NAME_SMB(Id)				((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_SMB))
#define EAPI_ID_MAPPING_GET_NAME_GPIO(Id)				((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_GPIO))
#define EAPI_ID_MAPPING_GET_NAME_WDT(Id)				((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_WDT))
#define EAPI_ID_MAPPING_GET_NAME_VGA_BACKLIGHT(Id)		((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_VGA_BACKLIGHT))
#define EAPI_ID_MAPPING_GET_NAME_STORAGE(Id)			((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_STORAGE))
#define EAPI_ID_MAPPING_GET_NAME_TML(Id)				((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_TML))
#define EAPI_ID_MAPPING_GET_NAME_INFO(Id)				((EApiId_t)(Id | EAPI_ID_BASE_GET_NAME_INFO))


#define EAPI_ID_BOARD_MANUFACTURER_STR					((EApiId_t)0x0)
#define EAPI_ID_BOARD_NAME_STR						((EApiId_t)0x1)
#define EAPI_ID_BOARD_REVISION_STR					((EApiId_t)0x2)
#define EAPI_ID_BOARD_SERIAL_STR					((EApiId_t)0x3)
#define EAPI_ID_BOARD_BIOS_REVISION_STR					((EApiId_t)0x4)
#define EAPI_ID_BOARD_HW_REVISION_STR					((EApiId_t)0x5)
#define EAPI_ID_BOARD_PLATFORM_TYPE_STR					((EApiId_t)0x6)

#define EAPI_ID_BOARD_EC_REVISION_STR					((EApiId_t)0x101)
#define EAPI_ID_BOARD_OS_REVISION_STR					((EApiId_t)0x102)
#define EAPI_ID_BOARD_CPU_MODEL_NAME_STR				((EApiId_t)0x103)

//DMI
#define EAPI_ID_BOARD_DMIBIOS_VENDOR_STR				((EApiId_t)0x201)
#define EAPI_ID_BOARD_DMIBIOS_VERSION_STR				((EApiId_t)0x202)
#define EAPI_ID_BOARD_DMIBIOS_DATE_STR					((EApiId_t)0x203)
#define EAPI_ID_BOARD_DMISYS_UUID_STR					((EApiId_t)0x204)
#define EAPI_ID_BOARD_DMISYS_VENDOR_STR					((EApiId_t)0x205)
#define EAPI_ID_BOARD_DMISYS_PRODUCT_STR				((EApiId_t)0x206)
#define EAPI_ID_BOARD_DMISYS_VERSION_STR				((EApiId_t)0x207)
#define EAPI_ID_BOARD_DMISYS_SERIAL_STR					((EApiId_t)0x208)
#define EAPI_ID_BOARD_DMIBOARD_VENDOR_STR				((EApiId_t)0x209)
#define EAPI_ID_BOARD_DMIBOARD_NAME_STR					((EApiId_t)0x20a)
#define EAPI_ID_BOARD_DMIBOARD_VERSION_STR				((EApiId_t)0x20b)
#define EAPI_ID_BOARD_DMIBOARD_SERIAL_STR				((EApiId_t)0x20c)
#define EAPI_ID_BOARD_DMIBOARD_ASSET_TAG_STR				((EApiId_t)0x20d)


#define EAPI_ID_BOARD_OEM0_STR						((EApiId_t)0x10)
#define EAPI_ID_BOARD_OEM1_STR						((EApiId_t)0x11)
#define EAPI_ID_BOARD_OEM2_STR						((EApiId_t)0x12)

/* 
 * EApiBoardGetStringA
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBufLen==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * pBufLen!=NULL&&*pBufLen&&pBuffer==NULL | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * strlen(Id)+1>*pBufLen                  | EAPI_STATUS_MORE_DATA
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE
EApiBoardGetStringA(
    __IN      EApiId_t  Id      , /* Name Id */
    __OUT     char     *pBuffer , /* Destination pBuffer */
    __INOUT   uint32_t *pBufLen   /* pBuffer Length */
    );


/*
 *
 *      B O A R D   I N F O M A T I O N   V A L U E S
 *
 */
/* IDS */
#define EAPI_ID_GET_EAPI_SPEC_VERSION         EAPI_UINT32_C(0) /* EAPI Specification 
                                                                * Revision I.E. The 
                                                                * EAPI Spec Version 
                                                                * Bits 31-24, Revision 
                                                                * 23-16, 15-0 always 0
                                                                * Used to implement 
                                                                * this interface
                                                                */

#define EAPI_ID_BOARD_BOOT_COUNTER_VAL        EAPI_UINT32_C(1) /* Units = Boots */
#define EAPI_ID_BOARD_RUNNING_TIME_METER_VAL  EAPI_UINT32_C(2) /* Units = Minutes */
#define EAPI_ID_BOARD_PNPID_VAL               EAPI_UINT32_C(3) /* Encoded PNP ID 
                                                                * Format 
                                                                * (Compressed ASCII)
                                                                */
#define EAPI_ID_BOARD_PLATFORM_REV_VAL        EAPI_UINT32_C(4) /* Platform Revision 
                                                                * I.E. The PICMG Spec 
                                                                * Version Bits 31-24,
                                                                * Revision 23-16, 
                                                                * 15-0 always 0
                                                                */

#define EAPI_ID_BOARD_DRIVER_VERSION_VAL  EAPI_UINT32_C(0x10000) /* Vendor Specific 
                                                                  * (Optional) 
                                                                  */
#define EAPI_ID_BOARD_LIB_VERSION_VAL     EAPI_UINT32_C(0x10001) /* Vendor Specific
                                                                  * (Optional) 
                                                                  */
#if 1	// Advantech EC defination.
#define EAPI_ID_GET_INDEX(Id)                (Id & 0xFF)
#define EAPI_ID_GET_TYPE(Id)                 (Id & 0x000FF000)

/* IDS */
// We start from 0x00050000 to to avoid conflict => SUSI_ID + 0x00030000
#define EAPI_ID_HWMON_TEMP_MAX               10                                  /* Maximum temperature item number */
#define EAPI_ID_HWMON_TEMP_BASE              EAPI_UINT32_C(0x00050000)
#define EAPI_ID_HWMON_TEMP                   EAPI_ID_HWMON_TEMP_BASE
#define EAPI_ID_HWMON_TEMP_CPU               EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 0)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_CHIPSET           EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 1)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_SYSTEM            EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 2)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_CPU2              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 3)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_OEM0              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 4)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_OEM1              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 5)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_OEM2              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 6)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_OEM3              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 7)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_OEM4              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 8)         /* 0.1 Kelvins */
#define EAPI_ID_HWMON_TEMP_OEM5              EAPI_UINT32_C(EAPI_ID_HWMON_TEMP_BASE + 9)         /* 0.1 Kelvins */

#define EAPI_ID_HWMON_VOLTAGE_MAX            25                                                 /* Maximum voltage item number */
#define EAPI_ID_HWMON_VOLTAGE_BASE           EAPI_UINT32_C(0x00051000)
#define EAPI_ID_HWMON_VOLTAGE                EAPI_ID_HWMON_VOLTAGE_BASE
#define EAPI_ID_HWMON_VOLTAGE_VCORE          EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 0)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VCORE2         EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 1)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_2V5            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 2)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_3V3            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 3)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5V             EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 4)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_12V            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 5)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5VSB           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 6)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_3VSB           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 7)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VBAT           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 8)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5NV            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 9)      /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_12NV           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 10)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VTT            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 11)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_24V            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 12)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_DC             EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 13)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_DCSTBY         EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 14)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VBATLI         EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 15)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_OEM0           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 16)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_OEM1           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 17)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_OEM2           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 18)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_OEM3           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 19)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_1V05           EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 20)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_1V5            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 21)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_1V8            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 22)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_DC2            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 23)     /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VIN            EAPI_UINT32_C(EAPI_ID_HWMON_VOLTAGE_BASE + 24)     /* millivolts */

#define EAPI_ID_HWMON_FAN_MAX                10                                  /* Maximum fan item number */
#define EAPI_ID_HWMON_FAN_BASE               EAPI_UINT32_C(0x00052000)
#define EAPI_ID_HWMON_FAN_CPU                EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 0)          /* RPM */
#define EAPI_ID_HWMON_FAN_SYSTEM             EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 1)          /* RPM */
#define EAPI_ID_HWMON_FAN_CPU2               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 2)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM0               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 3)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM1               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 4)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM2               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 5)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM3               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 6)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM4               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 7)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM5               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 8)          /* RPM */
#define EAPI_ID_HWMON_FAN_OEM6               EAPI_UINT32_C(EAPI_ID_HWMON_FAN_BASE + 9)          /* RPM */

#define EAPI_ID_HWMON_CURRENT_MAX            3                                   /* Maximum current item number */
#define EAPI_ID_HWMON_CURRENT_BASE           EAPI_UINT32_C(0x00053000)
#define EAPI_ID_HWMON_CURRENT_OEM0           EAPI_UINT32_C(EAPI_ID_HWMON_CURRENT_BASE + 0)      /* milliampere */
#define EAPI_ID_HWMON_CURRENT_OEM1           EAPI_UINT32_C(EAPI_ID_HWMON_CURRENT_BASE + 1)      /* milliampere */
#define EAPI_ID_HWMON_CURRENT_OEM2           EAPI_UINT32_C(EAPI_ID_HWMON_CURRENT_BASE + 2)      /* milliampere */

#define EAPI_ID_HWMON_POWER_MAX              1                                   /* Maximum current item number */
#define EAPI_ID_HWMON_POWER_BASE             EAPI_UINT32_C(0x00054000)
#define EAPI_ID_HWMON_POWER_OEM0             EAPI_UINT32_C(EAPI_ID_HWMON_POWER_BASE + 0)        /* millwatt */


#define EAPI_ID_HWMON_MAX                    EAPI_ID_HWMON_VOLTAGE_MAX           /* Maximum item number */

#define EAPI_KELVINS_OFFSET                  2731
#define EAPI_ENCODE_CELCIUS(Celsius)         (((Celsius) * 10) + EAPI_KELVINS_OFFSET)
#define EAPI_DECODE_CELCIUS(Kelvins)         (((Kelvins) - EAPI_KELVINS_OFFSET) / 10)
#define EAPI_DECODE_HWMON_VALUE(RawValue)    (RawValue / 1000)
#define EAPI_CELCIUS_TO_FAHRENHEIT(Celsius)  (32 + (Celsius * 9 / 5))

#define EAPI_ID_CAP_MAX						 12
#define EAPI_ID_CAP_BASE					 EAPI_UINT32_C(0x00060000)
#define EAPI_ID_CAP_HWMON					 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 0)
#define EAPI_ID_CAP_HWMON_TEMPERATURE		 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 1)
#define EAPI_ID_CAP_HWMON_VOLTAGE			 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 2)
#define EAPI_ID_CAP_HWMON_FAN				 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 3)
#define EAPI_ID_CAP_HWMON_CURRENT			 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 4)
#define EAPI_ID_CAP_HWMON_POWER				 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 5)
#define EAPI_ID_CAP_GPIO					 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 6)
#define EAPI_ID_CAP_GPIO_COUNT				 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 7)
#define EAPI_ID_CAP_GPIO_INTERRUPT			 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 8)
#define EAPI_ID_CAP_BRIGHTNESS				 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 9)
#define EAPI_ID_CAP_WDOG					 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 10)
#define EAPI_ID_CAP_ETP						 EAPI_UINT32_C(EAPI_ID_CAP_BASE + 11)

#define EAPI_ID_GPIO_MAX                    1
#define EAPI_ID_GPIO_BASE                       EAPI_UINT32_C(0x00070000)
#define EAPI_ID_GPIO_POE_PINNUM                 EAPI_UINT32_C(EAPI_ID_GPIO_BASE + 1)

#else

#define EAPI_ID_HWMON_CPU_TEMP            EAPI_UINT32_C(0x20000) /* 0.1 Kelvins */ 
#define EAPI_ID_HWMON_CHIPSET_TEMP        EAPI_UINT32_C(0x20001) /* 0.1 Kelvins */ 
#define EAPI_ID_HWMON_SYSTEM_TEMP         EAPI_UINT32_C(0x20002) /* 0.1 Kelvins */ 

#define EAPI_KELVINS_OFFSET 2731
#define EAPI_ENCODE_CELCIUS(Celsius) EAPI_UINT32_C((((Celsius)*10))+EAPI_KELVINS_OFFSET)
#define EAPI_DECODE_CELCIUS(Celsius) ((Celsius)- EAPI_KELVINS_OFFSET)/10

#define EAPI_ID_HWMON_VOLTAGE_VCORE       EAPI_UINT32_C(0x21004) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_2V5         EAPI_UINT32_C(0x21008) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_3V3         EAPI_UINT32_C(0x2100C) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VBAT        EAPI_UINT32_C(0x21010) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5V          EAPI_UINT32_C(0x21014) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5VSB        EAPI_UINT32_C(0x21018) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_12V         EAPI_UINT32_C(0x2101C) /* millivolts */

#define EAPI_ID_HWMON_FAN_CPU             EAPI_UINT32_C(0x22000) /* RPM */
#define EAPI_ID_HWMON_FAN_SYSTEM          EAPI_UINT32_C(0x22001) /* RPM */
#endif

/* 
 * EApiBoardGetValue
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pValue==NULL                           | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiBoardGetValue(
    __IN  EApiId_t  Id      , /* Value Id */
    __OUT uint32_t *pValue    /* Return Value */
    );



/*
 *
 *      B A C K L I G H T
 *
 */
/* IDS */
#define EAPI_ID_BACKLIGHT_MAX         3
#define EAPI_ID_BACKLIGHT_1           EAPI_UINT32_C(0)
#define EAPI_ID_BACKLIGHT_2           EAPI_UINT32_C(1)
#define EAPI_ID_BACKLIGHT_3           EAPI_UINT32_C(2)

#define EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM   EAPI_UINT32_C(0x00010000)
#define EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM   EAPI_UINT32_C(0x00010001)
#define EAPI_ID_DISPLAY_AUTO_BRIGHTNESS      EAPI_UINT32_C(0x00010002)

/* Backlight Values */
//#define EAPI_BACKLIGHT_SET_ON         EAPI_UINT32_C(0)
//#define EAPI_BACKLIGHT_SET_OFF        EAPI_UINT32_C(0xFFFFFFFF)
//#define EAPI_BACKLIGHT_SET_DIMEST     EAPI_UINT32_C(0)
//#define EAPI_BACKLIGHT_SET_BRIGHTEST  EAPI_UINT32_C(255)
#define EAPI_BACKLIGHT_SET_ON                1
#define EAPI_BACKLIGHT_SET_OFF               0
#define EAPI_AUTO_BRIGHTNESS_SET_ON          1
#define EAPI_AUTO_BRIGHTNESS_SET_OFF         0

/* 
 * EApiVgaGetBacklightEnable
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pEnable==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE
EApiVgaGetBacklightEnable( 
    __IN  EApiId_t  Id      , /* Backlight Id */
    __OUT uint32_t *pEnable   /* Backlight Enable */
    );
/* 
 * EApiVgaSetBacklightEnable
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Enable!=EAPI_BACKLIGHT_SET_ON&&
 * Enable!=EAPI_BACKLIGHT_SET_OFF         | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE
EApiVgaSetBacklightEnable(
    __IN  EApiId_t  Id      , /* Backlight Id */
    __IN  uint32_t  Enable    /* Backlight Enable */
    );
/* 
 * EApiVgaGetBacklightBrightness
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBright==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE
EApiVgaGetBacklightBrightness( 
    __IN  EApiId_t  Id      , /* Backlight Id */
    __OUT uint32_t *pBright   /* Backlight Brightness */
    );
/* 
 * EApiVgaSetBacklightBrightness
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Bright>EAPI_BACKLIGHT_SET_BRIGHTEST    | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE
EApiVgaSetBacklightBrightness(
    __IN  EApiId_t  Id      , /* Backlight Id */
    __IN  uint32_t  Bright    /* Backlight Brightness */
    );


/*
 *
 *      S T O R A G E
 *
 */
/* IDs */
#define EAPI_ID_STORAGE_STD              EAPI_UINT32_C(0)
/* Dummy Example */
#define EAPI_PMG_ID_STORAGE_SAMPLE       EAPI_CREATE_CUST_ID('P', 'M', 'G', 0) 
/* 
 * EApiStorageCap
 * 
 * Condition                                    | Return Values 
 * ---------------------------------------------+------------------------------
 * Library Uninitialized                        | EAPI_STATUS_NOT_INITIALIZED
 * ((pStorageSize==NULL)&&(pBlockLength==NULL)) | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                               | EAPI_STATUS_UNSUPPORTED
 * Common Error                                 | Common Error Code
 * Else                                         | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiStorageCap(
    __IN  EApiId_t  Id            , /* Storage Area Id */
    __OUT uint32_t  *pStorageSize , /* Total */
    __OUT uint32_t  *pBlockLength   /* Write Block Length
                                     * & Alignment 
                                     */
    );
/* 
 * EApiStorageAreaRead
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                             | EAPI_STATUS_INVALID_PARAMETER
 * BufLen==0                              | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Offset+ByteCnt>pStorageSize            | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Read Error                             | EAPI_STATUS_READ_ERROR
 * ByteCnt>BufLen                         | EAPI_STATUS_MORE_DATA
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiStorageAreaRead(
    __IN  EApiId_t  Id      , /* Storage Area Id */
    __IN  uint32_t  Offset  , /* Byte Offset */
    __OUT     void *pBuffer , /* Pointer to Data pBuffer */
    __IN  uint32_t  BufLen  , /* Data pBuffer Size in 
                               * bytes 
                               */
    __IN  uint32_t  ByteCnt   /* Number of bytes to read */
    );
/* 
 * EApiStorageAreaWrite
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                             | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Offset%pBlockLength                    | EAPI_STATUS_INVALID_BLOCK_ALIGNMENT
 * ByteCnt%pBlockLength                   | EAPI_STATUS_INVALID_BLOCK_ALIGNMENT
 * Offset+ByteCnt>pStorageSize            | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Write Error                            | EAPI_STATUS_WRITE_ERROR
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiStorageAreaWrite(
    __IN  EApiId_t  Id      , /* Storage Area Id */
    __IN  uint32_t  Offset  , /* Byte Offset */
    __IN      void *pBuffer , /* Pointer to Data pBuffer */
    __IN  uint32_t  ByteCnt   /* Number of bytes to write */
    );


/*
 *
 *      I 2 C
 *
 */
/* IDs */
#define EAPI_ID_I2C_EXTERNAL       EAPI_UINT32_C(0) /* Baseboard I2C Interface
                                                     * required 
                                                     */
#define EAPI_ID_I2C_LVDS_1         EAPI_UINT32_C(1) /* LVDS/EDP 1 Interface 
                                                     * (optional)
                                                     */
#define EAPI_ID_I2C_LVDS_2         EAPI_UINT32_C(2) /* LVDS/EDP 2 Interface 
                                                     * (optional)
                                                     */

/*
 * I2C Address Format 
 *
 *  L = Set to 0   
 *  H = Set to 1   
 *  X = Don't Care(Direction Bit)
 *  0-F Address Bit 
 *
 *  Bits 31-16 are Reserved and should be set to 0
 *
 *  Bit Offset      | F E D C B A 9 8 7 6 5 4 3 2 1 0
 *  ----------------+--------------------------------
 *  7  Bit Address  | L L L L L L L L 6 5 4 3 2 1 0 X
 *  10 Bit Address  | H H H H L 9 8 X 7 6 5 4 3 2 1 0
 *
 *  Examples where Don't Care bits set to 0
 *             Encoded Encoded
 *  Address     7Bit    10Bit
 *    0x01      0x02   0xF001
 *    0x58      0xA0   0xF058
 *    0x59      0xA2   0xF059
 *    0x77      0xEE   0xF077
 *    0x3FF            0xF6FF
 *
 */
#define EAPI_I2C_ENC_7BIT_ADDR(x)  EAPI_UINT8_C(((x)&0x07F)<<1)
#define EAPI_I2C_DEC_7BIT_ADDR(x)  EAPI_UINT8_C(((x)>>1)&0x07F)
/* 
 * EApiI2CGetBusCap
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pMaxBlkLen==NULL                       | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE
EApiI2CGetBusCap(
    __IN  EApiId_t  Id         , /* I2C Bus Id */
    __OUT uint32_t *pMaxBlkLen   /* Max Block Length 
                                  * Supported on this
                                  * interface 
                                  */
    );

/* 
 * EApiI2CWriteRead
 * 
 * Condition                                | Return Values 
 * -----------------------------------------+------------------------------
 * Library Uninitialized                    | EAPI_STATUS_NOT_INITIALIZED
 * (WriteBCnt>1)&&(pWBuffer==NULL)          | EAPI_STATUS_INVALID_PARAMETER
 * (ReadBCnt>1)&&(pRBuffer==NULL)           | EAPI_STATUS_INVALID_PARAMETER
 * (ReadBCnt>1)&&(RBufLen==0)               | EAPI_STATUS_INVALID_PARAMETER
 * ((WriteBCnt==0)&&(ReadBCnt==0))          | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                               | EAPI_STATUS_UNSUPPORTED
 * WriteBCnt>(pMaxBlkLen+1)                 | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * ReadBCnt>(pMaxBlkLen+1)                  | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Bus Busy  SDA/SDC low                    | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error        | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                 |
 *   SDA Remains low                        |
 * Timeout due to clock stretching          | EAPI_STATUS_TIMEOUT
 * start<Addr Byte><W>Nak                   | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte><R>Nak                   | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte><W>Ack<Data Byte 1>Nak   | EAPI_STATUS_WRITE_ERROR
 * ReadBCnt>(RBufLen+1)                     | EAPI_STATUS_MORE_DATA
 * Common Error                             | Common Error Code
 * Else                                     | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiI2CWriteReadRaw(
    __IN     EApiId_t  Id       , /* I2C Bus Id */
    __IN     uint8_t   Addr     , /* Encoded 7Bit I2C
                                   * Device Address 
                                   */
    __INOPT  void     *pWBuffer , /* Write Data pBuffer */
    __IN     uint32_t  WriteBCnt, /* Number of Bytes to 
                                   * write plus 1
                                   */
    __OUTOPT void     *pRBuffer , /* Read Data pBuffer */
    __IN     uint32_t  RBufLen  , /* Data pBuffer Length */
    __IN     uint32_t  ReadBCnt   /* Number of Bytes to 
                                   * Read plus 1
                                   */
    );

#define EApiI2CWriteRaw(Id, Addr, pBuffer, ByteCnt)         \
          EApiI2CWriteReadRaw(Id, Addr, pBuffer, ByteCnt, NULL, 0, 0)
#define EApiI2CReadRaw(Id, Addr, pBuffer, BufLen, ByteCnt) \
          EApiI2CWriteReadRaw(Id, Addr, NULL, 0, pBuffer, BufLen, ByteCnt)


#define EAPI_I2C_ENC_10BIT_ADDR(x) EAPI_UINT32_C(((x)&0xFF)|(((x)&0x0300)<<1)|0xF000)
#define EAPI_I2C_DEC_10BIT_ADDR(x) EAPI_UINT32_C(((x)&0xFF)|(((x)>>1)&0x300))
#define EAPI_I2C_IS_10BIT_ADDR(x)  (((x)&0xF800)==0xF000)
#define EAPI_I2C_IS_7BIT_ADDR(x)   (!EAPI_I2C_IS_10BIT_ADDR(x))

/*
 * I2C Transfer Types
 * Bits 31 & 30 Selects Command Type
 *
 * Transfer Type 1: 
 * Address Format : 7Bit
 * Command Type   : None
 * Data Direction : Write
 * Start<Addr Byte><W>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 2: 
 * Address Format : 7Bit
 * Command Type   : None
 * Data Direction : Read 
 * Start<Addr Byte><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 3: 
 * Address Format : 7Bit
 * Command Type   : Standard
 * Data Direction : Write
 * Start<Addr Byte><W>Ack<CMD Byte>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 4: 
 * Address Format : 7Bit
 * Command Type   : Standard
 * Data Direction : Read
 * Start<Addr Byte><W>Ack<CMD Byte>Ack 
 * Start<Addr Byte><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 5: 
 * Address Format : 7Bit
 * Command Type   : Extended
 * Data Direction : Write
 * Start<Addr Byte><W>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 6: 
 * Address Format : 7Bit
 * Command Type   : Extended
 * Data Direction : Read
 * Start<Addr Byte><W>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack 
 * Start<Addr Byte><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 7: 
 * Address Format : 10Bit
 * Command Type   : None
 * Data Direction : Write
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 8: 
 * Address Format : 10Bit
 * Command Type   : None
 * Data Direction : Read
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack 
 * Start<Addr Byte MSB><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 9: 
 * Address Format : 10Bit
 * Command Type   : Standard
 * Data Direction : Write
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 10: 
 * Address Format : 10Bit
 * Command Type   : Standard
 * Data Direction : Read
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte>Ack 
 * Start<Addr Byte MSB><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 11: 
 * Address Format : 10Bit
 * Command Type   : Extended
 * Data Direction : Write
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 12: 
 * Address Format : 10Bit
 * Command Type   : Extended
 * Data Direction : Read
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack
 * Start<Addr Byte MSB><R>Ack<Data Byte 1>Nak Stop
 *
 */
#define EAPI_I2C_STD_CMD          EAPI_UINT32_C(0<<30)
#define EAPI_I2C_EXT_CMD          EAPI_UINT32_C(2<<30)
#define EAPI_I2C_NO_CMD           EAPI_UINT32_C(1<<30)    
#define EAPI_I2C_CMD_TYPE_MASK    EAPI_UINT32_C(3<<30)    

#define EAPI_I2C_ENC_STD_CMD(x)  EAPI_UINT32_C(((x)&0xFF)|EAPI_I2C_STD_CMD)
#define EAPI_I2C_ENC_EXT_CMD(x)  EAPI_UINT32_C(((x)&0xFFFF)|EAPI_I2C_EXT_CMD)
#define EAPI_I2C_IS_EXT_CMD(x)   (EAPI_UINT32_C((x)&(EAPI_I2C_CMD_TYPE_MASK))==EAPI_I2C_EXT_CMD)
#define EAPI_I2C_IS_STD_CMD(x)   (EAPI_UINT32_C((x)&(EAPI_I2C_CMD_TYPE_MASK))==EAPI_I2C_STD_CMD)
#define EAPI_I2C_IS_NO_CMD(x)    (EAPI_UINT32_C((x)&(EAPI_I2C_CMD_TYPE_MASK))==EAPI_I2C_NO_CMD)
/* 
 * EApiI2CReadTransfer
 * Addr Byte 1 Below Designates Addr MSB in a 10bit address transfer and 
 * the complete address in an 7bit address transfer.
 * 
 * Condition                                | Return Values 
 * -----------------------------------------+------------------------------
 * Library Uninitialized                    | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                            | EAPI_STATUS_INVALID_PARAMETER
 * BufLen==0                                | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                               | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                               | EAPI_STATUS_UNSUPPORTED
 * ByteCnt>pMaxBlkLen                       | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Bus Busy  SDA/SDC low                    | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error        | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                 |
 *   SDA Remains low                        |
 * Time-out due to clock stretching         | EAPI_STATUS_TIMEOUT
 * start<Addr Byte 1><W>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><R>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<Addr Byte 2>Nak | EAPI_STATUS_WRITE_ERROR or
 *                                          | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<CMD Byte 1>Nak  | EAPI_STATUS_WRITE_ERROR
 * start<Addr Byte 1><W>Ack<Data Byte 1>Nak | EAPI_STATUS_WRITE_ERROR
 * ByteCnt>BufLen                           | EAPI_STATUS_MORE_DATA
 * Common Error                             | Common Error Code
 * Else                                     | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiI2CReadTransfer(
    __IN  EApiId_t  Id      , /* I2C Bus Id */
    __IN  uint32_t  Addr    , /* Encoded 7/10Bit I2C
                               * Device Address
                               */
    __IN  uint32_t  Cmd     , /* I2C Command/Offset */
    __OUT     void *pBuffer , /* Transfer Data pBuffer */
    __IN  uint32_t  BufLen  , /* Data pBuffer Length */
    __IN  uint32_t  ByteCnt   /* Byte Count to read */
    );
/* 
 * EApiI2CWriteTransfer
 * Addr Byte 1 Below Designates Addr MSB in a 10bit address transfer and 
 * the complete address in an 7bit address transfer.
 * 
 * Condition                                | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                    | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                            | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                               | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                               | EAPI_STATUS_UNSUPPORTED
 * ByteCnt+(overhead)>pMaxBlkLen            | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Bus Busy  SDA/SDC low                    | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error        | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                 |
 *   SDA Remains low                        |
 * Time-out due to clock stretching         | EAPI_STATUS_TIMEOUT
 * start<Addr Byte 1><W>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><R>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<Addr Byte 2>Nak | EAPI_STATUS_WRITE_ERROR or
 *                                          | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<CMD Byte 1>Nak  | EAPI_STATUS_WRITE_ERROR
 * start<Addr Byte 1><W>Ack<Data Byte 1>Nak | EAPI_STATUS_WRITE_ERROR
 * Common Error                             | Common Error Code
 * Else                                     | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE
EApiI2CWriteTransfer(
    __IN  EApiId_t  Id      , /* I2C Bus Id */
    __IN  uint32_t  Addr    , /* Encoded 7/10Bit I2C 
                               * Device Address 
                               */
    __IN  uint32_t  Cmd     , /* I2C Command/Offset */
    __IN      void *pBuffer , /* Transfer Data pBuffer */
    __IN  uint32_t  ByteCnt   /* Byte Count to write */
    );

/*
 * I2C Probe Types
 *
 * Probe Type 1: 
 * Address Format : 7Bit
 * Start<Addr Byte><W>Ack Stop
 *
 * Probe Type 2: 
 * Address Format : 10Bit
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack Stop
 *
 */

/* 
 * EApiI2CProbeDevice
 * 
 * Condition                                    | Return Values 
 * ---------------------------------------------+------------------------------
 * Library Uninitialized                        | EAPI_STATUS_NOT_INITIALIZED
 * Bus Busy  SDA/SDC low                        | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error            | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                     |
 *   SDA Remains low                            |
 * Time-out due to clock stretching             | EAPI_STATUS_TIMEOUT
 *                                              |
 * 7Bit Address                                 |
 * start<Addr Byte><W>Nak                       | EAPI_STATUS_NOT_FOUND
 *                                              |
 * 10Bit Address                                |
 * start<Addr Byte MSB><W>Nak                   | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte MSB><W>Ack<Addr Byte LSB>Nak | EAPI_STATUS_NOT_FOUND
 *                                              |
 * Common Error                                 | Common Error Code
 * Else                                         | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE
EApiI2CProbeDevice(
    __IN  EApiId_t  Id   , /* I2C Bus Id */
    __IN  uint32_t  Addr   /* Encoded 7/10Bit 
                            * I2C Device Address 
                            */
    );

/*
 *
 *      W A T C H D O G
 *
 */

/*
 *
 * After EApiWDogStart
 *
 * |<- Delay ->|<- Event Timeout ->|<- Reset Timeout ->|
 * A-----------B-------------------C-------------------D
 *
 *
 * After EApiWDogTrigger
 *
 * |<- Event Timeout ->|<- Reset Timeout ->|
 * E-------------------F-------------------G
 *
 *
 * Stage A
 *  Watchdog is started.
 *
 * Stage B
 *  Initial Delay Period is exhausted.
 *
 * Stage C/F
 *  Event is triggered, NMI, IRQ, or PIN is Triggered.
 *  To Allow for possible Software Recovery.
 *
 * Stage D/G
 *  System is reset.
 *
 * Stage E
 *  Watchdog is Triggered.
 *
 * EApiWDogTrigger/EApiWDogStop Must be called before Stage C/F
 * to prevent event from being generated.
 *
 * EApiWDogTrigger/EApiWDogStop Must be called before Stage D/G
 * to prevent The system from being reset.
 *
 */

/* 
 * EApiWDogGetCap
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                            | EAPI_STATUS_UNSUPPORTED
 * pMaxDelay==NULL&&                      |
 * pMaxResetTimeout==NULL&&               |
 * pMaxEventTimeout==NULL                 | EAPI_STATUS_INVALID_PARAMETER
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE
EApiWDogGetCap(
    __OUTOPT uint32_t *pMaxDelay       , /* Maximum Supported 
                                         * Delay in milliseconds
                                         */
    __OUTOPT uint32_t *pMaxEventTimeout, /* Maximum Supported 
                                         * Event Timeout in 
                                         * milliseconds
                                         * 0 == Unsupported
                                         */
    __OUTOPT uint32_t *pMaxResetTimeout  /* Maximum Supported 
                                         * Reset Timeout in 
                                         * milliseconds
                                         */
    );
/* 
 * EApiWDogStart
 * 
 * Condition                        | Return Values 
 * ---------------------------------+------------------------------
 * Library Uninitialized            | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                      | EAPI_STATUS_UNSUPPORTED
 * Delay>pMaxDelay                  | EAPI_STATUS_INVALID_PARAMETER
 * EventTimeout>pMaxEventTimeout    | EAPI_STATUS_INVALID_PARAMETER
 * ResetTimeout>pMaxResetTimeout    | EAPI_STATUS_INVALID_PARAMETER
 * Already Running                  | EAPI_STATUS_RUNNING
 * Common Error                     | Common Error Code
 * Else                             | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiWDogStart(
    __IN  uint32_t Delay       , /* Delay in milliseconds */
    __IN  uint32_t EventTimeout, /* Event Timeout in 
                                  * milliseconds 
                                  */
    __IN  uint32_t ResetTimeout  /* Reset Timeout in 
                                  * milliseconds 
                                  */
    );

/* 
 * EApiWDogTrigger
 * 
 * Condition                        | Return Values 
 * ---------------------------------+------------------------------
 * Library Uninitialized            | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                      | EAPI_STATUS_UNSUPPORTED
 * Watchdog Not Started             | EAPI_STATUS_ERROR
 * Common Error                     | Common Error Code
 * Else                             | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiWDogTrigger(void);

/* 
 * EApiWDogStop
 * 
 * Condition                        | Return Values 
 * ---------------------------------+------------------------------
 * Library Uninitialized            | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                      | EAPI_STATUS_UNSUPPORTED
 * Common Error                     | Common Error Code
 * Else                             | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiWDogStop(void);


/*
 *
 *      G P I O
 *
 */
/*
 *
 * +-----------------------------------------------+
 * |              Physical GPIO                    |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     +-----------------------------------------------+
 *    |     |     |     |     |     |     |     |                                               |
 *    |     |     |     |     |     |     +-----|-----------------------------------------+     |
 *    |     |     |     |     |     |     |     |                                         |     |
 *    |     |     |     |     |     +-----|-----|-----------------------------------+     |     |
 *    |     |     |     |     |     |     |     |                                   |     |     |
 *    |     |     |     |     +-----|-----|-----|-----------------------------+     |     |     |
 *    |     |     |     |     |     |     |     |                             |     |     |     |
 *    |     |     |     +-----|-----|-----|-----|-----------------------+     |     |     |     |
 *    |     |     |     |     |     |     |     |                       |     |     |     |     |
 *    |     |     +-----|-----|-----|-----|-----|-----------------+     |     |     |     |     |
 *    |     |     |     |     |     |     |     |                 |     |     |     |     |     |
 *    |     +-----|-----|-----|-----|-----|-----|-----------+     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |           |     |     |     |     |     |     |
 *    +-----|-----|-----|-----|-----|-----|-----|-----+     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |     |  |            EAPI_ID_GPIO_BITMASK00             |
 *    |     |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |  |            EAPI_ID_GPIO_GPIO07                |
 *    |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |  |            EAPI_ID_GPIO_GPIO06                |
 *    |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |
 *    |     |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |  |            EAPI_ID_GPIO_GPIO05                |
 *    |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |
 *    |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |  |            EAPI_ID_GPIO_GPIO04                |
 *    |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |
 *    |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |  +-----------------------------------------------+
 *    |     |     |  |            EAPI_ID_GPIO_GPIO03                |
 *    |     |     |  +-----------------------------------------------+
 *    |     |     |
 *    |     |     |     0     0     0     0     0     0     0
 *    |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |  +-----------------------------------------------+
 *    |     |  |            EAPI_ID_GPIO_GPIO02                |
 *    |     |  +-----------------------------------------------+
 *    |     |
 *    |     |     0     0     0     0     0     0     0
 *    |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |  +-----------------------------------------------+
 *    |  |            EAPI_ID_GPIO_GPIO01                |
 *    |  +-----------------------------------------------+
 *    |
 *    |     0     0     0     0     0     0     0
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 * |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 * +-----------------------------------------------+
 * |            EAPI_ID_GPIO_GPIO00                |
 * +-----------------------------------------------+
 */
/* IDs */
/*
 * Individual ID Per GPIO Mapping
 */
#define EAPI_GPIO_GPIO_ID(GPIO_NUM)    EAPI_UINT32_C(GPIO_NUM)
#define EAPI_GPIO_GPIO_BITMASK  EAPI_UINT32_C(1)


#define EAPI_ID_GPIO_GPIO00     EAPI_GPIO_GPIO_ID(0) /* (Optional) */
#define EAPI_ID_GPIO_GPIO01     EAPI_GPIO_GPIO_ID(1) /* (Optional) */
#define EAPI_ID_GPIO_GPIO02     EAPI_GPIO_GPIO_ID(2) /* (Optional) */
#define EAPI_ID_GPIO_GPIO03     EAPI_GPIO_GPIO_ID(3) /* (Optional) */

/*
 * Multiple GPIOs Per ID Mapping
 */
#define EAPI_GPIO_BANK_ID(GPIO_NUM)     EAPI_UINT32_C(0x10000|((GPIO_NUM)>>5))
#define EAPI_GPIO_BANK_MASK(GPIO_NUM) EAPI_UINT32_C((1<<((GPIO_NUM)&0x1F))
#define EAPI_GPIO_BANK_TEST_STATE(GPIO_NUM, TState, TValue) \
                        (((TValue>>((GPIO_NUM)&0x1F))&1)==(TState))

#define EAPI_ID_GPIO_BANK00    EAPI_GPIO_BANK_ID( 0) /* GPIOs  0 - 31 
                                                      * (optional)
                                                      */
#define EAPI_ID_GPIO_BANK01    EAPI_GPIO_BANK_ID(32) /* GPIOs 32 - 63 
                                                      * (optional)
                                                      */
#define EAPI_ID_GPIO_BANK02    EAPI_GPIO_BANK_ID(64) /* GPIOs 64 - 95
                                                      * (optional)
                                                      */


/* Bit mask Bit States */
#define EAPI_GPIO_BITMASK_SELECT   1
#define EAPI_GPIO_BITMASK_NOSELECT 0

/* Levels */
#define EAPI_GPIO_LOW     0
#define EAPI_GPIO_HIGH    1

/* Directions */
#define EAPI_GPIO_INPUT   1
#define EAPI_GPIO_OUTPUT  0

/* 
 * EApiGPIOGetDirectionCaps
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * ((pOutputs==NULL)&&(pInputs==NULL))| EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE 
EApiGPIOGetDirectionCaps(
    __IN     EApiId_t Id        , /* GPIO Id */
    __OUTOPT uint32_t *pInputs  , /* Supported GPIO Input
                                   * Bit Mask 
                                   */
    __OUTOPT uint32_t *pOutputs   /* Supported GPIO Output
                                   * Bit Mask 
                                   */
    );
/* 
 * EApiGPIOGetDirection
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * (Bitmask&~(pInputs|pOutputs))      | EAPI_STATUS_INVALID_BITMASK
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiGPIOGetDirection(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected
                                  * Bits 
                                  */
    __OUT uint32_t *pDirection   /* Current Direction */
    );
/* 
 * EApiGPIOSetDirection
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * (Bitmask&~(pInputs|pOutputs))      | EAPI_STATUS_INVALID_BITMASK
 * (Bitmask&pDirection)&~pInputs      | EAPI_STATUS_INVALID_DIRECTION
 * (Bitmask&~pDirection)&~pOutputs    | EAPI_STATUS_INVALID_DIRECTION
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApiStatus_t 
EAPI_CALLTYPE 
EApiGPIOSetDirection(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected 
                                  * Bits 
                                  */
    __IN  uint32_t Direction     /* Direction */
    );
/* 
 * EApiGPIOGetLevel
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * (Bitmask&~(pInputs|pOutputs))      | EAPI_STATUS_INVALID_BITMASK
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE 
EApiGPIOGetLevel(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected
                                  * Bits 
                                  */
    __OUT uint32_t *pLevel       /* Current Level */
    );
/* 
 * EApiGPIOSetLevel
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApiStatus_t
EAPI_CALLTYPE 
EApiGPIOSetLevel(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected 
                                  * Bits 
                                  */
    __IN  uint32_t Level         /* Level */  
    );
/*
 * EApiGPIOGetCount
 *
 * Condition                          | Return Values
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * pCount==NULL                       | EAPI_STATUS_INVALID_PARAMETER
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */

EApiStatus_t
EAPI_CALLTYPE
EApiGPIOGetCount(
    __OUT  uint32_t *pCount     /* GPIO count */
    );

EApiStatus_t
EAPI_CALLTYPE
EApiPoEGetLevel(
    __OUT uint32_t *pLevel      /* PoE pin level */
    );

EApiStatus_t
EAPI_CALLTYPE
EApiPoESetLevel(
    __IN uint32_t Level         /* PoE pin level */
    );


/*
 * EApiSMBReadByte
 *
 * Condition                          | Return Values
 * -----------------------------------+------------------------------
 * pBuffer==NULL                      | EAPI_STATUS_INVALID_PARAMETER
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */

EApiStatus_t
EAPI_CALLTYPE
EApiSMBReadByte(
    __IN EApiId_t Id,
    __IN uint8_t Addr,
    __IN uint8_t Cmd,
    __OUT uint8_t *pBuffer
    );

/*
 * EApiSMBWriteByte
 *
 * Condition                          | Return Values
 * -----------------------------------+------------------------------
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */

EApiStatus_t
EAPI_CALLTYPE
EApiSMBWriteByte(
    __IN EApiId_t Id,
    __IN uint8_t Addr,
    __IN uint8_t Cmd,
    __IN uint8_t Data
    );

/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _EAPI_H_ */

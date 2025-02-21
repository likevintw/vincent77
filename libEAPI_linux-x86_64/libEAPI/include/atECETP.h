#ifndef _ATECETP_H_
#define _ATECETP_H_

#include <stdbool.h>
#include <string.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_SUCCESS           0x0

#define ETP_DEVICE_INFO_AREA    0xA4
#define ETP_USER_INFO_AREA      0xA6

typedef struct {
	unsigned char DeviceOrderText[40];		// A4, offset 0
	unsigned char DeviceOrderNumber[10];	// A4, offset 40
	unsigned char DeviceIndex[3];			// A4, offset 50
	unsigned char DeviceSerialNumber[15];	// A4, offset 53
	unsigned char OperatingSystem[40];		// A4, offset 68
	unsigned char Image[40];				// A4, offset 108
	unsigned char Reverse[92];
} ETP_DATA, *PETP_DATA;

typedef struct {
	unsigned char UserSpace1[128]; 			// A6, offset 0
	unsigned char UserSpace2[128]; 			// A6, offset 128
} ETP_USER_DATA, *PETP_USER_DATA;

EApiStatus_t EApiGetLockStatus(__IN int SlaveAddr, __INOUT unsigned long *pLockStatus);
EApiStatus_t EApiSetEepromProtect(__IN int SlaveAddr, __IN bool bProtect, 
		__IN unsigned char *pPassword, __IN int PasswordLen);
EApiStatus_t EApiETPReadDeviceData(__INOUT PETP_DATA pOutBuffer);
EApiStatus_t EApiETPWriteDeviceData(__INOUT PETP_DATA pOutBuffer);
EApiStatus_t EApiETPReadUserData(__INOUT PETP_USER_DATA pOutBuffer);
EApiStatus_t EApiETPWriteUserData(__INOUT PETP_USER_DATA pOutBuffer);

#ifdef __cplusplus
}
#endif
#endif /* _ATECETP_H_ */


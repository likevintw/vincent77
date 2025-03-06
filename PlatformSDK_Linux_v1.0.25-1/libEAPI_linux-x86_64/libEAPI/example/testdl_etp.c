/* ***************************************************************************
 *
 * test_etp.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atECETP.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <syslog.h>
#include <dlfcn.h>

#define DEFAULT_LOCKFILE		"/var/run/test_etp.pid"
#define CMD_RETURN_BUF_SIZE		4096

void *hDLL = NULL;
typedef EApiStatus_t (*fnEApiGetLockStatus)(
		__IN int SlaveAddr, __INOUT unsigned long *pLockStatus);
typedef EApiStatus_t (*fnEApiSetEepromProtect)(
		__IN int SlaveAddr, __IN bool bProtect, 
		__IN unsigned char *pPassword, __IN int PasswordLen);
typedef EApiStatus_t (*fnEApiETPReadDeviceData)(
		__INOUT PETP_DATA pOutBuffer);
typedef EApiStatus_t (*fnEApiETPWriteDeviceData)(
		__INOUT PETP_DATA pOutBuffer);
typedef EApiStatus_t (*fnEApiETPReadUserData)(
		__INOUT PETP_USER_DATA pOutBuffer);
typedef EApiStatus_t (*fnEApiETPWriteUserData)(
		__INOUT PETP_USER_DATA pOutBuffer);

void openDLL()
{
	hDLL = dlopen("libEAPI.so", RTLD_LAZY);
	if (hDLL == NULL) {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void closeDLL()
{
	if (hDLL) {
		dlclose(hDLL);
		hDLL = NULL;
	}
}

// return 0: unlocked
// return 1: locked
// return other: error
unsigned long isLocked(int SlaveAddr)
{
	EApiStatus_t status = 0;
	unsigned long lockStatus = 0; 

	if (hDLL) {
		fnEApiGetLockStatus EApiGetLockStatus;
		EApiGetLockStatus = (fnEApiGetLockStatus)dlsym(hDLL, "EApiGetLockStatus");
		if (EApiGetLockStatus != NULL) {
			if ((status = EApiGetLockStatus(SlaveAddr, &lockStatus))
					!= ERROR_SUCCESS) {
				printf("%s:%d Error (status: %d)! \n", __func__, __LINE__, status);
				return status;
			}
			printf("[ 0x%X is %s ] \n", SlaveAddr, lockStatus ? "LOCKED":"UNLOCKED");
		} else {
			printf("Line:%d Error : Failed load symbol EApiGetLockStatus ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}

	return lockStatus;
}

void setProtect(int SlaveAddr, bool protect)
{
	EApiStatus_t status = 0;
	/* user define start */
	char password[16] = "12345678";
	/* user define end */

	if (hDLL) {
		fnEApiSetEepromProtect EApiSetEepromProtect;
		EApiSetEepromProtect = (fnEApiSetEepromProtect)dlsym(hDLL, "EApiSetEepromProtect");
		if (EApiSetEepromProtect != NULL) {
			if ((status = EApiSetEepromProtect(SlaveAddr, protect, 
							(unsigned char *)password, strlen(password))) 
					!= ERROR_SUCCESS) {
				printf("%s:%d Error (status: %d)! \n", __func__, __LINE__, status);
				return;
			}
			printf("[ %s 0x%X ] \n", protect ? "LOCK":"UNLOCK", SlaveAddr);
		} else {
			printf("Line:%d Error : Failed load symbol EApiSetEepromProtect ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void readDeviceData()
{
	EApiStatus_t status = 0;
	PETP_DATA pReadDeviceData = NULL;

	if (hDLL) {
		fnEApiETPReadDeviceData EApiETPReadDeviceData;
		EApiETPReadDeviceData = (fnEApiETPReadDeviceData)dlsym(hDLL, "EApiETPReadDeviceData");
		if (EApiETPReadDeviceData != NULL) {
			pReadDeviceData = (PETP_DATA)malloc(sizeof(ETP_DATA));
			if (pReadDeviceData == NULL) {
				printf("Error: malloc error (size: %lu) \n", (unsigned long)sizeof(ETP_DATA));
				return;
			}
			memset(pReadDeviceData, 0, sizeof(ETP_DATA));

			if ((status = EApiETPReadDeviceData(pReadDeviceData))
					!= ERROR_SUCCESS) {
				free(pReadDeviceData);
				printf("%s:%d Error (status: %d)! \n", __func__, __LINE__, status);
				return;
			}
			printf("read device data successful. \n");
			printf("DeviceOrderText: %-40.40s \n", pReadDeviceData->DeviceOrderText);
			printf("DeviceOrderNumber: %-10.10s \n", pReadDeviceData->DeviceOrderNumber);
			printf("DeviceIndex: %-3.3s \n", pReadDeviceData->DeviceIndex);
			printf("DeviceSerialNumber: %-15.15s \n", pReadDeviceData->DeviceSerialNumber);
			printf("OperatingSystem: %-40.40s \n", pReadDeviceData->OperatingSystem);
			printf("Image: %-40.40s \n", pReadDeviceData->Image);

			free(pReadDeviceData);
		} else {
			printf("Line:%d Error : Failed load symbol EApiETPReadDeviceData ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void readUserData()
{
	EApiStatus_t status = 0;
	PETP_USER_DATA pReadUserData = NULL;
	int i = 0;

	if (hDLL) {
		fnEApiETPReadUserData EApiETPReadUserData;
		EApiETPReadUserData = (fnEApiETPReadUserData)dlsym(hDLL, "EApiETPReadUserData");
		if (EApiETPReadUserData != NULL) {
			pReadUserData = (PETP_USER_DATA)malloc(sizeof(ETP_USER_DATA));
			if (pReadUserData == NULL) {
				printf("Error: malloc error (size: %lu) \n", (unsigned long)sizeof(ETP_USER_DATA));
				return;
			}
			memset(pReadUserData, 0, sizeof(ETP_USER_DATA));

			if ((status = EApiETPReadUserData(pReadUserData))
					!= ERROR_SUCCESS) {
				free(pReadUserData);
				printf("%s:%d Error (status: %d)! \n", __func__, __LINE__, status);
				return;
			}
			printf("read UserSpace1: (HEX)\n");
			for (i = 0; i < 128; i++) {
				if (i == 128 - 1) {
					printf("0x%02X\n", pReadUserData->UserSpace1[i]);
				} else {
					printf("0x%02X ", pReadUserData->UserSpace1[i]);
				}
			}

			printf("read UserSpace2: (HEX)\n");
			for (i = 0; i < 128; i++) {
				if (i == 128 - 1) {
					printf("0x%02X\n", pReadUserData->UserSpace2[i]);
				} else {
					printf("0x%02X ", pReadUserData->UserSpace2[i]);
				}
			}

			free(pReadUserData);
		} else {
			printf("Line:%d Error : Failed load symbol EApiETPReadUserData ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void writeUserData()
{
	EApiStatus_t status = 0;
	/* user define start */
	ETP_USER_DATA writeUserData = {
		{
			0x11, 0x22, 0x33, 0x44, 0x55, 
			0x66, 0x77, 0x88, 0x99, 0xAA, 
			0xBB, 0xCC, 0xDD, 0xEE, 0xFF
		},
		{
			0x11, 0x22, 0x33, 0x44, 0x55, 
			0x66, 0x77, 0x88, 0x99, 0xAA, 
			0xBB, 0xCC, 0xDD, 0xEE, 0xFF
		}
	};
	/* user define end */

	if (hDLL) {
		fnEApiETPWriteUserData EApiETPWriteUserData;
		EApiETPWriteUserData = (fnEApiETPWriteUserData)dlsym(hDLL, "EApiETPWriteUserData");
		if (EApiETPWriteUserData != NULL) {
	if ((status = EApiETPWriteUserData(&writeUserData))
			!= ERROR_SUCCESS) {
		printf("%s:%d Error (status: %d)! \n", __func__, __LINE__, status);
		return;
	}
	printf("write user data successful. \n");
		} else {
			printf("Line:%d Error : Failed load symbol EApiETPWriteUserData ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

int CheckExit(const char *pFile)
{
	if (pFile == NULL) {
		return -1;
	}

	int LockFd = open(pFile, O_RDWR | O_CREAT);
	if (LockFd == -1) {
		return -2;
	}

	int iret = flock(LockFd, LOCK_EX | LOCK_NB);
	if (iret == -1) {
		return -3;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	switch (CheckExit(DEFAULT_LOCKFILE)) {
	default:
		break;
	case -1:
		printf("Paramener error! \n");
		return 0;
	case -2:
		printf("Open file error! \n");
		return 0;
	case -3:
		printf("Repeatedly call! \n");
		return 0;
	}

	openDLL();
	readDeviceData();
	writeUserData();
	readUserData();
	closeDLL();

	return 0;
}

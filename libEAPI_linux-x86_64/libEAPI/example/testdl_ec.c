/* ***************************************************************************
 *
 * testdl_ec.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atEAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <syslog.h>
#include <dlfcn.h>
#include "eapi_sharefunc.h"

#define DEFAULT_LOCKFILE		"/var/run/test_ec.pid"
#define CMD_RETURN_BUF_SIZE		4096

void *hDLL = NULL;
typedef EApiStatus_t (*fnEApiBoardGetStringA)(EApiId_t Id, char *pBuffer, uint32_t *pBufLen);
typedef EApiStatus_t (*fnEApiGetCOMports)(PLATFORM_COMPORT **comports, unsigned int *len);
typedef EApiStatus_t (*fnEApiGetMemoryAvailable)(float *mem_available);
typedef EApiStatus_t (*fnEApiGetDiskInfo)(PDISK_INFO diskInfo);

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

void getBoardString(EApiId_t Id)
{
	char *pBuffer = NULL;
	uint32_t bufLen = 0;
	EApiStatus_t ret = 0;

	if (hDLL) {
		fnEApiBoardGetStringA EApiBoardGetStringA;
		EApiBoardGetStringA = (fnEApiBoardGetStringA)dlsym(hDLL, "EApiBoardGetStringA");
		if (EApiBoardGetStringA != NULL) {
			// Alloc buffer
			pBuffer = (char *)malloc(CMD_RETURN_BUF_SIZE);
			if (pBuffer == NULL) {
				return;
			}
			bufLen = CMD_RETURN_BUF_SIZE;
			memset(pBuffer, 0, bufLen);

			// call EAPI func and print result
			ret = EApiBoardGetStringA(Id, pBuffer, &bufLen);
			if (ret != 0){
                            char errorstr[0x80] = {0};
                            printf("ID: 0x%-8x\tError: [0x%-8x] %s \n", Id, ret, EApiStatus_StringTranslator(ret, errorstr));
			}
			else{
				printf("ID: 0x%-8x\tInformation: %s \n", Id, pBuffer);
				//printf("Id: %d \nret: %d \npBuffer: %s \nbufLen: %d \n", Id, ret, pBuffer, bufLen);

				// free buffer
				free(pBuffer);
			}	
		} 
		else {
			printf("Line:%d Error : Failed load symbol EApiBoardGetStringA ! \n", __LINE__);
		}
	} 
	else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void getMemoryAvailable()
{
	EApiStatus_t ret = 0;
	float mem_available = 0.0;

	if (hDLL) {
		fnEApiGetMemoryAvailable EApiGetMemoryAvailable;
		EApiGetMemoryAvailable = (fnEApiGetMemoryAvailable)dlsym(hDLL, "EApiGetMemoryAvailable");
		if (EApiGetMemoryAvailable != NULL) {
			// call EAPI func and print result
			ret = EApiGetMemoryAvailable(&mem_available);
			if (ret == EAPI_STATUS_INVALID_PARAMETER) {
				printf("NULL point error! \n");
				return;
			}
			printf("mem_available(KB): %.0f \n", mem_available);
			//printf("ret: %d \nmem_available(KB): %.0f \n", ret, mem_available);
		} else {
			printf("Line:%d Error : Failed load symbol EApiGetMemoryAvailable ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void getCOMports()
{
	PLATFORM_COMPORT *comports = NULL;
	unsigned int i = 0;
	unsigned int serialNum = 0;
	EApiStatus_t ret = 0;

	if (hDLL) {
		fnEApiGetCOMports EApiGetCOMports;
		EApiGetCOMports = (fnEApiGetCOMports)dlsym(hDLL, "EApiGetCOMports");
		if (EApiGetCOMports != NULL) {
			// call EAPI func and print result
			ret = EApiGetCOMports(&comports, &serialNum);
			if(ret != 0){
				printf("Call EAPI func FAIL");
			}
			else{
				printf("serialNum: %d \n", serialNum);
				//printf("serialNum: %d \nret: %d \n", serialNum, ret);
				if (comports != NULL) {
					for (i = 0; i < serialNum; i++) {
						printf("[console-%d] %s \n", i, comports[i].name);
						printf("[console-%d] %s \n", i, comports[i].pnpId);
						printf("[console-%d] %s \n", i, comports[i].manufacturer);
						printf("[console-%d] %s \n", i, comports[i].locationId);
					}
					free(comports);
				}
			 
				else {
					printf("Line:%d Error : Failed load symbol EApiGetCOMports ! \n", __LINE__);
				}
			} 
		}	
		else {
			printf("Line:%d Error : Failed load library ! \n", __LINE__);
		}
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
	getBoardString(EAPI_ID_BOARD_NAME_STR);
	getBoardString(EAPI_ID_BOARD_BIOS_REVISION_STR);
	getBoardString(EAPI_ID_BOARD_EC_REVISION_STR);
	getBoardString(EAPI_ID_BOARD_OS_REVISION_STR);
	getBoardString(EAPI_ID_BOARD_CPU_MODEL_NAME_STR);
        getBoardString( EAPI_ID_BOARD_DMIBIOS_VENDOR_STR );
        getBoardString( EAPI_ID_BOARD_DMIBIOS_VERSION_STR );
        getBoardString( EAPI_ID_BOARD_DMIBIOS_DATE_STR );
        getBoardString( EAPI_ID_BOARD_DMISYS_UUID_STR );
        getBoardString( EAPI_ID_BOARD_DMISYS_VENDOR_STR );
        getBoardString( EAPI_ID_BOARD_DMISYS_PRODUCT_STR );
        getBoardString( EAPI_ID_BOARD_DMISYS_VERSION_STR );
        getBoardString( EAPI_ID_BOARD_DMISYS_SERIAL_STR );
        getBoardString( EAPI_ID_BOARD_DMIBOARD_VENDOR_STR );
        getBoardString( EAPI_ID_BOARD_DMIBOARD_NAME_STR );
        getBoardString( EAPI_ID_BOARD_DMIBOARD_VERSION_STR );
        getBoardString( EAPI_ID_BOARD_DMIBOARD_SERIAL_STR );
        getBoardString( EAPI_ID_BOARD_DMIBOARD_ASSET_TAG_STR );

	getMemoryAvailable();
	getCOMports();
	closeDLL();

	return 0;
}

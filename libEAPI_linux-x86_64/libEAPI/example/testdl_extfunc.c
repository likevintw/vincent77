/* ***************************************************************************
 *
 * test_extfunc.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atECEXTFUNC.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dlfcn.h>

#define DEFAULT_LOCKFILE		"/var/run/test_extfunc.pid"
#define CMD_RETURN_BUF_SIZE		4096

#define LEDTEST
#define POWERTEST

// product_name
char board_id[32];

void *hDLL = NULL;
typedef EApiStatus_t (*fnEApiExtFunctionGetStatus)(
		__IN EApiId_t Id, 
		__INOUT uint32_t* pStatus);
typedef EApiStatus_t (*fnEApiExtFunctionSetStatus)(
		__IN EApiId_t Id, __IN uint32_t Status);

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

void getLEDStatus(unsigned int id)
{
	EApiStatus_t ret = 0;
	unsigned int status = 0;

	if (hDLL) {
		fnEApiExtFunctionGetStatus EApiExtFunctionGetStatus;
		EApiExtFunctionGetStatus = (fnEApiExtFunctionGetStatus)dlsym(hDLL, "EApiExtFunctionGetStatus");
		if (EApiExtFunctionGetStatus != NULL) {
			// call EAPI func and print result
			ret = EApiExtFunctionGetStatus(id, &status);
			if (ret != EAPI_STATUS_SUCCESS) {
				printf("Error: %s:%d \n", __func__, __LINE__);
				return;
			}
			printf("Get LED%d status: %s \n", id, status?"ON":"OFF");
		} else {
			printf("Line:%d Error : Failed load symbol EApiExtFunctionGetStatus ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void setLEDStatus(unsigned int id, unsigned int status)
{
	EApiStatus_t ret = 0;

	if (hDLL) {
		fnEApiExtFunctionSetStatus EApiExtFunctionSetStatus ;
		EApiExtFunctionSetStatus = (fnEApiExtFunctionSetStatus)dlsym(hDLL, "EApiExtFunctionSetStatus");
		if (EApiExtFunctionSetStatus != NULL) {
			// call EAPI func and print result
			ret = EApiExtFunctionSetStatus(id, status);
			if (ret != EAPI_STATUS_SUCCESS) {
				printf("Error: %s:%d \n", __func__, __LINE__);
				return;
			}
			printf("Set LED%d %s successful! \n", id, status?"ON":"OFF");
		} else {
			printf("Line:%d Error : Failed load symbol EApiExtFunctionSetStatus ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}

}

void CheckHWType ()
{
    //int result = 0
    char cmd[64];
    char *product_name_tmp = NULL;
	
    memset (cmd, 0, sizeof(cmd));
    memset (board_id, 0, sizeof(board_id));
    if( access( "/sys/class/dmi/id/product_name", F_OK ) != -1) {
        snprintf (cmd, 64, "/sys/class/dmi/id/product_name");
    }
    else{
        snprintf (cmd, 64, "/proc/board");
    }

    FILE *tmp=fopen(cmd, "r");
    while (fgets(board_id, sizeof(board_id), tmp) !=NULL);
    product_name_tmp = strstr(board_id, "\n");

    if(product_name_tmp){
        *product_name_tmp = '\0';
    }
    fclose(tmp);
}

void checkPowerStatus(unsigned int id)
{
	EApiStatus_t ret = 0;
	unsigned int status = 0;

	if (hDLL) {
		fnEApiExtFunctionGetStatus EApiExtFunctionGetStatus;
		EApiExtFunctionGetStatus = (fnEApiExtFunctionGetStatus)dlsym(hDLL, "EApiExtFunctionGetStatus");
		if (EApiExtFunctionGetStatus != NULL) {
			// call EAPI func and print result
			ret = EApiExtFunctionGetStatus(id, &status);
			if (ret != EAPI_STATUS_SUCCESS) {
				printf("Error: %s:%d \n", __func__, __LINE__);
				return;
			}
			printf("Get POWER%d status: %s \n", id, status?"ON":"OFF");
		} else {
			printf("Line:%d Error : Failed load symbol EApiExtFunctionGetStatus ! \n", __LINE__);
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
    int count = 5;
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

    CheckHWType();
    openDLL();
    if (strstr(board_id, "UNO-148") != NULL){
	printf("set LED to 0\n");
        setLEDStatus(EAPI_ID_EXT_FUNC_LED(0), 0);
        getLEDStatus(EAPI_ID_EXT_FUNC_LED(0));
        sleep(1);
	printf("set LED to 1\n");
        setLEDStatus(EAPI_ID_EXT_FUNC_LED(0), 1);
        getLEDStatus(EAPI_ID_EXT_FUNC_LED(0));
        sleep(1);
	exit(1);
    }
	
#ifdef LEDTEST
	// for UNO-1372G-J021AE
	while (count --) {
		setLEDStatus(EAPI_ID_EXT_FUNC_LED(1), 0);
		getLEDStatus(EAPI_ID_EXT_FUNC_LED(1));
		sleep(1);
		setLEDStatus(EAPI_ID_EXT_FUNC_LED(1), 1);
		getLEDStatus(EAPI_ID_EXT_FUNC_LED(1));
		sleep(1);
	}
#endif	// LEDTEST
#ifdef POWERTEST
	checkPowerStatus(EAPI_ID_EXT_FUNC_POWER_STATUS_VIN(0));
	checkPowerStatus(EAPI_ID_EXT_FUNC_POWER_STATUS_VIN(1));
#endif	// POWERTEST

	closeDLL();

	return 0;
}

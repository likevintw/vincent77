/* ***************************************************************************
 *
 * test_brightness.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atECBRIGHTNESS.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <syslog.h>
#include <dlfcn.h>
#include "eapi_sharefunc.h"

#define DEFAULT_LOCKFILE		"/var/run/test_etp.pid"
#define CMD_RETURN_BUF_SIZE		4096

void *hDLL = NULL;

typedef EApiStatus_t (*fnEApiDisplayGetBacklightBrightness)(
		__IN EApiId_t Id, __OUT uint32_t *pBright);
typedef EApiStatus_t (*fnEApiDisplaySetBacklightBrightness)(
		__IN EApiId_t Id, __IN uint32_t Bright);
typedef EApiStatus_t (*fnEApiDisplayGetCap)(__IN EApiId_t Id, 
		__IN uint32_t CapId, __OUT uint32_t *pValue);
typedef EApiStatus_t (*fnEApiDisplaySetCap)(__IN EApiId_t Id,
		__IN uint32_t CapId, __IN uint32_t Value);

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

void DisplayGetBacklightBrightness(EApiId_t Id, uint32_t *pBright)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;
	uint32_t Bright = 0;

	if (hDLL) {
		fnEApiDisplayGetBacklightBrightness EApiDisplayGetBacklightBrightness;
		EApiDisplayGetBacklightBrightness = (fnEApiDisplayGetBacklightBrightness)dlsym(hDLL, "EApiDisplayGetBacklightBrightness");
		if (EApiDisplayGetBacklightBrightness != NULL) {
			if ((status = EApiDisplayGetBacklightBrightness(Id, &Bright))
					!= EAPI_STATUS_SUCCESS) {
                            char errorstr[0x80] = {0};
                            printf("%s:%d Error (status: [0x%X]%s)! \n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, errorstr));
                            return;
			}
			*pBright = Bright;
			printf("Current bright: %u \n", *pBright);
		} else {
			printf("Line:%d Error : Failed load symbol EApiDisplayGetBacklightBrightness ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void DisplaySetBacklightBrightness(EApiId_t Id, uint32_t Bright)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiDisplaySetBacklightBrightness EApiDisplaySetBacklightBrightness;
		EApiDisplaySetBacklightBrightness = (fnEApiDisplaySetBacklightBrightness)dlsym(hDLL, "EApiDisplaySetBacklightBrightness");
		if (EApiDisplaySetBacklightBrightness != NULL) {
			if ((status = EApiDisplaySetBacklightBrightness(Id, Bright))
					!= EAPI_STATUS_SUCCESS) {
                                char errorstr[0x80] = {0};
                                printf("%s:%d Error (status: [0x%X]%s)! \n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, errorstr));
				return;
			}
		} else {
			printf("Line:%d Error : Failed load symbol EApiDisplaySetBacklightBrightness ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void DisplayGetCap(EApiId_t Id, uint32_t CapId, uint32_t *pValue)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;
	uint32_t Value = 0;

	if (hDLL) {
		fnEApiDisplayGetCap EApiDisplayGetCap;
		EApiDisplayGetCap = (fnEApiDisplayGetCap)dlsym(hDLL, "EApiDisplayGetCap");
		if (EApiDisplayGetCap != NULL) {
                    char str_id[0x40];
                    switch (CapId) {
                        case EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM:
                            sprintf(str_id, "EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM");
                            break;
                        case EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM:
                            sprintf(str_id, "EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM");
                            break;
                        case EAPI_ID_DISPLAY_AUTO_BRIGHTNESS:
                            sprintf(str_id, "EAPI_ID_DISPLAY_AUTO_BRIGHTNESS");
                            break;
                        default:
                            break;
                    }
			if ((status = EApiDisplayGetCap(Id, CapId, &Value))
					!= EAPI_STATUS_SUCCESS) {
                                char errorstr[0x80] = {0};
                                printf("%s (%s): %s[0x%X]) \n", __func__, str_id, EApiStatus_StringTranslator(status, errorstr), status);
				return;
			}
			*pValue = Value;
			printf("Value: %u \n", *pValue);
		} else {
			printf("Line:%d Error : Failed load symbol EApiDisplayGetCap ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void DisplaySetCap(EApiId_t Id, uint32_t CapId, uint32_t Value)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiDisplaySetCap EApiDisplaySetCap;
		EApiDisplaySetCap = (fnEApiDisplaySetCap)dlsym(hDLL, "EApiDisplaySetCap");
		if (EApiDisplaySetCap != NULL) {
                    char str_id[0x40];
                    switch (CapId) {
                        case EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM:
                            sprintf(str_id, "EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM");
                            break;
                        case EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM:
                            sprintf(str_id, "EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM");
                            break;
                        case EAPI_ID_DISPLAY_AUTO_BRIGHTNESS:
                            sprintf(str_id, "EAPI_ID_DISPLAY_AUTO_BRIGHTNESS");
                            break;
                        default:
                            break;
                    }
			if ((status = EApiDisplaySetCap(Id, CapId, Value))
					!= EAPI_STATUS_SUCCESS) {
                                char errorstr[0x80] = {0};
                                printf("%s (%s): %s[0x%X]) \n", __func__, str_id, EApiStatus_StringTranslator(status, errorstr), status);
				return;
			}
		} else {
			printf("Line:%d Error : Failed load symbol EApiDisplaySetCap ! \n", __LINE__);
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

void usage(char *filename)
{
	printf("Usage: #%s [OPTIONS]\n", filename);
	printf("OPTIONS:%s must have three parameters\n",filename);
   	printf("The first parameter is min brightness value\n");
   	printf("The second parameter is max brightness value\n");
   	printf("The last parameter is seted brightness value\n");
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

    uint32_t minnum = 0;
    uint32_t maxnum = 9;
    uint32_t setnum = 0;
	uint32_t i = 0, increment;

	openDLL();

	DisplaySetCap(EAPI_ID_BACKLIGHT_1, EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM, minnum);
	minnum = 0;
	DisplayGetCap(EAPI_ID_BACKLIGHT_1, EAPI_ID_DISPLAY_BRIGHTNESS_MINIMUM, &minnum); 

	DisplaySetCap(EAPI_ID_BACKLIGHT_1, EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM, maxnum);
	maxnum = 0;
	DisplayGetCap(EAPI_ID_BACKLIGHT_1, EAPI_ID_DISPLAY_BRIGHTNESS_MAXIMUM, &maxnum); 

        if(maxnum > 12) increment = maxnum /12;
        else increment = 1;

	for (i = minnum; i < maxnum; i=i+increment){
		setnum = 0;
		DisplaySetBacklightBrightness(EAPI_ID_BACKLIGHT_1, i);
		DisplayGetBacklightBrightness(EAPI_ID_BACKLIGHT_1, &setnum);
		sleep(1);
	}
        {//test max brightness
            setnum = 0;
		DisplaySetBacklightBrightness(EAPI_ID_BACKLIGHT_1, maxnum);
		DisplayGetBacklightBrightness(EAPI_ID_BACKLIGHT_1, &setnum);
        }


	closeDLL();
	return 0;
}

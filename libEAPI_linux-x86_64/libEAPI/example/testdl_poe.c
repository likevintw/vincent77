/* ***************************************************************************
 *
 * testdl_gpio.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atGPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/file.h>
#include <syslog.h>
#include "eapi_sharefunc.h"

#define DEFAULT_LOCKFILE		"/var/run/test_poe.pid"
#define CMD_RETURN_BUF_SIZE		4096
enum options_inpoetest {
    eopt_INVALID_OPT = 0,
    eopt_STATUS = 1,
    eopt_SET_ON = 2,
    eopt_SET_OFF = 3,
    eopt_HELPGUIDE = 4,
};


void *hDLL;
void *hDLL_poe; //to get PoE pin information

typedef EApiStatus_t (*fnEApiPoESetLevel) (uint32_t level);
typedef EApiStatus_t (*fnEApiPoEGetLevel) (uint32_t *level);
typedef EApiStatus_t (*fnEApiLibInitialize) (void);
typedef EApiStatus_t (*fnEApiLibUnInitialize) (void);
typedef EApiStatus_t (*fnEApiBoardGetValue) (uint32_t Id, uint32_t *value);

void *OpenEAPI()
{
	return dlopen("libATGPIO.so", RTLD_LAZY);
}

void *OpenPoEinfo()
{
    return dlopen("libEAPI.so", RTLD_LAZY);
}

void CloseDLL(void *hDLL)
{
	if(hDLL) {
		dlclose(hDLL);
	}
}

EApiStatus_t PoEGetPinNum(uint32_t *pin)
{
    EApiStatus_t status = EAPI_STATUS_SUCCESS;

    if (hDLL_poe) {
        fnEApiBoardGetValue EApiBoardGetValue;
        EApiBoardGetValue = (fnEApiBoardGetValue)dlsym(hDLL_poe, "EApiBoardGetValue");
        if (EApiBoardGetValue != NULL) {
            status = EApiBoardGetValue(EAPI_ID_GPIO_POE_PINNUM, pin);
        } else {
            printf("Dlsym Error : %s \n", __func__);
        }
    } else {
        printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
    }

    if (status != EAPI_STATUS_SUCCESS) {
        char buffer[0x80] = {0};
        printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
    }
    return status;

}

EApiStatus_t PoEGetLevel(uint32_t *level)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
            fnEApiPoEGetLevel EApiPoEGetLevel;
		EApiPoEGetLevel = (fnEApiPoEGetLevel)dlsym(hDLL, "EApiPoEGetLevel");
		if (EApiPoEGetLevel != NULL) {
			status = EApiPoEGetLevel(level);
		} else {
			printf("Dlsym Error : %s \n", __func__);
		}
	} else {
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS) {
                char buffer[0x80] = {0};
                printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
        return status;
}
EApiStatus_t PoESetLevel(uint32_t level)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
            fnEApiPoESetLevel EApiPoESetLevel;
		EApiPoESetLevel = (fnEApiPoESetLevel)dlsym(hDLL, "EApiPoESetLevel");
		if (EApiPoESetLevel != NULL) {
			status = EApiPoESetLevel(level);
		} else {
			printf("Dlsym Error : %s \n", __func__);
		}
	} else {
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS) {
                char buffer[0x80] = {0};
                printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
        return status;
}


void LibUnInitialize(void)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiLibUnInitialize EApiLibUnInitialize;

		EApiLibUnInitialize = (fnEApiLibUnInitialize)dlsym(hDLL, "EApiLibUnInitialize");
		if (EApiLibUnInitialize != NULL) {
			status = EApiLibUnInitialize();
		} else {
			printf("Dlsym Error : %s \n", __func__);
		}
	} else {
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS) {
		printf("Error : %s:%d (0x00%X) \n", __func__, __LINE__, status);
	}
}


bool LibInitialize(void)
{
        bool retval = true;
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiLibInitialize EApiLibInitialize;

		EApiLibInitialize = (fnEApiLibInitialize)dlsym(hDLL, "EApiLibInitialize");
		if (EApiLibInitialize != NULL) {
			status = EApiLibInitialize();
		} else {
			printf("Dlsym Error : %s \n", __func__);
                        retval = false;
		}
	} else {
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
                retval = false;
	}

	if (status != EAPI_STATUS_SUCCESS) {
                char buffer[0x80] = {0};
                printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
                retval = false;
	}
        return retval;
}

void Usage(void)
{
	printf("Usage: testdl_poe <command>\n");
        printf("--level         Show current level of PoE\n");
        printf("-s <on or off>  Switch ON or OFF\n");
        printf("-h              Print help guide\n");
}

uint32_t MyAtoU(const char *str)
{
	if (str == NULL) {
		printf("Error: NULL parameter. \n");
		return 999;
	}

	return (uint32_t)(str[0] - 48);
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


int getcmdvalue(int argc, char **argv){

    int ret_compare_level = 0, ret_compare_set = 0, ret_compare_helpguide = 0;

    for(int a = 0; a< argc; a++)
    {
        ret_compare_level = strcmp("--level", argv[a]);
        ret_compare_set = strcmp("-s", argv[a]);
        ret_compare_helpguide = strcmp("-h", argv[a]);
        if(0 == ret_compare_helpguide){
            return eopt_HELPGUIDE;
        }
        else if(0 == ret_compare_level){
            return eopt_STATUS;
        }
        else if ( 0 == ret_compare_set && (a+1)<argc ){//set and next opt string is available
            if( 0 == strcmp("on", argv[a+1])) return eopt_SET_ON;
            else if( 0 == strcmp("off", argv[a+1])) return eopt_SET_OFF;
            else return eopt_INVALID_OPT;
        }
        else{
            return eopt_INVALID_OPT;
        }
    }//end of for loop
    return eopt_INVALID_OPT;

}

int main(int argc, char* argv[])
{
    int optionval = eopt_INVALID_OPT;
    uint32_t Level = 0;

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


        //handle option
        optionval = getcmdvalue(argc-1, argv+1);
        
	hDLL = OpenEAPI();
        hDLL_poe = OpenPoEinfo();
        uint32_t value = 0;
        //Intialization is essential.
        if(false == LibInitialize()){
                printf("Unable to Intialize.\nPlease check device compatibility.\n");
                return 0;
        }

	switch (optionval){
            case eopt_INVALID_OPT:
                printf("Invalid option. Use -h for help guide\n");
                Usage();
                break;
            case eopt_STATUS:
                if(EAPI_STATUS_SUCCESS == PoEGetLevel(&Level) &&
                        EAPI_STATUS_SUCCESS == PoEGetPinNum(&value))
                {
                    if(0 == Level) printf("PoE(pin %d) status: OFF\n", value);
                    if(1 == Level) printf("PoE(pin %d) status: ON\n", value);
                }
                break;
            case eopt_SET_ON:
                if(EAPI_STATUS_SUCCESS ==PoESetLevel(1) &&
                        EAPI_STATUS_SUCCESS == PoEGetPinNum(&value))
                {
                   printf("PoE(pin %d) level is ON now.\n", value);
                }
                break;
            case eopt_SET_OFF:
                if(EAPI_STATUS_SUCCESS ==PoESetLevel(0) &&
                        EAPI_STATUS_SUCCESS == PoEGetPinNum(&value))
                {
                   printf("PoE(pin %d) level is OFF now.\n", value);
                }
                break;
            case eopt_HELPGUIDE:
                Usage();
                break;
            default:
                printf("Please confirm your option.\n");
                Usage();
                break;
	}

        LibUnInitialize();
	CloseDLL(hDLL);
        CloseDLL(hDLL_poe);
	return 0;
}

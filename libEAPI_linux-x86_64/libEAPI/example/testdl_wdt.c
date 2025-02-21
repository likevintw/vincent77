/* ***************************************************************************
 *
 * test_wdt.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atECWDT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <syslog.h>
#include <dlfcn.h>
#include <signal.h>

#define DEFAULT_LOCKFILE		"/var/run/test_etp.pid"
#define CMD_RETURN_BUF_SIZE		4096

void *hDLL = NULL;

typedef EApiStatus_t (*fnEApiWDogGetCap)(__OUTOPT uint32_t *pMaxDelay, 
		__OUTOPT uint32_t *pMaxEventTimeout, __OUTOPT uint32_t *pMaxResetTimeout);
typedef EApiStatus_t (*fnEApiWDogStart)(__IN uint32_t Delay, 
		__IN uint32_t EventTimeout, __IN uint32_t ResetTimeout);
typedef EApiStatus_t (*fnEApiWDogTrigger)(void);
typedef EApiStatus_t (*fnEApiWDogStop)(void);

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

void WDTGetCap(uint32_t *pMaxDelay, uint32_t *pMaxEventTimeout, uint32_t *pMaxResetTimeout)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;
	uint32_t MaxDelay = 0;
	uint32_t MaxEventTimeout = 0;
	uint32_t MaxResetTimeout = 0;

	if (hDLL) {
		fnEApiWDogGetCap EApiWDogGetCap;
		EApiWDogGetCap = (fnEApiWDogGetCap)dlsym(hDLL, "EApiWDogGetCap");
		if (EApiWDogGetCap != NULL) {
			if ((status = EApiWDogGetCap(&MaxDelay, &MaxEventTimeout, &MaxResetTimeout))
					!= EAPI_STATUS_SUCCESS) {
				printf("%s:%d Error (status: 0x%X)! \n", __func__, __LINE__, status);
				return;
			}
			printf("MaxDelay:%u MaxEventTimeout:%u MaxResetTimeout:%u (in milliseconds)\n", 
					MaxDelay, MaxEventTimeout, MaxResetTimeout);
			*pMaxDelay = MaxDelay;
			*pMaxEventTimeout = MaxEventTimeout;
			*pMaxResetTimeout = MaxResetTimeout;
		} else {
			printf("Line:%d Error : Failed load symbol EApiWDogGetCap ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

bool WDTStart(uint32_t Delay, uint32_t EventTimeout, uint32_t ResetTimeout)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiWDogStart EApiWDogStart;
		EApiWDogStart = (fnEApiWDogStart)dlsym(hDLL, "EApiWDogStart");
		if (EApiWDogStart != NULL) {
			if ((status = EApiWDogStart(Delay, EventTimeout, ResetTimeout))
					!= EAPI_STATUS_SUCCESS) {
				printf("%s:%d Error (status: 0x%X)! \n", __func__, __LINE__, status);
				return false;
			}
			printf("WDT start. \n");
			printf("WDT timeout has been set to %u seconds.\n"
					"After that, WDT will reset CPU.\n", ResetTimeout/1000);            
                        return true;
		} else {
			printf("Line:%d Error : Failed load symbol EApiWDogStart ! \n", __LINE__);
                        return false;
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
                return false;
	}
}

void WDTKeepAlive()
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiWDogTrigger EApiWDogTrigger;
		EApiWDogTrigger = (fnEApiWDogTrigger)dlsym(hDLL, "EApiWDogTrigger");
		if (EApiWDogTrigger != NULL) {
			if ((status = EApiWDogTrigger())
					!= EAPI_STATUS_SUCCESS) {
				printf("%s:%d Error (status: 0x%X)! \n", __func__, __LINE__, status);
				return;
			}
			printf("WDT keep alive. \n");
		} else {
			printf("Line:%d Error : Failed load symbol EApiWDogTrigger ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void WDTStop()
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL) {
		fnEApiWDogStop EApiWDogStop;
		EApiWDogStop = (fnEApiWDogStop)dlsym(hDLL, "EApiWDogStop");
		if (EApiWDogStop != NULL) {
			if ((status = EApiWDogStop())
					!= EAPI_STATUS_SUCCESS) {
				printf("%s:%d Error (status: 0x%X)! \n", __func__, __LINE__, status);
				return;
			}
			printf("WDT stop. \n");
		} else {
			printf("Line:%d Error : Failed load symbol EApiWDogStop ! \n", __LINE__);
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

static void term(int sig)
{
    printf("Got signal %d, call WDTStop\n", sig);
    WDTStop();
    closeDLL();
    exit(0);
}

void usage(char *programname)
{
		printf("Usage: %s <option> \n", programname);
		printf("[option]: \n");
		printf("          -s <timeout>  : watchdog is started, system will reboot after <timeout> seconds.\n");
		printf("          -t <T>        : set trigger interval as <T> seconds.\n");
		printf("                          This option cannot be used without -s\n");
		printf("          -d            : disable watchdog.\n");
		printf("          -h            : this help guide\n");
}

int main(int argc, char* argv[])
{
	uint32_t MaxDelay = 0;
	uint32_t MaxEventTimeout = 0;
	uint32_t MaxResetTimeout = 0;
	uint32_t resetTimeout = 0, triggerInterval = 0;
	bool keepalive = false;
	bool disable = false;

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

        switch(argc){
            case 1:
                usage(argv[0]);
                return 0;
                break;
            case 2: /* -h or -d */
                switch(argv[1][1])
                {
                    case 'h':
                        usage(argv[0]);
                        return 0;
                        break;
                    case 'd':
                        disable = true;
                        break;
                    default:
                        printf("Invalid option.\n");
                        usage(argv[0]);
                        return 0;
                        break;
                }
                break;
            case 3: /* -s <timeout> */
                switch(argv[1][1])
                {
                    case 's':
                        resetTimeout = atof(argv[2]);
                        break;
                    default:
                        printf("Invalid option.\n");
                        usage(argv[0]);
                        return 0;
                        break;
                }
                break;
            case 5: /* -s <timeout> -t <T> , or -t <T> -s <timeout> */
                if('s' == argv[1][1] && 't' == argv[3][1])
                {
                    resetTimeout = atof(argv[2]);
                    triggerInterval = atof(argv[4]);
                    keepalive = true;
                }
                else if ('t' == argv[1][1] && 's' == argv[3][1])
                {
                    triggerInterval = atof(argv[2]);
                    resetTimeout = atof(argv[4]);
                    keepalive = true;
                }
                else{
                    printf("Invalid option.\n");
                    usage(argv[0]);
                    return 0;
                }
                break;
            default:
                printf("Invalid option.\n");
                usage(argv[0]);
                return 0;
        }

        signal(SIGINT, term);
	openDLL();
	WDTGetCap(&MaxDelay, &MaxEventTimeout, &MaxResetTimeout);

	if (resetTimeout > MaxResetTimeout) {
		printf("The timeout value was out of range (1~%u) ! \n", MaxResetTimeout);
                closeDLL();
		return 0;
	}

	if (disable) {
		WDTStop();
                closeDLL();
                return 0;
        }

        if(true == WDTStart(0, 0, resetTimeout*1000)){	// set watchdog timeout=resetTimeout
            if (keepalive) {
                while (1){
                    sleep(triggerInterval);		// trigger(or ping) watchdog every <triggerInterval> seconds
                    WDTKeepAlive();
                }
            }
        }

	closeDLL();
	return 0;
}

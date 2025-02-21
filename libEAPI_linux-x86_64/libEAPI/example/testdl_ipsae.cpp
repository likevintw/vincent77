/* ***************************************************************************
 *
 * IPS-AE_Sample.cpp : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atIPSAE.h"
#include <sys/file.h>
#include <syslog.h>
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>

#define DEFAULT_LOCKFILE	"/var/run/test_ipsae.pid"

using namespace EApiCommon;


/**********************************************************************
 * Function:    
 *     atCallBack
 * Description: 
 *     atCallBack function will be called when the UPS status information 
 * is updated. UPS status message is stored in variable 'str'. There are 
 * two message type (EMERGENCY and INFORMATION):
 *     EMERGENCY  => Alerts when UPS work is abnormal.
 *     INFOMATION => Informations of UPS reports periodically.
 **********************************************************************/
class AdvIPSAEWorker : public IatCallBack {
	public:
        	virtual ~AdvIPSAEWorker() { }
	void atCallBack(CallBackType type, string str)
	{
		//printf("==============================\ntype: %d\n%s\n==============================\n", type, str.c_str());
		if (type == EMERGENCY) {
			syslog(LOG_EMERG, "%s", str.c_str());
#if 0
		} else if (type == INFOMATION) {
			syslog(LOG_INFO, "%s", str.c_str());
#endif
		}
	};
};

void *hDLL = NULL;
AdvIPSAEWorker *worker = NULL;
typedef	EApiStatus_t (*funcEApiUPSGetDevice)(IatIPSAE **, string, IatCallBack *);
typedef	EApiStatus_t (*funcEApiUPSDelDevice)();

void runIPS_AE(char *comport)
{
	printf("serial = %s \n", comport);
	EApiStatus_t ret = EAPI_STATUS_SUCCESS;

	if (worker == NULL) {
		worker = new AdvIPSAEWorker();
		printf("start, there will send a callback automatically.....\n");
	}

	hDLL = dlopen("libEAPI-IPS.so", RTLD_LAZY);
	if (hDLL != NULL) {
		funcEApiUPSGetDevice EApiUPSGetDevice;
		EApiUPSGetDevice = (funcEApiUPSGetDevice)dlsym(hDLL, "EApiUPSGetDevice");
		if (EApiUPSGetDevice != NULL) {
			IatIPSAE *patIPSAE = NULL;
			if ((ret = EApiUPSGetDevice(&patIPSAE, comport, (IatCallBack*)worker))) {
				printf("EApiUPSGetDevice Error: %d \n", ret);
			}
		} else {
			printf("Line:%d Error : Failed load symbol EApiUPSGetDevice ! \n", __LINE__);
		}
	} else {
		printf("Line:%d Error : Failed load library ! \n", __LINE__);
	}
}

void byeIPS_AE()
{
	if (hDLL) {
		funcEApiUPSDelDevice EApiUPSDelDevice;
		EApiUPSDelDevice = (funcEApiUPSDelDevice)dlsym(hDLL, "EApiUPSDelDevice");
		if (EApiUPSDelDevice != NULL) {
			EApiUPSDelDevice();
		} else {
			printf("Line:%d Error : Failed load symbol EApiUPSDelDevice ! \n", __LINE__);
		}
		dlclose(hDLL);
		hDLL = NULL;
	}

	if (worker != NULL) {
		delete worker;
	}
}

void getSerialStatus() 
{
	if (!hDLL) {
		return;
	}
	funcEApiUPSGetDevice EApiUPSGetDevice;
	EApiUPSGetDevice = (funcEApiUPSGetDevice)dlsym(hDLL, "EApiUPSGetDevice");
	if (EApiUPSGetDevice != NULL) {
		IatIPSAE *patIPSAE = NULL;
		if (!EApiUPSGetDevice(&patIPSAE, "", NULL)) {
			if (!patIPSAE->getSerialStatus()) {
				printf("Line:%d Error : Serial port was not connected ! \n", __LINE__);
			}
		}
	} else {
		printf("Line:%d Error : Failed load symbol EApiUPSGetDevice ! \n", __LINE__);
	}
}

void getIPSAEInfo(struct ipsaeInfo *info) {
	if (!hDLL || info == NULL) {
		return;
	}
	funcEApiUPSGetDevice EApiUPSGetDevice;
	EApiUPSGetDevice = (funcEApiUPSGetDevice)dlsym(hDLL, "EApiUPSGetDevice");
	if (EApiUPSGetDevice != NULL) {
		IatIPSAE *patIPSAE = NULL;
		if (!EApiUPSGetDevice(&patIPSAE, "", NULL)) {
			patIPSAE->getIPSAEInfo(info);
		}
	} else {
		printf("Line:%d Error : Failed load symbol EApiUPSGetDevice ! \n", __LINE__);
	}
}

void setDCoutCutOffDelayTime(int time_min) 
{
	if (!hDLL) {
		return;
	}
	funcEApiUPSGetDevice EApiUPSGetDevice;
	EApiUPSGetDevice = (funcEApiUPSGetDevice)dlsym(hDLL, "EApiUPSGetDevice");
	if (EApiUPSGetDevice != NULL) {
		IatIPSAE *patIPSAE = NULL;
		if (!EApiUPSGetDevice(&patIPSAE, "", NULL)) {
			printf("setDCoutCutOffDelayTime result => %s\n", 
					patIPSAE->setDCoutCutOffDelayTime(time_min).c_str());
		}
	} else {
		printf("Line:%d Error : Failed load symbol EApiUPSGetDevice ! \n", __LINE__);
	}
}

void setDCinLostDelayTime(int time_s) 
{
	if (!hDLL) {
		return;
	}
	funcEApiUPSGetDevice EApiUPSGetDevice;
	EApiUPSGetDevice = (funcEApiUPSGetDevice)dlsym(hDLL, "EApiUPSGetDevice");
	if (EApiUPSGetDevice != NULL) {
		IatIPSAE *patIPSAE = NULL;
		if (!EApiUPSGetDevice(&patIPSAE, "", NULL)) {
			printf("setDCinLostDelayTime result => %s\n", 
					patIPSAE->setDCinLostDelayTime(time_s).c_str());
		}
	} else {
		printf("Line:%d Error : Failed load symbol EApiUPSGetDevice ! \n", __LINE__);
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
	if (argc != 2) {
		printf("Usage: %s \"[COM_PATH]\" \n", argv[0]);
		printf("  [COM_PATH] - /dev/tty*N \n");
		return -1;
	}

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

	runIPS_AE(argv[1]);
	getSerialStatus();

	ipsaeInfo *info = new ipsaeInfo;

	while (1) {
		getIPSAEInfo(info);
		
		if (std::stoi(info->batteryvoltage) == 0) {
			cout << "connecting ..." << endl;
			sleep(1);
			continue;
		} else if (std::stoi(info->batteryvoltage) > 18000) {
			cout << "detect: IPS-2730" << endl;
			setDCinLostDelayTime(300);
			setDCoutCutOffDelayTime(5);
			break;
		} else {
			cout << "detect: IPS-1560" << endl;
			setDCinLostDelayTime(30);
			setDCoutCutOffDelayTime(2);
			break;
		}
	}

	printf("\n** Press any key to Get IPSAE status. \n");
	printf("** Press 'q' to exit. \n\n");
	bool loop = true;
	while (loop) {
		switch (getchar())
		{
		case 'q':
			printf("Exit now... \n");
			loop = false;
			break;
		default:
#if 1
			getIPSAEInfo(info);
			cout << "fwversion: " << info->fwversion << endl;
			cout << "ips: " << info->ips << endl;
			cout << "dcin: " << info->dcin << endl;
			cout << "battery: " << info->battery << endl;
			cout << "inputlostdelay: " << info->inputlostdelay << endl;
			cout << "cutoffdelay: " << info->cutoffdelay << endl;
			cout << "batterylife: " << info->batterylife << endl;
			cout << "batteryvoltage: " << info->batteryvoltage << endl;
			cout << "maxtemperature: " << info->maxtemperature << endl;
			cout << "temperature: " << info->temperature << endl;
			cout << "capacity: " << info->capacity << endl;
#endif
			break;
		}
	}

	byeIPS_AE();
	delete info;
	return 0;
}

/* ***************************************************************************
 *
 * IPS-AE_Sample.cpp : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atIPSAE.h"
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DEFAULT_LOCKFILE	"/var/run/test_ipsae.pid"
#define FIFO_PATH			"UPS_FIFO"

//#define PYTHON_CALL_TEST
//#define USE_FIFO

using namespace EApiCommon;

ipsaeInfo *pInfo;
#ifdef USE_FIFO
int *fifoFd;
#endif	// USE_FIFO

void runIPS_AE(const char *comport);
void byeIPS_AE();
void getSerialStatus();
void getIPSAEInfo(struct ipsaeInfo *info);
void setDCoutCutOffDelayTime(int time_min); 
void setDCinLostDelayTime(int time_s); 
int pythonCall(
		const char *fwversion,
		const char *ips,
		const char *dcin,
		const char *battery,
		const char *inputlostdelay,
		const char *cutoffdelay,
		const char *batterylife,
		const char *batteryvoltage,
		const char *maxtemperature,
		const char *temperature,
		const char *capacity);
int fifoWrite(int fd, const char *str);

/**********************************************************************
 * Function:    
 *     atCallBack
 * Description: 
 *     atCallBack function will be called when the UPS status information 
 *     is updated. UPS status message is stored in variable 'str'. There 
 *     are two message type (EMERGENCY and INFORMATION):
 *         EMERGENCY  => Alerts when UPS work is abnormal.
 *         INFOMATION => Informations of UPS reports periodically.
 **********************************************************************/
class AdvIPSAEWorker : public IatCallBack 
{
	void atCallBack(CallBackType type, string str)
	{
#ifdef PYTHON_CALL_TEST
		getIPSAEInfo(pInfo);
		if (pythonCall(
				pInfo->fwversion.c_str(),
				pInfo->ips.c_str(),
				pInfo->dcin.c_str(),
				pInfo->battery.c_str(),
				pInfo->inputlostdelay.c_str(),
				pInfo->cutoffdelay.c_str(),
				pInfo->batterylife.c_str(),
				pInfo->batteryvoltage.c_str(),
				pInfo->maxtemperature.c_str(),
				pInfo->temperature.c_str(),
				pInfo->capacity.c_str())) {
			syslog(LOG_EMERG, "Call external python function failed! \n");
			printf("Call external python function failed! \n");
		}
#else
#ifdef USE_FIFO
		if (fifoWrite(*fifoFd, str.c_str()) <= 0) {
			printf("Fifo Write failed! \n");
		}
#else
		printf(">>Callback====================\ntype: %d\n%s\n============================<<\n", type, str.c_str());
#endif	// USE_FIFO
#endif	// PYTHON_CALL_TEST

		if (type == EMERGENCY) {
			syslog(LOG_EMERG, "%s", str.c_str());
		//} else if (type == INFOMATION) {
		//	syslog(LOG_INFO, "%s", str.c_str());
		}
	};
};

void *hDLL = NULL;
AdvIPSAEWorker *worker = NULL;
typedef	EApiStatus_t (*funcEApiUPSGetDevice)(IatIPSAE **, string, IatCallBack *);
typedef	EApiStatus_t (*funcEApiUPSDelDevice)();

void runIPS_AE(const char *comport)
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

#ifdef USE_FIFO
	if (access(FIFO_PATH, F_OK) != 0) {
		if (mkfifo(FIFO_PATH, 0777) != 0) {
			printf("Line:%d Error : mkfifo error ! \n", __LINE__);
		}
	}
	
	*fifoFd = open(FIFO_PATH, O_WRONLY);
	if (*fifoFd == -1) {
		printf("Line:%d Error : open fifo error ! \n", __LINE__);
	}
#endif	// USE_FIFO
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

#ifdef USE_FIFO
	close(*fifoFd);
#endif	// USE_FIFO
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

#ifdef USE_FIFO
int fifoWrite(int fd, const char *str)
{

	int wNum = write(fd, str, strlen(str));
	//printf("%s:%d \n", __func__, __LINE__);

	return wNum;
}
#endif // USE_FIFO

#ifdef PYTHON_CALL_TEST
extern "C"
{
#include "Python.h"
}

/**********************************************************************
 * Function:    
 *     pythonCall
 * Description: 
 *     This is an example function that demonstrates how to calling 
 *     python function from C++. It is test pass in Python 3.5.1.
 *     Please visit folloing webkit to get more usage informations:
 *     https://docs.python.org/3/extending/extending.html#calling-python-functions-from-c 
 **********************************************************************/
int pythonCall(
		const char *fwversion,
		const char *ips,
		const char *dcin,
		const char *battery,
		const char *inputlostdelay,
		const char *cutoffdelay,
		const char *batterylife,
		const char *batteryvoltage,
		const char *maxtemperature,
		const char *temperature,
		const char *capacity)
{
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	int result = 0;

	/* 
	 * Initialize the Python interpreter.  Required. 
	 * */
	Py_Initialize();	
	if(!Py_IsInitialized()) {
		return -1;
	}

	/*
	 * int PyRun_SimpleString(const char *command)
	 * 
	 * This is a simplified interface to PyRun_SimpleStringFlags() below,
	 * leaving the PyCompilerFlags* argument set to NULL.
	 *
	 * PyRun_SimpleStringFlags(const char *command, PyCompilerFlags *flags)
	 * Executes the Python source code from command in the __main__ module
	 * according to the flags argument. If __main__ does not already exist, it
	 * is created. Returns 0 on success or -1 if an exception was raised. If
	 * there was an error, there is no way to get the exception information.
	 * */
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	/* Optionally import the module; alternatively,
	 * import can be deferred until the embedded script
	 * imports it.
	 * */
	if ((pModule = PyImport_ImportModule("cppCallPython")) == NULL) {
		Py_Finalize();
		return -1;
	}

	/*
	 * PyObject *PyObject_GetAttrString(PyObject *o, const char *attr_name)
	 *
	 * Retrieve an attribute named attr_name from object o. Returns the
	 * attribute value on success, or NULL on failure. This is the equivalent of
	 * the Python expression o.attr_name.
	 * */
	if ((pFunc = PyObject_GetAttrString(pModule, "testFunction")) == NULL) {
		Py_Finalize();
		return -1;
	}

	/*
	 * PyObject *PyTuple_New(Py_ssize_t len)
	 *
	 * Return a new tuple object of size len, or NULL on failure.
	 * */
	PyObject *pArgs = PyTuple_New(11);		

	/*
	 * int PyTuple_SetItem(PyObject *p, Py_ssize_t pos, PyObject *o)
	 *
	 * Insert a reference to object o at position pos of the tuple pointed to by
	 * p. Return 0 on success.
	 * */
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", fwversion));
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", ips));
	PyTuple_SetItem(pArgs, 2, Py_BuildValue("s", dcin));
	PyTuple_SetItem(pArgs, 3, Py_BuildValue("s", battery));
	PyTuple_SetItem(pArgs, 4, Py_BuildValue("s", inputlostdelay));
	PyTuple_SetItem(pArgs, 5, Py_BuildValue("s", cutoffdelay));
	PyTuple_SetItem(pArgs, 6, Py_BuildValue("s", batterylife));
	PyTuple_SetItem(pArgs, 7, Py_BuildValue("s", batteryvoltage));
	PyTuple_SetItem(pArgs, 8, Py_BuildValue("s", maxtemperature));
	PyTuple_SetItem(pArgs, 9, Py_BuildValue("s", temperature));
	PyTuple_SetItem(pArgs, 10, Py_BuildValue("s", capacity));

	/*
	 * PyObject *PyEval_CallObject(PyObject *func, PyObject *arg)
	 *
	 * This function has two arguments, both pointers to arbitrary Python
	 * objects: the Python function, and the argument list. The argument list
	 * must always be a tuple object, whose length is the number of arguments.
	 * To call the Python function with no arguments, pass an empty tuple; to
	 * call it with one argument, pass a singleton tuple.
	 * */
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);

	/*
	 * int PyArg_Parse( PyObject *args, char *format, ...)
	 *
	 * Convert value.
	 * */
	PyArg_Parse(pReturn, "i", &result);		

	/*
	 * void Py_Finalize()
	 *
	 * This is a backwards-compatible version of Py_FinalizeEx() that disregards
	 * the return value.
	 *
	 * Py_FinalizeEx() Undo all initializations made by Py_Initialize() and 
	 * subsequent use of Python/C API functions, and destroy all sub-interpreters 
	 * (see Py_NewInterpreter() below) that were created and not yet destroyed 
	 * since the last call to Py_Initialize(). Ideally, this frees all memory
	 * allocated by the Python interpreter. This is a no-op when called for a
	 * second time (without calling Py_Initialize() again first). Normally the
	 * return value is 0. If there were errors during finalization (flushing
	 * buffered data), -1 is returned.
	 * */
	Py_Finalize();

	return result;
}
#endif // PYTHON_CALL_TEST

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
	if (argc != 2 || strncmp(argv[1], "/dev/ttyXR", 10)) {
		printf("Usage: %s [COM_PATH] \n", argv[0]); 
		printf("  [COM_PATH] - /dev/ttyXR* \n");
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

#ifdef USE_FIFO
	fifoFd = new int(0);
#endif	// USE_FIFO
	runIPS_AE(argv[1]);
	getSerialStatus();
	pInfo = new ipsaeInfo;
	while (1) {
		getIPSAEInfo(pInfo);
		
		if (std::stoi(pInfo->batteryvoltage) == 0) {
			printf("connecting ... \n");
			sleep(1);
			continue;
		} else if (std::stoi(pInfo->batteryvoltage) > 18000) {
			printf("detect: IPS-2730 \n");
			setDCinLostDelayTime(300);
			setDCoutCutOffDelayTime(5);
			break;
		} else {
			printf("detect: IPS-1560 \n");
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
			getIPSAEInfo(pInfo);
#ifdef PYTHON_CALL_TEST
			pythonCall(
					pInfo->fwversion.c_str(),
					pInfo->ips.c_str(),
					pInfo->dcin.c_str(),
					pInfo->battery.c_str(),
					pInfo->inputlostdelay.c_str(),
					pInfo->cutoffdelay.c_str(),
					pInfo->batterylife.c_str(),
					pInfo->batteryvoltage.c_str(),
					pInfo->maxtemperature.c_str(),
					pInfo->temperature.c_str(),
					pInfo->capacity.c_str());
#else
#ifdef USE_FIFO
			string tmpStr = "\nfwversion: " + pInfo->fwversion + "\n"
				+ "ips: " + pInfo->ips + "\n"
				+ "dcin: " + pInfo->dcin + "\n"
				+ "battery: " + pInfo->battery + "\n" 
				+ "inputlostdelay: " + pInfo->inputlostdelay + "\n"
				+ "cutoffdelay: " + pInfo->cutoffdelay + "\n"
				+ "batterylife: " + pInfo->batterylife + "\n"
				+ "batteryvoltage: " + pInfo->batteryvoltage + "\n"
				+ "maxtemperature: " + pInfo->maxtemperature + "\n"
				+ "temperature: " + pInfo->temperature + "\n"
				+ "capacity: " + pInfo->capacity + "\n\n";
			fifoWrite(*fifoFd, tmpStr.c_str());
#else
			printf(">>getIPSAEInfo================ \n");
			printf("fwversion: %s \n", pInfo->fwversion.c_str());
			printf("ips: %s \n", pInfo->ips.c_str());
			printf("dcin: %s \n", pInfo->dcin.c_str());
			printf("battery: %s \n", pInfo->battery.c_str());
			printf("inputlostdelay: %s \n", pInfo->inputlostdelay.c_str());
			printf("cutoffdelay: %s \n", pInfo->cutoffdelay.c_str());
			printf("batterylife: %s \n", pInfo->batterylife.c_str());
			printf("batteryvoltage: %s \n", pInfo->batteryvoltage.c_str());
			printf("maxtemperature: %s \n", pInfo->maxtemperature.c_str());
			printf("temperature: %s \n", pInfo->temperature.c_str());
			printf("capacity: %s \n", pInfo->capacity.c_str());
			printf("============================<< \n");
#endif	// USE_FIFO
#endif	// PYTHON_CALL_TEST
			break;
		}
	}

	byeIPS_AE();
#ifdef USE_FIFO
	delete fifoFd;
#endif	// USE_FIFO
	delete pInfo;
	return 0;
}

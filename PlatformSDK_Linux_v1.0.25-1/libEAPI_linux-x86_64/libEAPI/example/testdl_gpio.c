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

#define DEFAULT_LOCKFILE "/var/run/test_gpio.pid"
#define CMD_RETURN_BUF_SIZE 4096

void *hDLL;

typedef EApiStatus_t (*fnEApiLibInitialize)(void);
typedef EApiStatus_t (*fnEApiLibUnInitialize)(void);

void *OpenEAPI()
{
	return dlopen("libEAPI.so", RTLD_LAZY);
	// return dlopen("libATGPIO.so", RTLD_LAZY);
}

void CloseEAPI(void *hDLL)
{
	if (hDLL)
	{
		dlclose(hDLL);
	}
}

void GPIOGetLevel(EApiId_t Id, uint32_t Bitmask, uint32_t *pLevel)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiGPIOGetLevel EApiGPIOGetLevel;
		EApiGPIOGetLevel = (fnEApiGPIOGetLevel)dlsym(hDLL, "EApiGPIOGetLevel");
		if (EApiGPIOGetLevel != NULL)
		{
			status = EApiGPIOGetLevel(Id, Bitmask, pLevel);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

void GPIOSetLevel(EApiId_t Id, uint32_t Bitmask, uint32_t Level)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiGPIOSetLevel EApiGPIOSetLevel;
		EApiGPIOSetLevel = (fnEApiGPIOSetLevel)dlsym(hDLL, "EApiGPIOSetLevel");
		if (EApiGPIOSetLevel != NULL)
		{
			status = EApiGPIOSetLevel(Id, Bitmask, Level);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

void GPIOGetDirection(EApiId_t Id, uint32_t Bitmask, uint32_t *pDirection)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiGPIOGetDirection EApiGPIOGetDirection;
		EApiGPIOGetDirection = (fnEApiGPIOGetDirection)dlsym(hDLL, "EApiGPIOGetDirection");
		if (EApiGPIOGetDirection != NULL)
		{
			status = EApiGPIOGetDirection(Id, Bitmask, pDirection);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

void GPIOSetDirection(EApiId_t Id, uint32_t Bitmask, uint32_t Direction)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiGPIOSetDirection EApiGPIOSetDirection;
		EApiGPIOSetDirection = (fnEApiGPIOSetDirection)dlsym(hDLL, "EApiGPIOSetDirection");
		if (EApiGPIOSetDirection != NULL)
		{
			status = EApiGPIOSetDirection(Id, Bitmask, Direction);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

void GPIOGetDirectionCaps(EApiId_t Id, uint32_t *pInputs, uint32_t *pOutputs)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiGPIOGetDirectionCaps EApiGPIOGetDirectionCaps;
		EApiGPIOGetDirectionCaps = (fnEApiGPIOGetDirectionCaps)dlsym(hDLL, "EApiGPIOGetDirectionCaps");
		if (EApiGPIOGetDirectionCaps != NULL)
		{
			status = EApiGPIOGetDirectionCaps(Id, pInputs, pOutputs);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

void GPIOGetCount(uint32_t *pCount)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiGPIOGetCount EApiGPIOGetCount;
		EApiGPIOGetCount = (fnEApiGPIOGetCount)dlsym(hDLL, "EApiGPIOGetCount");
		if (EApiGPIOGetCount != NULL)
		{
			status = EApiGPIOGetCount(pCount);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

void LibUnInitialize(void)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiLibUnInitialize EApiLibUnInitialize;

		EApiLibUnInitialize = (fnEApiLibUnInitialize)dlsym(hDLL, "EApiLibUnInitialize");
		if (EApiLibUnInitialize != NULL)
		{
			status = EApiLibUnInitialize();
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
	}
}

bool LibInitialize(void)
{
	bool retval = true;
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

	if (hDLL)
	{
		fnEApiLibInitialize EApiLibInitialize;

		EApiLibInitialize = (fnEApiLibInitialize)dlsym(hDLL, "EApiLibInitialize");
		if (EApiLibInitialize != NULL)
		{
			status = EApiLibInitialize();
			print("fffffff:%d\n", status);
		}
		else
		{
			printf("Dlsym Error : %s \n", __func__);
			retval = false;
		}
	}
	else
	{
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
		retval = false;
	}

	if (status != EAPI_STATUS_SUCCESS)
	{
		char buffer[0x80] = {0};
		printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
		retval = false;
	}
	return retval;
}
void Usage(const char *name, int maxpincount)
{
	printf("Usage: %s [Choose] [Other arg...]\n", name);
	printf("  - GetCaps: %s [Choose](1) [Id](0~%d) \n", name, maxpincount - 1);
	printf("  - GetDirection: %s [Choose](2) [Id](0~%d) \n", name, maxpincount - 1);
	printf("  - SetDirection: %s [Choose](3) [Id](0~%d) [Direction](1:input, 0:output) \n", name, maxpincount - 1);
	printf("  - GetLevel: %s [Choose](4) [Id](0~%d) \n", name, maxpincount - 1);
	printf("  - SetLevel: %s [Choose](5) [Id](0~%d) [Level](1:high, 0:low) \n", name, maxpincount - 1);
	printf("  - GetCount: %s [Choose](6) \n", name);
}

int MyAtoU(const char *str)
{
	if (str == NULL)
	{
		printf("Error: NULL parameter. \n");
		return 999;
	}

	int ret = atoi(str);
	if (str[0] != '0' && ret == 0)
		ret = -1;
	return ret;
	//        return (uint32_t)(str[0] - 48);
}

int CheckExit(const char *pFile)
{
	if (pFile == NULL)
	{
		return -1;
	}

	int LockFd = open(pFile, O_RDWR | O_CREAT);
	if (LockFd == -1)
	{
		return -2;
	}

	int iret = flock(LockFd, LOCK_EX | LOCK_NB);
	if (iret == -1)
	{
		return -3;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	char choose = '0';
	uint32_t Id = 0, Inputs = 0, Outputs = 0;
	uint32_t Bitmask = 1, Direction = 0, Level = 0;
	int MaxCount = 16;

	switch (CheckExit(DEFAULT_LOCKFILE))
	{
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

	hDLL = OpenEAPI();
	// Intialization is essential.
	if (false == LibInitialize())
	{
		printf("Unable to Intialize.\nPlease check device compatibility.\n");
		return 0;
	}
	else
	{
		Outputs = 0;
		GPIOGetCount(&Outputs);
		if (0 != Outputs)
			MaxCount = Outputs;
	}

	if (argc < 3 && 6 != MyAtoU(argv[1]))
	{
		Usage(argv[0], MaxCount);
		return 0;
	}
	choose = argv[1][0];

	switch (choose)
	{
	case '1':
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0)
		{
			Usage(argv[0], MaxCount);
			return 0;
		}
		else
		{
			Id = MyAtoU(argv[2]);
		}

		GPIOGetDirectionCaps(Id, &Inputs, &Outputs);
		printf("GPIOGetDirectionCaps Id: %u \nInputs: %u \nOutputs: %u \n",
			   Id, Inputs, Outputs);
		break;
	case '2':
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0)
		{
			Usage(argv[0], MaxCount);
			return 0;
		}
		else
		{
			Id = MyAtoU(argv[2]);
		}

		GPIOGetDirection(Id, Bitmask, &Direction);
		printf("GPIOGetDirection Id: %u \nDirection: %u \n", Id, Direction);
		break;
	case '3':
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0 || MyAtoU(argv[3]) >= 2)
		{
			Usage(argv[0], MaxCount);
			return 0;
		}
		else
		{
			Id = MyAtoU(argv[2]);
			Direction = MyAtoU(argv[3]);
		}

		GPIOSetDirection(Id, Bitmask, Direction);
		printf("GPIOSetDirection Id: %u \nDirection: %u \n", Id, Direction);
		break;
	case '4':
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0)
		{
			Usage(argv[0], MaxCount);
			return 0;
		}
		else
		{
			Id = MyAtoU(argv[2]);
		}

		GPIOGetLevel(Id, Bitmask, &Level);
		printf("GPIOGetLevel Id: %u \nlevel: %u \n", Id, Level);
		break;
	case '5':
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0 || MyAtoU(argv[3]) >= 2)
		{
			Usage(argv[0], MaxCount);
			return 0;
		}
		else
		{
			Id = MyAtoU(argv[2]);
			Level = MyAtoU(argv[3]);
		}
		GPIOSetLevel(Id, Bitmask, Level);
		printf("GPIOSetLevel Id: %u \nLevel: %u \n", Id, Level);
		break;
	case '6':
		GPIOGetCount(&Outputs);
		printf("GPIOGetCount: %u\n", Outputs);
		break;
	default:
		Usage(argv[0], MaxCount);
		break;
	}

	LibUnInitialize();
	CloseEAPI(hDLL);
	return 0;
}

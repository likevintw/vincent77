/* ***************************************************************************
 *
 * testdl_hwmon.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atHWMON.h"
#include "atEAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/file.h>
#include <syslog.h>
#include "eapi_sharefunc.h"

#define DEFAULT_LOCKFILE                "/var/run/test_hwmon.pid"
#define CMD_RETURN_BUF_SIZE             4096

typedef EApiStatus_t (*fnEApiBoardGetStringA) (
		__IN EApiId_t Id,
		__OUT char *pValue,
		__INOUT uint32_t *pBufLen
		);


void BoardGetString(EApiId_t Id, char *result){
	EApiStatus_t status = EAPI_STATUS_SUCCESS ;
	char *pBuffer = NULL;
	uint32_t bufLen = 0;
	if (hDLL) {
		fnEApiBoardGetStringA EApiBoardGetStringA = NULL;
		EApiBoardGetStringA = (fnEApiBoardGetStringA)dlsym(hDLL,"EApiBoardGetStringA");
		if (EApiBoardGetStringA != NULL) {
			pBuffer = (char *)malloc(CMD_RETURN_BUF_SIZE);
			if (pBuffer == NULL) {
				return;
			}
			bufLen = CMD_RETURN_BUF_SIZE;
			memset(pBuffer, 0, bufLen);
			status = EApiBoardGetStringA(Id, pBuffer, &bufLen);
			strcpy (result, pBuffer);
			free(pBuffer);
		} else {
			printf("Dlsym Error : %s \n", __func__);
		}
	} else {
		printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
	}

	if (status != EAPI_STATUS_SUCCESS) {
            char errorstr[0x80] = {0};
            printf("Unsuccess Status: %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, errorstr));
	}

}



void BoardGetValue(EApiId_t Id, uint32_t *pValue)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiBoardGetValue EApiBoardGetValue = NULL;
                EApiBoardGetValue = (fnEApiBoardGetValue)dlsym(hDLL,"EApiBoardGetValue");
                if (EApiBoardGetValue != NULL) {
                        status = EApiBoardGetValue(Id, pValue);
                } else {
                        printf("Dlsym Error : %s \n", __func__);
                }
        } else {
                printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
        }

        if (status != EAPI_STATUS_SUCCESS) {
            char errorstr[0x80] = {0};
            printf("Unsuccess Status: %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, errorstr));
        }
}


int main(int argc, char* argv[])
{
	uint32_t Id = 0, Value = 0;
	char cvalue[10];
	double dvalue = 0;
	memset(cvalue, 0, sizeof(cvalue));

	char result[CMD_RETURN_BUF_SIZE] = {0};


printf("----------------------------------------------------------\n");
printf("BoardGetString\n");
hDLL = OpenEAPILIB();
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_MANUFACTURER_STR;
        BoardGetString(Id, result);
        printf("EAPI_BOARD_MANUFACTURER_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_NAME_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_NAME_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_REVISION_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_REVISION_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_SERIAL_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_SERIAL_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
	Id = EAPI_ID_BOARD_BIOS_REVISION_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_BIOS_REVISION_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_HW_REVISION_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_HW_REVISION_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_PLATFORM_TYPE_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_PLATFORM_TYPE_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_EC_REVISION_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_EC_REVISION_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_OS_REVISION_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_OS_REVISION_STR\n Id: 0x%X  Value: %s \n", Id, result);
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_BOARD_CPU_MODEL_NAME_STR;
        BoardGetString(Id, result);
        printf("EAPI_ID_BOARD_CPU_MODEL_NAME_STR\n Id: 0x%X  Value: %s \n", Id, result);                        
printf("\n");
printf("----------------------------------------------------------\n");
printf("BoardGetValue\n");
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_TEMP_CPU;
        BoardGetValue(Id, &Value);
        Value = ((uint32_t)(EAPI_DECODE_CELCIUS(Value)));
        printf("EAPI_ID_HWMON_TEMP_CPU\n Id: 0x%X  Value: %u \n", Id, Value);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_TEMP_SYSTEM;
        BoardGetValue(Id, &Value);
        Value = ((uint32_t)(EAPI_DECODE_CELCIUS(Value)));
        printf("EAPI_ID_HWMON_TEMP_SYSTEM\n Id: 0x%X  Value: %u \n", Id, Value);
        Value = 0;
/* 
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_TEMP_OEM0;
        BoardGetValue(Id, &Value);
        printf("EAPI_ID_HWMON_TEMP_OEM0\n Id: 0x%X  Value: %u \n", Id, Value);
        Value = 0;
*/        
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_VCORE;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_VCORE\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_3V3;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_3V3\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_5V;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_5V\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_12V;
        BoardGetValue(Id, &Value);
	dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_12V\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_VBAT;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_VBAT\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_DC;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_DC\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_3VSB;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_3VSB\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_5VSB;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_5VSB\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_VOLTAGE_VIN;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_VOLTAGE_VIN\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_HWMON_CURRENT_OEM1;
        BoardGetValue(Id, &Value);
        dvalue = Value;
        dvalue = dvalue/1000;
        printf("EAPI_ID_HWMON_CURRENT_OEM1\n Id: 0x%X  Value: %f \n", Id, dvalue);
        Value = 0;
printf("----------------------------------------------------------\n");
        Id = EAPI_ID_GPIO_POE_PINNUM;
        BoardGetValue(Id, &Value);
        printf("EAPI_ID_GPIO_POE_PINNUM\n Id: 0x%X  Value: %u \n", Id, Value);
        Value = 0;
printf("----------------------------------------------------------\n");
	Id = EAPI_ID_HWMON_FAN_CPU;
        BoardGetValue(Id, &Value);
        printf("EAPI_ID_HWMON_FAN_CPU\n Id: 0x%X  Value: %u \n", Id, Value);
        Value = 0;
printf("----------------------------------------------------------\n");
	Id = EAPI_ID_HWMON_FAN_SYSTEM;
        BoardGetValue(Id, &Value);
        printf("EAPI_ID_HWMON_FAN_SYSTEM\n Id: 0x%X  Value: %u \n", Id, Value);
        Value = 0;
printf("----------------------------------------------------------\n");
        CloseEAPILIB(hDLL);
        return 0;

}

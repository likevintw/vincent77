/* ***************************************************************************
 *
 * uno-mxm-info.c : Defines the entry point for the console application.
 *
 * ***************************************************************************/

#include "atSMBUS.h"
#include "atEAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/file.h>
#include <syslog.h>
#include "eapi_sharefunc.h"


void *hDLL;

void* OpenEAPI()
{
	return dlopen("libATSMBUS.so", RTLD_LAZY);
}

void CloseEAPI(void *hDLL)
{
        if(hDLL) {
                dlclose(hDLL);
        }
}

EApiStatus_t SMBReadByte(EApiId_t Id, uint8_t Addr, uint8_t Cmd, uint8_t* pBuffer)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiSMBReadByte EApiSMBReadByte;
                EApiSMBReadByte = (fnEApiSMBReadByte)dlsym(hDLL, "EApiSMBReadByte");
                if (EApiSMBReadByte != NULL) {
                        status = EApiSMBReadByte(Id, Addr, Cmd, pBuffer);
                } else {
			status = EAPI_STATUS_ERROR ;
                        printf("Dlsym Error : %s \n", __func__);
                }
        } else {
		status = EAPI_STATUS_ERROR ;
                printf("Dlopen Error : %s:%d ! \n", __func__, __LINE__);
        }

        if (status != EAPI_STATUS_SUCCESS) {
                char buffer[0x80] = {0};
                printf("uno-mxm-info error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}


int main(void)
{
    EApiStatus_t result = EAPI_STATUS_SUCCESS, result_2nd;

    uint8_t slave_add = 0x4f, data_add, data_add_2nd;
    uint8_t data;
    uint32_t calculate_data;

    
    hDLL = OpenEAPI();

    
    /* GPU temp */
    data_add = 0x00;
    result = SMBReadByte(0, slave_add, data_add, &data);
    if(EAPI_STATUS_SUCCESS == result){
        printf("[0x%02X] --- GPU Temp: %03u°C\n", data_add, data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }

    /*Fan duty*/
    data_add = 0x20;
    result = SMBReadByte(0, slave_add, data_add, &data);
    if(EAPI_STATUS_SUCCESS == result){
        printf("[0x%02X] --- Fan Duty: %03u%%\n", data_add, data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }
    /*FAN Tachometer*/
    data_add = 0x2a;
    result = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data = data << 8;

    data_add = 0x2b;
    result_2nd = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data += data;
    
    if(EAPI_STATUS_SUCCESS == result && EAPI_STATUS_SUCCESS == result_2nd){
        printf("[0x%02X/0x%02X] --- FAN TACH: %u RPM\n", 0x2a, 0x2b, calculate_data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }

    /* GPU Info 2*/
    printf("GPU Info 2 [SMbus]\n");
    
    
    data_add = 0xfd;
    data_add_2nd = 0xfe;
    result = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data = data << 8;
    result_2nd = SMBReadByte(0, slave_add, data_add_2nd, &data);
    calculate_data += data;
    if(EAPI_STATUS_SUCCESS == result && EAPI_STATUS_SUCCESS == result_2nd){
        printf("[0x%02X/0x%02X] --- VendorID: 0x%04X\n", data_add, data_add_2nd, calculate_data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }


    data_add = 0x63;
    data_add_2nd = 0x62;
    result = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data = data << 8;
    result_2nd = SMBReadByte(0, slave_add, data_add_2nd, &data);
    calculate_data += data;
    if(EAPI_STATUS_SUCCESS == result && EAPI_STATUS_SUCCESS == result_2nd){
        printf("[0x%02X/0x%02X] --- VendorID: 0x%04X\n", data_add, data_add_2nd, calculate_data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }


    data_add = 0x65;
    data_add_2nd = 0x64;
    result = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data = data << 8;
    result_2nd = SMBReadByte(0, slave_add, data_add_2nd, &data);
    calculate_data += data;
    if(EAPI_STATUS_SUCCESS == result && EAPI_STATUS_SUCCESS == result_2nd){
        printf("[0x%02X/0x%02X] --- DeviceID: 0x%04X\n", data_add, data_add_2nd, calculate_data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }


    data_add = 0x67;
    data_add_2nd = 0x66;
    result = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data = data << 8;
    result_2nd = SMBReadByte(0, slave_add, data_add_2nd, &data);
    calculate_data += data;
    if(EAPI_STATUS_SUCCESS == result && EAPI_STATUS_SUCCESS == result_2nd){
        printf("[0x%02X/0x%02X]--SubVenderID: 0x%04X\n", data_add, data_add_2nd, calculate_data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }


    data_add = 0x69;
    data_add_2nd = 0x68;
    result = SMBReadByte(0, slave_add, data_add, &data);
    calculate_data = data << 8;
    result_2nd = SMBReadByte(0, slave_add, data_add_2nd, &data);
    calculate_data += data;
    if(EAPI_STATUS_SUCCESS == result && EAPI_STATUS_SUCCESS == result_2nd){
        printf("[0x%02X/0x%02X]--SubDeviceID: 0x%04X\n", data_add, data_add_2nd, calculate_data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }


    data_add = 0xff;
    result = SMBReadByte(0, slave_add, data_add, &data);
    if(EAPI_STATUS_SUCCESS == result){
        printf("[0x%02X] --- GPU  Revision: 0x%02X\n", data_add, data);
    }
    else{
        printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
        goto EXIT;
    }

    /* FanCurve_Table */
    printf("FanCurve_Table\n"); 


    data_add = 0x30;
    data_add_2nd = 0x40;
    for(uint8_t a = 0; a< 8; a++)
    {
        result = SMBReadByte(0, slave_add, data_add+a, &data);
        if(EAPI_STATUS_SUCCESS == result){
            if(0xff != data){
            printf("[0x%02X] --- FanCurve [Temp]: %03u°C\n", data_add+a, data);
            }
            else{
                printf("[0x%02X] --- No Data\n", data_add+a);
            }
        }

        result = SMBReadByte(0, slave_add, data_add_2nd + a, &data);
        if(EAPI_STATUS_SUCCESS == result){
            if(0xff != data){
            printf("[0x%02X] --- FanCurve [Duty]: %03u%%\n", data_add_2nd+a, data);
            }
            else{
                printf("[0x%02X] --- No Data\n", data_add_2nd+a);
            }
        }
        else{
            printf("[uno-mxm-info]: EApiSMBReadByte failed with slave add: 0x%02X data add: 0x%02X\n", slave_add, data_add);
            goto EXIT;
        }
    }

EXIT:
    CloseEAPI(hDLL);
    return 0;

}

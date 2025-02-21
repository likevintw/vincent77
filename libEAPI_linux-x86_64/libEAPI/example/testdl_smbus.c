/* ***************************************************************************
 *
 * testdl_smbus.c : Defines the entry point for the console application.
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
                printf("testdl_smbus error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}


/* transfer string to number. 16 base.
 * ret -1 for unsuccess
 */
int gethexvalue(const char* input)
{
    char *retstr = NULL;
    long int value;
    value = strtol(input, &retstr, 16);
    if(*retstr || !*input){
        return -1;
    }
    else{
        return value;
    }

}

void Usage(FILE *stream)
{
    fprintf(stream, "\n\n==== Input format: ");
    fprintf(stream, "testdl_smbus [R/W] [BUSID] [SLAVE-ADDRESS] [DATA-ADDRESS]\n");
    fprintf(stream, "             [R/W]: read(r) or write(w) function\n");
    fprintf(stream, "           [BUSID]: I2C bus ID\n"); 
    fprintf(stream, "   [SLAVE-ADDRESS]: slave address\n");
    fprintf(stream, "    [DATA-ADDRESS]: data address\n");
}



#define TESTDL_SMBUS_INPUTVAR_COUNT 5

/* input of this example code
 * <r/w> <bus-id> <slave-address> <data-address>
 */
int main(int argc, char* argv[])
{
    EApiStatus_t result = EAPI_STATUS_SUCCESS;

    uint8_t slave_add, data_add;
    uint8_t data;
    int busid;

    if(TESTDL_SMBUS_INPUTVAR_COUNT == argc){
        slave_add = gethexvalue(argv[3]);
        data_add = gethexvalue(argv[4]);
    }
    else{
        fprintf(stderr, "Invalid input format\n");
        Usage(stderr);
    }

    busid = atoi(argv[2]);
    if(0 > busid ){
        fprintf(stderr, "Only accepts busid >=0 (Your input:%s)\n", argv[2]);
        Usage(stderr);
        return -1;
    }

    if(-1 == slave_add || -1 == data_add){
        fprintf(stderr, "Invalid slave address or data address\n");
        Usage(stderr);
        return -1;
    }

    if(!(1 == strlen(argv[1]) && (argv[1][0] == 'r'))){
        fprintf(stderr, "Your 2nd variable(%s) is not supported.\n", argv[1]);
        Usage(stderr);
        return -1;
    }

    hDLL = OpenEAPI();
    result = SMBReadByte((EApiId_t)atoi(argv[2]), slave_add, data_add, &data);
    if(EAPI_STATUS_SUCCESS == result){
        printf("result: 0x%x\n", data);
    }

    CloseEAPI(hDLL);

    return 0;
}

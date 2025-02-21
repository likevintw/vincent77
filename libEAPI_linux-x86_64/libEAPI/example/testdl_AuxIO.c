#include "atAuxIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/file.h>
#include <syslog.h>
#include "eapi_sharefunc.h"


#include <cstdlib>

void *hDLL;

typedef EApiStatus_t (*fnEApiGetGPIOMask)(uint32_t *pGPIOMask);
typedef EApiStatus_t (*fnEApiGPIOGetDirectionCaps)(EApiId_t Id, uint32_t  *pInputs, uint32_t *pOutputs);
typedef EApiStatus_t (*fnEApiGPIOGetLevel)(EApiId_t Id, uint32_t  Bitmask, uint32_t *pLevel);
typedef EApiStatus_t (*fnEApiGPIOSetLevel)(EApiId_t Id, uint32_t  Bitmask, uint32_t pLevel);
typedef EApiStatus_t (*fnEApiGPIOGetDirection)(EApiId_t Id, uint32_t  Bitmask, uint32_t *pDirection);
typedef EApiStatus_t (*fnEApiGPIOSetDirection)(EApiId_t Id, uint32_t  Bitmask, uint32_t Direction);
typedef EApiStatus_t (*fnEApiGetAIMask)(uint32_t *pAIMask);
typedef EApiStatus_t (*fnEApiGetAOMask)(uint32_t *pAOMask);
typedef EApiStatus_t (*fnEApiAIGetValue)(EApiId_t Id, uint32_t *pValue);
typedef EApiStatus_t (*fnEApiAOSetValue)(EApiId_t Id, uint32_t Value);
typedef EApiStatus_t (*fnEApiAOGetValue)(EApiId_t Id, uint32_t *pValue);
typedef EApiStatus_t (*fnEApiSetDefault)(EApiId_t Id);
typedef EApiStatus_t (*fnEApiAIOSetScale)(uint32_t Direction , char *pScale) ;
typedef EApiStatus_t (*fnEApiAIOGetScale)(uint32_t Direction , char *pScale);
typedef EApiStatus_t (*fnEApiAIOGetAvailableScale)(uint32_t Direction ,char *pScale); 
typedef EApiStatus_t (*fnEApiGPIOGetCount)(uint32_t *pCount);
typedef EApiStatus_t (*fnEApiLibInitialize) (void);
typedef EApiStatus_t (*fnEApiLibUnInitialize)  (void);


//global string to keep GPIO/ADC/DAC mask
//e.g. GPIO mask 0x05 -> channel 0 and 2 are GPIO mode
//String content: 0,2
char strGPIOMask[0x30] = {0};
char strADCMask[0x30] = {0};
char strDACMask[0x30] = {0};


void *OpenEAPI()
{
	return dlopen("libATAuxIO.so", RTLD_LAZY);

}

void CloseEAPI(void *hDLL)
{
        if(hDLL) {
                dlclose(hDLL);
        }
}

EApiStatus_t GetGPIOCount(uint32_t *pCount)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGPIOGetCount EApiGPIOGetCount;
                EApiGPIOGetCount = (fnEApiGPIOGetCount)dlsym(hDLL, "EApiGPIOGetCount");
                if (EApiGPIOGetCount != NULL) {
                        status = EApiGPIOGetCount(pCount);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}


EApiStatus_t GetGPIOLevel(EApiId_t Id, uint32_t Bitmask, uint32_t *pLevel)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGPIOGetLevel EApiGPIOGetLevel;
                EApiGPIOGetLevel = (fnEApiGPIOGetLevel)dlsym(hDLL, "EApiGPIOGetLevel");
                if (EApiGPIOGetLevel != NULL) {
                        status = EApiGPIOGetLevel(Id, Bitmask, pLevel);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}

EApiStatus_t SetGPIOLevel(EApiId_t Id, uint32_t Bitmask, uint32_t Level)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGPIOSetLevel EApiGPIOSetLevel;
                EApiGPIOSetLevel = (fnEApiGPIOSetLevel)dlsym(hDLL, "EApiGPIOSetLevel");
                if (EApiGPIOSetLevel != NULL) {
                        status = EApiGPIOSetLevel(Id, Bitmask, Level);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }
	return status ;
}

EApiStatus_t  GetGPIODirection(EApiId_t Id, uint32_t Bitmask, uint32_t *pDirection)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGPIOGetDirection EApiGPIOGetDirection;
                EApiGPIOGetDirection = (fnEApiGPIOGetDirection)dlsym(hDLL, "EApiGPIOGetDirection");
                if (EApiGPIOGetDirection != NULL) {
                        status = EApiGPIOGetDirection(Id, Bitmask, pDirection);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}

EApiStatus_t  SetGPIODirection(EApiId_t Id, uint32_t Bitmask, uint32_t Direction)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGPIOSetDirection EApiGPIOSetDirection;
                EApiGPIOSetDirection = (fnEApiGPIOSetDirection)dlsym(hDLL, "EApiGPIOSetDirection");
                if (EApiGPIOSetDirection != NULL) {
                        status = EApiGPIOSetDirection(Id, Bitmask, Direction);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}
EApiStatus_t GetGPIODirCaps(EApiId_t Id, uint32_t *pInputs, uint32_t *pOutputs)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGPIOGetDirectionCaps EApiGPIOGetDirectionCaps;
                EApiGPIOGetDirectionCaps = (fnEApiGPIOGetDirectionCaps)dlsym(hDLL, "EApiGPIOGetDirectionCaps");
                if (EApiGPIOGetDirectionCaps != NULL) {
                        status = EApiGPIOGetDirectionCaps(Id, pInputs, pOutputs);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;
}

EApiStatus_t GetGPIOMask(uint32_t *pGPIOMask)
{
	EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGetGPIOMask EApiGetGPIOMask;
                EApiGetGPIOMask = (fnEApiGetGPIOMask)dlsym(hDLL, "EApiGetGPIOMask");
                if (EApiGetGPIOMask != NULL) {
                        status = EApiGetGPIOMask(pGPIOMask);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }
	return status ;
}

EApiStatus_t GetAIMask(uint32_t *pAIMask, bool silenceforunsupport)
{
	 EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGetAIMask EApiGetAIMask;
                EApiGetAIMask = (fnEApiGetAIMask)dlsym(hDLL, "EApiGetAIMask");
                if (EApiGetAIMask != NULL) {
                        status = EApiGetAIMask(pAIMask);
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
                if(true != silenceforunsupport) printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }
	return status ;

}

EApiStatus_t GetAOMask(uint32_t *pAOMask, bool silenceforunsupport)
{
	 EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiGetAOMask EApiGetAOMask;
                EApiGetAOMask = (fnEApiGetAOMask)dlsym(hDLL, "EApiGetAOMask");
                if (EApiGetAOMask != NULL) {
                        status = EApiGetAOMask(pAOMask);
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
                if(true != silenceforunsupport) printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;

}

EApiStatus_t   GetAIValue(uint32_t iPin, uint32_t *pvalue)
{
	 EApiStatus_t status = EAPI_STATUS_SUCCESS;
	
        if (hDLL) {
                fnEApiAIGetValue EApiAIGetValue;
                EApiAIGetValue = (fnEApiAIGetValue)dlsym(hDLL, "EApiAIGetValue");
                if (EApiAIGetValue != NULL) {			
                        status = EApiAIGetValue( iPin,pvalue);			
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }
	
	return status ;
}

EApiStatus_t GetAOValue(uint32_t iPin, uint32_t *pvalue)
{
	 EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiAOGetValue EApiAOGetValue;
                EApiAOGetValue = (fnEApiAOGetValue)dlsym(hDLL, "EApiAOGetValue");
                if (EApiAOGetValue != NULL) {
                        status = EApiAOGetValue(iPin,pvalue);
		
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }
	return status ;
}


EApiStatus_t SetAOValue(uint32_t iPin, double value)
{
	 EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiAOSetValue EApiAOSetValue;
                EApiAOSetValue = (fnEApiAOSetValue)dlsym(hDLL, "EApiAOSetValue");
                if (EApiAOSetValue != NULL) {			
                        status = EApiAOSetValue(iPin,value);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }
	return status ;

}

EApiStatus_t  PinReset(uint32_t iPin)
{
 	EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiSetDefault EApiSetDefault;
                EApiSetDefault = (fnEApiSetDefault)dlsym(hDLL, "EApiSetDefault");
                if (EApiSetDefault != NULL) {
                        status = EApiSetDefault(iPin);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;

}

EApiStatus_t SetAIOScale(uint32_t Direction ,char *pScale)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiAIOSetScale  EApiAIOSetScale;
                EApiAIOSetScale = (fnEApiAIOSetScale)dlsym(hDLL, "EApiAIOSetScale");
                if ( EApiAIOSetScale != NULL) {
                        status =  EApiAIOSetScale(Direction , pScale);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

	return status ;

}


EApiStatus_t GetAIOScale(uint32_t Direction ,char *pScale)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiAIOGetScale  EApiAIOGetScale;
                EApiAIOGetScale = (fnEApiAIOGetScale)dlsym(hDLL, "EApiAIOGetScale");
                if ( EApiAIOGetScale != NULL) {
                        status =  EApiAIOGetScale(Direction ,pScale);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

        return status ;

}

EApiStatus_t GetAIOAvailScale(uint32_t Direction ,char *pScale)
{
        EApiStatus_t status = EAPI_STATUS_SUCCESS;

        if (hDLL) {
                fnEApiAIOGetAvailableScale EApiAIOGetAvailableScale;
                EApiAIOGetAvailableScale = (fnEApiAIOGetAvailableScale)dlsym(hDLL, "EApiAIOGetAvailableScale");
                if ( EApiAIOGetAvailableScale != NULL) {
                        status =  EApiAIOGetAvailableScale(Direction ,pScale);
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
                printf("Error : %s:%d (0x00%X) %s\n", __func__, __LINE__, status, EApiStatus_StringTranslator(status, buffer));
        }

        return status ;

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
                char buffer[0x80] = {0};
                printf("Error[0x00%X] : %s\n", status, EApiStatus_StringTranslator(status, buffer));
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

//This function transfers mask to string and keep them in char array above.
void GetPinStringfromMask(void)
{
    
    char* pstr = NULL;
    uint32_t gpiocount = 0;
    
    GetGPIOCount(&gpiocount);
    if(0 == gpiocount) gpiocount = 16; //max count

    uint32_t targetbit = 1; 
    uint32_t mask = 0;
    int nprinted = 0;


    mask = 0;
    GetGPIOMask(&mask);
    pstr = strGPIOMask;

    if( 0xFF == mask || 0xFFFF == mask ){
        sprintf(pstr, "0~%u", gpiocount);
    }
    else{
        for (uint32_t a = 0; a < gpiocount; a++){
            if((targetbit << a) & mask){
                nprinted = sprintf(pstr, "%d,", a);
                pstr += nprinted;
            }
        }
        *(pstr-1) = 0;//remove the last comma in generated string
    }


    mask = 0;
    pstr = strADCMask;
    GetAIMask(&mask, true);
    for (uint32_t a = 0; a < gpiocount; a++){
        if((targetbit << a) & mask){
            sprintf(pstr, "%d,", a);
            pstr +=2;
        }
    }
    *(pstr-1) = 0;

    mask = 0;
    pstr = strDACMask;
    GetAOMask(&mask, true);
    for (uint32_t a = 0; a < gpiocount; a++){
        if((targetbit << a) & mask){
            sprintf(pstr, "%d,", a);
            pstr +=2;
        }
    }
    *(pstr-1) = 0;
}

void Usage(const char *name)
{
        printf("Usage: %s [Choose] [Other arg...]\n", name);
        printf("  - GetGPIO_Caps: %s [Choose](1) [Id](%s) \n", name, strGPIOMask);
        printf("  - GetGPIO_Direction: %s [Choose](2) [Id](%s) \n", name, strGPIOMask);
        printf("  - SetGPIO_Direction: %s [Choose](3) [Id](%s) [Direction](0:output, 1:input) \n", name, strGPIOMask);
        printf("  - GetGPIO_Level: %s [Choose](4) [Id](%s) \n", name, strGPIOMask);
        printf("  - SetGPIO_Level: %s [Choose](5) [Id](%s) [Level](1:high, 0:low) \n", name, strGPIOMask);
	printf("  - GetGPIO_Mask %s [Choose](6) \n" ,name);
	printf("  - GetADC_Mask %s [Choose](7) \n" ,name);
	printf("  - GetDAC_Mask %s [Choose](8) \n" ,name);
	printf("  - GetADC_Value %s [Choose](9) [Id](%s)\n" ,name, strADCMask);
	printf("  - GetDAC_Value %s [Choose](A) [Id](%s) \n" ,name, strDACMask);
        printf("  - SetDAC_Value %s [Choose](B) [Id](%s) [Value](5:Max , 0:min) or (2.5:Max , 0:min)\n" ,name, strDACMask);
        printf("  - Pin_Reset %s [Choose](C) --- not supported -- \n",name);
	printf("  - SetADC_DAC_Scale %s [Choose](D) [scale] [Direction](0:output, 1:input) \n" ,name);
	printf("  - GetADC_DAC_Scale %s [Choose](E) [Direction](0:output, 1:input) \n" ,name);
	printf("  - GetADC_DAC_Avaiable Scale %s [Choose](F) [Direction](0:output, 1:input) \n" ,name);
}

int MyAtoU(const char *str)
{
        if (str == NULL) {
                printf("Error: NULL parameter. \n");
                return 999;
        }

        int ret = atoi(str);
        if(str[0] != '0' && ret == 0) ret = -1;
        return ret;
//        return (uint32_t)(str[0] - 48);
}

int main(int argc, char* argv[])
{
	char choose = '0';
	uint32_t Id = 0, Inputs = 0, Outputs = 0  ;
        uint32_t Bitmask = 1, Direction = 0, Level = 0 ,Value =0 ;
	double value = 0 ,Scale = 0 ,d_Value =0; 
	char scale_str[64];
        int MaxCount = 16;

        hDLL = OpenEAPI();

        
        if(hDLL){
            Outputs = 0;
            LibInitialize();
            GetPinStringfromMask();
            GetGPIOCount(&Outputs);
            if(0 != Outputs) MaxCount = Outputs;

        }
        else{
                printf("Failed to load library. Please check libATAuxIO.so is accessible.\n");
                return -1;
        }

	if (argc < 2) {
                Usage(argv[0]);
                return 0;
        }
        else choose = argv[1][0];	

 switch (choose)
        {

	 case '1':  //GetGPIO_Caps:
                if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
                }
		if (EAPI_STATUS_SUCCESS ==  GetGPIODirCaps(Id, &Inputs, &Outputs))
                	printf("GPIOGetDirectionCaps Id: %u \nInputs: %u \nOutputs: %u \n",Id, Inputs, Outputs);
		else
		 	return 0;
                break;
        case '2':  //GetGPIO_Direction
                if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
	        }
		//if ( EAPI_STATUS_SUCCESS == GetGPIOMask(&Bitmask) && EAPI_STATUS_SUCCESS == GetGPIODirection(Id, Bitmask, &Direction))
		 if ( EAPI_STATUS_SUCCESS == GetGPIODirection(Id, 255, &Direction))
                	printf("GPIOGetDirection Id: %u \nDirection: %u \n", Id, Direction);
                else
                    return 0;
                break;
        case '3':    //
                if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0 || MyAtoU(argv[3]) >= 2) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
                        Direction = MyAtoU(argv[3]);
                }
		//if ( EAPI_STATUS_SUCCESS == GetGPIOMask(&Bitmask) && EAPI_STATUS_SUCCESS == SetGPIODirection(Id, Bitmask, Direction))
		if ( EAPI_STATUS_SUCCESS == SetGPIODirection(Id, 255, Direction))
                         printf("GPIOSetDirection Id: %u \nDirection: %u \n", Id, Direction);
                else
                    return 0;

                break;
        case '4':
                if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
                }
		//if ( EAPI_STATUS_SUCCESS == GetGPIOMask(&Bitmask) && EAPI_STATUS_SUCCESS == GetGPIOLevel(Id, Bitmask, &Level))
		if (EAPI_STATUS_SUCCESS == GetGPIOLevel(Id, 255, &Level))
	                printf("GPIOGetLevel Id: %u \nlevel: %u \n", Id, Level);
		else
                    return 0;
                break;
        case '5':
                if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0 || MyAtoU(argv[3]) >= 2) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
                        Level = MyAtoU(argv[3]);
                }
		//if ( EAPI_STATUS_SUCCESS ==  GetGPIOMask(&Bitmask) && EAPI_STATUS_SUCCESS ==  SetGPIOLevel(Id,Bitmask, Level))
		if ( EAPI_STATUS_SUCCESS ==  SetGPIOLevel(Id,255, Level))
	                printf("GPIOSetLevel Id: %u \nLevel: %u \n", Id, Level);
		else
                    return 0;
                break;
	case '6':
		if ( EAPI_STATUS_SUCCESS == GetGPIOMask(&Bitmask))
			printf("GetGPIOMask  bitmask: 0x%x \n\n", Bitmask);
		else
                    return 0;
                break;	
	case '7':
		if ( EAPI_STATUS_SUCCESS == GetAIMask(&Bitmask, false))
			printf("GetAIMask  bitmask: 0x%x \n\n", Bitmask);
		else
                    return 0;
		break;
	case '8':
		if ( EAPI_STATUS_SUCCESS == GetAOMask(&Bitmask, false))
	                printf("GetAOMask  bitmask: 0x%x \n\n", Bitmask);
 		else
                    return 0;
                break;                
	case '9':
		 if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0 ) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
                       
                }		 
				
		if ( EAPI_STATUS_SUCCESS == GetAIOScale(1 ,scale_str) && EAPI_STATUS_SUCCESS == GetAIValue(Id,&Value))
		{
			Scale = atof(scale_str);
			d_Value = Value*Scale/1000 ;		        	
			printf("GetAIValue  Id: %u \nValue: %.2f \n", Id, d_Value);
		}
		else 			
			return 0;
                break;
	case 'A':
		 if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0 ) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);

                }
                if ( EAPI_STATUS_SUCCESS == GetAIOScale(0 ,scale_str) && EAPI_STATUS_SUCCESS == GetAOValue(Id,&Value))
		{
		       Scale = atof(scale_str);
		       d_Value = Value *Scale/1000;
	               printf(" GetAOValue Id: %u \nValue: %.2f \n", Id, d_Value);
			
		}
		else
			return 0;
                break;
	case 'B':
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0  || MyAtoU(argv[3]) >5  || MyAtoU(argv[3]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
			value = atof(argv[3]);
                }
		if (EAPI_STATUS_SUCCESS == GetAIOScale(0 , scale_str))
		{
			 Scale = atof(scale_str);
			if (Scale!= 0){
				value = value*1000/Scale;
				if (value > 4095)
					value = 4095 ;
				if (EAPI_STATUS_SUCCESS == SetAOValue(Id,value))
					printf(" SetAOValue Id: %u \n rawValue: %f \n", Id, value);
			        else
                        		return 0;				
			}		
		}
                break;
	case 'C':	
		printf(" PinRet not support \n");
		return 0;
	#if 0
		if (MyAtoU(argv[2]) >= MaxCount || MyAtoU(argv[2]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Id = MyAtoU(argv[2]);
                       
                }		
		PinReset(Id);
		printf(" PinReset Id: %u \nValue: %u \n", Id, Value);
	#endif
                break;
	case 'D':
		char *Scal ;
		if (MyAtoU(argv[3]) >=2  || MyAtoU(argv[3]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {                       
		       Scal= argv[2];
		       Direction = MyAtoU(argv[3]);                    
                        
                }

		SetAIOScale(Direction ,Scal );
                printf(" Set Scale: %s  , Direction : %d\n", Scal , Direction);
                break;
	case 'E':
		if (MyAtoU(argv[2]) >=2  || MyAtoU(argv[2]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
			Direction = MyAtoU(argv[2]);
                }           	
		GetAIOScale(Direction ,scale_str);
                printf(" get scale: %s  , Direction : %d \n", scale_str , Direction);
                break;
	 case 'F':
                if (MyAtoU(argv[2]) >=2  || MyAtoU(argv[2]) < 0) {
                        Usage(argv[0]);
                        return 0;
                } else {
                        Direction = MyAtoU(argv[2]);
                }
                GetAIOAvailScale(Direction ,scale_str);
                printf(" get scale: %s  , Direction : %d \n", scale_str , Direction);
                break;


        default:
                Usage(argv[0]);
                break;
        }
 
        LibUnInitialize();
        CloseEAPI(hDLL);
        return 0;

}


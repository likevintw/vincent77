#ifndef _AUXIO_H_
#define _AUXIO_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

EApiStatus_t
EAPI_CALLTYPE
EApiGPIOGetLevel (
                __IN EApiId_t Id,
                __IN uint32_t Bitmask,
                __OUT uint32_t *pLevel
                );
EApiStatus_t
EAPI_CALLTYPE
EApiGPIOSetLevel (
                __IN EApiId_t Id,
                __IN uint32_t Bitmask,
                __IN uint32_t Level
                );
EApiStatus_t
EAPI_CALLTYPE
EApiGPIOGetDirection (
                __IN EApiId_t Id,
                __IN uint32_t Bitmask,
                __OUT uint32_t *pDirection
                );
EApiStatus_t
EAPI_CALLTYPE
EApiGPIOSetDirection (
                __IN EApiId_t Id,
                __IN uint32_t Bitmask,
                __IN uint32_t Direction
                );
EApiStatus_t
EAPI_CALLTYPE
EApiGPIOGetDirectionCaps (
                __IN EApiId_t Id,
                __OUTOPT uint32_t *pInputs,
                __OUTOPT uint32_t *pOutputs
                );
EApiStatus_t
EAPI_CALLTYPE
EApiAIGetValue(
        __IN  EApiId_t Id, /* ADC port Id */
        __OUT uint32_t *pValue       /* Current Value */
        );

EApiStatus_t
EAPI_CALLTYPE
EApiAOSetValue(
        __IN  EApiId_t Id, /* DAC port Id */
        __IN  uint32_t Value         /* Value */
        );

EApiStatus_t
EAPI_CALLTYPE
EApiAOGetValue(
        __IN  EApiId_t Id, /* DAC port Id */
        __OUT uint32_t *pValue       /* Output Value */
        );

EApiStatus_t
EAPI_CALLTYPE
EApiGetGPIOMask(
        __OUT uint32_t *pGPIOMask  /* Current GPIOMask */
        );

EApiStatus_t
EAPI_CALLTYPE
EApiGetAIMask(
	__OUT uint32_t *pAIMask
	);

EApiStatus_t
EAPI_CALLTYPE
EApiGetAOMask(
	__OUT uint32_t  *pAOMask
	);


EApiStatus_t
EAPI_CALLTYPE
EApiSetDefault(
	__IN EApiId_t Id
	);


EApiStatus_t 
EAPI_CALLTYPE
EApiAIOSetScale(
        __IN uint32_t Direction ,
        __IN char *pScale
	) ;

EApiStatus_t 
EAPI_CALLTYPE
EApiAIOGetScale(
        __IN uint32_t Direction ,
        __OUT char *pScale);

EApiStatus_t 
EAPI_CALLTYPE
EApiAIOGetAvailableScale(
         __IN uint32_t Direction ,
         __OUT char *pScale);


typedef EApiStatus_t (*fnEApiGPIOGetLevel) (
		__IN EApiId_t Id,
		__IN uint32_t Bitmask, 
		__OUT uint32_t *pLevel
		);

typedef EApiStatus_t (*fnEApiGPIOSetLevel) (
		__IN EApiId_t Id,
		__IN uint32_t Bitmask, 
		__IN uint32_t Level
		);

typedef EApiStatus_t (*fnEApiGPIOGetDirection) (
		__IN EApiId_t Id,
		__IN uint32_t Bitmask, 
		__OUT uint32_t *pDirection
		);

typedef EApiStatus_t (*fnEApiGPIOSetDirection) (
		__IN EApiId_t Id,
		__IN uint32_t Bitmask, 
		__IN uint32_t Direction
		);

typedef EApiStatus_t (*fnEApiGPIOGetDirectionCaps) (
		__IN EApiId_t Id,
		__OUTOPT uint32_t *pInputs, 
		__OUTOPT uint32_t *pOutputs
		);


typedef EApiStatus_t (*fnEApiAIGetValue)(
	        __IN  EApiId_t Id, /* ADC port Id */
        	__OUT uint32_t *pValue       /* Current Value */
        	);

typedef EApiStatus_t (*fnEApiAOSetValue)(
        	__IN  EApiId_t Id, /* DAC port Id */
        	__IN  uint32_t Value         /* Value */
        	);

typedef EApiStatus_t (*fnEApiAOGetValue)(
        	__IN  EApiId_t Id, /* DAC port Id */
        	__OUT uint32_t *pValue       /* Output Value */
        	);

typedef EApiStatus_t (*fnEApiGetGPIOMask)(
        	__OUT uint32_t *pGPIOMask  /* Current GPIOMask */
        	);

typedef EApiStatus_t (*fnEApiGetAIMask)(
        	__OUT uint32_t *pAIMask  /* Current AIMask */
        	);

typedef EApiStatus_t (*fnEApiGetAOMask)(
        	__OUT uint32_t *pAOMask  /* Current AOMask */
        	);

typedef EApiStatus_t (*fnEApiSetDefault)(
	       	__IN EApiId_t Id
		);

typedef EApiStatus_t (*fnEApiAIOSetScale)( 
		__IN uint32_t Direction ,
        	__IN char *pScale
		);

typedef EApiStatus_t (*fnEApiAIOGetScale)(
		__IN uint32_t Direction , 
		__OUT char *pScale
		);

typedef EApiStatus_t (*fnEApiAIOGetAvailableScale)(
	 	__IN uint32_t Direction ,
	 	__OUT char *pScale
	 	);

#define EAPIFunction(h,s) 	fn##s s = (fn##s)dlsym(h,#s)

#ifdef __cplusplus
}
#endif
#endif 

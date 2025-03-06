#ifndef _ATGPIO_H_
#define _ATGPIO_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

void *OpenATGPIO()
{
	return dlopen("libATGPIO.so", RTLD_LAZY);
}

void CloseATGPIO(void *hDLL)
{
	if (hDLL) {
		dlclose(hDLL);
	}
}


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

typedef EApiStatus_t (*fnEApiGPIOGetCount) (
		__OUT uint32_t *pCount
		);

#define EAPIFunction(h,s) 	fn##s s = (fn##s)dlsym(h,#s)

#ifdef __cplusplus
}
#endif
#endif /* _ATGPIO_H_ */

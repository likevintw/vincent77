#ifndef _ATHWMON_H_
#define _ATHWMON_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

void *hDLL;

void *OpenEAPILIB()
{
	return dlopen("libEAPI.so", RTLD_LAZY);
}

void CloseEAPILIB(void *hDLL)
{
	if (hDLL) {
		dlclose(hDLL);
	}
}

EApiStatus_t EApiBoardGetValue(
		__IN EApiId_t Id,
		__OUT uint32_t *pValue
		);

typedef EApiStatus_t (*fnEApiBoardGetValue) (
		__IN EApiId_t Id,
		__OUT uint32_t *pValue
		);

#define EAPIFunction(h,s) 	fn##s s = (fn##s)dlsym(h,#s)

#ifdef __cplusplus
}
#endif
#endif /* _ATHWMON_H_ */

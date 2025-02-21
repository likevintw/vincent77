#ifndef _ATSMBUS_H_
#define _ATSMBUS_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef EApiStatus_t (*fnEApiSMBReadByte) (
		__IN EApiId_t Id,
		__IN uint8_t Addr,
		__IN uint8_t Cmd,
		__OUT uint8_t *pBuffer
		);

typedef EApiStatus_t (*fnEApiSMBWriteByte) (
		__IN EApiId_t Id,
		__IN uint8_t Addr,
		__IN uint8_t Cmd,
		__IN uint8_t Data
		);


#define EAPIFunction(h,s) 	fn##s s = (fn##s)dlsym(h,#s)

#ifdef __cplusplus
}
#endif
#endif /* _ATSMBUS_H_ */

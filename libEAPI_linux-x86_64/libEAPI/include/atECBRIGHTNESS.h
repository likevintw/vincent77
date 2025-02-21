#ifndef _ATECBRIGHTNESS_H_
#define _ATECBRIGHTNESS_H_

#include <string.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLEAR()			printf("\033[2J")
#define RESET_CURSOR()	printf("\033[H")

EApiStatus_t EApiDisplayGetBacklightBrightness(
		__IN EApiId_t Id, __OUT uint32_t *pBright);
EApiStatus_t EApiDisplaySetBacklightBrightness(
		__IN EApiId_t Id, __IN uint32_t Bright);
EApiStatus_t EApiDisplayGetCap(__IN EApiId_t Id, 
		__IN uint32_t CapId, __OUT uint32_t *pValue);
EApiStatus_t EApiDisplaySetCap(__IN EApiId_t Id,
		__IN uint32_t CapId, __IN uint32_t Value);

#ifdef __cplusplus
}
#endif
#endif /* _ATECBRIGHTNESS_H_ */


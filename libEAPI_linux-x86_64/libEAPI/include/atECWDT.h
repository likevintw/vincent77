#ifndef _ATECWDT_H_
#define _ATECWDT_H_

#include <string.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLEAR()			printf("\033[2J")
#define RESET_CURSOR()	printf("\033[H")

/*
 * Valid range: 
 * Delay(=0) 
 * EventTimeout(=0) 
 * ResetTimeout(1~6553)
 */
EApiStatus_t EApiWDogGetCap(__OUTOPT uint32_t *pMaxDelay, 
		__OUTOPT uint32_t *pMaxEventTimeout, __OUTOPT uint32_t *pMaxResetTimeout);
EApiStatus_t EApiWDogStart(__IN uint32_t Delay, 
		__IN uint32_t EventTimeout, __IN uint32_t ResetTimeout);
EApiStatus_t EApiWDogTrigger(void);
EApiStatus_t EApiWDogStop(void);

#ifdef __cplusplus
}
#endif
#endif /* _ATECWDT_H_ */


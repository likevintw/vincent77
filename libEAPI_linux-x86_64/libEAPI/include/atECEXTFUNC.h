#ifndef _ATECEXTFUNC_H_
#define _ATECEXTFUNC_H_

#include <stdbool.h>
#include <string.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EAPI_EXT_FUNC_LED_MAX					16
#define EAPI_ID_EXT_FUNC_LED_BASE				0x00000000
#define EAPI_ID_EXT_FUNC_LED(N)					(EAPI_ID_EXT_FUNC_LED_BASE + N)
#define EAPI_ID_EXT_FUNC_LED_MIN				0x00000000
#define EAPI_ID_EXT_FUNC_LED_MAX				0x0000000F
//#define EAPI_EXT_FUNC_LED_ID_TO_INDEX(ID)		
#define EAPI_EXT_FUNC_POWER_VIN_MAX				2
#define EAPI_ID_EXT_FUNC_POWER_STATUS_BASE		0x00000010
#define EAPI_ID_EXT_FUNC_POWER_STATUS_VIN(N)	(EAPI_ID_EXT_FUNC_POWER_STATUS_BASE + N)
#define EAPI_ID_EXT_FUNC_POWER_STATUS_VIN_MIN	0x00000010
#define EAPI_ID_EXT_FUNC_POWER_STATUS_VIN_MAX	0x00000011 
//#define EAPI_EXT_FUNC_POWER_STATUS_VIN_ID_TO_INDEX
#define EAPI_ID_EXT_FUNC_MAX					0x000000FF

EApiStatus_t EApiExtFunctionGetStatus(__IN EApiId_t Id, __INOUT uint32_t* pStatus);
EApiStatus_t EApiExtFunctionSetStatus(__IN EApiId_t Id, __IN uint32_t Status);

#ifdef __cplusplus
}
#endif
#endif /* _ATECEXTFUNC_H_ */


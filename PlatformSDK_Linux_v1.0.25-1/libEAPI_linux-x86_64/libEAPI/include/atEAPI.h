#ifndef _ATEAPI_H_
#define _ATEAPI_H_

#include <string.h>
#include <stdbool.h>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	EAPI_ID_BOARD_NAME_STR
#define EAPI_ID_BOARD_NAME_STR				0x1
#endif
#ifndef EAPI_ID_BOARD_BIOS_REVISION_STR
#define EAPI_ID_BOARD_BIOS_REVISION_STR		0x4
#endif
#ifndef EAPI_ID_BOARD_EC_REVISION_STR
#define EAPI_ID_BOARD_EC_REVISION_STR		0x101
#endif
#ifndef EAPI_ID_BOARD_OS_REVISION_STR
#define EAPI_ID_BOARD_OS_REVISION_STR		0x102
#endif
#ifndef EAPI_ID_BOARD_CPU_MODEL_NAME_STR
#define EAPI_ID_BOARD_CPU_MODEL_NAME_STR	0x103
#endif

#define COMPORT_ITEM_BUFFER_SIZE 32

typedef struct _PLATFORM_COMPORT {
	char name[COMPORT_ITEM_BUFFER_SIZE];
	char pnpId[COMPORT_ITEM_BUFFER_SIZE];
	char manufacturer[COMPORT_ITEM_BUFFER_SIZE];
	char locationId[COMPORT_ITEM_BUFFER_SIZE];
} PLATFORM_COMPORT;

#define AT_PLATFORM_NO_ERROR					0x0
#define AT_PLATFORM_INVALID_PARAMETER_ERROR		AT_PLATFORM_NO_ERROR + 0x1
#define AT_PLATFORM_UNKNOW_ERROR				AT_PLATFORM_NO_ERROR + 0x2

// Disk partition information return structure
typedef enum _PARTITION_STYLE { 
	PARTITION_STYLE_MBR = 0,
	PARTITION_STYLE_GPT = 1,
	PARTITION_STYLE_RAW = 2
} PARTITION_STYLE;

typedef struct _PARTITION_INFORMATION_MBR {
	unsigned char	PartitionType;
	bool 			BootIndicator;
	bool 			RecognizedPartition;
	uint32_t   		HiddenSectors;
} PARTITION_INFORMATION_MBR, *PPARTITION_INFORMATION_MBR;

typedef struct _GUID 
{ 
	unsigned long        Data1; 
	unsigned short       Data2; 
	unsigned short       Data3; 
	unsigned char        Data4[8]; 
} GUID;

typedef struct _PARTITION_INFORMATION_GPT {
	GUID		PartitionType;
	GUID		PartitionId;
	uint64_t	Attributes;
	unsigned short   	Name[36];
} PARTITION_INFORMATION_GPT, *PPARTITION_INFORMATION_GPT;

typedef struct {
	PARTITION_STYLE PartitionStyle;
	int64_t   		StartingOffset;
	int64_t		  	PartitionLength;
	uint32_t        PartitionNumber;
	bool         	RewritePartition;
	union {
		PARTITION_INFORMATION_MBR Mbr;
		PARTITION_INFORMATION_GPT Gpt;
	};
} PARTITION_INFORMATION_EX;

typedef struct _PART_VOLUME_INFO {
    PARTITION_INFORMATION_EX partitionInfo;		// Partition information structure. Get partition size here
	int32_t 	serialNumber;					// Partition serial number
	char fileSystem[16];						// File system type: NTFS, FAT32, ..., and so on
	char volumeType[16];						// VolumeType: fixed, removable, ... and so on
} PART_VOLUME_INFO, *PPART_VOLUME_INFO;

typedef struct _DISK_PART_INFO {
	int64_t diskSize;							// Disk size
	uint32_t	 partitionStyle;				// 0 = MBR, 1 = GPT
    uint32_t	 partitionCount;				// Partition count in each disk
	PART_VOLUME_INFO partVolumeInfo[128];		// Partition and volume information structure, support 128 partition in one disk at most
} DISK_PART_INFO, *PDISK_PART_INFO;

typedef struct _DISK_INFO {
	uint32_t	 	diskCount;					// Disk count in this device
	DISK_PART_INFO	diskPartInfo[8];			// Disk information structure, support 8 disk in one device at most
} DISK_INFO, *PDISK_INFO;

EApiStatus_t EApiBoardGetStringA(EApiId_t Id, char *pBuffer, uint32_t *pBufLen);
EApiStatus_t EApiGetCOMports(PLATFORM_COMPORT **comports, unsigned int *len);
EApiStatus_t EApiGetMemoryAvailable(float *mem_available);
EApiStatus_t EApiGetDiskInfo(PDISK_INFO diskInfo);

#ifdef __cplusplus
}
#endif
#endif /* _ATEAPI_H_ */

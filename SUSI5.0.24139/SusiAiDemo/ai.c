#include "SusiAi.h"
#include "os_winnt.h"
#include "os_linux.h"

#define STRING_MAXIMUM_LENGTH			128
#define SUSIDEMO_FUNCTIONS_GOBACK		(-1)
#define SUSIDEMO_FUNCTIONS_UNDEFINED	(-2)

#define SUSIDEMO_DEVICE_AVAILALBE		1
#define SUSIDEMO_DEVICE_UNAVAILALBE		0
#define NELEMS(_array)	(uint32_t)(sizeof(_array) / sizeof(_array[0]))

enum funcRank {
	funcNvidiaX86,
	funcDockerImage,
	funcContainer,
	funcNVArm,
	funcX86INTEL,
	funcMTKArm,
	funcNXPArm,
	NumFunc,
};

static const char *AIX86Str[][2] = {
	{"GPU Current ID",	""},
	{"GPU Usage",		"%"},
	{"GPU Temp.",		"Celsius"},
	{"GPU Perf.",		""},
	{"Power Usage",		"W"},
	{"Power Cap.",		"W"},
	{"Memory Inuse",	"MiB"},
	{"Memory Total",	"MiB"},
	{"Fan Speed",		"%" },
	{"Numbers of GPU",	""},
	{"Compute Mode",	"" },
	{"Display Active",	"" }
};

static const char *ComputeMode[] = {
	"Default",
	"Exclusive_Thread",
	"Prohibited",
	"Exclusive_process",
	"Others"
};

static const char *AIX86StrStr[] = {
	"GPU Name",
	"Driver Version",
	"CUDA Version",
	"CUDNN Version"
};

static const char *AIX86INTELValStr[][2] = {
	{"CPU Usage",		"%"},
	{"GPU Usage",		"%"},
	{"CPU Temp.",		"Celsius"},
	{"GPU Temp.",		"Celsius"}
};

static const char *AIJETSONValStr[][2] = {
	{"CPU Usage",		"%"},
	{"GPU Usage",		"%"},
	{"GPU Temp.",		"Celsius"},
	{"RAM Usage",		"MB"},
	{"Fan Speed",		"%" },
	{"Power Mode Total",	""}
};

static const char *AIX86INTELStrStr[] = {
	"CPU Name",
	"GPU Name"
};

static const char *AIJETSONStrStr[] = {
	"CUDA Version",
	"cudnn Version",
	"TensorRT Version",
	"OPENCV Version",
	"HW Version",
	"Power Mode(current)",
	"JetPack Version",
};

static const char *AIDockerStr[][2] = {
	{"Image Size", "KB"}
};

static const char *AIDockerStrStr[] = {
	"Image ID",
	"Image Tag",
	"Image base",
	"Architecture",
	"Build Time",
	"Build On Docker"
};

static const char *AIContainerStrStr[] = {
	"Run on image id",
	"Run on image",
	"Name",
	"Container ID",
	"Status",
	"Connected IP",
	"Gateway",
	"Mac Address"
};

static const char *AIContainerStr[][2] = {
	{"CPU Usage",		"%"},
	{"Memory Usage",	"%"},
	{"Memory Inuse",	"MB"},
	{"Memory Total",	"MB"}
};

static const char *AIMTKStr[][2] = {
	{"GPU Usage.",		"%"},
	{"CPU Temp.",		"Celsius"},
	{"GPU1 Temp.",		"Celsius"},
	{"GPU2 Temp.",          "Celsius"},
	{"Memory Info.",	"KB"}
};

static const char *AINXPStr[][2] = {
	{"CPU Usage",		"%"},
	{"CPU Temp.",		"Celsius"},
	{"Memory Info.",	"KB"}
};

uint32_t pCaps = 0;
static int8_t functions[NumFunc + 1];	/* NumFunc + GoBack */
int wait_enter(void)
{
	int c, i = 0;

	fflush(stdout);
	while ((c = getchar()) != '\n' && c != EOF)
		i++;

	return i;
}
int input_uint(uint32_t *psetVal, uint8_t base, uint32_t maxVal, uint32_t minVal)
{
	int pass;

	fflush(stdout);

	if (psetVal == NULL)
		return -1;

	switch (base)
	{
	case 8:
		pass = SCANF_IN("%o", psetVal);
		break;
	case 10:
		pass = SCANF_IN("%u", psetVal);
		break;
	case 16:
		pass = SCANF_IN("%x", psetVal);
		break;
	default:
		return -1;
	}

	if (wait_enter())
		return -1;	/* one or more invalid characters */

	if (pass <= 0)
		return -1;	/* no valid character */

	if (*psetVal > maxVal || *psetVal < minVal)
		return -1;

	return 0;
}
uint8_t ai_init(void)
{
	uint8_t index = 0;

	if (SusiAIInitialize() == SUSI_STATUS_SUCCESS)
	{
		if (SusiAIGetCaps(SUSI_ID_AI_SUPPORT_FLAGS, &pCaps) == SUSI_STATUS_SUCCESS)
		{
			functions[index++] = SUSIDEMO_FUNCTIONS_GOBACK;

			if (pCaps & SUSI_AI_FLAG_SUPPORT_X86_NV)
				functions[index++] = funcNvidiaX86;

			if (pCaps & SUSI_AI_FLAG_SUPPORT_DOCKER_IMG)
				functions[index++] = funcDockerImage;

			if (pCaps & SUSI_AI_FLAG_SUPPORT_CONTAINER)
				functions[index++] = funcContainer;

			if (pCaps & SUSI_AI_FLAG_SUPPORT_ARM_NV)
				functions[index++] = funcNVArm;

			if (pCaps & SUSI_AI_FLAG_SUPPORT_X86_INTEL)
				functions[index++] = funcX86INTEL;

			if (pCaps & SUSI_AI_FLAG_SUPPORT_ARM_MTK)
				functions[index++] = funcMTKArm;
			
			if (pCaps & SUSI_AI_FLAG_SUPPORT_ARM_NXP)
				functions[index++] = funcNXPArm;

			while (index < NELEMS(functions))
				functions[index++] = SUSIDEMO_FUNCTIONS_UNDEFINED;

			return SUSIDEMO_DEVICE_AVAILALBE;
		}
	}
	while (index < NELEMS(functions))
		functions[index++] = SUSIDEMO_FUNCTIONS_UNDEFINED;

	return SUSIDEMO_DEVICE_UNAVAILALBE;
}
uint8_t ai_jetson_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t  getStrLen = 0;
	char getStr[STRING_MAXIMUM_LENGTH];

	uint32_t  getVal = 0, i = 0, pm_total_num = 0, idTemp = 0;

	for (i = 0; i < SUSI_AI_ID_ARM_NV_MAX; i++)
	{
		idTemp = SUSI_AI_ID_ARM_NV_BASE + i;
		status = SusiAIGetValue(idTemp, &getVal);
		if (status == SUSI_STATUS_SUCCESS)
		{
			printf("%-15s: %d %s\n", AIJETSONValStr[i][0], getVal, AIJETSONValStr[i][1]);

			if (idTemp == SUSI_AI_ID_ARM_NV_POWER_MODE_Total)
			{
				pm_total_num = getVal;
			}
		}
	}


	for (i = 0; i < SUSI_AI_ID_ARM_NV_STR_MAX - 1; i++)
	{
		getStrLen = STRING_MAXIMUM_LENGTH;
		//status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_NAME_ARM_NV_AI(i), getStr, &getStrLen);
		idTemp = SUSI_ID_BASE_GET_NAME_ARM_NV_AI + i;
		status = SusiAIGetStringA(idTemp, getStr, &getStrLen);
		if (status == SUSI_STATUS_SUCCESS)
			printf("%-15s: %s\n", AIJETSONStrStr[i], getStr);
	}

	if (pm_total_num)
	{
		for (i = 0; i < pm_total_num; i++)
		{
			getStrLen = STRING_MAXIMUM_LENGTH;
			idTemp = SUSI_ID_MAPPING_GET_VALUE(SUSI_AI_ID_ARM_NV_POWER_MODE_NAME, i);
			// printf("SUSI_AI_ID_ARM_NV_POWER_MODE_NAME : idTemp : %x\n", idTemp );  
			status = SusiAIGetStringA(idTemp, getStr, &getStrLen);

			if (status == SUSI_STATUS_SUCCESS)
			{
				printf("Power Mode[%d]: %s\n", i, getStr);
			}
#if 0
			//test for power mode setting
			status = SusiAISetValue(SUSI_AI_ID_ARM_NV_SET_POWER_MODE, i ); 
			if (status == SUSI_STATUS_SUCCESS)
			{ 
					   printf("Power Mode[%d]: Set Successfully  \n", i   ); 
			}
#endif
		}
	}
#if 0
	//test for fan speed setting
	uint32_t fanSpeedVal = 120;
	status = SusiAISetValue(SUSI_AI_ID_ARM_NV_SET_FAN_SPEED, fanSpeedVal);
	{
		printf("Fan Speed [value:%d]: Set Successfully  \n", fanSpeedVal);
	}
#endif
	return status;
}
uint8_t ai_x86_intel_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t getVal = 0, getStrLen = 0, i = 0;
	char getStr[STRING_MAXIMUM_LENGTH];

	for (i = 0; i < SUSI_AI_ID_X86_INTEL_STR_MAX; i++)
	{
		getStrLen = STRING_MAXIMUM_LENGTH;
		status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_NAME_X86_INTEL_AI(i), getStr, &getStrLen);
		if (status == SUSI_STATUS_SUCCESS)
			printf("%-15s: %s\n", AIX86INTELStrStr[i], getStr);
	}

	for (i = 0; i < SUSI_AI_ID_X86_INTEL_MAX; i++) 
	{
		status = SusiAIGetValue((SUSI_AI_ID_X86_INTEL_GET_BASE + i), &getVal);
		if (status == SUSI_STATUS_SUCCESS)
		{
			if((SUSI_AI_ID_X86_INTEL_GET_BASE + i) == SUSI_AI_ID_X86_INTEL_CPU_USAGE ||
			   (SUSI_AI_ID_X86_INTEL_GET_BASE + i) == SUSI_AI_ID_X86_INTEL_GPU_USAGE)
				printf("%-15s: %.02f %s\n", AIX86INTELValStr[i][0], (float)getVal / 100.0, AIX86INTELValStr[i][1]);
			else
				printf("%-15s: %d %s\n", AIX86INTELValStr[i][0], getVal, AIX86INTELValStr[i][1]);
		}
	}
	return status;
}
uint8_t ai_x86_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t getVal = 0, getStrLen = STRING_MAXIMUM_LENGTH, i = 0, num = 0, index = 0;
	char getStr[STRING_MAXIMUM_LENGTH];

	status = SusiAIGetValue(SUSI_AI_ID_X86_NV_GET_COUNT, &num);

	if (status == SUSI_STATUS_SUCCESS)
	{
		printf("\n");
		if (num > 1)
		{
			for (index = 0; index < num; index++)
			{
				status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_VALUE(SUSI_AI_ID_X86_NV_NAME_STR, index), getStr, &getStrLen);
				if (status == SUSI_STATUS_SUCCESS)
					printf("%d: %s", index, getStr);
			}
			printf("\nEnter your choice: \n");
			if (input_uint(&index, 10, num - 1, 0))
				goto exit;
		}

		for (i = 0; i < SUSI_AI_ID_X86_NV_STR_MAX; i++)
		{
			if (num > 1 && i == 0)
				continue;
			status = SusiAIGetStringA(SUSI_ID_BASE_GET_NAME_X86_NV_AI + i, getStr, &getStrLen);
			if (status == SUSI_STATUS_SUCCESS)
				printf("%-15s: %s", AIX86StrStr[i], getStr);
		}

		for (i = 0; i < SUSI_AI_ID_X86_NV_MAX; i++)
		{
			if ((SUSI_AI_ID_X86_NV_BASE + i) == SUSI_AI_ID_X86_NV_GET_COUNT)
				continue;

			status = SusiAIGetValue(SUSI_ID_MAPPING_GET_VALUE((SUSI_AI_ID_X86_NV_BASE + i), index), &getVal);
			if (status == SUSI_STATUS_SUCCESS)
			{
				if (SUSI_AI_ID_X86_NV_BASE + i == SUSI_AI_ID_X86_NV_POWER_USAGE)
				{
					printf("%-15s: %.02f %s\n", AIX86Str[i][0], (float)(getVal / 100.0), AIX86Str[i][1]);
					continue;
				}
				else if (SUSI_AI_ID_X86_NV_BASE + i == SUSI_AI_ID_X86_NV_PERF)
				{
					printf("%-15s: P%d\n", AIX86Str[i][0], getVal);
					continue;
				}
				else if (SUSI_AI_ID_X86_NV_BASE + i == SUSI_AI_ID_X86_NV_COMPUTE_MODE)
				{
					printf("%-15s: %s\n", AIX86Str[i][0], ComputeMode[getVal]);
					continue;
				}
				else if (SUSI_AI_ID_X86_NV_BASE + i == SUSI_AI_ID_X86_NV_DISPLAY_ACTIVE)
				{
					printf("%-15s: %s\n", AIX86Str[i][0], getVal == 1 ? "On" : "Off");
					continue;
				}
				printf("%-15s: %d %s\n", AIX86Str[i][0], getVal, AIX86Str[i][1]);
			}
		}
	}
exit:
	return status;
}

uint8_t ai_docker_img_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t getVal = 0, getStrLen = 0, i = 0, num = 0, index = 0;
	char getStr[STRING_MAXIMUM_LENGTH];

	status = SusiAIGetValue(SUSI_AI_ID_DOCKER_IMG_COUNT, &num);

	if (status == SUSI_STATUS_SUCCESS)
	{
		printf("\n");
		for (index = 0; index < num; index++)
		{
			status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_VALUE(SUSI_AI_ID_DOCKER_IMG_TAG_STR, index), getStr, &getStrLen);
			if (status == SUSI_STATUS_SUCCESS)
				printf("%d: %s", index, getStr);
		}
		printf("\nEnter your choice: \n");
	}

	if (input_uint(&index, 10, num - 1, 0))
		goto exit;

	for (i = 0; i < SUSI_AI_ID_DOCKER_IMG_STR_MAX; i++)
	{
		status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_VALUE(SUSI_ID_MAPPING_GET_NAME_DOCKER_IMG_AI(i), index), getStr, &getStrLen);
		if (status == SUSI_STATUS_SUCCESS)
			printf("%-15s: %s", AIDockerStrStr[i], getStr);
	}

	for (i = 0; i < SUSI_AI_ID_DOCKER_IMG_MAX; i++)
	{
		status = SusiAIGetValue(SUSI_ID_MAPPING_GET_VALUE((SUSI_AI_ID_DOCKER_IMG_BASE + i), index), &getVal);
		if (status == SUSI_STATUS_SUCCESS)
		{
			if ((SUSI_AI_ID_DOCKER_IMG_BASE + i) == SUSI_AI_ID_DOCKER_IMG_SIZE)
				printf("%-15s: %.02f %s\n", AIDockerStr[i][0], (float)getVal / 1000.0, AIDockerStr[i][1]);
			else
				printf("%-15s: %d %s\n", AIDockerStr[i][0], getVal, AIDockerStr[i][1]);
		}
	}

exit:
	return status;
}
uint8_t ai_containter_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t getVal = 0, getStrLen = 0, i = 0, num = 0, index = 0;
	char getStr[STRING_MAXIMUM_LENGTH];

	status = SusiAIGetValue(SUSI_AI_ID_CONTAINER_COUNT, &num);

	if (status == SUSI_STATUS_SUCCESS)
	{
		printf("\n");
		for (index = 0; index < num; index++)
		{
			status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_VALUE(SUSI_AI_ID_CONTAINER_NAME_STR, index), getStr, &getStrLen);
			if (status == SUSI_STATUS_SUCCESS)
				printf("%d: %s", index, getStr);
		}
		printf("\nEnter your choice: \n");
	}

	if (input_uint(&index, 10, num - 1, 0))
		goto exit;

	for (i = 0; i < SUSI_AI_ID_CONTAINER_STR_MAX; i++)
	{
		status = SusiAIGetStringA(SUSI_ID_MAPPING_GET_VALUE(SUSI_ID_MAPPING_GET_NAME_CONTAINER_AI(i), index), getStr, &getStrLen);
		if (status == SUSI_STATUS_SUCCESS)
			printf("%-15s: %s", AIContainerStrStr[i], getStr);
	}

	for (i = 0; i < SUSI_AI_ID_CONTAINER_MAX; i++)
	{
		status = SusiAIGetValue(SUSI_ID_MAPPING_GET_VALUE((SUSI_AI_ID_CONTAINER_BASE + i), index), &getVal);
		if (status == SUSI_STATUS_SUCCESS)
		{
			if ((SUSI_AI_ID_CONTAINER_BASE + i) == SUSI_AI_ID_CONTAINER_MEM_INUSE)
				printf("%-15s: %.03f %s\n", AIContainerStr[i][0], (float)getVal / 1000.0, AIContainerStr[i][1]);
			else if ((SUSI_AI_ID_CONTAINER_BASE + i) == SUSI_AI_ID_CONTAINER_MEM_TOTAL)
				printf("%-15s: %d %s\n", AIContainerStr[i][0], getVal / 1000, AIContainerStr[i][1]);
			else if ((SUSI_AI_ID_CONTAINER_BASE + i) == SUSI_AI_ID_CONTAINER_COUNT)
				printf("%-15s: %d %s\n", AIContainerStr[i][0], getVal, AIContainerStr[i][1]);
			else
				printf("%-15s: %.02f %s\n", AIContainerStr[i][0], (float)getVal / 100.0, AIContainerStr[i][1]);
		}
	}

exit:
	return status;
}
uint8_t ai_genio_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t getVal = 0, i = 0;
	for (i = 0; i < SUSI_AI_ID_ARM_MTK_MAX; i++)
	{
		status = SusiAIGetValue((SUSI_AI_ID_ARM_MTK_BASE + i), &getVal);
		if (status == SUSI_STATUS_SUCCESS)
		{
			printf("%-15s: %d %s\n", AIMTKStr[i][0], getVal, AIMTKStr[i][1]);
		}
	}
	return status;
}
uint8_t ai_imx93_info(void)
{
	SusiStatus_t status = SUSI_STATUS_UNSUPPORTED;
	uint32_t getVal = 0, i = 0;
	for (i = 0; i < SUSI_AI_ID_ARM_NXP_MAX; i++)
	{
		status = SusiAIGetValue((SUSI_AI_ID_ARM_NXP_BASE + i), &getVal);
		if (status == SUSI_STATUS_SUCCESS)
		{
			printf("%-15s: %d %s\n", AINXPStr[i][0], getVal, AINXPStr[i][1]);
		}
	}
	return status;
}
static void title(const char *name)
{
	printf(
		"************************************************************************\n"
		"**                           SUSI AI demo                             **\n"
		"** Note: Advantech SUSI AI supports Intel CPU/GPU, Nvidia and others. **\n"
		"** If you do not see the relevant items, please ensure that both your **\n"
		"** hardware and drivers support these components, and that the        **\n"
		"** appropriate drivers are installed.                                 **\n"
		"************************************************************************\n\n"
	);

	printf("%s\n\n", name);
}
static void menu(void)
{
	uint8_t i = 0;

	printf("0) Back to Main menu\n");

	if (pCaps & SUSI_AI_FLAG_SUPPORT_X86_NV)
		printf("%d) Nvidia x86\n", ++i);
	if (pCaps & SUSI_AI_FLAG_SUPPORT_DOCKER_IMG)
		printf("%d) Docker Image\n", ++i);
	if (pCaps & SUSI_AI_FLAG_SUPPORT_CONTAINER)
		printf("%d) Container\n", ++i);
	if (pCaps & SUSI_AI_FLAG_SUPPORT_ARM_NV)
		printf("%d) Nvidia ARM\n", ++i);
	if (pCaps & SUSI_AI_FLAG_SUPPORT_X86_INTEL)
		printf("%d) Intel x86 \n", ++i);
	if (pCaps & SUSI_AI_FLAG_SUPPORT_ARM_MTK)
		printf("%d) MTK ARM\n", ++i);
	if (pCaps & SUSI_AI_FLAG_SUPPORT_ARM_NXP)
		printf("%d) NXP ARM\n", ++i);

	printf("\nEnter your choice: ");
	fflush(stdout);
}
int clr_screen(void)
{
	return system(CLRSCR);
}
int main(void)
{
	uint32_t op;
	if (ai_init() == SUSIDEMO_DEVICE_UNAVAILALBE)
	{
		printf("SUSI AI initialize failed\n");
		wait_enter();
		goto exit;
	}
	while (1)
	{
		clr_screen();
		title("AI");
		menu();
		if (input_uint(&op, 10, NELEMS(functions) - 1, 0))
			goto unknown;

		switch (functions[op])
		{
		case SUSIDEMO_FUNCTIONS_GOBACK:
			goto exit;
		case funcNvidiaX86:
			ai_x86_info();
			goto pause;
		case funcDockerImage:
			ai_docker_img_info();
			goto pause;
		case funcContainer:
			ai_containter_info();
			goto pause;
		case funcNVArm:
			ai_jetson_info();
			goto pause;
		case funcX86INTEL:
			ai_x86_intel_info();
			goto pause;
		case funcMTKArm:
			ai_genio_info();
			goto pause;
		case funcNXPArm:
			ai_imx93_info();
			goto pause;

		default:
			goto unknown;
		}
	unknown:
		printf("Unknown choice!\n");
	pause:
		printf("\nPress ENTER to continue. ");
		wait_enter();
	}
exit:
	printf("Exit the program...\n");

	if (SusiAIUninitialize() != SUSI_STATUS_SUCCESS)
	{
		printf("SusiAIUninitialize() failed.\n");
		return -1;
	}
	return 0;
}

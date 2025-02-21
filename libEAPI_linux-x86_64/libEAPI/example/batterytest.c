/*************************************************************************
 > File Name: ledtest.c
 > Author: suchao.wang
 > Mail: suchao.wang@advantech.com.cn
 > Created Time: Thu 20 Nov 2014 05:40:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "board_resource.h"

static inline void LOG(const char* ms, ... )
{
	char wzLog[1024] = {0};
	char buffer[1024+0x40] = {0};
	va_list args;
	va_start(args, ms);
	vsprintf( wzLog ,ms,args);
	va_end(args);

	struct timeval tv;
	gettimeofday(&tv,NULL);
	struct tm *local;
	local = localtime(&tv.tv_sec);
	sprintf(buffer,"%04d-%02d-%02d %02d:%02d:%02d.%06ld %s\n", local->tm_year+1900, 1 + local->tm_mon,
				local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec,tv.tv_usec,
				wzLog);
	FILE* file = fopen("testResut.log","a+");
	fwrite(buffer,1,strlen(buffer),file);
	fclose(file);

	pid_t parent = getppid();
	if( parent == 2 || parent == 3)
		syslog(LOG_INFO,"%s",wzLog);
	else
		printf("%s",buffer);
	return ;
}
int main(int argc, char *argv[])
{

	BR_HANDLE fd;
	unsigned int mseconds=1000;
	unsigned int nodeId,oldid = 0;
	BR_RESULT ret = BR_SUCCESS;


	if(argc ==2)
		mseconds=strtoul(argv[1],NULL,10);
	do
	{
		ret = Board_Init(&fd);
		if (ret != BR_SUCCESS)
		{
//				printf("open device fail[%d]\n", ret);
				continue;
		}
		Board_GetBattery(fd, &nodeId);
		Board_DeInit(fd);
		if(oldid == nodeId)
		{
			printf("battery:%d(%xh)\n", nodeId, nodeId);
		}else{
			LOG("battery:%d(%xh)", nodeId, nodeId);
			oldid = nodeId;
		}

		usleep(mseconds*1000);
	} while (1);

	return 0;
}

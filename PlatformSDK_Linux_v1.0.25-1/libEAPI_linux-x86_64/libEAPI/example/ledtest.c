/*************************************************************************
 > File Name: ledtest.c
 > Author: suchao.wang
 > Mail: suchao.wang@advantech.com.cn
 > Created Time: Thu 20 Nov 2014 05:40:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "board_resource.h"

int main(int argc, char *argv[])
{

        BR_HANDLE fd, fd2, fd3;
	BR_RESULT ret = BR_SUCCESS;
	ret = LED_Init(LED_TYPE_RUN, &fd);
	if (ret != BR_SUCCESS)
		printf("open device fail[%d]\n", ret);
	ret = LED_Init(LED_TYPE_ERROR, &fd2);
	if (ret != BR_SUCCESS)
		printf("open device fail[%d]\n", ret);
	ret = LED_Init(LED_TYPE_PROGRAM, &fd3);
	if (ret != BR_SUCCESS)
		printf("open device fail[%d]\n", ret);
	printf("fd:%lx,%lx,%lx\n",fd,fd2,fd3);
	if(fd3 > 0)
		LED_Blink(fd3,1000,1000);
//	while(1);
	while (fd > 0 || fd2 > 0 || fd3 > 0 )
	{
		if(fd > 0)
			LED_On(fd);
		if(fd2 > 0)
			LED_On(fd2);
		if(fd3 > 0)
			LED_On(fd3);
		sleep(1);
		if(fd > 0)
			LED_Off(fd);
		if(fd2 > 0)
			LED_Off(fd2);
		if(fd3 > 0)
			LED_Off(fd3);
		sleep(3);
	}

	return 0;
}

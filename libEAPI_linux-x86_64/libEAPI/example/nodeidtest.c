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

	BR_HANDLE fd;
	unsigned int nodeId;
	BR_RESULT ret = BR_SUCCESS;
	ret = Board_Init(&fd);
	if (ret != BR_SUCCESS)
		printf("open device fail[%d]\n", ret);
	Board_GetNodeID( fd, &nodeId );
	Board_DeInit(fd);
	printf("nodeid:%d(%xh)\n",nodeId,nodeId);
	return 0;
}

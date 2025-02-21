/*************************************************************************
 > File Name: ledtest.c
 > Author: suchao.wang
 > Mail: suchao.wang@advantech.com.cn
 > Created Time: Thu 20 Nov 2014 05:40:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include "board_resource.h"

#define EXAMPLEPROGRAM_WDTTEST_TIMEOUT_DEFFAULT 15000
BR_HANDLE wdt_fd;
//void sigroutine(int dunno) {

//	if(dunno == SIGINT)
//		exit(-1);
//	BR_RESULT ret = BR_SUCCESS;
//	ret = WDT_Disable(wdt_fd);
//	if (ret != BR_SUCCESS)
//		printf("diable wdt fail[%d]\n", ret);
//	exit(-1);
//}

static void term(int sig)
{
    printf("Got signal %d, but watchdog won't be disabled.\n", sig);
    printf("This device will reboot after %d seconds.\n",
            EXAMPLEPROGRAM_WDTTEST_TIMEOUT_DEFFAULT/1000);
    WDT_DeInit(wdt_fd);

    exit(0);
}

void usage(char *programname)
{
		printf("Start wdt timer and ping it per second : run %s without option.\n", programname);
		printf("Or get help guide             : %s -h\n", programname);

}
int main(int argc, char *argv[])
{

        if(2 == argc && argv[1][0]=='-' && argv[1][1]=='h')
        {
            usage(argv[0]);
            return 0;
        }
        else if (argc > 1){
            printf("Invalid option.\n\n");
            usage(argv[0]);
            return 0;
        }

	printf("Press Ctrl+C to stop pinging watchdog \nThe system will reboot in %d seconds if pinging stopped.\n",
                EXAMPLEPROGRAM_WDTTEST_TIMEOUT_DEFFAULT/1000);

	BR_RESULT ret = BR_SUCCESS;
        signal(SIGINT, term);
	ret = WDT_Init(&wdt_fd);
	if (ret != BR_SUCCESS)
	{
		printf("open device fail[%d]\n", ret);
		return 0;
	}
	ret = WDT_Enable(wdt_fd,EXAMPLEPROGRAM_WDTTEST_TIMEOUT_DEFFAULT);
	if (ret != BR_SUCCESS)
	{
		printf("enable wdt fail[%d]\n", ret);
		return 0;
	}

	WDT_SetMode(wdt_fd,WATCH_MODE_MANUAL,130);
	while(1){
		ret = WDT_Strobe(wdt_fd);
		if (ret != BR_SUCCESS)
		{
			printf("Pinging wdt failed[%d]\n", ret);
			if(BR_DEVICE_ALREADY_OPENED == ret)
			{
				do
				{
					ret = WDT_Enable(wdt_fd,2);
					if (ret != BR_SUCCESS)
					{
						printf("enable wdt fail[%d]\n", ret);
					}else{
						printf("enable wdt success\n");
					}
				}while(ret != BR_SUCCESS);
			}
		}else{
			printf("Pinging(sending strobe) wdt success\n");
		}
		sleep(1);
	}

	return 0;
}

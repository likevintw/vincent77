#include "common.h"

enum funcRank {
	funcNetwrokControl,
	funcNetwrokStatus,
	funcNetworkHostName,
	funcNetworkMacAddr,
	funcNetworkMDeviceIP,
	funcNetworkMSubMask,
	funcNetworkMDomainNameServerIP,
	funcNetworkMGatewayIP,
	NumFunc,
};
typedef struct _NetworkMap {
	char* Descriptions;
	uint32_t contorl;
} NetworkMap;
;
static NetworkMap networkCtrlStr[] = {
	{"Disconnect LAN", 0x00},
	{"Connect LAN with Static IP.All network settings must be completed first", 0x01},
	{"Connect LAN with DHCP server", 0x02},
	{"Store all of modified settings to flash", 0x10},
	{"Restore all of modified settings", 0x11},
	{"Reload factory settings from flash", 0x12}
};
static NetworkMap networkServerTypeStr[] = {
	{ "No Provision", 0x00 },
	{ "NMC server", 0x01 },
	{ "DeviceOn server", 0x02 }
};
static const char *funcRoStr[] = {
	"Current device IP",
	"Current sub mask",
	"Current domain name server IP",
	"Current getway IP",
	"Network error code",
	"Server type",
	"Server domain name",
	"Server IP/Port",
};
static const char *StatusStr[][2] = {
	{ "Non-available", "Available" },
	{ "No modify", "Modify" },
	{ "No error", "Error" },
	{ "Link-down", "Link-up" },
	{ "Static IP", "DHCP Server" },
	{ "Invalid", "Valid" },
	{ "Dis-connected", "Connected" },
	{ "Dedicated LAN Port", "NCSI Side-band Port" },
};
static const char *funcNetwrokStatusStr[] = {
	"Network Available",
	"Network setting modify",
	"Network error",
	"Link status",
	"IP source",
	"IP address",
	"Remote server connected",
	"Network Interface Type",
};
static const char *funcStr[] = {
	"Network control",
	"Network status",
	"Network host name",
	"Network MAC address",
	"Modified device IP",
	"Modified sub mask",
	"Modified domain name server IP",
	"Mofified getway IP",
};
static int8_t functions[NumFunc + 1];	/* NumFunc + GoBack */

void getStr(uint32_t *val, char* str)
{
	uint8_t i = 0;
	for (i = 0; i < NAME_MAXIMUM_LENGTH; i++)
		str[i] = (char)val[i];
}

uint8_t network_init(void)
{
	uint32_t i = 0, index = 0, getVal = 0;

	if (SusiBoardGetValue(SUSI_ID_NETWORK_STATUS, &getVal) == SUSI_STATUS_SUCCESS)
	{
			functions[index++] = SUSIDEMO_FUNCTIONS_GOBACK;
			for(i = 0; i < NumFunc; i++)
				functions[index++] = i;

			while (index < NELEMS(functions))
				functions[index++] = SUSIDEMO_FUNCTIONS_UNDEFINED;

			return SUSIDEMO_DEVICE_AVAILALBE;
	}
	while (index < NELEMS(functions))
		functions[index++] = SUSIDEMO_FUNCTIONS_UNDEFINED;

	return SUSIDEMO_DEVICE_UNAVAILALBE;
}
uint8_t network_ipaddr(SusiId_t Id)
{
	SusiStatus_t status;
	uint32_t ip[4] = { 0 }, addr = 0;
	uint8_t i = 0;

	for (i = 0; i < 4; i++)
	{
		printf("Type %d/4 IP address(DEC): ", i + 1);
		if (input_uint(&addr, 10, 255, 0))
		{
			printf("Invalid input\n");
			return 1;
		}
		else
			ip[i] = addr;
	}
	for (i = 0; i < 3; i++)
		printf("%d.", ip[i]);
	printf("%d\n", ip[3]);

	status = SusiBoardSetValue(Id, ip);
	if (status == SUSI_STATUS_SUCCESS)
		printf("Set address success\n");
	else
		printf("Set address failed(0x%X)\n", status);

	return status;
}
uint8_t network_macaddr(void)
{
	SusiStatus_t status;
	uint32_t mac[6] = { 0 }, addr = 0;
	uint8_t i = 0;

	for (i = 0; i < 6; i++)
	{
		printf("Type %d/6 MAC address(HEX): 0x", i+1);
		if (input_uint(&addr, 16, 0xFF, 0x00))
		{
			printf("Invalid input\n");
			return 1;
		}
		else
			mac[i] = addr;
	}
	for (i = 0; i < 5; i++)
		printf("%02X:", mac[i]);
	printf("%02X\n", mac[5]);

	status = SusiBoardSetValue(SUSI_ID_NETWORK_MAC_ADDRESS, mac);
	if (status == SUSI_STATUS_SUCCESS)
		printf("Set MAC address success\n");
	else
		printf("Set MAC address failed(0x%X)\n", status);

	return status;
}
uint8_t network_hostname(void)
{
	SusiStatus_t status;
	uint8_t i = 0;
	char str[NAME_MAXIMUM_LENGTH];
	uint32_t hostname[NAME_MAXIMUM_LENGTH], c = 0;
	memset(hostname, 0, sizeof(uint32_t) * NAME_MAXIMUM_LENGTH);

	fflush(stdout);
	printf("Note: maximum length of host name is %u-words\n", NAME_MAXIMUM_LENGTH);
	printf("Note: Press enter to finish it\n");
	printf("Type new host name: ");

	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (i < (NAME_MAXIMUM_LENGTH - 1))
			hostname[i++] = c;
	}
	hostname[i] = '\0';

	status = SusiBoardSetValue(SUSI_ID_NETWORK_HOST_NAME, hostname);
	if (status == SUSI_STATUS_SUCCESS)
	{
		getStr(hostname, str);
		printf("Set %s success\n", str);
	}
	else
		printf("Set hostname failed(0x%X)\n", status);

	return status;

}
uint8_t network_status(void)
{
	SusiStatus_t status;
	uint32_t getVal = 0;
	uint8_t i = 0, j = 0;
	status = SusiBoardGetValue(SUSI_ID_NETWORK_STATUS, &getVal);
	printf("\nNetwork status is 0x%X\n\n", getVal);
	if (status == SUSI_STATUS_SUCCESS)
	{
		for (i = 0; i < 8; i++)
		{
			j = (getVal >> i) & 0x01;
			printf("%-30s: %s\n", funcNetwrokStatusStr[i], StatusStr[i][j]);
		}
	}
	else
		printf("Get Network status failed(0x%X)\n", status);
	return status;
}
uint8_t network_control(void)
{
	SusiStatus_t status = SUSI_STATUS_SUCCESS;
	uint32_t op = 0;
	uint8_t i = 0;

	for (i = 0; i < 6; i++)
		printf("%d) %s\n", i, networkCtrlStr[i].Descriptions);

	if (input_uint(&op, 10, 5, 0))
	{
		printf("Invalid input\n");
		goto exit;
	}

	status = SusiBoardSetValue(SUSI_ID_NETWORK_CONTROL, &networkCtrlStr[op].contorl);
	if (status == SUSI_STATUS_SUCCESS)
		printf("Set 0x%X success\n", networkCtrlStr[op].contorl);
	else
		printf("Set 0x%X failed(0x%X)\n", networkCtrlStr[op].contorl, status);
exit:
	return status;
}

static void network_title(void)
{
	printf("**********************************************\n");
	printf("**               SUSI4.0 demo               **\n");
	printf("**********************************************\n");
	printf("\nNetwork\n\n");
}
static void menu(void)
{
	uint32_t getVal = 0, hostName[NAME_MAXIMUM_LENGTH] = { '\0' }, mac[6] = { 0 }, ip[4] = { 0 };
	uint32_t domainName[STRING_MAXIMUM_LENGTH] = { '\0' }, ipport[5] = { 0 };
	char str[NAME_MAXIMUM_LENGTH];
	SusiStatus_t status;
	SusiId_t id;
	uint8_t i = 0, j = 0;

	printf("0) Back to Main menu\n");

	for (i = 1; i < NELEMS(functions) && functions[i] != SUSIDEMO_FUNCTIONS_UNDEFINED; i++)
	{
		id = SUSI_ID_NETWORK_CONTROL + functions[i];

		if (id <= SUSI_ID_NETWORK_STATUS)
			status = SusiBoardGetValue(id, &getVal);
		else if (id == SUSI_ID_NETWORK_HOST_NAME)
			status = SusiBoardGetValue(id, hostName);
		else if (id == SUSI_ID_NETWORK_MAC_ADDRESS)
			status = SusiBoardGetValue(id, mac);
		else
		{
			memset(ip, 0, sizeof(uint32_t)*4);
			status = SusiBoardGetValue(id, ip);
		}

		if (status == SUSI_STATUS_SUCCESS)
		{
			if (id == SUSI_ID_NETWORK_CONTROL)
			{
				for (j = 0; j < 6; j++)
				{
					if (networkCtrlStr[j].contorl == getVal)
					{
						printf("%u) %-30s: %s\n", i, funcStr[functions[i]], networkCtrlStr[j].Descriptions);
						break;
					}
				}
			}
			else if (id == SUSI_ID_NETWORK_STATUS)
				printf("%u) %-30s: 0x%X\n", i, funcStr[functions[i]], getVal);
			else if (id == SUSI_ID_NETWORK_HOST_NAME)
			{
				getStr(hostName, str);
				printf("%u) %-30s: %s\n", i, funcStr[functions[i]], str);
			}
			else if (id == SUSI_ID_NETWORK_MAC_ADDRESS)
				printf("%u) %-30s: %02X:%02X:%02X:%02X:%02X:%02X\n", i, funcStr[functions[i]], mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			else
				printf("%u) %-30s: %d.%d.%d.%d\n", i, funcStr[functions[i]], ip[0], ip[1], ip[2], ip[3]);
		}
		else
		{
			printf("%u) %-30s: get 0x%08X failed. (0x%08X)\n", i, funcStr[functions[i]], id, status);
		}
	}

	for (i = 0; i < 8; i++)
	{
		id = SUSI_ID_NETWORK_C_DEVICE_IP + i;

		if (id <= SUSI_ID_NETWORK_C_GATEWAY_IP)
		{
			memset(ip, 0, sizeof(uint32_t) * 4);
			status = SusiBoardGetValue(id, ip);
			if (status == SUSI_STATUS_SUCCESS)
				printf("   %-30s: %d.%d.%d.%d\n", funcRoStr[i], ip[0], ip[1], ip[2], ip[3]);
			else
				printf("   %-30s: get 0x%08X failed. (0x%08X)\n", funcRoStr[i], id, status);
		}
		else if (id == SUSI_ID_NETWORK_ERROR_CODE)
		{
			status = SusiBoardGetValue(id, &getVal);
			if (status == SUSI_STATUS_SUCCESS)
				printf("   %-30s: 0x%X\n", funcRoStr[i], getVal);
			else
				printf("   %-30s: get 0x%08X failed. (0x%08X)\n", funcRoStr[i], id, status);
		}
		else if(id == SUSI_ID_NETWORK_SERVER_TYPE)
		{
			status = SusiBoardGetValue(id, &getVal);
			if (status == SUSI_STATUS_SUCCESS)
			{
				for (j = 0; j < 3; j++)
				{
					if (networkServerTypeStr[j].contorl == getVal)
					{
						printf("   %-30s: %s\n", funcRoStr[i], networkServerTypeStr[j].Descriptions);
						break;
					}
				}
			}
			else
				printf("   %-30s: get 0x%08X failed. (0x%08X)\n", funcRoStr[i], id, status);
		}
		else if (id == SUSI_ID_NETWORK_SERVER_DOMAIN_NAME)
		{
			status = SusiBoardGetValue(id, domainName);
			if (status == SUSI_STATUS_SUCCESS)
			{
				getStr(domainName, str);
				printf("   %-30s: %s\n", funcRoStr[i], str);
			}
			else
				printf("   %-30s: get server domain name failed. (0x%08X)\n", funcRoStr[i], status);
		}
		else if (id == SUSI_ID_NETWORK_SERVER_IP_PORT)
		{
			status = SusiBoardGetValue(id, ipport);
			if (status == SUSI_STATUS_SUCCESS)
				printf("   %-30s: %d.%d.%d.%d:%d\n", funcRoStr[i], ipport[0], ipport[1], ipport[2], ipport[3], ipport[4]);
			else
				printf("   %-30s: get server ip/port failed. (0x%08X)\n", funcRoStr[i], status);
		}
		else
			printf("Unknown SUSI ID: 0x%08X\n", id);
	}
	printf("\nEnter your choice: ");
	fflush(stdout);
}

void network_main(void)
{
	uint32_t op;

	while (1)
	{
		clr_screen();
		network_title();
		menu();
		if (input_uint(&op, 10, NELEMS(functions) - 1, 0))
			goto unknown;

		switch (functions[op])
		{
		case SUSIDEMO_FUNCTIONS_GOBACK:
			goto exit;
		case funcNetwrokControl:
			network_control();
			goto pause;
		case funcNetwrokStatus:
			network_status();
			goto pause;
		case funcNetworkHostName:
			network_hostname();
			goto pause;
		case funcNetworkMacAddr:
			network_macaddr();
			goto pause;
		case funcNetworkMDeviceIP:
			network_ipaddr(SUSI_ID_NETWORK_M_DEVICE_IP);
			goto pause;
		case funcNetworkMSubMask:
			network_ipaddr(SUSI_ID_NETWORK_M_SUB_MASK);
			goto pause;
		case funcNetworkMDomainNameServerIP:
			network_ipaddr(SUSI_ID_NETWORK_M_DOMAIN_NAME_SERVER_IP);
			goto pause;
		case funcNetworkMGatewayIP:
			network_ipaddr(SUSI_ID_NETWORK_M_GATEWAY_IP);
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
}

#include "OsDeclarations.h"
#include "SusiIoT.h"
#include "SusiIoTAPI.h"
#include <stdlib.h>
#include <sstream>  // 需要包含sstream

void SUSI_IOT_API EventCallBack(SusiIoTId_t id, char *jsonstr)
{
    printf("EventCallBack\nId:0x%d\nData:%s\n", id, jsonstr);
}



int main(int argc, char **argv)
{
    
    SusiIoTStatus_t status;
    status = SusiIoTInitialize();
    SusiIoTSetPFEventHandler(EventCallBack);
    const char *buffer = NULL;
    char jsonToStringResult[1100];

    json_t *jsonObject = json_object();
    sprintf(jsonToStringResult,"%s", jsonObject);
    printf("FFFFFFFF %s\n", jsonToStringResult);
    
    if(SusiIoTGetPFCapability(jsonObject) != 0)
    {
        printf("\nSusiIoTGetPFCapability failed. \n");
    }
    else
    {
        buffer = json_dumps(jsonObject, JSON_INDENT(4) | JSON_PRESERVE_ORDER | JSON_REAL_PRECISION(10));
        printf("%s\n", buffer);
        sprintf(jsonToStringResult,"%s", buffer);
        printf("%s\n", jsonToStringResult);

        printf("KKKKKKKKKK\n");
        buffer = SusiIoTGetPFDataString(353697792);
        printf("%s\n", buffer);

    }
    if (buffer != NULL)
    {
        SusiIoTMemFree((void *)buffer);
        buffer = NULL;
    }
    return status;
}
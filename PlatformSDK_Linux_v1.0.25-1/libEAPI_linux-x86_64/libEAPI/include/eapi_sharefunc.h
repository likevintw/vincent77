
#ifndef _EAPI_SHAREFUNC_H_
#define _EAPI_SHAREFUNC_H_
//buffer size: 0x80
char* EApiStatus_StringTranslator(EApiStatus_t status, char *Outputbuffer)
{
        if(NULL == Outputbuffer) return NULL;
        switch(status)
        {
                case EAPI_STATUS_NOT_INITIALIZED   :
                        sprintf(Outputbuffer, "Library is not initialized");
                        break;
                case EAPI_STATUS_INITIALIZED       :
                        sprintf(Outputbuffer, "Library has been initialized");
                        break;
                case EAPI_STATUS_ALLOC_ERROR       :
                        sprintf(Outputbuffer, "Memory allocation failed");
                        break;
                case EAPI_STATUS_DRIVER_TIMEOUT    :
                        sprintf(Outputbuffer, "Time out in driver");
                        break;
                case EAPI_STATUS_INVALID_PARAMETER :
                        sprintf(Outputbuffer, "Invalid parameter");
                        break;
                case EAPI_STATUS_INVALID_BLOCK_ALIGNMENT :
                        sprintf(Outputbuffer, "Incorrect block alignment");
                        break;
                case EAPI_STATUS_INVALID_BLOCK_LENGTH    :
                        sprintf(Outputbuffer, "Invalid block length");
                        break;
                case EAPI_STATUS_INVALID_DIRECTION       :
                        sprintf(Outputbuffer, "Invalid direction");
                        break;
                case EAPI_STATUS_INVALID_BITMASK         :
                        sprintf(Outputbuffer, "Invalid bitmask");
                        break;
                case EAPI_STATUS_RUNNING                 :
                        sprintf(Outputbuffer, "Already running");
                        break;
                case EAPI_STATUS_UNSUPPORTED       :
                        sprintf(Outputbuffer, "Unsupported");
                        break;
                case EAPI_STATUS_NOT_FOUND         :
                        sprintf(Outputbuffer, "Not found");
                        break;
                case EAPI_STATUS_TIMEOUT           :
                        sprintf(Outputbuffer, "Timeout");
                        break;
                case EAPI_STATUS_BUSY_COLLISION    :
                        sprintf(Outputbuffer, "Watchdog device is busy");
                        break;
                case EAPI_STATUS_READ_ERROR        :
                        sprintf(Outputbuffer, "Read error");
                        break;
                case EAPI_STATUS_WRITE_ERROR       :
                        sprintf(Outputbuffer, "Write error");
                        break;
                case EAPI_STATUS_MORE_DATA         :
                        sprintf(Outputbuffer, "Need larger buffer");
                        break;
                case EAPI_STATUS_GET_STATUS_ERROR  :
                        sprintf(Outputbuffer, "Failed to get ETP lock status");
                        break;
                case EAPI_STATUS_LOCKED            :
                        sprintf(Outputbuffer, "Current ETP was locked  (read only)");
                        break;
                case EAPI_STATUS_ERROR             :
                        sprintf(Outputbuffer, "Generic error");
                        break;
                case EAPI_STATUS_SUCCESS           :
                        sprintf(Outputbuffer, "Success");
                        break;
        }
        return Outputbuffer;
}

#endif

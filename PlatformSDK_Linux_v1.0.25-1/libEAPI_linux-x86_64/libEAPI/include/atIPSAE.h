#ifndef _ATIPSAE_H_
#define _ATIPSAE_H_

#include <string>
#include "EApi.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;

namespace EApiCommon
{
	enum CallBackType
	{
		EMERGENCY = 0,
		INFOMATION,
	};
	
	struct ipsaeInfo {
		string fwversion;
		string ips;
		string dcin;
		string battery;
		string inputlostdelay;
		string cutoffdelay;
		string batterylife;
		string batteryvoltage;
		string maxtemperature;
		string temperature;
		string capacity;
	};

	class IatCallBack {
	public:
		virtual void atCallBack(CallBackType type, string str) = 0;
	};
	
	class IatIPSAE {
	public:
		virtual string getVersion() = 0;
		virtual string getDevVersion() = 0;
		virtual void getIPSAEInfo(struct ipsaeInfo *info) = 0;
		virtual bool getSerialStatus() = 0;
		virtual void setCallBack(IatCallBack *_cbobj) = 0;
		virtual string setDCinLostDelayTime(int sec) = 0;
		virtual string setDCoutCutOffDelayTime(int minute) = 0;
	};
}

EApiStatus_t EApiUPSGetDevice(EApiCommon::IatIPSAE **device, string port, EApiCommon::IatCallBack *_cbobj);
EApiStatus_t EApiUPSDelDevice();

#ifdef __cplusplus
}
#endif

#endif /* _ATIPSAE_H_ */

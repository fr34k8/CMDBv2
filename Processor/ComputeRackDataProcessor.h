#pragma once
#include "ComputeDataProcessor.h"

class CDeviceModel;
class CRackBayChassisModel;
class CRackSwitchChassisModel;
typedef vector<CDeviceModel*> DeviceModelArray;
typedef vector<CRackBayChassisModel*> RackBayChassisModelArray;
typedef vector<CRackSwitchChassisModel*> RackSwitchChassisModelArray;
typedef map<string, DeviceModelArray*> RackName2DeviceArrayMap;
typedef map<string, RackBayChassisModelArray*> IP2CRackBayChassisArrayMap;
typedef map<string, RackSwitchChassisModelArray*> IP2CRackSwitchChassisArrayMap;
class CComputeRackDataProcessor :
	public CComputeDataProcessor
{
public:
	CComputeRackDataProcessor(const string& strCfgFile);
	~CComputeRackDataProcessor(void);
protected:
	bool Connect();
	bool LoadData();
	void ComputeData();
	bool LoadServerInfo();
	bool LoadChassisInfo();
	bool LoadAggregationSwitchInfo();
	bool LoadAccessSwitchInfo();
	bool LoadCoreSwitchInfo();
	bool LoadPDUInfo();
	void PrepareData(BSONObj boDeviceInfo, int iCIType);
	void DestroyData();	
	void CalculateAvailableU(string strMapKey, DeviceModelArray* pDeviceModelArray);
private:
	CDeviceModel* CreateRackServerModel(BSONObj boCIInfo);
	CDeviceModel* CreateRackSwitchModel(BSONObj boCIInfo);
	CDeviceModel* CreateDeviceModel(BSONObj boCIInfo, int iCIType);
protected:	
	RackName2DeviceArrayMap m_mapRackName2DeviceArray;
	IP2CRackBayChassisArrayMap m_mapIP2CRackBayChassisArray;
	IP2CRackSwitchChassisArrayMap m_mapIP2RackSwitchChassisArray;
};

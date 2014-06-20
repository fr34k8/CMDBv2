#pragma once
#include "DeviceModel.h"

class CRackSwitchChassisModel :
	public CDeviceModel
{
public:
	CRackSwitchChassisModel(void);
	~CRackSwitchChassisModel(void);

	void Load(const BSONObj& boRecord);
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
private:
	string m_strSwitchSerial;
	string m_strSwitchName;
};
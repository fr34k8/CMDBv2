#pragma once
#include "DeviceModel.h"

class CRackSwitchModel:
	public CDeviceModel
{
public:
	CRackSwitchModel(void);
	~CRackSwitchModel(void);	

	operator int();
	operator string();
	CMongodbModel& operator=(int iValue);
	CMongodbModel& operator=(string strValue);

	void Load(const BSONObj& boSwitchInfo);
	void BuildArrayVlan(map<int, bool> &mapArrayVlan, BSONArrayBuilder &babArrayVlan);
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
private:			
	string m_strSwitchName;
	string m_strSwitchSerial;
	string m_strSwitchModel;
	BSONObj m_boSwitchInfo;
};
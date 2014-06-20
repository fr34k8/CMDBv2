#pragma once
#include "DeviceModel.h"

class CRackBayChassisModel:
	public CDeviceModel
{
public:
	CRackBayChassisModel(void);
	~CRackBayChassisModel(void);

	operator int();
	operator string();
	CMongodbModel& operator=(int iValue);
	CMongodbModel& operator=(string strValue);

	void Load(const BSONObj& boRecord);
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
private:
	int m_nBayId;
	string m_strServerSerial;
	string m_strServerName;
	string m_strProductAlias;
	string m_strProductCode;
};
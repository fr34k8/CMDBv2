#pragma once
#include "DeviceModel.h"

class CRackServerUModel:
	public CDeviceModel
{
public:
	CRackServerUModel(void);
	~CRackServerUModel(void);

	operator int();
	operator string();
	CMongodbModel& operator=(int iValue);
	CMongodbModel& operator=(string strValue);	

	void Load(const BSONObj& boRecord);
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
protected:	
	string m_strServerSerial;
	string m_strServerName;
	string m_strProductAlias;
	string m_strProductCode;
};
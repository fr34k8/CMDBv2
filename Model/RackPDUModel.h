#pragma once
#include "DeviceModel.h"

class CRackPDUModel :
	public CDeviceModel
{
public:
	CRackPDUModel(void);
	~CRackPDUModel(void);

	void Load(const BSONObj& boPDUInfo);
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
protected:
	double	m_dAmpe;
	string	m_strName;
	string	m_strUnit;
	string	m_strPMM;
};

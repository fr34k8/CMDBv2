#pragma once
#include "DeviceModel.h"

#define FIELD_VLAN_INFO "vlan_info"
class CAccessSwitchModel :
	public CDeviceModel
{
public:
	CAccessSwitchModel(void);
	virtual ~CAccessSwitchModel(void);

	operator BSONArray();
	CMongodbModel& operator=(BSONArray boValue);

	void AllowVlan2VlanInfo(string strAllowVlan);
protected:
	void VlanRange2VlanInfo(int nStartVlan, int nEndVlan, BSONArrayBuilder& arrBuilderVlanInfo);
protected:
	BSONArray m_barrVlanInfo;
};
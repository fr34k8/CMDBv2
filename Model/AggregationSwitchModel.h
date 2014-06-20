#pragma once
#include "DeviceModel.h"

#define FIELD_RACK_INFO "rack_info"
#define FIELD_ACC_RACK "acc_rack"

class CAggregationSwitchModel :
	public CDeviceModel
{
public:
	CAggregationSwitchModel(void);
	virtual ~CAggregationSwitchModel(void);

	operator BSONArray();
	CMongodbModel& operator=(BSONArray boValue);
	void AccessRack2RackInfo(string strAccessRack);
protected:
	BSONArray m_barrRackInfo;
};
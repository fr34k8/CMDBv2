#pragma once
#include "DeviceModel.h"

class CChassisModel :
	public CDeviceModel
{
public:
	CChassisModel(void);
	virtual ~CChassisModel(void);

	static string GetIPAddress(BSONObj boCIInfo);
	static string GetModel(BSONObj boCIInfo); 
	static int GetFloor(BSONObj boCIInfo);
};
#pragma once
#include "DeviceModel.h"

class CRowServerU;

class CRowModel :
	public CDeviceModel
{
public:
	CRowModel(void);
	~CRowModel(void);

	bool GetRackQuery(Query &queryRack, BSONObj boRowRecord);
};
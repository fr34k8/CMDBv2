#pragma once
#include "UpdateCIUSpaceProcessor.h"

class CUpdateChassisUSpaceProcessor : public CUpdateCIUSpaceProcessor
{
public:
	CUpdateChassisUSpaceProcessor(const string& strFileName);
	virtual ~CUpdateChassisUSpaceProcessor(void);
protected:
	bool Connect();
	auto_ptr<DBClientCursor> LoadMapDB();
};
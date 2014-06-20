#pragma once
#include "UpdateCIUSpaceProcessor.h"

class CUpdateServerUSpaceProcessor : public CUpdateCIUSpaceProcessor
{
public:
	CUpdateServerUSpaceProcessor(const string& strFileName);
	virtual ~CUpdateServerUSpaceProcessor(void);
protected:
	bool Connect();
	auto_ptr<DBClientCursor> LoadDB();
	int CalculateUSpace(BSONObj boRecord);
};
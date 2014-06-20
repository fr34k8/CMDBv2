#pragma once
#include "CIInfoMappingProcessor.h"

class CServerInfoMappingProcessor : public CCIInfoMappingProcessor
{
public:
	CServerInfoMappingProcessor(const string& strFileName);
	virtual ~CServerInfoMappingProcessor(void);
protected:
	bool Connect();
	auto_ptr<DBClientCursor> LoadDB();
};
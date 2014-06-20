#pragma once
#include "UpdateCIUSpaceProcessor.h"

class CUpdateCoreSwitchUSpaceProcessor : public CUpdateCIUSpaceProcessor
{
public:
	CUpdateCoreSwitchUSpaceProcessor(const string& strFileName);
	virtual ~CUpdateCoreSwitchUSpaceProcessor(void);
protected:
	bool Connect();
};
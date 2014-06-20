#pragma once
#include "UpdateCIUSpaceProcessor.h"

class CUpdateAccessSwitchUSpaceProcessor : public CUpdateCIUSpaceProcessor
{
public:
	CUpdateAccessSwitchUSpaceProcessor(const string& strFileName);
	virtual ~CUpdateAccessSwitchUSpaceProcessor(void);
protected:
	bool Connect();
};
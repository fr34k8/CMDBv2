#pragma once
#include "Processor.h"

class CZabbixAPIController;
class CZabbixAPIProcessor :
	public CProcessor
{
public:
	CZabbixAPIProcessor(const string& strFileName);
	virtual ~CZabbixAPIProcessor(void);
protected:
	CZabbixAPIController* m_pZabbixAPIController;
};

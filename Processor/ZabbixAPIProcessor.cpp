#include "ZabbixAPIProcessor.h"
#include "../Controller/ZabbixAPIController.h"

CZabbixAPIProcessor::CZabbixAPIProcessor(const string& strFileName)
:CProcessor(strFileName)
{
	m_pZabbixAPIController = new CZabbixAPIController();
}

CZabbixAPIProcessor::~CZabbixAPIProcessor(void)
{
	if (NULL != m_pZabbixAPIController)
	{
		delete m_pZabbixAPIController;
	}
}

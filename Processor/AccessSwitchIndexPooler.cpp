#include "AccessSwitchIndexPooler.h"
#include "../Controller/AccessSwitchInfoIndexController.h"

CAccessSwitchIndexPooler::CAccessSwitchIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CAccessSwitchInfoIndexController();
}

CAccessSwitchIndexPooler::~CAccessSwitchIndexPooler(void)
{
}

#include "CoreSwitchIndexPooler.h"
#include "../Controller/CoreSwitchInfoIndexController.h"

CCoreSwitchIndexPooler::CCoreSwitchIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CCoreSwitchInfoIndexController();
}

CCoreSwitchIndexPooler::~CCoreSwitchIndexPooler(void)
{
}

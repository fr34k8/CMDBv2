#include "ChassisIndexPooler.h"
#include "../Controller/ChassisInfoIndexController.h"

CChassisIndexPooler::CChassisIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CChassisInfoIndexController();
}

CChassisIndexPooler::~CChassisIndexPooler(void)
{
}

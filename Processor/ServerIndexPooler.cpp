#include "ServerIndexPooler.h"
#include "../Model/CIInfoIndexModel.h"
#include "../Controller/CIInfoIndexController.h"
#include "../Controller/ServerInfoIndexController.h"
#include "../Controller/CIInfoChangeController.h"
#include "../Controller/ServerInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CServerIndexPooler::CServerIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CServerInfoIndexController();
}

CServerIndexPooler::~CServerIndexPooler(void)
{
}
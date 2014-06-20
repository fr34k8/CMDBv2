#include "PeerLinkIndexPooler.h"
#include "../Controller/PeerLinkInfoIndexController.h"

CPeerLinkIndexPooler::CPeerLinkIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CPeerLinkInfoIndexController();
}

CPeerLinkIndexPooler::~CPeerLinkIndexPooler(void)
{
}

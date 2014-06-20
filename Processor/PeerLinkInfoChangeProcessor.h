#pragma once
#include "CIInfoChangeProcessor.h"

class CPeerLinkInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CPeerLinkInfoChangeProcessor(const string& strCfgFile);
	~CPeerLinkInfoChangeProcessor(void);
};

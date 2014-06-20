#pragma once
#include "CIInfoChangeProcessor.h"

class CRackInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CRackInfoChangeProcessor(const string& strCfgFile);
	~CRackInfoChangeProcessor(void);
};

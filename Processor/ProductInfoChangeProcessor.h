#pragma once
#include "CIInfoChangeProcessor.h"

class CProductInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CProductInfoChangeProcessor(const string& strCfgFile);
	~CProductInfoChangeProcessor(void);
};

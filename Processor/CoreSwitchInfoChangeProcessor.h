#pragma once
#include "CIInfoChangeProcessor.h"

class CCoreSwitchInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CCoreSwitchInfoChangeProcessor(const string& strCfgFile);
	~CCoreSwitchInfoChangeProcessor(void);
};

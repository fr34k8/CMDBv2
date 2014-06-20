#pragma once
#include "CIInfoChangeProcessor.h"

class CAccessSwitchInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CAccessSwitchInfoChangeProcessor(const string& strCfgFile);
	~CAccessSwitchInfoChangeProcessor(void);
};

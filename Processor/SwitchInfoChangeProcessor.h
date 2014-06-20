#pragma once
#include "CIInfoChangeProcessor.h"

class CSwitchInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CSwitchInfoChangeProcessor(const string& strCfgFile);
	~CSwitchInfoChangeProcessor(void);
};

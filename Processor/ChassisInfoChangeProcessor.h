#pragma once
#include "CIInfoChangeProcessor.h"

class CChassisInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CChassisInfoChangeProcessor(const string& strCfgFile);
	~CChassisInfoChangeProcessor(void);
};

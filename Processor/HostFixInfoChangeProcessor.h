#pragma once
#include "CIInfoChangeProcessor.h"

class CHostFixInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CHostFixInfoChangeProcessor(const string& strCfgFile);
	~CHostFixInfoChangeProcessor(void);
};

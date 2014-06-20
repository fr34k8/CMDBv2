#pragma once
#include "CIInfoChangeProcessor.h"

class CPMMInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CPMMInfoChangeProcessor(const string& strCfgFile);
	~CPMMInfoChangeProcessor(void);
};

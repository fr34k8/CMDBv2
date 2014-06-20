#pragma once
#include "CIInfoChangeProcessor.h"

class CPDUInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CPDUInfoChangeProcessor(const string& strCfgFile);
	~CPDUInfoChangeProcessor(void);
};

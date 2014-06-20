#pragma once
#include "CIInfoChangeProcessor.h"

class CRowInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CRowInfoChangeProcessor(const string& strCfgFile);
	~CRowInfoChangeProcessor(void);
};

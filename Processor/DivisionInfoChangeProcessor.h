#pragma once
#include "CIInfoChangeProcessor.h"

class CDivisionInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CDivisionInfoChangeProcessor(const string& strCfgFile);
	~CDivisionInfoChangeProcessor(void);
};

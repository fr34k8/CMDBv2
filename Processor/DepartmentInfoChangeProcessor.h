#pragma once
#include "CIInfoChangeProcessor.h"

class CDepartmentInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CDepartmentInfoChangeProcessor(const string& strCfgFile);
	~CDepartmentInfoChangeProcessor(void);
};

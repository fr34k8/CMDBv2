#pragma once
#include "CIInfoChangeProcessor.h"

class CAggregationSwitchInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CAggregationSwitchInfoChangeProcessor(const string& strCfgFile);
	~CAggregationSwitchInfoChangeProcessor(void);
};

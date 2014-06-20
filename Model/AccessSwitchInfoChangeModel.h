#pragma once
#include "CIInfoChangeModel.h"

class CAccessSwitchInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CAccessSwitchInfoChangeModel(void);
	~CAccessSwitchInfoChangeModel(void);
	void InitLookUpByPass();
};

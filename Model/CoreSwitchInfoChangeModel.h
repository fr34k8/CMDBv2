#pragma once
#include "CIInfoChangeModel.h"

class CCoreSwitchInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CCoreSwitchInfoChangeModel(void);
	~CCoreSwitchInfoChangeModel(void);
	void InitLookUpByPass();
};

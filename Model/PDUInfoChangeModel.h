#pragma once
#include "CIInfoChangeModel.h"

class CPDUInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CPDUInfoChangeModel(void);
	~CPDUInfoChangeModel(void);
	void InitLookUpByPass();
};

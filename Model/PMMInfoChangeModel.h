#pragma once
#include "CIInfoChangeModel.h"

class CPMMInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CPMMInfoChangeModel(void);
	~CPMMInfoChangeModel(void);
	void InitLookUpByPass();
};

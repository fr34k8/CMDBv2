#pragma once
#include "CIInfoChangeModel.h"

class CProductInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CProductInfoChangeModel(void);
	~CProductInfoChangeModel(void);
protected:
	void InitLookUpFieldValue();
	void InitLookUpByPass();
};

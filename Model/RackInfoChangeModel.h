#pragma once
#include "CIInfoChangeModel.h"

class CRackInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CRackInfoChangeModel(void);
	~CRackInfoChangeModel(void);
protected:
	void InitLookUpByPass();
};

#pragma once
#include "CIInfoChangeModel.h"

class CDivisionInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CDivisionInfoChangeModel(void);
	~CDivisionInfoChangeModel(void);
protected:
	void InitLookUpFieldValue();
	void InitLookUpByPass();
};

#pragma once
#include "CIInfoChangeModel.h"

class CDepartmentInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CDepartmentInfoChangeModel(void);
	~CDepartmentInfoChangeModel(void);
protected:
	void InitLookUpFieldValue();
	void InitLookUpByPass();
};

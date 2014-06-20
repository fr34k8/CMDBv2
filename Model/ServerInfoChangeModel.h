#pragma once
#include "CIInfoChangeModel.h"

class CServerInfoChangeModel:
	public CCIInfoChangeModel
{
public:
	CServerInfoChangeModel(void);
	~CServerInfoChangeModel(void);
protected:
	void InitLookUpFieldValue();
	void InitLookUpByPass();
};
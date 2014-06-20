#pragma once
#include "CIInfoIndexController.h"

class CRackInfoIndexController :
	public CCIInfoIndexController
{
public:
	CRackInfoIndexController(void);
	~CRackInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};

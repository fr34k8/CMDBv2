#pragma once
#include "CIInfoIndexController.h"

class CPDUInfoIndexController :
	public CCIInfoIndexController
{
public:
	CPDUInfoIndexController(void);
	~CPDUInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};

#pragma once
#include "CIInfoIndexController.h"

class CPMMInfoIndexController :
	public CCIInfoIndexController
{
public:
	CPMMInfoIndexController(void);
	~CPMMInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};

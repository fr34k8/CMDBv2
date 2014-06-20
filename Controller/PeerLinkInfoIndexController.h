#pragma once
#include "CIInfoIndexController.h"

class CPeerLinkInfoIndexController :
	public CCIInfoIndexController
{
public:
	CPeerLinkInfoIndexController(void);
	~CPeerLinkInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};

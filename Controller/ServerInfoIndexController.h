#pragma once
#include "CIInfoIndexController.h"

class CServerInfoIndexController :
	public CCIInfoIndexController
{
public:
	CServerInfoIndexController(void);
	~CServerInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};

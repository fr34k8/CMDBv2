#pragma once
#include "CMDBController.h"

class CCIInfoIndexController : public CCMDBController
{
public:
	CCIInfoIndexController(void);
	~CCIInfoIndexController(void);
	virtual bool RemoveInfoChange(Query queryRemoveCondition) = 0;
};

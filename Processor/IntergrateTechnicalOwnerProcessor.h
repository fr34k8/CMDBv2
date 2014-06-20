#pragma once
#include "Processor.h"

class CPhysicalServerNotificationController;
class CIntergrateTechnicalOwnerProcessor : public CProcessor
{
public:
	CIntergrateTechnicalOwnerProcessor(const string& strCfgFile);
	virtual ~CIntergrateTechnicalOwnerProcessor(void);

	void Proceed();

protected:
	CPhysicalServerNotificationController *m_pNotificationController;
	bool Connect();
};

#pragma once
#include "Processor.h"

class CCMDBController;
class CDeviceModel;
class CCIInfoMappingProcessor : public CProcessor
{
public:
	CCIInfoMappingProcessor(const string& strFileName);
	virtual ~CCIInfoMappingProcessor(void);
	bool Proceed();
protected:
	bool ProceedData();
	virtual auto_ptr<DBClientCursor> LoadDB();
	virtual bool Connect() = 0;
	virtual BSONObj CreateMapping(BSONObj boRecord);
	CCMDBController *m_pCIController;
	CDeviceModel *m_pCIModel;
};
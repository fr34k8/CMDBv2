#pragma once
#include "Processor.h"

class CCMDBController;
class CCIInfoChangeController;
class CCIInfoChangeModel;
class CCIInfoChangeProcessor: public CProcessor
{
public:
	CCIInfoChangeProcessor(const string& strFileName);
	virtual ~CCIInfoChangeProcessor(void);
	bool ProceedMining();
protected:
	virtual auto_ptr<DBClientCursor> LoadDB();
	virtual bool ProceedMiningRecord(BSONObj &boCurrRecord);	
	virtual bool Connect();
	CCMDBController *m_pCIController;
	CCIInfoChangeController *m_pCIInfoChangeController;
	CCIInfoChangeModel *m_pCIInfoChangeModel;
};
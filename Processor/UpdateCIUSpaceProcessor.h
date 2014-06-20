#pragma once
#include "Processor.h"

class CCMDBController;
class CUpdateCIUSpaceProcessor : public CProcessor
{
public:
	CUpdateCIUSpaceProcessor(const string& strFileName);
	virtual ~CUpdateCIUSpaceProcessor(void);
	bool Proceed();
protected:
	bool ProceedData();
	virtual auto_ptr<DBClientCursor> LoadDB();
	virtual auto_ptr<DBClientCursor> LoadMapDB();
	virtual bool PrepareCISpace();
	virtual bool Connect() = 0;
	virtual int CalculateUSpace(BSONObj boRecord);
	CCMDBController *m_pCIController;
	map<string, int> m_mapModel2Space;
};
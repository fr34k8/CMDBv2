#pragma once
#include "ComputeDataProcessor.h"

class CRackController;
class CComputeRowDataProcessor :
	public CComputeDataProcessor
{
public:
	CComputeRowDataProcessor(const string& strCfgFile);
	~CComputeRowDataProcessor(void);
protected:
	bool Connect();
	bool LoadData();
	void ComputeData(); 
protected:
	auto_ptr<DBClientCursor> m_ptrCursor;
	CRackController* m_pRackController;
};

#pragma once
#include "Processor.h"
#include "../Model/CIInfoIndexModel.h"

class CCIIndexPoolerModel;
class CCIInfoChangeController;
typedef vector<CCIInfoIndexModel*> CIInfoIndexModelArray; // vector pointer of Inverted Index model
typedef void* (*StartPoolerFunc)(void *); // define type for function
class CCIInfoIndexProcessor: public CProcessor
{
public:
	CCIInfoIndexProcessor(const string& strFileName);
	virtual ~CCIInfoIndexProcessor(void);
	virtual void ProceedInfoIndex();

protected:
	virtual void Init(const string& strCfgFile){};
	virtual void Destroy(){};
	virtual bool Connect();

	bool LoadDB(auto_ptr<DBClientCursor> &ptrResultCursor);
	vector<CCIIndexPoolerModel*> PrepareIndexing(auto_ptr<DBClientCursor>&);
	int ComputePoolerIndex(int *, map<BSONElement, int> *, BSONElement, int);
	virtual void LaunchMultiPoolers(vector<CCIIndexPoolerModel*>);
	void DestroyData(vector<CCIIndexPoolerModel*>& arrCIInfoIndexModelArray);
	int CalculatePoolerNumber();

protected:
	int m_nInfoIndexPooler;
	string m_strCfgFile;
	CCIInfoChangeController *m_pCIInfoChangeController;
	StartPoolerFunc m_pFuncStartPoller; 
	long long m_nRecordCount;
};

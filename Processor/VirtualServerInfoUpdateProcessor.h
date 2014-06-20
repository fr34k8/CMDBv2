#pragma once
#include "CIInfoUpdateProcessor.h"

class CComputeServerDataProcessor;

class CVirtualServerInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CVirtualServerInfoUpdateProcessor(const string& strCfgFile);
	~CVirtualServerInfoUpdateProcessor(void);
	bool Connect();
protected:
/*****************************************
*Author: DuyMN
******************************************/
	bool CanComputeData() { return true; }
	void InsertSpecialDataInfo(BSONObj boNewCIInfo);
	void UpdateSpecialDataInfo(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);

/*****************************************
*Author: DuyMN
******************************************/
protected:
	CComputeServerDataProcessor *m_pComputeServerDataProcessor;
//******************************************
};
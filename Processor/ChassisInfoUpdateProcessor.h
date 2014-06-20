#pragma once
#include "CIInfoUpdateProcessor.h"

class CChassisInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CChassisInfoUpdateProcessor(const string& strCfgFile);
	~CChassisInfoUpdateProcessor(void);
protected:
	bool CanComputeData() { return true; }
	void InsertData(BSONObj boNewCIInfo);
	void DeleteData(BSONObj boNewCIInfo);
	void UpdateData(BSONObj boOldCIInfo, BSONObj boChangedData, BSONObj boChangedFields);
};
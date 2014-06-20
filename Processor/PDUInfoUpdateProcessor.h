#pragma once
#include "CIInfoUpdateProcessor.h"

class CRackController;

class CPDUInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CPDUInfoUpdateProcessor(const string& strCfgFile);
	~CPDUInfoUpdateProcessor(void);
	bool Connect();
protected:
	bool CanComputeData() { return true; }	
	void InsertData(BSONObj boNewCIInfo);
	void DeleteData(BSONObj boNewCIInfo);
	void UpdateData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
/*****************************************
*Author: DuyMN
******************************************/
protected:
	CRackController *m_pRackController;
private:
	void InsertPDUGraphicData(BSONObj boNewCIInfo);
	void DeletePDUGraphicData(BSONObj boNewCIInfo);
	void UpdatePDUGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
//******************************************
};
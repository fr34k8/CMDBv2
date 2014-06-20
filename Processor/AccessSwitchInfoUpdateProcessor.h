#pragma once
#include "CIInfoUpdateProcessor.h"

class CRackController;
class CRackModel;

class CAccessSwitchInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CAccessSwitchInfoUpdateProcessor(const string& strCfgFile);
	~CAccessSwitchInfoUpdateProcessor(void);
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
	CRackModel *m_pRackModel;
private:
	void InsertSwitchUGraphicData(BSONObj boNewCIInfo);
	void DeleteSwitchUGraphicData(BSONObj boNewCIInfo);
	void UpdateSwitchUGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
	
	void InsertSwitchChassisGraphicData(BSONObj boNewCIInfo);
	void DeleteSwitchChassisGraphicData(BSONObj boNewCIInfo);
	void UpdateSwitchChassisGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
	//******************************************
};
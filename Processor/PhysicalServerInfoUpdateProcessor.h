#pragma once
#include "CIInfoUpdateProcessor.h"

class CRackController;
class CRackModel;
class CComputeServerDataProcessor;

class CPhysicalServerInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CPhysicalServerInfoUpdateProcessor(const string&);
	~CPhysicalServerInfoUpdateProcessor(void);
	
	bool Connect();
protected:
	bool CreateMailNotification(int iActionType, BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
	bool CanComputeData() { return true; }	
	void InsertData(BSONObj boNewCIInfo);
	void DeleteData(BSONObj boNewCIInfo);
	void UpdateData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
	
	void InsertSpecialDataInfo(BSONObj boNewCIInfo);
	void UpdateSpecialDataInfo(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
	BSONArray TrackChangeInterface(BSONElement beOldInterface, BSONElement beNewInterface, BSONElement beClock);
private:
	bool NotifyServerLocation(int iActionType, BSONObj boNewCIInfo, BSONObj boChangedFields);
	bool NotifyServerInterface(int iActionType, BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields);
	void InsertServerUGraphicData(BSONObj boNewCIInfo);
	void DeleteServerUGraphicData(BSONObj boNewCIInfo);
	void UpdateServerUGraphicData(BSONObj boOldCIInfo, BSONObj boChangedData, BSONObj boChangedFields);
	void InsertServerChassisGraphicData(BSONObj boNewCIInfo);
	void DeleteServerChassisGraphicData(BSONObj boNewCIInfo);
	void UpdateServerChassisGraphicData(BSONObj boOldCIInfo, BSONObj boChangedData, BSONObj boChangedFields);
	void BuildNetworkInfo(map<string, BSONArrayBuilder*> &map_strbabNetWork, vector<BSONElement> vbeNetwork, BSONElement beClock, string strType = "");

/*****************************************
*Author: DuyMN
******************************************/
protected:
	CRackController *m_pRackController;
	CRackModel *m_pRackModel;
	CComputeServerDataProcessor *m_pComputeServerDataProcessor;
//******************************************
};
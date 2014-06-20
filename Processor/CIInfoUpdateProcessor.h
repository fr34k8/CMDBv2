#pragma once
#include "Processor.h"

class CCMDBController;
class CCIInfoUpdateController;
class CCIInfoChangeController;
class CCIHistoryLogController;
class CNotificationController;
class CPartnerInfoController;
class CMailboxController;
class CCIInfoChangeModel;
class CCIHistoryLogModel;
class CNotificationModel;
class CMongodbModel;

struct CIRelation
{
	string strRelatedCI;
	string strTmpCICollection;
	string strRelatedField;
	string strForeignKeyField;
};
typedef map<string,MongodbModelArray*> mapKey2BSONObjArrayPtr;
typedef map<string,CMongodbModel*> mapKey2BSONObjPtr;
typedef map<string,vector<CIRelation> > mapField2BSONElementArray;

class CCIInfoUpdateProcessor: public CProcessor
{
public:
	CCIInfoUpdateProcessor(const string& strFileName);
	virtual ~CCIInfoUpdateProcessor(void);

	bool ProceedUpdateCIInfo();

protected:
	auto_ptr<DBClientCursor> LoadNewCIInfo();
	auto_ptr<DBClientCursor> LoadCIRelationship();
	void PrepareUpdating(auto_ptr<DBClientCursor> &ptrInfoUpdateCursor);
	void PrepareCIRelationshipInfo(auto_ptr<DBClientCursor> &ptrCIRelationshipCursor);
	bool GetCurrentCIInfo(auto_ptr<DBClientCursor> &ptrCIInfoCursor);
	void ETLNotification(auto_ptr<DBClientCursor> &ptrCIInfoCursor);
	bool LaunchUpdateProcess();
	bool TrackChangedCIInfo(BSONElement beObjID, BSONObj boOldCIInfo, 
							BSONObj boNewCIInfo);
	bool InsertHistoryLog(BSONElement beObjID, BSONObj boOldCIInfo, BSONObj boNewCIInfo);
	bool UpdateCIInfo(string strKey, BSONObj bsCIInfo);
	bool DeleteTmpCIInfo(BSONElement beId);

	auto_ptr<DBClientCursor> GetRelatedCIInfo(string strTable, BSONObj boCondition);

	BSONObj RemoveRedundantFields(BSONObj pCIInfo);
		
	virtual bool Connect();
	bool CreateNotificationData(int iActionType, BSONObj boNotificationData,
										BSONObj boChangedFields);

	virtual bool ProcessUpdateRelatedCI(BSONObj boOldCIInfo, BSONObj boChangedData,
		BSONObj boChangedFields);

	virtual bool CanComputeData() { return false; }
	void ComputeData(int iActionType, BSONObj boOldCIInfo, 
							BSONObj boNewCIInfo, BSONObj boChangedFields);

	virtual void InsertData(BSONObj boNewCIInfo) {}
	virtual void DeleteData(BSONObj boNewCIInfo) {}
	virtual void UpdateData(BSONObj boOldCIInfo, BSONObj boChangedData, BSONObj boChangedFields) {}
	
	/*************************************
	* UpdateSpecialInfo
	* DuyMN
	**************************************/
	virtual void InsertSpecialDataInfo(BSONObj boNewCIInfo){}
	virtual void UpdateSpecialDataInfo(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields){}

	void DestroyMapData();

	virtual bool CreateMailNotification(int iActionType, BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields) { };
protected:
	bool m_bIsNotification;
	bool m_bIsMailNotification;
	int m_nCIType;

	mapKey2BSONObjArrayPtr m_mapKey2NewCIInfoArray;
	mapKey2BSONObjPtr m_mapKey2CurrCIInfo;
	mapField2BSONElementArray m_mapField2CIRelationshipArray;
	
	CCMDBController *m_pCMDBController;
	CCIInfoChangeController *m_pCIInfoChangeController;
	CCIInfoUpdateController *m_pCIInfoUpdateController;
	CCIHistoryLogController *m_pCIHistoryLogController;
	CNotificationController *m_pNotificationController;
	CPartnerInfoController *m_pPartnerInfoController;	
	CMailboxController *m_pMailboxController;

	CCIInfoChangeModel *m_pCIInfoChangeModel;	
	CCIHistoryLogModel *m_pCIHistoryLogModel;
	CNotificationModel *m_pNotificationModel;
};
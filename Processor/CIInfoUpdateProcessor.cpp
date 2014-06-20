#include "CIInfoUpdateProcessor.h"
#include "../Controller/CMDBController.h"
#include "../Controller/CIInfoUpdateController.h"
#include "../Controller/CIInfoChangeController.h"
#include "../Controller/CIHistoryLogController.h"
#include "../Controller/ServerInfoChangeController.h"
#include "../Controller/NotificationController.h"
#include "../Controller/PartnerInfoController.h"
#include "../Controller/MailboxController.h"
#include "../Model/MongodbModel.h"
#include "../Model/CIModel.h"
#include "../Model/CIInfoChangeModel.h"
#include "../Model/CIHistoryLogModel.h"
#include "../Model/NotificationModel.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CCIInfoUpdateProcessor::CCIInfoUpdateProcessor(const string& strFileName)
:CProcessor(strFileName)
{
	m_pPartnerInfoController = new CPartnerInfoController();
	m_bIsNotification = false;
	m_bIsMailNotification = false;
}

CCIInfoUpdateProcessor::~CCIInfoUpdateProcessor(void)
{
	if (NULL != m_pCMDBController)
	{
		delete m_pCMDBController;
	}

	if (NULL != m_pCIInfoChangeController)
	{
		delete m_pCIInfoChangeController;
	}

	if (NULL != m_pCIInfoUpdateController)
	{
		delete m_pCIInfoUpdateController;
	}

	if (NULL != m_pCIHistoryLogController)
	{
		delete m_pCIHistoryLogController;
	}

	if (NULL != m_pCIInfoChangeModel)
	{
		delete m_pCIInfoChangeModel;
	}

	if (NULL != m_pCIHistoryLogModel)
	{
		delete m_pCIHistoryLogModel;
	}

	if (NULL != m_pNotificationController)
	{
		delete m_pNotificationController;
	}
	
	if (NULL != m_pNotificationModel)
	{
		delete m_pNotificationModel;
	}

	if (NULL != m_pPartnerInfoController)
	{
		delete m_pPartnerInfoController;
	}

	if (NULL != m_pMailboxController)
	{
		delete m_pMailboxController;
	}
}

bool CCIInfoUpdateProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIInfoUpdateController);
	RegisterController(m_pCIHistoryLogController);
	RegisterController(m_pCMDBController);
	RegisterController(m_pCIInfoChangeController);
	RegisterController(m_pPartnerInfoController);
	
	if (m_bIsMailNotification)
	{
		RegisterController(m_pMailboxController, MONGODB_MAILBOX_GROUP);
	}
	
	if(m_bIsNotification)
	{
		RegisterController(m_pNotificationController);
	}
	return CProcessor::Connect();
}

auto_ptr<DBClientCursor> CCIInfoUpdateProcessor::LoadNewCIInfo() 
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	ptrResultCursor = m_pCIInfoUpdateController->Find(Query(BSON("deleted"<<0)));
	return ptrResultCursor;
}

auto_ptr<DBClientCursor> CCIInfoUpdateProcessor::GetRelatedCIInfo(string strTable, BSONObj boCondition)
{
	auto_ptr<DBClientCursor> ptrResultCursor;
	try
	{
		ptrResultCursor = m_pCMDBController->Find(strTable, Query(boCondition));
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "GetRelatedCIInfo()","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG,strLog);
	}
	return ptrResultCursor;
}

auto_ptr<DBClientCursor> CCIInfoUpdateProcessor::LoadCIRelationship() 
{
	auto_ptr<DBClientCursor> ptrResultCursor;
	try
	{
		ptrResultCursor = m_pCMDBController->Find(TBL_CI_RELATIONSHIP, Query(BSON("is_active" << ACTIVE << "ci_name" << m_pCMDBController->GetTableName())));
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "LoadCIRelationship()","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG,strLog);
	}
	return ptrResultCursor;
}

void CCIInfoUpdateProcessor::PrepareCIRelationshipInfo(auto_ptr<DBClientCursor> &ptrCIRelationshipCursor)
{
	string strField;
	BSONObj boCIRelationshipInfo;
	StringSet setFieldNames;
	StringSet::iterator sit;
	BSONElement beCIFieldRelationInfo;
	vector<BSONElement> vbeCIRelationship;
	vector<CIRelation> vstCIRelationship;
	CIRelation stCIRelation;
	
	try
	{
		while (ptrCIRelationshipCursor->more()) 
		{
			boCIRelationshipInfo = ptrCIRelationshipCursor->nextSafe();
			StringArray arrFieldName;
			arrFieldName.push_back("_id");
			arrFieldName.push_back("ci_type");
			arrFieldName.push_back("ci_name");
			arrFieldName.push_back("is_active");
			//arrFieldName.push_back("status");

			boCIRelationshipInfo = CMongodbModel::RemoveFields(&boCIRelationshipInfo, arrFieldName);

			boCIRelationshipInfo.getFieldNames(setFieldNames);

			for(sit=setFieldNames.begin(); sit!=setFieldNames.end(); sit++)
			{
				strField = *sit;
				vector<CIRelation> vCIRelation;

				beCIFieldRelationInfo = boCIRelationshipInfo.getField(strField);
				vbeCIRelationship = beCIFieldRelationInfo.Array();
				for (unsigned i=0; i<vbeCIRelationship.size(); i++) 
				{
					 BSONObj boCIRelation = vbeCIRelationship[i].Obj();
					 stCIRelation.strRelatedCI			= boCIRelation.getStringField("related_ci");
					 stCIRelation.strTmpCICollection	= boCIRelation.getStringField("tmp_ci_collection");
					 stCIRelation.strRelatedField		= boCIRelation.getStringField("related_field");
					 stCIRelation.strForeignKeyField	= boCIRelation.getStringField("foreign_key");
					 vstCIRelationship.push_back(stCIRelation);
				}

				m_mapField2CIRelationshipArray[strField] = vstCIRelationship;	
				vbeCIRelationship.clear();
				vstCIRelationship.clear();
			}
		}		
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "PrepareCIRelationshipInfo(BSONObj)","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG,strLog);
	}
}

void CCIInfoUpdateProcessor::PrepareUpdating(auto_ptr<DBClientCursor> &ptrInfoUpdateCursor)
{
	string strKey;
	BSONObj oCIUpdateInfo;
	MongodbModelArray* arrBSONObjModel;

	try
	{
		while (ptrInfoUpdateCursor->more()) 
		{
			oCIUpdateInfo = ptrInfoUpdateCursor->nextSafe();
			strKey	= CUtilities::GetMongoObjId(oCIUpdateInfo.getField("ci_id").toString(false));
			CMongodbModel *oCIUpdateInfoModel = new CMongodbModel(oCIUpdateInfo);

			if (m_mapKey2NewCIInfoArray.find(strKey) != m_mapKey2NewCIInfoArray.end()) 
			{
				// existed key
				arrBSONObjModel = (MongodbModelArray*) m_mapKey2NewCIInfoArray[strKey];
				arrBSONObjModel->push_back(oCIUpdateInfoModel);
			}
			else 
			{
				// not existed key
				arrBSONObjModel = new MongodbModelArray();
				arrBSONObjModel->push_back(oCIUpdateInfoModel);
				m_mapKey2NewCIInfoArray[strKey] = arrBSONObjModel;
			}
		}		
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "PrepareUpdating(BSONObj)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG,strLog);
	}
}

bool CCIInfoUpdateProcessor::GetCurrentCIInfo(auto_ptr<DBClientCursor> &ptrCIInfoCursor)
{
	try
	{
		string strKey;
		BSONObj boCIInfo;
		BSONArrayBuilder babKeyArray;

		// Build list of CI id
		for(mapKey2BSONObjArrayPtr::iterator mit = m_mapKey2NewCIInfoArray.begin(); mit != m_mapKey2NewCIInfoArray.end(); mit++) 
		{
			babKeyArray << OID(mit->first);
		}

		// Load data from particular CI table (such as server table) that matches CI id list
		//ptrCIInfoCursor = m_pCMDBController->Find(QUERY("_id"<<BSON("$in"<<babKeyArray.arr())));

		if (!m_pCMDBController->Find(ptrCIInfoCursor, QUERY("_id"<<BSON("$in"<<babKeyArray.arr()))))
		{
			return false;
		}

		while(ptrCIInfoCursor->more())
		{
			boCIInfo = ptrCIInfoCursor->nextSafe();

			// Build map from CI id to CI's record
			strKey = CUtilities::GetMongoObjId(boCIInfo.getField("_id").toString(false));
			CMongodbModel *pCIInfoModel = new CMongodbModel(boCIInfo);
			m_mapKey2CurrCIInfo[strKey]	= pCIInfoModel;		
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "GetCurrentCIInfo()","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}

	return true;
}

// boolean return true if data has been changed, else return false
bool CCIInfoUpdateProcessor::InsertHistoryLog(BSONElement beCIObjectId, BSONObj boOldCIInfo, BSONObj boNewCIInfo)
{
	bool bIsDataChanged = false;

	try
	{
		string strField;
		StringSet setFieldNames;
		StringSet::iterator sit;

		BSONObj boLog;
		int iChangeType;
		long long lChangeDate;
		string strUsername;
		
		strUsername	= boNewCIInfo.hasField("change_by") ? boNewCIInfo.getStringField("change_by") : boOldCIInfo.getStringField("change_by");
		lChangeDate = atoll(boNewCIInfo.hasField("clock") ? boNewCIInfo["clock"].toString(false).c_str() : boOldCIInfo["clock"].toString(false).c_str());
		iChangeType	= boNewCIInfo.hasField("action_type") ? boNewCIInfo.getIntField("action_type") : boOldCIInfo.getIntField("action_type");

		m_pCIHistoryLogModel->SetUsername(strUsername);
		m_pCIHistoryLogModel->SetObjectId(beCIObjectId);
		m_pCIHistoryLogModel->SetChangeDate(lChangeDate);
		m_pCIHistoryLogModel->SetChangeType(iChangeType);
		
		if (iChangeType == ACTION_TYPE_DELETE) 
		{
			RemoveRedundantFields(boOldCIInfo).getFieldNames(setFieldNames);
		}
		else 
		{
			RemoveRedundantFields(boNewCIInfo).getFieldNames(setFieldNames);
		}

		for(sit=setFieldNames.begin(); sit!=setFieldNames.end(); sit++)
		{
			strField = *sit;
			BSONElement beNewValue, beOldValue;
			
			if (boNewCIInfo.hasField(strField.c_str())) 
			{
				beNewValue = boNewCIInfo.getField(strField);
			}
			if (boOldCIInfo.hasField(strField.c_str())) 
			{
				beOldValue = boOldCIInfo.getField(strField);
			}
			
			if (beNewValue != beOldValue)
			{
				bIsDataChanged = true;
				if (!beOldValue.eoo()) 
				{
					m_pCIHistoryLogModel->AppendOldValues(BSON(strField<<beOldValue));
				}
				else 
				{
					m_pCIHistoryLogModel->AppendOldValues(BSON(strField<<""));
				}
				if (!beNewValue.eoo()) 
				{
					m_pCIHistoryLogModel->AppendNewValues(BSON(strField<<beNewValue));
				}
				else 
				{
					m_pCIHistoryLogModel->AppendNewValues(BSON(strField<<""));
				}	
			}	
		}

		if (bIsDataChanged) 
		{
			boLog = m_pCIHistoryLogModel->GetCIHistoryLog();
			
			if(!m_pCIHistoryLogController->InsertHistoryLog(boLog, lChangeDate))
			{
				CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "InsertHistoryLog(BSONObj,BSONObj)", "FAIL:Insert"));
			}
		}
		m_pCIHistoryLogModel->Unset();
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "InsertHistoryLog(BSONObj,BSONObj)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bIsDataChanged;
}

// boolean return true if data has been changed, else return false
bool CCIInfoUpdateProcessor::TrackChangedCIInfo(BSONElement beObjID, 
												BSONObj boOldCIInfo, 
												BSONObj boNewCIInfo)
{
	BSONObjArray vTrackChangedCursor;
	bool bIsDataChanged = false;
	try
	{
		bIsDataChanged = m_pCIInfoChangeModel->GetCIInfoChangeCursor(vTrackChangedCursor, beObjID, boOldCIInfo, boNewCIInfo);
		if (vTrackChangedCursor.size() > 0) 
		{
			for(int i=0; i<vTrackChangedCursor.size(); i++)
			{
				if(!m_pCIInfoChangeController->Insert(vTrackChangedCursor[i]))
				{
					CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "TrackChangedCIInfo(BSONObj,BSONObj)", "FAIL:Insert"));
					return false;
				}
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "TrackChangedCIInfo(BSONObj,BSONObj)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bIsDataChanged = false;
	}
	return bIsDataChanged;
}

BSONObj CCIInfoUpdateProcessor::RemoveRedundantFields(BSONObj pCIInfo)
{
	StringArray arrFieldName;
	arrFieldName.push_back("_id");
	arrFieldName.push_back("ci_id");
	arrFieldName.push_back("action_type");
	arrFieldName.push_back("change_by");
	arrFieldName.push_back("deleted");
	arrFieldName.push_back("old");
	arrFieldName.push_back("old_src");
	arrFieldName.push_back("created_date");
	return CMongodbModel::RemoveFields(&pCIInfo, arrFieldName);
}

bool CCIInfoUpdateProcessor::UpdateCIInfo(string strKey, BSONObj bsCIInfo)
{
	try
	{
		return m_pCMDBController->Update(BSON("$set"<<bsCIInfo),QUERY("_id"<<OID(strKey)));
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "UpdateCIInfo(string,BSONObj)","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}
	return true;
}

bool CCIInfoUpdateProcessor::DeleteTmpCIInfo(BSONElement beCIId)
{
	try
	{
		return m_pCIInfoUpdateController->Update(BSON("$set"<<BSON("deleted"<<1)),QUERY("_id"<<beCIId));
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "DeleteTmpCIInfo","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}
	return true;
}

bool CCIInfoUpdateProcessor::LaunchUpdateProcess()
{
	int iActionType;
	bool bActionResult = true;
	BSONElement beCIId, beTmpCIId;
	BSONObj boTempCIInfo, boChangedFields;
	auto_ptr<DBClientCursor> ptrPartnerInfo = auto_ptr<DBClientCursor>();

	//BSONObjArray arrPartnerInfo;

	try
	{
		/*
		Insert history log
		Trackchange for info_change table
		Update ci table
		Insert notification table
		*/
		for(mapKey2BSONObjArrayPtr::iterator mit = m_mapKey2NewCIInfoArray.begin(); mit != m_mapKey2NewCIInfoArray.end(); mit++) 
		{
			string strKey = mit->first;
			MongodbModelArray* vtNewCIInfo = mit->second;
			if (vtNewCIInfo->size() > 0)
			{
				MongodbModelArray::iterator vit = vtNewCIInfo->begin();
				while (vit != vtNewCIInfo->end())
				{
					BSONObj boOldCIInfo;
					BSONObj boNewCIInfo;
					CMongodbModel *pNewCIInfoModel = *vit;
					boNewCIInfo = *pNewCIInfoModel;

					bActionResult	= false;

					beTmpCIId		= boNewCIInfo.getField("_id");
					beCIId			= boNewCIInfo.getField("ci_id");
					iActionType		= boNewCIInfo.getIntField("action_type");

					switch(iActionType)
					{
						case ACTION_TYPE_ADD:
							InsertHistoryLog(beCIId, BSONObj(), boNewCIInfo);
							bActionResult = TrackChangedCIInfo(beCIId, BSONObj(), 
																RemoveRedundantFields(boNewCIInfo));
							boOldCIInfo = BSONObj();
							break;
						case ACTION_TYPE_UPDATE:
							if (m_mapKey2CurrCIInfo.find(strKey) != m_mapKey2CurrCIInfo.end()) 
							{
								if (boNewCIInfo.hasField("old_src"))
								{
									if(boNewCIInfo.getIntField("old_src") == OLD_FIELD){ // get old value from old field
										boOldCIInfo = boNewCIInfo["old"].Obj();
									}
									else {
										boOldCIInfo = *m_mapKey2CurrCIInfo[strKey];	
									}
								}
								else{
									boOldCIInfo = *m_mapKey2CurrCIInfo[strKey];	
								}
								boTempCIInfo = RemoveRedundantFields(boNewCIInfo);
								if (TrackChangedCIInfo(beCIId, boOldCIInfo, boTempCIInfo)) 
								{
									bActionResult = InsertHistoryLog(beCIId, boOldCIInfo, boNewCIInfo);
									if (bActionResult)
									{
										bActionResult = UpdateCIInfo(strKey, boTempCIInfo);
									}
									if (bActionResult)
									{
										// Update info which has just changed into curr map CIInfo
										(m_mapKey2CurrCIInfo[strKey])->UpdateBSONObj(CMongodbModel::MergeBSONObj(&boOldCIInfo, &boTempCIInfo));
										// Write mail notification
									}
								}
								else
								{
									bActionResult = true;
								}
							}
							else
							{
								bActionResult = true;
							}
							break;
						case ACTION_TYPE_DELETE:
							InsertHistoryLog(beCIId, boNewCIInfo, BSONObj());
							bActionResult = TrackChangedCIInfo(beCIId, RemoveRedundantFields(boNewCIInfo), BSONObj());
							boOldCIInfo = BSONObj();
							break;
					}
					
					if (bActionResult) {
						bool bCreateNotiSuccess = true;
						bool bUpdateRelatedCISuccess = true;						

						boNewCIInfo = CMongodbModel::MergeBSONObj(&boOldCIInfo, &boNewCIInfo, boChangedFields);
						if(m_bIsNotification){
							// Create data to notify via APIs
							bCreateNotiSuccess = CreateNotificationData(iActionType, boNewCIInfo, boChangedFields);
						}
						
						/* Create mail notification data */
						CreateMailNotification(iActionType, boOldCIInfo, boNewCIInfo, boChangedFields);
						// Update relationship
						bUpdateRelatedCISuccess = ProcessUpdateRelatedCI(boOldCIInfo, boNewCIInfo, boChangedFields);

						// Compute data to draw chassis, server on rack map
						ComputeData(iActionType, boOldCIInfo, boNewCIInfo, boChangedFields);

						if (bCreateNotiSuccess && bUpdateRelatedCISuccess)
						{
							DeleteTmpCIInfo(beTmpCIId);
						}
					}

					//delete pNewCIInfoModel;
					vit++;
				}
				vtNewCIInfo->clear();
			}
		}

		DestroyMapData();		
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "LaunchUpdateProcess","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		DestroyMapData();
	}

	return bActionResult;
}

bool CCIInfoUpdateProcessor::ProcessUpdateRelatedCI(BSONObj boOldCIInfo, BSONObj boCIInfoChanged,
										BSONObj boChangedFields)
{
	StringSet setFieldNames;
	vector<CIRelation> vstCIFieldRelationship;
	vector<CIRelation>::iterator vit;
	StringSet::iterator sit;
	CIRelation stCIRelation;
	string strField;
	auto_ptr<DBClientCursor> ptrRelatedCIInfoCursor;
	BSONObj boCondition, boCIRelationshipInfo;
	BSONObj boInsertTMPCIInfo;
	vector<BSONObj> vboBulkData;

	bool bActionRes = true;
	try{
		boChangedFields.getFieldNames(setFieldNames);
		for(sit=setFieldNames.begin(); sit!=setFieldNames.end(); sit++)
		{
			strField = *sit;
			if (m_mapField2CIRelationshipArray.find(strField) != m_mapField2CIRelationshipArray.end()) 
			{
				vstCIFieldRelationship = m_mapField2CIRelationshipArray[strField];

				vit = vstCIFieldRelationship.begin();
				while(vit != vstCIFieldRelationship.end())
				{
					stCIRelation = *vit;
					if (stCIRelation.strRelatedCI == SERVER)
					{
						if (stCIRelation.strTmpCICollection == TBL_TMP_SERVER_PHYSICAL)
						{
							boCondition = BSON(
								stCIRelation.strForeignKeyField		<< boCIInfoChanged.getField("ci_id")	<<
							//	stCIRelation.strRelatedField		<< boOldCIInfo.getField(strField)		<<
								"server_type" << BSON("$in" << BSON_ARRAY(SERVER_UNKNOWN << SERVER_U << SERVER_CHASSIS)
							) );
						}
						else 
						{
							if (stCIRelation.strTmpCICollection == TBL_TMP_SERVER_VIRTUAL)
							{
								boCondition = BSON(
									stCIRelation.strForeignKeyField << boCIInfoChanged.getField("ci_id")	<<
							//		stCIRelation.strRelatedField	<< boOldCIInfo.getField(strField)		<<
									"server_type"					<< SERVER_VIRTUAL
								);
							}
						}
					}
					else 
					{
						boCondition = BSON(
							//	stCIRelation.strRelatedField		<< boOldCIInfo.getField(strField) <<
							stCIRelation.strForeignKeyField		<< boCIInfoChanged.getField("ci_id")
						);
					}
					ptrRelatedCIInfoCursor = GetRelatedCIInfo(stCIRelation.strRelatedCI, boCondition);

					if ((ptrRelatedCIInfoCursor.get() != NULL) && (ptrRelatedCIInfoCursor->more()))
					{
						while (ptrRelatedCIInfoCursor->more()) 
						{
							boCIRelationshipInfo = ptrRelatedCIInfoCursor->nextSafe();
							boInsertTMPCIInfo = BSON(
								"ci_id"							<< boCIRelationshipInfo.getField("_id") <<
								stCIRelation.strRelatedField	<< boCIInfoChanged.getField(strField)	<<
								"action_type"					<< ACTION_UPDATE						<<
								"change_by"						<< CHANGE_BY_BACKEND					<<
								"clock"							<< boCIInfoChanged.getField("clock")	<<
								"deleted"						<< NO									<<
								"old_src"						<< CI_COLLECTION
							);
							vboBulkData.push_back(boInsertTMPCIInfo);	
						}	
						if (vboBulkData.size() > 0)
						{
							bool bRs = m_pCMDBController->BulkInsert(stCIRelation.strTmpCICollection, vboBulkData);
							if (!bRs) 
							{
								bActionRes = false;
							}
							vboBulkData.clear();
						}
					}

					ptrRelatedCIInfoCursor.reset();
					vit++;
				}
			}
		}
		return bActionRes;
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "ProcessUpdateRelatedCI","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return false;
}

bool CCIInfoUpdateProcessor::CreateNotificationData(int iActionType, 
													BSONObj boNotificationData,
													BSONObj boChangedFields)
{
	BSONObjBuilder bobPartnerNoti;
	BSONObj boPartnerInfo, boPartnerNoti;
	vector<BSONElement> vbeAPIInputFields;
	vector<BSONElement>::iterator vit;
	BSONObjArray::iterator bit;
	string strInputName, strPartnerName;
	StringArray arrFieldName;
	int iStatus, iPartner;
	BSONObjArray arrPartnerInfo;
	auto_ptr<DBClientCursor> ptrPartnerInfo = auto_ptr<DBClientCursor>();
		
	// Collecting partner info by table name	
	if (!m_pPartnerInfoController->Find(ptrPartnerInfo, QUERY("table_name"<<m_pNotificationController->GetTableName())))
	{
		return false;
	}
		
	while(ptrPartnerInfo->more())
	{			
		arrPartnerInfo.push_back(ptrPartnerInfo->nextSafe()); 
	}

	/*
		Remove redundent fields for notification
	*/
	arrFieldName.push_back("_id");
	arrFieldName.push_back("ci_id");
	arrFieldName.push_back("clock");
	arrFieldName.push_back("change_by");
	arrFieldName.push_back("deleted");
	arrFieldName.push_back("old");
	arrFieldName.push_back("old_src");
	boNotificationData = CMongodbModel::RemoveFields(&boNotificationData, arrFieldName);

	bit = arrPartnerInfo.begin();
	iStatus = DONE; // Status = 1 : All partners are notified.
	try{
		/* 
		Tracking for Partner notification status in notification ci table.
		*/
		while(bit != arrPartnerInfo.end()) 
		{
			boPartnerInfo = *bit;
			iPartner = DONE;
			if(boPartnerInfo.hasField("input")){
				vbeAPIInputFields = boPartnerInfo["input"].Array();
				vit = vbeAPIInputFields.begin();
				while(vit != vbeAPIInputFields.end())
				{
					strInputName = CUtilities::RemoveBraces((*vit).toString(false,false));
					if(boChangedFields.hasField(strInputName.c_str())){
						iStatus = NOT_YET;
						iPartner = NOT_YET;
						break;
					}
					vit++;
				}
			}
			strPartnerName = boPartnerInfo.hasField("partner_name") ? boPartnerInfo.getStringField("partner_name") : "";
			bobPartnerNoti.append(strPartnerName, iPartner);
			bit++;
		}
		if (NOT_YET == iStatus)
		{
			bobPartnerNoti.append("noti_status", iStatus);
			boPartnerNoti = bobPartnerNoti.obj();
			boNotificationData = CMongodbModel::MergeBSONObj(&boNotificationData, &boPartnerNoti);
			m_pNotificationController->Insert(boNotificationData);
		}
		return true;
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "CreateNotificationData","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return false;
}

void CCIInfoUpdateProcessor::DestroyMapData()
{
	mapKey2BSONObjArrayPtr::iterator itArray = m_mapKey2NewCIInfoArray.begin();
	while (itArray != m_mapKey2NewCIInfoArray.end())
	{
		if (((*itArray).second)->size() > 0)
		{
			MongodbModelArray::iterator itVector = ((*itArray).second)->begin();
			while (itVector != ((*itArray).second)->end())
			{
				delete *itVector;
				itVector++;
			}
		}
		delete (*itArray).second;
		itArray++;
	}
	m_mapKey2NewCIInfoArray.clear();

	mapKey2BSONObjPtr::iterator it = m_mapKey2CurrCIInfo.begin();
	while (it != m_mapKey2CurrCIInfo.end())
	{
		delete (*it).second;
		it++;
	}
	m_mapKey2CurrCIInfo.clear();

	m_mapField2CIRelationshipArray.clear();
}

bool CCIInfoUpdateProcessor::ProceedUpdateCIInfo()
{ 
	if (!Connect())
	{
		cout <<"Some connection failed.\n";
		return false;
	}

	cout << "All connections are ready!" << endl;
	try
	{
		while (true)
		{
			auto_ptr<DBClientCursor> ptrCIInfoCursor = auto_ptr<DBClientCursor>();
			auto_ptr<DBClientCursor> ptrInfoUpdateCursor = auto_ptr<DBClientCursor>();
			auto_ptr<DBClientCursor> ptrCIRelationshipCursor = auto_ptr<DBClientCursor>();

			
			ptrCIRelationshipCursor = LoadCIRelationship();
			if ((ptrCIRelationshipCursor.get() != NULL) && (ptrCIRelationshipCursor->more()))
			{
				PrepareCIRelationshipInfo(ptrCIRelationshipCursor);
			}

			ptrInfoUpdateCursor = LoadNewCIInfo();
			if ((ptrInfoUpdateCursor.get() != NULL) && (ptrInfoUpdateCursor->more()))
			{
				PrepareUpdating(ptrInfoUpdateCursor);
				if (!GetCurrentCIInfo(ptrCIInfoCursor))
				{
					DestroyMapData();
				}
				else
				{
					LaunchUpdateProcess();
				}
			}
			else
			{
				//Sleep for a while
				sleep(TRACK_CHANGE_INTERVAL);
			}

			ptrCIInfoCursor.reset();
			ptrInfoUpdateCursor.reset();
			ptrCIRelationshipCursor.reset();
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoUpdateProcessor", "ProceedUpdateCIInfo(BSONObj)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}

	return false;
}

void CCIInfoUpdateProcessor::ComputeData(int iActionType, 
												BSONObj boOldCIInfo, 
												BSONObj boNewCIInfo, 
												BSONObj boChangedFields)
{
	if (!CanComputeData())
	{
		return;
	}		

	switch (iActionType)
	{
	case ACTION_INSERT:
		InsertData(boNewCIInfo);
		InsertSpecialDataInfo(boNewCIInfo);
		break;
	case ACTION_UPDATE:
		UpdateData(boOldCIInfo, boNewCIInfo, boChangedFields);
		UpdateSpecialDataInfo(boOldCIInfo, boNewCIInfo, boChangedFields);
		break;
	case ACTION_DELETE:
		DeleteData(boNewCIInfo);
		break;
	}
}
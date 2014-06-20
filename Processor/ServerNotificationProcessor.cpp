#include "ServerNotificationProcessor.h"
#include "../Model/NotificationModel.h"
#include "../Notification/DCServerNotificationAPI.h"
#include "../Controller/ServerNotificationController.h"
#include "../Model/MongodbModel.h"

CServerNotificationProcessor::CServerNotificationProcessor(const string& strFileName)
:CNotificationProcessor(strFileName)
{
	m_pNotificationController = new CServerNotificationController();
	m_pFuncStartDispatcher = &StartDispatcher;
}

CServerNotificationProcessor::~CServerNotificationProcessor(void)
{
}

auto_ptr<DBClientCursor> CServerNotificationProcessor::LoadNotificationInfo()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	try
	{
		ptrResultCursor = m_pNotificationController->Find(QUERY("status"<<0<<"server_type"<<3));
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "LoadDB()","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(strLog);
	}
	return ptrResultCursor;
}

void* CServerNotificationProcessor::StartDispatcher(void *pData)
{
	CNotificationModel* pNotificationModel = static_cast<CNotificationModel*>(pData);
	BSONObj boNotificationModel;
	BSONElement beOID;
	StringArray arrFieldName;
	

	arrFieldName.push_back("_id");
	arrFieldName.push_back("server_type");
	arrFieldName.push_back("DC");
	arrFieldName.push_back("status");
	boNotificationModel = *pNotificationModel;
	boNotificationModel = CMongodbModel::RemoveFields(&boNotificationModel, arrFieldName);
	pNotificationModel->SetData(boNotificationModel);

	if (pNotificationModel->GetPartnerName() == PARTNER_DC)
	{
		CDCServerNotificationAPI dcAPI;
		pNotificationModel->SetNotification(dcAPI.Notify(pNotificationModel));
	}
}

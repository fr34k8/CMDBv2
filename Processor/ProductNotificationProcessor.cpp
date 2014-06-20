#include "ProductNotificationProcessor.h"
#include "../Model/NotificationModel.h"
#include "../Notification/DCProductNotificationAPI.h"
#include "../Notification/MISProductNotificationAPI.h"
#include "../Controller/ProductNotificationController.h"

CProductNotificationProcessor::CProductNotificationProcessor(const string& strFileName)
:CNotificationProcessor(strFileName)
{
	m_pNotificationController = new CProductNotificationController();
	m_pFuncStartDispatcher = &StartDispatcher;
}

CProductNotificationProcessor::~CProductNotificationProcessor(void)
{
}

void* CProductNotificationProcessor::StartDispatcher(void *pData)
{
	int iIsNotified;
	BSONObj boMailInfo;
	CNotificationModel* pNotificationModel = static_cast<CNotificationModel*>(pData);
	if (pNotificationModel->GetPartnerName() == PARTNER_DC)
	{
		CDCProductNotificationAPI dcAPI;
		iIsNotified = dcAPI.Notify(pNotificationModel);
		pNotificationModel->SetNotification(iIsNotified);
		/*if (iIsNotified != API_ACTION_SUCCESS)
		{
			dcAPI.CreateMailInfo(pNotificationModel);
		}*/
		/*pNotificationModel->SetNotification(1);
		dcAPI.CreateMailInfo(pNotificationModel);*/
	}
	//if (pNotificationModel->GetPartnerName() == PARTNER_MIS)
	//{
	//	CMISProductNotificationAPI misAPI;
	//	for (int i = 0; i < API_RETRY_TIME; i++)
	//	{
	//		iIsNotified = misAPI.Notify(pNotificationModel);
	//		if (iIsNotified)
	//			break;
	//	}
	//	pNotificationModel->SetNotification(iIsNotified);
	//	if (iIsNotified != API_ACTION_SUCCESS)
	//	{
	//		misAPI.CreateMailInfo(pNotificationModel);
	//	}
	//	/*pNotificationModel->SetNotification(1);
	//	misAPI.CreateMailInfo(pNotificationModel);*/
	//}
}



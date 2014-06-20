#include "PhysicalServerNotificationProcessor.h"
#include "../Model/NotificationModel.h"
#include "../Notification/DCServerNotificationAPI.h"
#include "../Notification/SnSServerNotificationAPI.h"
#include "../Controller/PhysicalServerNotificationController.h"

CPhysicalServerNotificationProcessor::CPhysicalServerNotificationProcessor(const string& strFileName)
:CNotificationProcessor(strFileName)
{
	m_pNotificationController = new CPhysicalServerNotificationController();
	m_pFuncStartDispatcher = &StartDispatcher;
}

CPhysicalServerNotificationProcessor::~CPhysicalServerNotificationProcessor(void)
{
}

void* CPhysicalServerNotificationProcessor::StartDispatcher(void *pData)
{
	CNotificationModel* pNotificationModel = static_cast<CNotificationModel*>(pData);

	if (pNotificationModel->GetPartnerName() == PARTNER_DC)
	{
		CDCServerNotificationAPI pDCAPI;
		pNotificationModel->SetNotification(pDCAPI.Notify(pNotificationModel));
	}
	if (pNotificationModel->GetPartnerName() == PARTNER_SNS)
	{
		CSnSServerNotificationAPI pSnSAPI;
		pNotificationModel->SetNotification(pSnSAPI.Notify(pNotificationModel));
	}
}

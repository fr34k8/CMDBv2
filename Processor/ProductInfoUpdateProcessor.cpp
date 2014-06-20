#include "ProductInfoUpdateProcessor.h"
#include "../Controller/ProductController.h"
#include "../Controller/ProductInfoChangeController.h"
#include "../Controller/ProductInfoUpdateController.h"
#include "../Controller/ProductHistoryLogController.h"
#include "../Controller/ProductNotificationController.h"
#include "../Controller/PartnerInfoController.h"
#include "../Model/ProductInfoChangeModel.h"
#include "../Model/CIHistoryLogModel.h"
#include "../Model/ProductHistoryLogModel.h"
#include "../Model/ProductNotificationModel.h"

CProductInfoUpdateProcessor::CProductInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController	= new CProductInfoUpdateController();
	m_pCIInfoChangeController	= new CProductInfoChangeController();
	m_pCMDBController			= new CProductController();
	m_pCIHistoryLogController	= new CProductHistoryLogController();	
	m_pNotificationController	= new CProductNotificationController();

	m_pCIHistoryLogModel		= new CProductHistoryLogModel();
	m_pCIInfoChangeModel		= new CProductInfoChangeModel();
	m_pNotificationModel		= new CProductNotificationModel();
	
	m_bIsNotification	= true;
}

CProductInfoUpdateProcessor::~CProductInfoUpdateProcessor(void)
{	
}


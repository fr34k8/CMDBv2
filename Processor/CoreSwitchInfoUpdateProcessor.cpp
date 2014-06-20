#include "CoreSwitchInfoUpdateProcessor.h"
#include "../Controller/CoreSwitchController.h"
#include "../Controller/CoreSwitchInfoChangeController.h"
#include "../Controller/CoreSwitchInfoUpdateController.h"
#include "../Controller/CoreSwitchHistoryLogController.h"
#include "../Controller/RackController.h"
#include "../Model/CoreSwitchInfoChangeModel.h"
#include "../Model/CoreSwitchHistoryLogModel.h"
#include "../Model/RackModel.h"
#include "../Model/RackSwitchModel.h"
#include "../Common/Common.h"
#include "../Common/DBCommon.h"

CCoreSwitchInfoUpdateProcessor::CCoreSwitchInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CCoreSwitchInfoUpdateController();
	m_pCIInfoChangeController = new CCoreSwitchInfoChangeController();
	m_pCMDBController = new CCoreSwitchController();
	m_pCIHistoryLogController = new CCoreSwitchHistoryLogController();
	m_pCIHistoryLogModel = new CCoreSwitchHistoryLogModel();
	m_pCIInfoChangeModel = new CCoreSwitchInfoChangeModel();

	//DuyMN
	m_pRackController	= new CRackController();	//Object Rack Controller
	m_pRackModel		= new CRackModel();			//Object Rack Model
	m_nCIType			= CI_TYPE_CORE_SWITCH;
}

CCoreSwitchInfoUpdateProcessor::~CCoreSwitchInfoUpdateProcessor(void)
{
	if (NULL != m_pRackController)
	{
		delete m_pRackController;
	}

	if (NULL != m_pRackModel)
	{
		delete m_pRackModel;
	}
}
	
bool CCoreSwitchInfoUpdateProcessor::Connect()
{
	RegisterController(m_pRackController);	//Register Rack Controller
	return CCIInfoUpdateProcessor::Connect();
}
void CCoreSwitchInfoUpdateProcessor::InsertData(BSONObj boNewCIInfo)
{
	BSONObj boSwitchType = BSON(FIELD_RACK_SWITCH_TYPE << m_nCIType);
	boNewCIInfo = CMongodbModel::MergeBSONObj(&boNewCIInfo, &boSwitchType);

	InsertSwitchGraphicData(boNewCIInfo);
}

void CCoreSwitchInfoUpdateProcessor::DeleteData(BSONObj boNewCIInfo)
{
	cout << "Dang delete" << endl;
	DeleteSwitchGraphicData(boNewCIInfo);
}

void CCoreSwitchInfoUpdateProcessor::UpdateData(BSONObj boOldCIInfo, 
														 BSONObj boNewCIInfo, 
														 BSONObj boChangedFields)
{
	BSONObj boSwitchType = BSON(FIELD_RACK_SWITCH_TYPE << m_nCIType);
	boNewCIInfo = CMongodbModel::MergeBSONObj(&boNewCIInfo, &boSwitchType);
	
	cout << "Update New CIInfo:" << boNewCIInfo.toString() << endl;

	UpdateSwitchGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
}

void CCoreSwitchInfoUpdateProcessor::InsertSwitchGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting Insert Switch..." << endl;
	m_pRackController->AddRackSwitch(boNewCIInfo);
}

void CCoreSwitchInfoUpdateProcessor::DeleteSwitchGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting delete ..." << endl;
	m_pRackController->RemoveRackSwitch(boNewCIInfo);
}

void CCoreSwitchInfoUpdateProcessor::UpdateSwitchGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	cout << "Starting update ..." << endl;
	m_pRackController->UpdateRackSwitch(boOldCIInfo, boNewCIInfo, boChangedFields);
}
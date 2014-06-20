#include "AccessSwitchInfoUpdateProcessor.h"
#include "../Controller/AccessSwitchController.h"
#include "../Controller/AccessSwitchInfoChangeController.h"
#include "../Controller/AccessSwitchInfoUpdateController.h"
#include "../Controller/AccessSwitchHistoryLogController.h"
#include "../Controller/MailboxController.h"
#include "../Controller/RackController.h"
#include "../Model/AccessSwitchInfoChangeModel.h"
#include "../Model/AccessSwitchHistoryLogModel.h"
#include "../Model/RackModel.h"
#include "../Model/RackSwitchModel.h"
#include "../Common/Common.h"
#include "../Common/DBCommon.h"


CAccessSwitchInfoUpdateProcessor::CAccessSwitchInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CAccessSwitchInfoUpdateController();
	m_pCIInfoChangeController = new CAccessSwitchInfoChangeController();
	m_pCMDBController		  = new CAccessSwitchController();
	m_pCIHistoryLogController = new CAccessSwitchHistoryLogController();
	m_pCIHistoryLogModel	  = new CAccessSwitchHistoryLogModel();
	m_pCIInfoChangeModel	  = new CAccessSwitchInfoChangeModel();
	m_pMailboxController	  = new CMailboxController();
	m_bIsMailNotification	  = true;

	//DuyMN
	m_pRackController	= new CRackController();	//Object Rack Controller
	m_pRackModel		= new CRackModel();			//Object Rack Model
	m_nCIType			= CI_TYPE_ACCESS_SWITCH;
}

CAccessSwitchInfoUpdateProcessor::~CAccessSwitchInfoUpdateProcessor(void)
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

bool CAccessSwitchInfoUpdateProcessor::Connect()
{
	RegisterController(m_pRackController);	//Register Rack Controller
	return CCIInfoUpdateProcessor::Connect();
}
void CAccessSwitchInfoUpdateProcessor::InsertData(BSONObj boNewCIInfo)
{
	int iSwitchType = CMongodbModel::GetIntFieldValue(boNewCIInfo, "switch_type", UNKNOWN);
	
	BSONObj boSwitchType = BSON(FIELD_RACK_SWITCH_TYPE << m_nCIType);
	boNewCIInfo = CMongodbModel::MergeBSONObj(&boNewCIInfo, &boSwitchType);

	switch(iSwitchType)
	{
	case SWITCH_U:
		InsertSwitchUGraphicData(boNewCIInfo);
		break;
	case SWITCH_MODULE:
		InsertSwitchChassisGraphicData(boNewCIInfo);
		break;
	}
}

void CAccessSwitchInfoUpdateProcessor::DeleteData(BSONObj boNewCIInfo)
{
	int iSwitchType = CMongodbModel::GetIntFieldValue(boNewCIInfo, "switch_type", UNKNOWN);
	
	switch(iSwitchType)
	{
	case SWITCH_U:
		DeleteSwitchUGraphicData(boNewCIInfo);
		break;
	case SWITCH_MODULE:
		DeleteSwitchChassisGraphicData(boNewCIInfo);
		break;
	}
}

void CAccessSwitchInfoUpdateProcessor::UpdateData(BSONObj boOldCIInfo, 
														 BSONObj boNewCIInfo, 
														 BSONObj boChangedFields)
{
	int iSwitchType = CMongodbModel::GetIntFieldValue(boNewCIInfo, "switch_type", UNKNOWN);
	
	BSONObj boSwitchType = BSON(FIELD_RACK_SWITCH_TYPE << m_nCIType);
	boNewCIInfo = CMongodbModel::MergeBSONObj(&boNewCIInfo, &boSwitchType);

	switch(iSwitchType)
	{
	case SWITCH_U:
		UpdateSwitchUGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
		break;
	case SWITCH_MODULE:
		UpdateSwitchChassisGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
		break;
	}
}

void CAccessSwitchInfoUpdateProcessor::InsertSwitchUGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting Insert Switch U..." << endl;
	m_pRackController->AddRackSwitch(boNewCIInfo);
}

void CAccessSwitchInfoUpdateProcessor::DeleteSwitchUGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting delete Switch U..." << endl;
	m_pRackController->RemoveRackSwitch(boNewCIInfo);
}

void CAccessSwitchInfoUpdateProcessor::UpdateSwitchUGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	cout << "Starting update Switch U..." << endl;
	m_pRackController->UpdateRackSwitch(boOldCIInfo, boNewCIInfo, boChangedFields);
}

void CAccessSwitchInfoUpdateProcessor::InsertSwitchChassisGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting Insert Switch Chassis ..." << endl;
	m_pRackController->AddRackSwitchChassis(boNewCIInfo, m_pMailboxController);
}

void CAccessSwitchInfoUpdateProcessor::DeleteSwitchChassisGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting delete Switch Chassis ..." << endl;
	m_pRackController->RemoveRackSwitchChassis(boNewCIInfo);
}

void CAccessSwitchInfoUpdateProcessor::UpdateSwitchChassisGraphicData(BSONObj boOldCIInfo, 
																	  BSONObj boNewCIInfo, 
																	  BSONObj boChangedFields)
{
	cout << "Starting update Switch Chassis ..." << endl;
	m_pRackController->UpdateRackSwitchChassis(boOldCIInfo, boNewCIInfo, boChangedFields, m_pMailboxController);
}
#include "AggregationSwitchInfoUpdateProcessor.h"
#include "../Controller/AggregationSwitchController.h"
#include "../Controller/AggregationSwitchInfoChangeController.h"
#include "../Controller/AggregationSwitchInfoUpdateController.h"
#include "../Controller/AggregationSwitchHistoryLogController.h"
#include "../Controller/RackController.h"
#include "../Model/AggregationSwitchInfoChangeModel.h"
#include "../Model/AggregationSwitchHistoryLogModel.h"
#include "../Model/RackModel.h"
#include "../Model/RackSwitchModel.h"
#include "../Common/Common.h"
#include "../Common/DBCommon.h"

CAggregationSwitchInfoUpdateProcessor::CAggregationSwitchInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CAggregationSwitchInfoUpdateController();
	m_pCIInfoChangeController = new CAggregationSwitchInfoChangeController();
	m_pCMDBController = new CAggregationSwitchController();
	m_pCIHistoryLogController = new CAggregationSwitchHistoryLogController();
	m_pCIHistoryLogModel = new CAggregationSwitchHistoryLogModel();
	m_pCIInfoChangeModel = new CAggregationSwitchInfoChangeModel();

	//DuyMN
	m_pRackController	= new CRackController();	//Object Rack Controller
	m_pRackModel		= new CRackModel();			//Object Rack Model
	m_nCIType			= CI_TYPE_AGGREGATION_SWITCH;
}

CAggregationSwitchInfoUpdateProcessor::~CAggregationSwitchInfoUpdateProcessor(void)
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

bool CAggregationSwitchInfoUpdateProcessor::Connect()
{
	RegisterController(m_pRackController);	//Register Rack Controller
	return CCIInfoUpdateProcessor::Connect();
}
void CAggregationSwitchInfoUpdateProcessor::InsertData(BSONObj boNewCIInfo)
{
	BSONObj boSwitchType = BSON(FIELD_RACK_SWITCH_TYPE << m_nCIType);
	boNewCIInfo = CMongodbModel::MergeBSONObj(&boNewCIInfo, &boSwitchType);

	InsertSwitchGraphicData(boNewCIInfo);
}

void CAggregationSwitchInfoUpdateProcessor::DeleteData(BSONObj boNewCIInfo)
{
	cout << "Dang delete" << endl;
	DeleteSwitchGraphicData(boNewCIInfo);
}

void CAggregationSwitchInfoUpdateProcessor::UpdateData(BSONObj boOldCIInfo, 
														 BSONObj boNewCIInfo, 
														 BSONObj boChangedFields)
{
	BSONObj boSwitchType = BSON(FIELD_RACK_SWITCH_TYPE << m_nCIType);
	boNewCIInfo = CMongodbModel::MergeBSONObj(&boNewCIInfo, &boSwitchType);
	UpdateSwitchGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
}

void CAggregationSwitchInfoUpdateProcessor::InsertSwitchGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting Insert Switch..." << endl;
	m_pRackController->AddRackSwitch(boNewCIInfo);
}

void CAggregationSwitchInfoUpdateProcessor::DeleteSwitchGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting delete ..." << endl;
	m_pRackController->RemoveRackSwitch(boNewCIInfo);
}

void CAggregationSwitchInfoUpdateProcessor::UpdateSwitchGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	cout << "Starting Update ..." << endl;
	m_pRackController->UpdateRackSwitch(boOldCIInfo, boNewCIInfo, boChangedFields);
}
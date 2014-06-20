#include "PDUInfoUpdateProcessor.h"
#include "../Controller/PDUController.h"
#include "../Controller/PDUInfoChangeController.h"
#include "../Controller/PDUInfoUpdateController.h"
#include "../Controller/PDUHistoryLogController.h"
#include "../Controller/RackController.h"
#include "../Model/PDUInfoChangeModel.h"
#include "../Model/PDUHistoryLogModel.h"

CPDUInfoUpdateProcessor::CPDUInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CPDUInfoUpdateController();
	m_pCIInfoChangeController = new CPDUInfoChangeController();
	m_pCMDBController = new CPDUController();
	m_pCIHistoryLogController = new CPDUHistoryLogController();
	m_pCIHistoryLogModel = new CPDUHistoryLogModel();
	m_pCIInfoChangeModel = new CPDUInfoChangeModel();

	//DuyMN
	m_pRackController	= new CRackController();	//Object Rack Controller
}

CPDUInfoUpdateProcessor::~CPDUInfoUpdateProcessor(void)
{
	if (NULL != m_pRackController)
	{
		delete m_pRackController;
	}
}

bool CPDUInfoUpdateProcessor::Connect()
{
	RegisterController(m_pRackController);	//Register Rack Controller
	return CCIInfoUpdateProcessor::Connect();
}
void CPDUInfoUpdateProcessor::InsertData(BSONObj boNewCIInfo)
{
	InsertPDUGraphicData(boNewCIInfo);
}

void CPDUInfoUpdateProcessor::DeleteData(BSONObj boNewCIInfo)
{
	cout << "Dang delete" << endl;
	DeletePDUGraphicData(boNewCIInfo);
}

void CPDUInfoUpdateProcessor::UpdateData(BSONObj boOldCIInfo, 
														 BSONObj boNewCIInfo, 
														 BSONObj boChangedFields)
{
	UpdatePDUGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
}

void CPDUInfoUpdateProcessor::InsertPDUGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting Insert pdu..." << endl;
	m_pRackController->AddRackPDU(boNewCIInfo);
}

void CPDUInfoUpdateProcessor::DeletePDUGraphicData(BSONObj boNewCIInfo)
{
	cout << "Starting delete pdu..." << endl;
	m_pRackController->RemoveRackPDU(boNewCIInfo);
}

void CPDUInfoUpdateProcessor::UpdatePDUGraphicData(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	cout << "Starting Update pdu..." << endl;
	m_pRackController->UpdateRackPDU(boOldCIInfo, boNewCIInfo, boChangedFields);
}
#include "ComputeRackDataProcessor.h"
#include "../Controller/ServerController.h"
#include "../Controller/AccessSwitchController.h"
#include "../Controller/AggregationSwitchController.h"
#include "../Controller/ChassisController.h"
#include "../Controller/CoreSwitchController.h"
#include "../Controller/PDUController.h"
#include "../Controller/RackController.h"
#include "../Model/DeviceModel.h"
#include "../Model/RackServerUModel.h"
#include "../Model/RackBayChassisModel.h"
#include "../Model/RackSwitchChassisModel.h"
#include "../Model/RackChassisModel.h"
#include "../Model/ChassisModel.h"
#include "../Model/RackSwitchModel.h"
#include "../Model/RackPDUModel.h"

CComputeRackDataProcessor::CComputeRackDataProcessor(const string& strCfgFile)
:CComputeDataProcessor(strCfgFile)
{	
	m_pCIController = new CRackController();
}

CComputeRackDataProcessor::~CComputeRackDataProcessor(void)
{	
	DestroyData();
}

bool CComputeRackDataProcessor::Connect()
{	
	return CComputeDataProcessor::Connect();
}

bool CComputeRackDataProcessor::LoadData()
{
	if (!LoadServerInfo())
	{
		return false;
	}

	if (!LoadAggregationSwitchInfo())
	{
		return false;
	}

	if (!LoadAccessSwitchInfo())
	{
		return false;
	}

	if (!LoadCoreSwitchInfo())
	{
		return false;
	}

	if (!LoadPDUInfo())
	{
		return false;
	}

	if (!LoadChassisInfo())
	{
		return false;
	}

	return true;
}

bool CComputeRackDataProcessor::LoadServerInfo()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();
	if (!m_pCIController->FindOperatingPhysicalServer(ptrCursor))
	{
		return false;
	}

	while (ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();		
		PrepareData(boRecord, CI_TYPE_SERVER);
	}
	ptrCursor.reset();
	return true;
}

bool CComputeRackDataProcessor::LoadChassisInfo()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();	

	if (!m_pCIController->FindOperatingChassis(ptrCursor))
	{
		return false;
	}

	while (ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();		
		PrepareData(boRecord, CI_TYPE_CHASSIS);
	}
	ptrCursor.reset();
	return true;
}

bool CComputeRackDataProcessor::LoadAggregationSwitchInfo()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();

	if (!m_pCIController->FindOperatingAggregationSwitch(ptrCursor))
	{
		return false;
	}

	while (ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();		
		PrepareData(boRecord, CI_TYPE_AGGREGATION_SWITCH);
	}
	ptrCursor.reset();
	return true;
}

bool CComputeRackDataProcessor::LoadAccessSwitchInfo()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();
	
	if (!m_pCIController->FindOperatingAccessSwitch(ptrCursor))
	{
		return false;
	}

	while (ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();		
		PrepareData(boRecord, CI_TYPE_ACCESS_SWITCH);
	}
	ptrCursor.reset();
	return true;
}

bool CComputeRackDataProcessor::LoadCoreSwitchInfo()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();
	
	if (!m_pCIController->FindOperatingCoreSwitch(ptrCursor))
	{
		return false;
	}

	while (ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();		
		PrepareData(boRecord, CI_TYPE_CORE_SWITCH);
	}
	ptrCursor.reset();
	return true;
}

bool CComputeRackDataProcessor::LoadPDUInfo()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();

	if (!m_pCIController->FindOperatingPDU(ptrCursor))
	{
		return false;
	}

	while (ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();
		PrepareData(boRecord, CI_TYPE_PDU);
	}
	ptrCursor.reset();
	return true;
}

CDeviceModel* CComputeRackDataProcessor::CreateRackServerModel(BSONObj boCIInfo)
{
	RackBayChassisModelArray *pRackBayChassisModelArray;
	CDeviceModel* pDeviceModel = NULL;	
	string strIPAddress = "";
	int iServerType = boCIInfo.hasField("server_type") ? boCIInfo.getIntField("server_type") : 0;

	switch (iServerType)
	{
	case SERVER_U:
		pDeviceModel = new CRackServerUModel();		
		break;
	case SERVER_CHASSIS:
		pDeviceModel = new CRackBayChassisModel();
		if (boCIInfo.hasField("chassis"))
		{
			strIPAddress = boCIInfo.getStringField("chassis");
			if (strIPAddress != "")
			{
				IP2CRackBayChassisArrayMap::iterator it = m_mapIP2CRackBayChassisArray.find(strIPAddress);
				// Get device array object
				if (it != m_mapIP2CRackBayChassisArray.end())
				{
					pRackBayChassisModelArray = (*it).second;
				}
				else
				{
					pRackBayChassisModelArray = new RackBayChassisModelArray();
					m_mapIP2CRackBayChassisArray[strIPAddress] = pRackBayChassisModelArray;
				}

				if (NULL != pDeviceModel)
				{
					pRackBayChassisModelArray->push_back((CRackBayChassisModel*)pDeviceModel);
				}
			}
		}
		break;		
	default:
		pDeviceModel = new CDeviceModel();
	}

	return pDeviceModel;
}

CDeviceModel* CComputeRackDataProcessor::CreateRackSwitchModel(BSONObj boCIInfo)
{
	RackSwitchChassisModelArray *pRackSwitchChassisModelArray;
	CDeviceModel* pDeviceModel = NULL;
	string strIPAddress = "";
	int iSwitchType = boCIInfo.hasField("switch_type") ? boCIInfo.getIntField("switch_type") : 0;

	switch (iSwitchType)
	{
	case SWITCH_U:
		pDeviceModel = new CRackSwitchModel();
		break;
	case SWITCH_MODULE:
		pDeviceModel = new CRackSwitchChassisModel();
		if (boCIInfo.hasField("ip_chassis"))
		{
			strIPAddress = boCIInfo.getStringField("ip_chassis");
			if (strIPAddress != "")
			{
				IP2CRackSwitchChassisArrayMap::iterator it = m_mapIP2RackSwitchChassisArray.find(strIPAddress);
				// Get device array object
				if (it != m_mapIP2RackSwitchChassisArray.end())
				{
					pRackSwitchChassisModelArray = (*it).second;
				}
				else
				{
					pRackSwitchChassisModelArray = new RackSwitchChassisModelArray();
					m_mapIP2RackSwitchChassisArray[strIPAddress] = pRackSwitchChassisModelArray;
				}

				if (NULL != pDeviceModel)
				{
					pRackSwitchChassisModelArray->push_back((CRackSwitchChassisModel*)pDeviceModel);
				}
			}
		}
		break;
	default:
		pDeviceModel = new CDeviceModel();
	}

	return pDeviceModel;
}

CDeviceModel* CComputeRackDataProcessor::CreateDeviceModel(BSONObj boCIInfo, int iCIType)
{
	CDeviceModel* pDeviceModel = NULL;	
	string strIPAddress = "";
	IP2CRackBayChassisArrayMap::iterator itIP2BayDeviceModel;
	IP2CRackSwitchChassisArrayMap::iterator itIP2SwitchDeviceModel;
	switch (iCIType)
	{
	case CI_TYPE_SERVER: 
		pDeviceModel = CreateRackServerModel(boCIInfo);			
		break;
	case CI_TYPE_ACCESS_SWITCH:
	case CI_TYPE_AGGREGATION_SWITCH:
	case CI_TYPE_CORE_SWITCH:
		pDeviceModel = CreateRackSwitchModel(boCIInfo);
		break;
	case CI_TYPE_PDU:
		pDeviceModel = new CRackPDUModel();
		break;
	case CI_TYPE_CHASSIS:
		pDeviceModel = new CRackChassisModel();
		if (boCIInfo.hasField("ip_address"))
		{
			strIPAddress = CChassisModel::GetIPAddress(boCIInfo);
			if (strIPAddress != "")
			{
				itIP2BayDeviceModel = m_mapIP2CRackBayChassisArray.find(strIPAddress);
				if (itIP2BayDeviceModel != m_mapIP2CRackBayChassisArray.end())
				{
					((CRackChassisModel*)pDeviceModel)->AddRackBayChassisModel((*itIP2BayDeviceModel).second);
				}

				itIP2SwitchDeviceModel = m_mapIP2RackSwitchChassisArray.find(strIPAddress);
				if (itIP2SwitchDeviceModel != m_mapIP2RackSwitchChassisArray.end())
				{
					((CRackChassisModel*)pDeviceModel)->AddRackSwitchChassisModel((*itIP2SwitchDeviceModel).second);
				}
			}
		}
		break;
	default:
		pDeviceModel = new CDeviceModel();
	}

	pDeviceModel->Load(boCIInfo);
	return pDeviceModel;
}
void CComputeRackDataProcessor::PrepareData(BSONObj boCIInfo, int iCIType)
{
	string strName, strSite, strRackKey;
	DeviceModelArray* pDeviceArray;
	CDeviceModel* pDeviceModel;
	BSONObj boDeviceInfo;
	if ((boCIInfo.hasField("rack") &&
		boCIInfo.hasField("site") &&
		boCIInfo.hasField("u") &&
		boCIInfo.hasField("u_space")) 
		|| (CI_TYPE_PDU == iCIType && 
		boCIInfo.hasField("rack") &&
		boCIInfo.hasField("site")))
	{
		strName = boCIInfo.getStringField("rack");
		strSite = boCIInfo.getStringField("site");
		if (strName.empty() || strSite.empty())
		{
			return;
		}
		strRackKey = strSite + ":" + strName;
		RackName2DeviceArrayMap::iterator it = m_mapRackName2DeviceArray.find(strRackKey);
		// Get device array object
		if (it != m_mapRackName2DeviceArray.end())
		{
			pDeviceArray = (*it).second;
		}
		else
		{
			pDeviceArray = new DeviceModelArray();
			m_mapRackName2DeviceArray[strRackKey] = pDeviceArray;
		}
		pDeviceModel = CreateDeviceModel(boCIInfo, iCIType);
		if (NULL != pDeviceModel)
		{
			pDeviceModel->SetCIType(iCIType);
			pDeviceArray->push_back(pDeviceModel);
		}
	}
}

void CComputeRackDataProcessor::DestroyData()
{
	RackName2DeviceArrayMap::iterator it = m_mapRackName2DeviceArray.begin();
	while (it != m_mapRackName2DeviceArray.end())
	{
		DeviceModelArray* pDeviceModelArray = (*it).second;

		// Destroy device model data
		DeviceModelArray::iterator itDevice = pDeviceModelArray->begin();
		while (itDevice != pDeviceModelArray->end())
		{
			delete *itDevice;
			itDevice++;
		}
		delete pDeviceModelArray;

		it++;
	}
	m_mapRackName2DeviceArray.clear();

	IP2CRackBayChassisArrayMap::iterator bit = m_mapIP2CRackBayChassisArray.begin();
	while (bit != m_mapIP2CRackBayChassisArray.end())
	{
		RackBayChassisModelArray* pRackBayChassisModelArray = (*bit).second;

		// Destroy device model data
		RackBayChassisModelArray::iterator bitDevice = pRackBayChassisModelArray->begin();
		while (bitDevice != pRackBayChassisModelArray->end())
		{
			delete *bitDevice;
			bitDevice++;
		}
		delete pRackBayChassisModelArray;

		bit++;
	}
	m_mapIP2CRackBayChassisArray.clear();

	IP2CRackSwitchChassisArrayMap::iterator sit = m_mapIP2RackSwitchChassisArray.begin();
	while (sit != m_mapIP2RackSwitchChassisArray.end())
	{
		RackSwitchChassisModelArray* pRackSwitchChassisModelArray = (*sit).second;

		// Destroy device model data
		RackSwitchChassisModelArray::iterator sitDevice = pRackSwitchChassisModelArray->begin();
		while (sitDevice != pRackSwitchChassisModelArray->end())
		{
			delete *sitDevice;
			sitDevice++;
		}
		delete pRackSwitchChassisModelArray;

		sit++;
	}
	m_mapIP2RackSwitchChassisArray.clear();
}

void CComputeRackDataProcessor::CalculateAvailableU(string strRackKey,
														DeviceModelArray* pDeviceModelArray)
{
	BSONArrayBuilder babArrayAvailableU, babArrayChassis, babArrayServerU, babArraySwitch, babArrayVlan, babArrayPDU;
	map<int, bool> mapArrayVlan;
	CDeviceModel* pDeviceModel;
	int iU;
	int iSpace, iUPos;
	bool arrAvailableU[RACK_MAX_U + 1]; // Store available U array
	// Init available U
	for (int i = 1; i < RACK_MAX_U + 1; i++)
	{
		arrAvailableU[i] = true;
	}

	//cout << "-------------------" << strRackKey << endl;
	DeviceModelArray::iterator itDevice = pDeviceModelArray->begin();
	while (itDevice != pDeviceModelArray->end())
	{		
		BSONObj boRackDeviceInfo;
		pDeviceModel = *itDevice;
		iU = pDeviceModel->GetU();	
		CRackServerUModel* pServerU = NULL;
		CRackSwitchModel* pSwitchU = NULL;
		switch (pDeviceModel->GetCIType())
		{
		case CI_TYPE_SERVER:	
			pServerU = dynamic_cast<CRackServerUModel*>(pDeviceModel);
			if (NULL != pServerU)
			{
				pDeviceModel->Save(boRackDeviceInfo);
				babArrayServerU << boRackDeviceInfo;
			}
			else
			{
				pDeviceModel->SetSpace(0);
			}
			break;
		case CI_TYPE_CHASSIS:
			pDeviceModel->Save(boRackDeviceInfo);
			babArrayChassis << boRackDeviceInfo;
			break;
		case CI_TYPE_PDU:
			pDeviceModel->Save(boRackDeviceInfo);
			babArrayPDU << boRackDeviceInfo;
			break;
		case CI_TYPE_ACCESS_SWITCH:
			pSwitchU = dynamic_cast<CRackSwitchModel*>(pDeviceModel);
			if (NULL != pSwitchU)
			{
				pDeviceModel->Save(boRackDeviceInfo);
				((CRackSwitchModel*)pDeviceModel)->BuildArrayVlan(mapArrayVlan, babArrayVlan);
				babArraySwitch << boRackDeviceInfo;
			}
			else
			{
				pDeviceModel->SetSpace(0);
			}
			break;
		case CI_TYPE_AGGREGATION_SWITCH:						
		case CI_TYPE_CORE_SWITCH:
			pSwitchU = dynamic_cast<CRackSwitchModel*>(pDeviceModel);
			if (NULL != pSwitchU)
			{
				pDeviceModel->Save(boRackDeviceInfo);
				babArraySwitch << boRackDeviceInfo;
			}
			else
			{
				pDeviceModel->SetSpace(0);
			}

			break;
		default:
			break;
		}

		// Fill un-available U
		for (int i = iU; i < iU + pDeviceModel->GetSpace(); i++)
		{
			arrAvailableU[i] = false;
		}
		itDevice++;
	}
	// Calculate available U array
	int iPos = 1;
	while (iPos < RACK_MAX_U + 1)
	{
		BSONObj boAvailableU, boDeviceInfo, boURange, boRackDeviceInfo;
		iSpace = 0;
		iUPos = iPos;
		if (arrAvailableU[iPos])
		{
			while ((iPos < RACK_MAX_U + 1) && (arrAvailableU[iPos]))
			{
				iSpace++;
				iPos++;
			}
			/*-- Add new available entry --*/
			boAvailableU = BSON("u_id" << iUPos << "u_count" << iSpace);
			babArrayAvailableU << boAvailableU;
		}

		iPos++;		
	}
	vector<string> vRackKey = CUtilities::SplitString(strRackKey, ":");
	if (2 == vRackKey.size())
	{
		Query queryRack = QUERY("site" << vRackKey[0] << "name" << vRackKey[1]);
		//cout << "Update:" << queryRack << endl;
		m_pCIController->Update(BSON("$set" << BSON(
			"available_u" << babArrayAvailableU.arr() <<
			"chassis" << babArrayChassis.arr() <<				
			"server_u" << babArrayServerU.arr() <<						
			"switch" << babArraySwitch.arr() <<
			"pdu" << babArrayPDU.arr() <<
			"vlan" << babArrayVlan.arr()
			)), queryRack);
	}
	//cout << "-------------------" << strRackKey << endl << endl;
	/*-- clear map --*/
	mapArrayVlan.clear();
}

void CComputeRackDataProcessor::ComputeData()
{
	string strRackKey;
	RackName2DeviceArrayMap::iterator it = m_mapRackName2DeviceArray.begin();	
	while (it != m_mapRackName2DeviceArray.end())
	{
		strRackKey = (*it).first;
		DeviceModelArray* pDeviceModelArray = (*it).second;
		CalculateAvailableU(strRackKey, pDeviceModelArray);
		it++;
	}		
}
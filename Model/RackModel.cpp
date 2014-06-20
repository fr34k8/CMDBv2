#include "RackModel.h"

#define FIELD_U_ID			"u_id"
#define FIELD_U_COUNT		"u_count"
#define FIELD_AVAILABLE_U	"available_u"

CRackModel::CRackModel(void)
{
}

CRackModel::~CRackModel(void)
{
}

BSONObj CRackModel::GetAddServerURecord(BSONObj boInfo)
{
	BSONObj boRecord = BSON("$push"<<BSON("server_u"<<boInfo));
	return boRecord.copy();
}
BSONObj CRackModel::GetDeleteServerURecord(string strServerSerial)
{
	BSONObj boRecord = BSON("$pull"<<BSON("server_u"<<BSON("server_serial"<<strServerSerial)));
	return boRecord.copy();
}

BSONObj CRackModel::GetAddServerChassisRecord(BSONObj boInfo)
{
	BSONObj boRecord = BSON("$push"<<BSON("chassis.$.bay" << boInfo));
	return boRecord.copy();
}

BSONObj CRackModel::GetDeleteServerChassisRecord(std::string strServerSerial)
{
	BSONObj boRecord = BSON("$pull"<<BSON("chassis.$.bay"<<BSON("server_serial"<<strServerSerial)));
	return boRecord.copy();
}

BSONObj CRackModel::GetAddSwitchRecord(BSONObj boInfo)
{
	BSONObj boRecord = BSON("$push"<<BSON("switch"<<boInfo));
	return boRecord.copy();
}
BSONObj CRackModel::GetDeleteSwitchRecord(string strServerSerial)
{
	BSONObj boRecord = BSON("$pull"<<BSON("switch"<<BSON("switch_serial"<<strServerSerial)));
	return boRecord.copy();
}

BSONObj CRackModel::GetAddSwitchChassisRecord(BSONObj boInfo)
{
	BSONObj boRecord = BSON("$push"<<BSON("chassis.$.switch" << boInfo));
	return boRecord.copy();
}

BSONObj CRackModel::GetDeleteSwitchChassisRecord(string strSwitchSerial)
{
	BSONObj boRecord = BSON("$pull"<<BSON("chassis.$.switch"<<BSON("switch_serial"<<strSwitchSerial)));
	return boRecord.copy();
}

BSONObj CRackModel::GetAddPDURecord(const BSONObj& boInfo)
{
	BSONObj boRecord = BSON("$push"<<BSON("pdu"<<boInfo));
	return boRecord.copy();
}

BSONObj CRackModel::GetDeletePDURecord(const string& strPDUName, const string& strPDUPMM)
{
	BSONObj boRecord = BSON("$pull"<<BSON("pdu"<<BSON("name" << strPDUName << "pmm" << strPDUPMM)));
	return boRecord.copy();
}

Query CRackModel::IsExistsChassisQuery(string strRackName, string strSite, string strIPChassis)
{
	BSONObj boCond = BSON("name"<<strRackName<<"site"<<strSite<<"chassis.ip"<<strIPChassis);
	Query qCond = Query(boCond);
	return qCond;
}

Query CRackModel::IsExistsRackQuery(string strRackName, string strSite)
{
	BSONObj boCond = BSON("name"<<strRackName<<"site"<<strSite);
	Query qCond = Query(boCond);
	return qCond;
}

void CRackModel::Load(const BSONObj& boRackInfo)
{	
	if (boRackInfo.hasField(FIELD_AVAILABLE_U))
	{
		BSONElement eAvailableU = boRackInfo[FIELD_AVAILABLE_U];
		m_vtAvailableU = eAvailableU.Array();		
	}	
}

void CRackModel::InitAvailableU(bool bIsAvailable)
{
	// Init available status for Us
	for (int i = 1; i < RACK_MAX_U + 1; i++)
	{
		m_arrAvailableU[i] = bIsAvailable;
	}
}

void CRackModel::UpdateAvailableU(int nFromU, int nToU, bool bIsAvailableRange)
{
	if (nFromU > nToU)
	{
		return;
	}

	if (nToU > RACK_MAX_U)
	{
		nToU = RACK_MAX_U;
	}

	for (int i = nFromU; i < nToU + 1; i++)
	{
		m_arrAvailableU[i] = bIsAvailableRange;
	}
}

//*************************************************
//DuyMN
//*************************************************
void CRackModel::UpdateAvailableU(BSONObj& boRackInfo, int nFromU, int nToU, bool bIsAvailable)
{
	BSONArrayBuilder babArrayAvailableU;
	BSONObj boAvailableU;
		
	//*********************
	//DuyMN
	InitAvailableU(false);
	Load(boRackInfo);
	LoadAvailableU(true);
	//*********************

	UpdateAvailableU(nFromU, nToU, bIsAvailable);
	CalculateAvailableU(babArrayAvailableU);
	boAvailableU = BSON(FIELD_AVAILABLE_U << babArrayAvailableU.arr());
	cout << boAvailableU.toString() << endl;

	boRackInfo = CMongodbModel::MergeBSONObj(&boRackInfo, &boAvailableU);
}

void CRackModel::AddAvailableU(BSONObj& boRackInfo, int nFromU, int nToU)
{
	UpdateAvailableU(boRackInfo, nFromU, nToU, true);	
}

void CRackModel::RemoveAvailableU(BSONObj& boRackInfo, int nFromU, int nToU)
{	
	UpdateAvailableU(boRackInfo, nFromU, nToU, false);
}


void CRackModel::CalculateAvailableU(BSONArrayBuilder& babArrayAvailableU)
{
	// Calculate available U array
	int iPos = 1;
	int iSpace = 0;
	int iUPos;
	BSONObj boAvailableU;
	
	while (iPos <= RACK_MAX_U)
	{		
		iSpace = 0;
		iUPos = iPos;
		
		if (m_arrAvailableU[iPos])
		{
			while ((iPos <= RACK_MAX_U) && (m_arrAvailableU[iPos] == true))
			{
				iSpace++;
				iPos++;
			}

			/*-- Add new available entry --*/
			boAvailableU = BSON(FIELD_U_ID << iUPos << FIELD_U_COUNT << iSpace);

			babArrayAvailableU << boAvailableU;
		}

		iPos++;		
	}
}

void CRackModel::CreateSwitchChassisMailInfo(const BSONObj &boSwitchInfo, mongo::BSONObj &boMailDataInfo)
{
	string strRack, strSite, strIPChassis, strSwitchSerial, strSwitchName;
	
	strRack			= CMongodbModel::GetStringFieldValue(boSwitchInfo, "rack", "");
	strSite			= CMongodbModel::GetStringFieldValue(boSwitchInfo, "site", "");
	strIPChassis	= CMongodbModel::GetStringFieldValue(boSwitchInfo, "ip_chassis", "");
	strSwitchSerial = CMongodbModel::GetStringFieldValue(boSwitchInfo, "serial", "");
	strSwitchName   = CMongodbModel::GetStringFieldValue(boSwitchInfo, "name", "");
	boMailDataInfo = BSON(
			"rack" << strRack <<
			"site" << strSite <<
			"ip_chassis" << strIPChassis <<
			"serial" << strSwitchSerial <<
			"name" << strSwitchName
		);
}

void CRackModel::LoadAvailableU(bool bIsAvailable)
{
	BSONElement beU;
	BSONObj boU;
	int iUID;
	int iUCount;

	std::vector<BSONElement>::iterator it = m_vtAvailableU.begin();
	while (it != m_vtAvailableU.end())
	{
		beU = *it;		
		boU = beU.Obj();

		iUID	= boU.getIntField(FIELD_U_ID);
		iUCount = boU.getIntField(FIELD_U_COUNT);

		UpdateAvailableU(iUID, iUID +  iUCount - 1, bIsAvailable);
		
		it++;
	}
}

BSONObj CRackModel::GetVLanInfo(auto_ptr<DBClientCursor> ptrRackCursor)
{
	map<BSONElement, bool> mapArrayVlan;
	BSONArrayBuilder babArrayVLan;
	BSONObj boRackRecord, boVLanArray;
	vector<BSONElement> vbeVLanArray;
	vector<BSONElement>::iterator it;
	while (ptrRackCursor->more())
	{
		boRackRecord = ptrRackCursor->nextSafe();
		if (!boRackRecord.hasField("vlan"))
		{
			continue;
		}
		vbeVLanArray = boRackRecord["vlan"].Array();
		it = vbeVLanArray.begin();
		while (it != vbeVLanArray.end())
		{
			if (mapArrayVlan.find(*it) == mapArrayVlan.end())
			{
				mapArrayVlan[(*it)] = true;
				babArrayVLan << *it;
			}
			it++;
		}
	}
	boVLanArray = BSON("$set"<<BSON("vlan_info" << babArrayVLan.arr()));
	return boVLanArray;
}
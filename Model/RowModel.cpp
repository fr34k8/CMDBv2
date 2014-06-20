#include "RowModel.h"

CRowModel::CRowModel(void)
{
}

CRowModel::~CRowModel(void)
{
}

bool CRowModel::GetRackQuery(Query &queryRack ,BSONObj boRowRecord)
{
	bool bResult = false;
	if (boRowRecord.hasField("site") && boRowRecord.hasField("rack_info"))
	{
		queryRack = QUERY("site" << boRowRecord["site"] << "name" << BSON("$in" << boRowRecord["rack_info"].Obj()));
		bResult = true;
	}
	return bResult;
}
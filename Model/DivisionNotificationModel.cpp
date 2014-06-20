#include "DivisionNotificationModel.h"

CDivisionNotificationModel::CDivisionNotificationModel(void)
{
}

CDivisionNotificationModel::~CDivisionNotificationModel(void)
{
}

BSONObj CDivisionNotificationModel::GetNotificationInfo(BSONObj boCIInfo, BSONObj boNewCIInfo, BSONObj boAPIFields)
{
	BSONObj boAPIFields;
	StringArray arrFieldName;
	arrFieldName.push_back("_id");
	arrFieldName.push_back("notified");
	arrFieldName.push_back("deleted");
	arrFieldName.push_back("change_by");
	arrFieldName.push_back("ci_id");
	boNewCIInfo = CMongodbModel::RemoveFields(&boNewCIInfo, arrFieldName);
	arrFieldName.clear();
	arrFieldName.push_back("_id");
	boCIInfo = CMongodbModel::RemoveFields(&boCIInfo, arrFieldName);

	//boAPIFields = BSON("DC"<<0<<"status"<<0);
	boCIInfo = CMongodbModel::MergeBSONObj(&boCIInfo, &boNewCIInfo);
	boCIInfo = CMongodbModel::MergeBSONObj(&boCIInfo, &boAPIFields);
	return boCIInfo;
}

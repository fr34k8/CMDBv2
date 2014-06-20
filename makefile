INCPATH1=/home/hieutt/CMDBv2/src/
INCPATH2=/usr/local/include
INCPATH3=/home/hieutt/gsoap-2.8/gsoap
LIB1=/usr/local/lib -lmongoclient 
LIB2=/usr/lib64 -lboost_thread-mt -lboost_filesystem -lboost_system -lboost_regex -ljson_linux-gcc-4.4.7_libmt -ldl -lcurl
LIB3=-I/usr/include/mysql -g -pipe -m64 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fno-strict-aliasing
LIB4=-L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto -lcurl
CC=g++
CFLAGS=-L$(LIB1) -L$(LIB2) $(LIB3) $(LIB4) -I$(INCPATH1) -I$(INCPATH2) 

################### Division info mining #######################
DIVISION_INFO_MINING_MAIN=DivisionInfoChangeMiningMain.cpp
DIVISION_INFO_MINING_FILE=DivisionInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/DivisionInfoChangeModel.o \
./Model/CIInfoIndexModel.o ./Model/JsonModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/DivisionController.o ./Controller/CIInfoChangeController.o \
./Controller/DivisionInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/DivisionInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/DivisionInfoChangeProcessor.o \
./Processor/CIIndexPooler.o ./Processor/DivisionIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Division info index #######################
DIVISION_INFO_INDEX_MAIN=DivisionInfoIndexMain.cpp
DIVISION_INFO_INDEX_FILE=DivisionInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/DivisionInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/DivisionController.o ./Controller/CIInfoChangeController.o \
./Controller/DivisionInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/DivisionInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/DivisionInfoChangeProcessor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/DivisionInfoIndexProcessor.o ./Processor/CIIndexPooler.o ./Processor/DivisionIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Department info mining #######################
DEPARTMENT_INFO_MINING_MAIN=DepartmentInfoChangeMiningMain.cpp
DEPARTMENT_INFO_MINING_FILE=DepartmentInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/DepartmentInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o ./Model/JsonModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/DepartmentDefenseInfoModel.o ./Model/DepartmentModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/DepartmentController.o \
./Controller/DivisionController.o ./Controller/CIInfoChangeController.o \
./Controller/DepartmentInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/DepartmentInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/DepartmentInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIIndexPooler.o ./Processor/DepartmentIndexPooler.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Product info index #######################
DEPARTMENT_INFO_INDEX_MAIN=DepartmentInfoIndexMain.cpp
DEPARTMENT_INFO_INDEX_FILE=DepartmentInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/DepartmentInfoChangeModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o ./Model/JsonModel.o \
./Model/DepartmentDefenseInfoModel.o ./Model/DepartmentModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/DepartmentController.o \
./Controller/DivisionController.o ./Controller/CIInfoChangeController.o \
./Controller/DepartmentInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/DepartmentInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/DepartmentInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIInfoIndexProcessor.o ./Processor/DepartmentInfoIndexProcessor.o ./Processor/CIIndexPooler.o ./Processor/DepartmentIndexPooler.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Product info mining #######################
PRODUCT_INFO_MINING_MAIN=ProductInfoChangeMiningMain.cpp
PRODUCT_INFO_MINING_FILE=ProductInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ProductInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ProductController.o ./Controller/CIInfoChangeController.o \
./Controller/ProductInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/ProductInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ProductInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIIndexPooler.o ./Processor/ProductIndexPooler.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o
 
 ################### Product info index #######################
PRODUCT_INFO_INDEX_MAIN=ProductInfoIndexMain.cpp
PRODUCT_INFO_INDEX_FILE=ProductInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ProductInfoChangeModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ProductController.o ./Controller/CIInfoChangeController.o \
./Controller/ProductInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/ProductInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ProductInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIInfoIndexProcessor.o ./Processor/ProductInfoIndexProcessor.o ./Processor/CIIndexPooler.o ./Processor/ProductIndexPooler.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Server info mining #######################
SERVER_INFO_MINING_MAIN=ServerInfoChangeMiningMain.cpp
SERVER_INFO_MINING_FILE=ServerInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ServerInfoChangeModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ServerController.o ./Controller/CIInfoChangeController.o \
./Controller/ServerInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/ServerInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ServerInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIIndexPooler.o ./Processor/ServerIndexPooler.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Server info index #######################
SERVER_INFO_INDEX_MAIN=ServerInfoIndexMain.cpp
SERVER_INFO_INDEX_FILE=ServerInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ServerInfoChangeModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ServerController.o ./Controller/CIInfoChangeController.o \
./Controller/ServerInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/ServerInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ServerInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIInfoIndexProcessor.o ./Processor/ServerInfoIndexProcessor.o ./Processor/CIIndexPooler.o ./Processor/ServerIndexPooler.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Rack info mining #######################
RACK_INFO_MINING_MAIN=RackInfoChangeMiningMain.cpp
RACK_INFO_MINING_FILE=RackInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/RackInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Model/CIModel.o ./Model/RackModel.o ./Model/DeviceModel.o \
./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/ServerModel.o ./Model/MailboxModel.o \
./Model/RackPDUModel.o \
./Controller/MailboxController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/RackController.o ./Controller/CIInfoChangeController.o \
./Controller/RackInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/RackInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/RackInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Row info mining #######################
ROW_INFO_MINING_MAIN=RowInfoChangeMiningMain.cpp
ROW_INFO_MINING_FILE=RowInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/RowInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/RowController.o ./Controller/CIInfoChangeController.o \
./Controller/RowInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/RowInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/RowInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AccessSwitch info mining #######################
ACCESS_SWITCH_INFO_MINING_MAIN=AccessSwitchInfoChangeMiningMain.cpp
ACCESS_SWITCH_INFO_MINING_FILE=AccessSwitchInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/AccessSwitchInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/AccessSwitchController.o ./Controller/CIInfoChangeController.o \
./Controller/AccessSwitchInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/AccessSwitchInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/AccessSwitchInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### CoreSwitch info mining #######################
CORE_SWITCH_INFO_MINING_MAIN=CoreSwitchInfoChangeMiningMain.cpp
CORE_SWITCH_INFO_MINING_FILE=CoreSwitchInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/CoreSwitchInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/CoreSwitchController.o ./Controller/CIInfoChangeController.o \
./Controller/CoreSwitchInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/CoreSwitchInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/CoreSwitchInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AggregationSwitch info mining #######################
AGGREGATION_SWITCH_INFO_MINING_MAIN=AggregationSwitchInfoChangeMiningMain.cpp
AGGREGATION_SWITCH_INFO_MINING_FILE=AggregationSwitchInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/AggregationSwitchInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/AggregationSwitchController.o ./Controller/CIInfoChangeController.o \
./Controller/AggregationSwitchInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/AggregationSwitchInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/AggregationSwitchInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PDU info mining #######################
PDU_INFO_MINING_MAIN=PDUInfoChangeMiningMain.cpp
PDU_INFO_MINING_FILE=PDUInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PDUInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PDUController.o ./Controller/CIInfoChangeController.o \
./Controller/PDUInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/PDUInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/PDUInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Chassis info mining #######################
CHASSIS_INFO_MINING_MAIN=ChassisInfoChangeMiningMain.cpp
CHASSIS_INFO_MINING_FILE=ChassisInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ChassisInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ChassisController.o ./Controller/CIInfoChangeController.o \
./Controller/ChassisInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/ChassisInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ChassisInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PeerLink info mining #######################
PEER_LINK_INFO_MINING_MAIN=PeerLinkInfoChangeMiningMain.cpp
PEER_LINK_INFO_MINING_FILE=PeerLinkInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PeerLinkInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PeerLinkController.o ./Controller/CIInfoChangeController.o \
./Controller/PeerLinkInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/PeerLinkInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/PeerLinkInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PMM info mining #######################
PMM_INFO_MINING_MAIN=PMMInfoChangeMiningMain.cpp
PMM_INFO_MINING_FILE=PMMInfoChangeMiningMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PMMInfoChangeModel.o ./Model/CIInfoIndexModel.o \
./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PMMController.o ./Controller/CIInfoChangeController.o \
./Controller/PMMInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/PMMInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/PMMInfoChangeProcessor.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Physical Server Info Update #######################
PHYSICAL_SERVER_INFO_UPDATE_MAIN=PhysicalServerInfoUpdateMain.cpp
PHYSICAL_SERVER_INFO_UPDATE_FILE=PhysicalServerInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ServerInfoChangeModel.o \
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/ServerHistoryLogModel.o \
./Model/NotificationModel.o ./Model/ServerNotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Model/DeviceModel.o ./Model/RackModel.o ./Model/RackServerUModel.o \
./Model/RackBayChassisModel.o ./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/RackPDUModel.o ./Model/UserModel.o ./Model/JsonModel.o \
./Model/RoleOwnerModel.o ./Model/TechnicalOwnerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ServerController.o  \
./Controller/CIInfoUpdateController.o ./Controller/PhysicalServerInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/ServerInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/ServerHistoryLogController.o \
./Controller/NotificationController.o ./Controller/PhysicalServerNotificationController.o \
./Controller/PartnerInfoController.o ./Controller/UserController.o \
./Controller/MailboxController.o \
./Controller/CIRelationshipController.o \
./Controller/RackController.o \
./Controller/AdminController.o ./Controller/AdminProductOwnerController.o ./Controller/AdminProductRolesController.o \
./Controller/AdminUserGroupsProductsController.o ./Controller/AdminUserGroupsUsersController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ServerInfoChangeProcessor.o ./Processor/Thread.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/PhysicalServerInfoUpdateProcessor.o \
./Processor/ComputeDataProcessor.o ./Processor/ComputeServerDataProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Virtual Server Info Update #######################
VIRTUAL_SERVER_INFO_UPDATE_MAIN=VirtualServerInfoUpdateMain.cpp
VIRTUAL_SERVER_INFO_UPDATE_FILE=VirtualServerInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ServerInfoChangeModel.o \
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/ServerHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Model/RoleOwnerModel.o ./Model/TechnicalOwnerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ServerController.o  \
./Controller/CIInfoUpdateController.o ./Controller/VirtualServerInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/ServerInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/ServerHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Controller/AdminController.o ./Controller/AdminProductOwnerController.o ./Controller/AdminProductRolesController.o \
./Controller/AdminUserGroupsProductsController.o ./Controller/AdminUserGroupsUsersController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ServerInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/VirtualServerInfoUpdateProcessor.o \
./Processor/ComputeDataProcessor.o ./Processor/ComputeServerDataProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o


################### Division Server Info Update #######################
DIVISION_INFO_UPDATE_MAIN=DivisionInfoUpdateMain.cpp
DIVISION_INFO_UPDATE_FILE=DivisionInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/DivisionInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/DivisionHistoryLogModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/DivisionController.o  \
./Controller/CIInfoUpdateController.o ./Controller/DivisionInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/DivisionInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/DivisionHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/DivisionInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/DivisionInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Department Server Info Update #######################
DEPARTMENT_INFO_UPDATE_MAIN=DepartmentInfoUpdateMain.cpp
DEPARTMENT_INFO_UPDATE_FILE=DepartmentInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/DepartmentInfoChangeModel.o \
./Model/CIModel.o ./Model/JsonModel.o \
./Model/CIHistoryLogModel.o ./Model/DepartmentHistoryLogModel.o \
./Model/DepartmentDefenseInfoModel.o ./Model/DepartmentModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/NotificationModel.o  ./Model/DepartmentNotificationModel.o\
./Model/PartnerInfoModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/DepartmentController.o  \
./Controller/DivisionController.o \
./Controller/CIInfoUpdateController.o ./Controller/DepartmentInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/DepartmentInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/DepartmentHistoryLogController.o \
./Controller/NotificationController.o ./Controller/DepartmentNotificationController.o \
./Controller/PartnerInfoController.o \./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/DepartmentInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/DepartmentInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Product Server Info Update #######################
PRODUCT_INFO_UPDATE_MAIN=ProductInfoUpdateMain.cpp
PRODUCT_INFO_UPDATE_FILE=ProductInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ProductInfoChangeModel.o \
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/ProductHistoryLogModel.o \
./Model/NotificationModel.o ./Model/ProductNotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ProductController.o  \
./Controller/CIInfoUpdateController.o ./Controller/ProductInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/ProductInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/ProductHistoryLogController.o \
./Controller/NotificationController.o ./Controller/ProductNotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ProductInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/ProductInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Product Notification #######################
PRODUCT_NOTIFICATION_MAIN=ProductNotificationMain.cpp
PRODUCT_NOTIFICATION_FILE=ProductNotificationMain.o \
./Model/MongodbModel.o ./Model/NotificationModel.o ./Model/PartnerInfoModel.o \
./Model/CIModel.o \
./Model/MailboxModel.o ./Model/RackModel.o ./Model/ServerModel.o ./Model/DeviceModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/NotificationController.o ./Controller/PartnerInfoController.o ./Controller/ProductNotificationController.o \
./Controller/CIRelationshipController.o ./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/NotificationProcessor.o ./Processor/ProductNotificationProcessor.o \
./Notification/NotificationAPI.o ./Notification/DCProductNotificationAPI.o ./Notification/MISProductNotificationAPI.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Division Synchronization #######################
DIVISION_SYNCHRONIZATION_MAIN=DivisionSynchronizationMain.cpp
DIVISION_SYNCHRONIZATION_FILE=DivisionSynchronizationMain.o \
./Model/MongodbModel.o ./Model/CollectorModel.o ./Model/JsonModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/DepartmentDefenseInfoModel.o ./Model/DepartmentModel.o \
./Model/MailboxModel.o ./Model/RackModel.o ./Model/ServerModel.o ./Model/DeviceModel.o ./Model/CIModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/CollectorController.o ./Controller/DivisionController.o  \
./Controller/DepartmentController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/SynchronizationProcessor.o ./Processor/DivisionInfoSynchronizationProcessor.o \
./Synchronization/SynchronizationData.o ./Synchronization/MISDivisionSynchronization.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o 

################### Department Synchronization #######################
DEPARTMENT_SYNCHRONIZATION_MAIN=DepartmentSynchronizationMain.cpp
DEPARTMENT_SYNCHRONIZATION_FILE=DepartmentSynchronizationMain.o \
./Model/MongodbModel.o ./Model/CollectorModel.o ./Model/JsonModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/DepartmentDefenseInfoModel.o ./Model/DepartmentModel.o \
./Model/MailboxModel.o ./Model/RackModel.o ./Model/ServerModel.o ./Model/DeviceModel.o ./Model/CIModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/CollectorController.o ./Controller/DepartmentController.o \
./Controller/DivisionController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/SynchronizationProcessor.o ./Processor/DepartmentInfoSynchronizationProcessor.o \
./Synchronization/SynchronizationData.o ./Synchronization/MISDepartmentSynchronization.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o 

################### Server Notification #######################
SERVER_NOTIFICATION_MAIN=PhysicalServerNotificationMain.cpp
SERVER_NOTIFICATION_FILE=PhysicalServerNotificationMain.o \
./Model/MongodbModel.o ./Model/NotificationModel.o ./Model/PartnerInfoModel.o \
./Model/CIModel.o \
./Model/MailboxModel.o ./Model/RackModel.o ./Model/ServerModel.o ./Model/DeviceModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/MailboxController.o \
./Controller/NotificationController.o ./Controller/PartnerInfoController.o ./Controller/PhysicalServerNotificationController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/NotificationProcessor.o ./Processor/PhysicalServerNotificationProcessor.o \
./Notification/NotificationAPI.o ./Notification/DCServerNotificationAPI.o ./Notification/SnSServerNotificationAPI.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### User Synchronization #######################
USER_SYNCHRONIZATION_MAIN=UserSynchronizationMain.cpp
USER_SYNCHRONIZATION_FILE=UserSynchronizationMain.o \
./Model/MongodbModel.o ./Model/CollectorModel.o ./Model/JsonModel.o \
./Model/DepartmentDefenseInfoModel.o ./Model/DepartmentModel.o \
./Model/DivisionDefenseInfoModel.o ./Model/DivisionModel.o \
./Model/UserModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/CollectorController.o ./Controller/UserController.o  \
./Controller/DepartmentController.o ./Controller/DivisionController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/SynchronizationProcessor.o ./Processor/UserInfoSynchronizationProcessor.o \
./Synchronization/SynchronizationData.o ./Synchronization/MISUserSynchronization.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o 

################### Server Checker Statistic#######################
SERVER_STATISTIC_CHECKER_MAIN = ServerStatisticCheckerMain.cpp
SERVER_STATISTIC_CHECKER_FILE = ServerStatisticCheckerMain.o \
./Model/MongodbModel.o ./Model/CollectorModel.o ./Model/JsonModel.o \
./Model/ServerStatisticCheckerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/CollectorController.o ./Controller/CheckerController.o  \
./Controller/ServerStatisticCheckerController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CheckerProcessor.o ./Processor/ServerCheckerProcessor.o \
./DataChecker/BaseChecker.o ./DataChecker/ServerChecker.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Hardware Checker Statistic#######################
HARDWARE_CHECKER_MAIN = HardwareInfoCheckerMain.cpp
HARDWARE_CHECKER_FILE = HardwareInfoCheckerMain.o \
./Model/MongodbModel.o ./Model/CollectorModel.o ./Model/JsonModel.o \
./Model/HardwareCheckerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/CollectorController.o ./Controller/CheckerController.o  \
./Controller/HardwareCheckerController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CheckerProcessor.o ./Processor/HardwareCheckerProcessor.o \
./DataChecker/BaseChecker.o ./DataChecker/HardwareChecker.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Interface Checker Statistic#######################
INTERFACE_CHECKER_MAIN = InterfaceInfoCheckerMain.cpp
INTERFACE_CHECKER_FILE = InterfaceInfoCheckerMain.o \
./Model/MongodbModel.o ./Model/CollectorModel.o ./Model/JsonModel.o \
./Model/InterfaceCheckerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/CollectorController.o ./Controller/CheckerController.o  \
./Controller/InterfaceCheckerController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Config/md5.o \
./Processor/Processor.o \
./Processor/CheckerProcessor.o ./Processor/InterfaceCheckerProcessor.o \
./External/BaseExternal.o ./External/SDKService.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Product Total Cross Check #######################
# PRODUCT_TOTAL_CROSS_CHECK_MAIN = ProductTotalCrossCheckMain.cpp
# PRODUCT_TOTAL_CROSS_CHECK_FILE = ProductTotalCrossCheckMain.o \
# ./Model/MongodbModel.o ./Model/JsonModel.o \
# ./Controller/MongodbController.o ./Controller/CMDBController.o \
# ./Config/ConfigFile.o ./Config/ConfigReader.o \
# ./Processor/Processor.o \
# ./Processor/CITotalCrossCheckProcessor.o ./Processor/ProductTotalCrossCheckProcessor.o \
# ./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Rack info index #######################
RACK_INFO_INDEX_MAIN=RackInfoIndexMain.cpp
RACK_INFO_INDEX_FILE=RackInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/RackInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Model/RackDefenseInfoModel.o \
./Model/CIModel.o ./Model/RackModel.o ./Model/DeviceModel.o \
./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/ServerModel.o ./Model/MailboxModel.o \
./Model/RackPDUModel.o \
./Controller/MailboxController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/RackController.o ./Controller/CIInfoChangeController.o \
./Controller/RackInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/RackInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/RackInfoChangeProcessor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/RackInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/RackIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### CoreSwitch info index #######################
CORE_SWITCH_INFO_INDEX_MAIN=CoreSwitchInfoIndexMain.cpp
CORE_SWITCH_INFO_INDEX_FILE=CoreSwitchInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/CoreSwitchInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Model/CoreSwitchDefenseInfoModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/CoreSwitchController.o ./Controller/CIInfoChangeController.o \
./Controller/CoreSwitchInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/CoreSwitchInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/CoreSwitchInfoChangeProcessor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/CoreSwitchInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/CoreSwitchIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AggregationSwitch info index #######################
AGGREGATION_SWITCH_INFO_INDEX_MAIN=AggregationSwitchInfoIndexMain.cpp
AGGREGATION_SWITCH_INFO_INDEX_FILE=AggregationSwitchInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/AggregationSwitchInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Model/AggregationSwitchDefenseInfoModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/AggregationSwitchController.o ./Controller/CIInfoChangeController.o \
./Controller/AggregationSwitchInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/AggregationSwitchInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoChangeProcessor.o ./Processor/AggregationSwitchInfoChangeProcessor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/AggregationSwitchInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/AggregationSwitchIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################## AccessSwitch info index #######################
ACCESS_SWITCH_INFO_INDEX_MAIN=AccessSwitchInfoIndexMain.cpp
ACCESS_SWITCH_INFO_INDEX_FILE=AccessSwitchInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/AccessSwitchInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Model/AccessSwitchDefenseInfoModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/AccessSwitchController.o ./Controller/CIInfoChangeController.o \
./Controller/AccessSwitchInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/AccessSwitchInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/AccessSwitchInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/AccessSwitchIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Chassis info index #######################
CHASSIS_INFO_INDEX_MAIN=ChassisInfoIndexMain.cpp
CHASSIS_INFO_INDEX_FILE=ChassisInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ChassisInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ChassisController.o ./Controller/CIInfoChangeController.o \
./Controller/ChassisInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/ChassisInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/ChassisInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/ChassisIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PeerLink info index #######################
PEERLINK_INFO_INDEX_MAIN=PeerLinkInfoIndexMain.cpp
PEERLINK_INFO_INDEX_FILE=PeerLinkInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PeerLinkInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PeerLinkController.o ./Controller/CIInfoChangeController.o \
./Controller/PeerLinkInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/PeerLinkInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/PeerLinkInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/PeerLinkIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PDU info index #######################
PDU_INFO_INDEX_MAIN=PDUInfoIndexMain.cpp
PDU_INFO_INDEX_FILE=PDUInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PDUInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PDUController.o ./Controller/CIInfoChangeController.o \
./Controller/PDUInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/PDUInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/PDUInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/PDUIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Row info index #######################
ROW_INFO_INDEX_MAIN=RowInfoIndexMain.cpp
ROW_INFO_INDEX_FILE=RowInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/RowInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/RowController.o ./Controller/CIInfoChangeController.o \
./Controller/RowInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/RowInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/RowInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/RowIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PMM info index #######################
PMM_INFO_INDEX_MAIN=PMMInfoIndexMain.cpp
PMM_INFO_INDEX_FILE=PMMInfoIndexMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PMMInfoChangeModel.o ./Model/JsonModel.o \
./Model/CIInfoIndexModel.o ./Model/CIIndexPoolerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PMMController.o ./Controller/CIInfoChangeController.o \
./Controller/PMMInfoChangeController.o ./Controller/CIInfoIndexController.o ./Controller/PMMInfoIndexController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o \
./Processor/CIInfoIndexProcessor.o ./Processor/PMMInfoIndexProcessor.o \
./Processor/CIIndexPooler.o ./Processor/PMMIndexPooler.o ./Processor/Thread.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PMM Server Info Update #######################
PMM_INFO_UPDATE_MAIN=PMMInfoUpdateMain.cpp
PMM_INFO_UPDATE_FILE=PMMInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PMMInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/PMMHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PMMController.o  \
./Controller/CIInfoUpdateController.o ./Controller/PMMInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/PMMInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/PMMHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/PMMInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/PMMInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Row Server Info Update #######################
ROW_INFO_UPDATE_MAIN=RowInfoUpdateMain.cpp
ROW_INFO_UPDATE_FILE=RowInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/RowInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/RowHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/RowController.o  \
./Controller/CIInfoUpdateController.o ./Controller/RowInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/RowInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/RowHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/RowInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/RowInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Rack Server Info Update #######################
RACK_INFO_UPDATE_MAIN=RackInfoUpdateMain.cpp
RACK_INFO_UPDATE_FILE=RackInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/RackInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/RackHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/MailboxModel.o \
./Model/RackModel.o ./Model/DeviceModel.o \
./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/ServerModel.o \
./Model/RackPDUModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/RackController.o  \
./Controller/CIInfoUpdateController.o ./Controller/RackInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/RackInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/RackHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/RackInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/RackInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### CoreSwitch Server Info Update #######################
CORE_SWITCH_INFO_UPDATE_MAIN=CoreSwitchInfoUpdateMain.cpp
CORE_SWITCH_INFO_UPDATE_FILE=CoreSwitchInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/CoreSwitchInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/CoreSwitchHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Model/RackModel.o ./Model/DeviceModel.o ./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/RackPDUModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/CoreSwitchController.o  \
./Controller/CIInfoUpdateController.o ./Controller/CoreSwitchInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/CoreSwitchInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/CoreSwitchHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Controller/RackController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/CoreSwitchInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/CoreSwitchInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AggregationSwitch Server Info Update #######################
AGGREGATION_SWITCH_INFO_UPDATE_MAIN=AggregationSwitchInfoUpdateMain.cpp
AGGREGATION_SWITCH_INFO_UPDATE_FILE=AggregationSwitchInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/AggregationSwitchInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/AggregationSwitchHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Model/RackModel.o ./Model/DeviceModel.o ./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/RackPDUModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/AggregationSwitchController.o  \
./Controller/CIInfoUpdateController.o ./Controller/AggregationSwitchInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/AggregationSwitchInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/AggregationSwitchHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Controller/RackController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/AggregationSwitchInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/AggregationSwitchInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AccessSwitch Server Info Update #######################
ACCESS_SWITCH_INFO_UPDATE_MAIN=AccessSwitchInfoUpdateMain.cpp
ACCESS_SWITCH_INFO_UPDATE_FILE=AccessSwitchInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/AccessSwitchInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/AccessSwitchHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Model/RackModel.o ./Model/RackSwitchModel.o \
./Model/DeviceModel.o ./Model/RackSwitchChassisModel.o \
./Model/RackPDUModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/AccessSwitchController.o  \
./Controller/CIInfoUpdateController.o ./Controller/AccessSwitchInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/AccessSwitchInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/AccessSwitchHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Controller/RackController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/AccessSwitchInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/AccessSwitchInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Chassis Server Info Update #######################
CHASSIS_INFO_UPDATE_MAIN=ChassisInfoUpdateMain.cpp
CHASSIS_INFO_UPDATE_FILE=ChassisInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/ChassisInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/ChassisHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o \
./Model/DeviceModel.o ./Model/RackModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/ChassisController.o  \
./Controller/CIInfoUpdateController.o ./Controller/ChassisInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/ChassisInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/ChassisHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/ChassisInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/ChassisInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PDU Server Info Update #######################
PDU_INFO_UPDATE_MAIN=PDUInfoUpdateMain.cpp
PDU_INFO_UPDATE_FILE=PDUInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PDUInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/PDUHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o ./Model/DeviceModel.o \
./Model/MailboxModel.o ./Model/RackModel.o ./Model/ServerModel.o ./Model/RackPDUModel.o \
./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PDUController.o  \
./Controller/CIInfoUpdateController.o ./Controller/PDUInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/PDUInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/PDUHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Controller/RackController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/PDUInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/PDUInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### PeerLink Server Info Update #######################
PEERLINK_INFO_UPDATE_MAIN=PeerLinkInfoUpdateMain.cpp
PEERLINK_INFO_UPDATE_FILE=PeerLinkInfoUpdateMain.o \
./Model/MongodbModel.o ./Model/CIInfoChangeModel.o ./Model/PeerLinkInfoChangeModel.o ./Model/JsonModel.o\
./Model/CIModel.o \
./Model/CIHistoryLogModel.o ./Model/PeerLinkHistoryLogModel.o \
./Model/NotificationModel.o \
./Model/PartnerInfoModel.o ./Model/DeviceModel.o \
./Model/MailboxModel.o ./Model/ServerModel.o ./Model/RackModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o ./Controller/PeerLinkController.o  \
./Controller/CIInfoUpdateController.o ./Controller/PeerLinkInfoUpdateController.o\
./Controller/CIInfoChangeController.o ./Controller/PeerLinkInfoChangeController.o \
./Controller/CIHistoryLogController.o ./Controller/PeerLinkHistoryLogController.o \
./Controller/NotificationController.o \
./Controller/PartnerInfoController.o \
./Controller/CIRelationshipController.o \
./Controller/MailboxController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoChangeProcessor.o ./Processor/PeerLinkInfoChangeProcessor.o \
./Processor/CIInfoUpdateProcessor.o ./Processor/PeerLinkInfoUpdateProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Server Model Mapping #######################
SERVER_MODEL_MAPPING_MAIN=ServerInfoMappingMain.cpp
SERVER_MODEL_MAPPING_FILE=ServerInfoMappingMain.o \
./Model/MongodbModel.o ./Model/CIModel.o ./Model/DeviceModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/ServerController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoMappingProcessor.o ./Processor/ServerInfoMappingProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Chassis Model Mapping #######################
CHASSIS_MODEL_MAPPING_MAIN=ChassisInfoMappingMain.cpp
CHASSIS_MODEL_MAPPING_FILE=ChassisInfoMappingMain.o \
./Model/MongodbModel.o ./Model/CIModel.o ./Model/DeviceModel.o ./Model/ChassisModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/ChassisController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoMappingProcessor.o ./Processor/ChassisInfoMappingProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AggregationSwitch Model Mapping #######################
AGGREGATIONSWITCH_MODEL_MAPPING_MAIN=AggregationSwitchInfoMappingMain.cpp
AGGREGATIONSWITCH_MODEL_MAPPING_FILE=AggregationSwitchInfoMappingMain.o \
./Model/MongodbModel.o ./Model/CIModel.o ./Model/DeviceModel.o ./Model/AggregationSwitchModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/AggregationSwitchController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoMappingProcessor.o ./Processor/AggregationSwitchInfoMappingProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AccessSwitch Model Mapping #######################
ACCESSSWITCH_MODEL_MAPPING_MAIN=AccessSwitchInfoMappingMain.cpp
ACCESSSWITCH_MODEL_MAPPING_FILE=AccessSwitchInfoMappingMain.o \
./Model/MongodbModel.o ./Model/CIModel.o ./Model/DeviceModel.o ./Model/AccessSwitchModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/AccessSwitchController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoMappingProcessor.o ./Processor/AccessSwitchInfoMappingProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### CoreSwitch Model Mapping #######################
CORESWITCH_MODEL_MAPPING_MAIN=CoreSwitchInfoMappingMain.cpp
CORESWITCH_MODEL_MAPPING_FILE=CoreSwitchInfoMappingMain.o \
./Model/MongodbModel.o ./Model/CIModel.o ./Model/DeviceModel.o ./Model/CoreSwitchModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/CoreSwitchController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoMappingProcessor.o ./Processor/CoreSwitchInfoMappingProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Model Mapping #######################
MODEL_MAPPING_MAIN=CIInfoMappingMain.cpp
MODEL_MAPPING_FILE=CIInfoMappingMain.o \
./Model/MongodbModel.o ./Model/CIModel.o ./Model/DeviceModel.o \
./Model/AggregationSwitchModel.o ./Model/AccessSwitchModel.o ./Model/CoreSwitchModel.o \
./Model/ChassisModel.o ./Model/ServerModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CMDBController.o \
./Controller/AggregationSwitchController.o ./Controller/AccessSwitchController.o ./Controller/CoreSwitchController.o \
./Controller/ChassisController.o ./Controller/ServerController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/CIInfoMappingProcessor.o ./Processor/AggregationSwitchInfoMappingProcessor.o \
./Processor/AccessSwitchInfoMappingProcessor.o ./Processor/CoreSwitchInfoMappingProcessor.o \
./Processor/ChassisInfoMappingProcessor.o ./Processor/ServerInfoMappingProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Server U Space Updating #######################
SERVER_USPACE_UPDATE_MAIN=UpdateServerUSpaceMain.cpp
SERVER_USPACE_UPDATE_FILE=UpdateServerUSpaceMain.o \
./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/ServerController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/UpdateCIUSpaceProcessor.o ./Processor/UpdateServerUSpaceProcessor.o ./Processor/CUpdateChassisUSpaceProcesso.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### Chassis U Space Updating #######################
CHASSIS_USPACE_UPDATE_MAIN=UpdateChassisUSpaceMain.cpp
CHASSIS_USPACE_UPDATE_FILE=UpdateChassisUSpaceMain.o \
./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/ChassisController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/UpdateCIUSpaceProcessor.o ./Processor/UpdateChassisUSpaceProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################# AggregationSwitch U Space Updating #######################
AGGREGATIONSWITCH_USPACE_UPDATE_MAIN=UpdateAggregationSwitchUSpaceMain.cpp
AGGREGATIONSWITCH_USPACE_UPDATE_FILE=UpdateAggregationSwitchUSpaceMain.o \
./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/AggregationSwitchController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/UpdateCIUSpaceProcessor.o ./Processor/UpdateAggregationSwitchUSpaceProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################# AccessSwitch U Space Updating #######################
ACCESSSWITCH_USPACE_UPDATE_MAIN=UpdateAccessSwitchUSpaceMain.cpp
ACCESSSWITCH_USPACE_UPDATE_FILE=UpdateAccessSwitchUSpaceMain.o \
./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/AccessSwitchController.o\
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/UpdateCIUSpaceProcessor.o ./Processor/UpdateAccessSwitchUSpaceProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################# CoreSwitch U Space Updating #######################
CORESWITCH_USPACE_UPDATE_MAIN=UpdateCoreSwitchUSpaceMain.cpp
CORESWITCH_USPACE_UPDATE_FILE=UpdateCoreSwitchUSpaceMain.o \
./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o ./Controller/CoreSwitchController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/UpdateCIUSpaceProcessor.o ./Processor/UpdateCoreSwitchUSpaceProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################# CoreSwitch U Space Updating #######################
USPACE_UPDATE_MAIN=UpdateCIUSpaceMain.cpp
USPACE_UPDATE_FILE=UpdateCIUSpaceMain.o \
./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Controller/CMDBController.o \
./Controller/ServerController.o ./Controller/AccessSwitchController.o \
./Controller/AggregationSwitchController.o ./Controller/ChassisController.o \
./Controller/CoreSwitchController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Processor/Processor.o ./Processor/Thread.o \
./Processor/UpdateCIUSpaceProcessor.o ./Processor/UpdateCoreSwitchUSpaceProcessor.o \
./Processor/UpdateAccessSwitchUSpaceProcessor.o ./Processor/UpdateAggregationSwitchUSpaceProcessor.o \
./Processor/UpdateChassisUSpaceProcessor.o ./Processor/UpdateServerUSpaceProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o

################### AccessSwitch Data Compute #######################
ACCESS_SWITCH_DATA_COMPUTE_MAIN=AccessSwitchDataComputeMain.cpp
ACCESS_SWITCH_DATA_COMPUTE_FILE=AccessSwitchDataComputeMain.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Model/AccessSwitchModel.o ./Model/DeviceModel.o \
./Model/CIModel.o ./Model/MongodbModel.o \
./Controller/AccessSwitchController.o ./Controller/CMDBController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Processor/Processor.o ./Processor/ComputeDataProcessor.o \
./Processor/ComputeAccessSwitchDataProcessor.o

################### AggregationSwitch Data Compute #######################
AGGREGATION_SWITCH_DATA_COMPUTE_MAIN=AggregationSwitchDataComputeMain.cpp
AGGREGATION_SWITCH_DATA_COMPUTE_FILE=AggregationSwitchDataComputeMain.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Model/AggregationSwitchModel.o ./Model/DeviceModel.o \
./Model/CIModel.o ./Model/MongodbModel.o \
./Controller/AggregationSwitchController.o ./Controller/CMDBController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Processor/Processor.o ./Processor/ComputeDataProcessor.o \
./Processor/ComputeAggregationSwitchDataProcessor.o

################### Rack Data Compute #######################
RACK_DATA_COMPUTE_MAIN=ComputeRackDataMain.cpp
RACK_DATA_COMPUTE_FILE=ComputeRackDataMain.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Model/ServerModel.o ./Model/RackBayChassisModel.o ./Model/RackSwitchChassisModel.o \
./Model/DeviceModel.o ./Model/RackServerUModel.o \
./Model/CIModel.o ./Model/MongodbModel.o ./Model/RackChassisModel.o \
./Model/ChassisModel.o ./Model/RackSwitchModel.o \
./Model/RackModel.o ./Model/MailboxModel.o ./Model/RackPDUModel.o \
./Controller/ServerController.o ./Controller/AccessSwitchController.o \
./Controller/AggregationSwitchController.o ./Controller/ChassisController.o \
./Controller/CoreSwitchController.o ./Controller/RackController.o \
./Controller/MailboxController.o \
./Controller/CMDBController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Processor/Processor.o ./Processor/ComputeDataProcessor.o \
./Processor/ComputeRackDataProcessor.o

################### Technical Owner Server Data Compute #######################
TECHNICAL_OWNER_SERVER_DATA_COMPUTE_MAIN=TechnicalOwnerServerComputeMain.cpp
TECHNICAL_OWNER_SERVER_DATA_COMPUTE_FILE=TechnicalOwnerServerComputeMain.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Model/RoleOwnerModel.o ./Model/TechnicalOwnerModel.o \
./Model/CIModel.o ./Model/MongodbModel.o \
./Controller/MongodbController.o ./Controller/CMDBController.o \
./Controller/MySQLController.o ./Controller/ServerController.o \
./Controller/AdminController.o ./Controller/AdminProductOwnerController.o ./Controller/AdminProductRolesController.o \
./Controller/AdminUserGroupsProductsController.o ./Controller/AdminUserGroupsUsersController.o \
./Processor/Processor.o ./Processor/ComputeDataProcessor.o \
./Processor/ComputeServerDataProcessor.o

################### Server Internal Data Check #######################
SERVER_INTERNAL_DATA_CHECK_MAIN=InternalServerDataCheckMain.cpp
SERVER_INTERNAL_DATA_CHECK_FILE=InternalServerDataCheckMain.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Model/ServerModel.o ./Model/DeviceModel.o \
./Model/CIModel.o ./Model/MongodbModel.o \
./Controller/ServerController.o ./Controller/CMDBController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Processor/Processor.o ./Processor/InternalDataCheckProcessor.o \
./Processor/InternalServerDataCheckProcessor.o

################### Row Data Compute #######################
ROW_DATA_COMPUTE_MAIN=ComputeRowDataMain.cpp
ROW_DATA_COMPUTE_FILE=ComputeRowDataMain.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Model/ServerModel.o \
./Model/DeviceModel.o ./Model/RackSwitchModel.o ./Model/RackSwitchChassisModel.o \
./Model/CIModel.o ./Model/MongodbModel.o \
./Model/RackModel.o ./Model/RowModel.o ./Model/MailboxModel.o \
./Controller/RowController.o ./Controller/RackController.o \
./Controller/MailboxController.o \
./Controller/CMDBController.o \
./Controller/MongodbController.o ./Controller/MySQLController.o \
./Processor/Processor.o ./Processor/ComputeDataProcessor.o \
./Processor/ComputeRowDataProcessor.o

all: main file 
main: ServerInfoChangeMiningMain.o ServerInfoIndexMain.o \
	PhysicalServerInfoUpdateMain.o VirtualServerInfoUpdateMain.o \
	DivisionInfoUpdateMain.o DepartmentInfoUpdateMain.o ProductInfoUpdateMain.o \
	DivisionInfoChangeMiningMain.o DivisionInfoIndexMain.o \
	DepartmentInfoChangeMiningMain.o DepartmentInfoIndexMain.o \
	ProductInfoChangeMiningMain.o ProductInfoIndexMain.o \
	DivisionSynchronizationMain.o DepartmentSynchronizationMain.o \
	ProductNotificationMain.o PhysicalServerNotificationMain.o \
	UserSynchronizationMain.o ServerStatisticCheckerMain.o \
	HardwareInfoCheckerMain.o InterfaceInfoCheckerMain.o \
	RackInfoChangeMiningMain.o RowInfoChangeMiningMain.o \
	AccessSwitchInfoChangeMiningMain.o CoreSwitchInfoChangeMiningMain.o \
	AggregationSwitchInfoChangeMiningMain.o PDUInfoChangeMiningMain.o \
	ChassisInfoChangeMiningMain.o PeerLinkInfoChangeMiningMain.o \
	RackInfoIndexMain.o CoreSwitchInfoIndexMain.o \
	AggregationSwitchInfoIndexMain.o AccessSwitchInfoIndexMain.o \
	ChassisInfoIndexMain.o PeerLinkInfoIndexMain.o \
	PDUInfoIndexMain.o RowInfoIndexMain.o \
	RowInfoUpdateMain.o PDUInfoUpdateMain.o PeerLinkInfoUpdateMain.o ChassisInfoUpdateMain.o \
	AccessSwitchInfoUpdateMain.o AggregationSwitchInfoUpdateMain.o CoreSwitchInfoUpdateMain.o RackInfoUpdateMain.o \
	ServerInfoMappingMain.o ChassisInfoMappingMain.o CoreSwitchInfoMappingMain.o \
	AggregationSwitchInfoMappingMain.o AccessSwitchInfoMappingMain.o CIInfoMappingMain.o \
	UpdateServerUSpaceMain.o UpdateChassisUSpaceMain.o \
	UpdateAggregationSwitchUSpaceMain.o UpdateAccessSwitchUSpaceMain.o UpdateCoreSwitchUSpaceMain.o \
	AccessSwitchDataComputeMain.o ComputeRackDataMain.o AggregationSwitchDataComputeMain.o \
	UpdateCIUSpaceMain.o InternalServerDataCheckMain.o \
	TechnicalOwnerServerComputeMain.o ComputeRowDataMain.o \
	PMMInfoIndexMain.o PMMInfoChangeMiningMain.o PMMInfoUpdateMain.o
	
DivisionInfoChangeMiningMain.o: $(DIVISION_INFO_MINING_MAIN)
	$(CC) -c $(DIVISION_INFO_MINING_MAIN)
DivisionInfoIndexMain.o: $(DIVISION_INFO_INDEX_MAIN)
	$(CC) -c $(DIVISION_INFO_INDEX_MAIN)	
DepartmentInfoChangeMiningMain.o: $(DEPARTMENT_INFO_MINING_MAIN)
	$(CC) -c $(DEPARTMENT_INFO_MINING_MAIN)	
DepartmentInfoIndexMain.o: $(DEPARTMENT_INFO_INDEX_MAIN)
	$(CC) -c $(DEPARTMENT_INFO_INDEX_MAIN)	
ProductInfoChangeMiningMain.o: $(PRODUCT_INFO_MINING_MAIN)
	$(CC) -c $(PRODUCT_INFO_MINING_MAIN)
ProductInfoIndexMain.o: $(PRODUCT_INFO_INDEX_MAIN)
	$(CC) -c $(PRODUCT_INFO_INDEX_MAIN)
ServerInfoChangeMiningMain.o: $(SERVER_INFO_MINING_MAIN)
	$(CC) -c $(SERVER_INFO_MINING_MAIN)
ServerInfoIndexMain.o: 	$(SERVER_INFO_INDEX_MAIN)
	$(CC) -c $(SERVER_INFO_INDEX_MAIN)
PhysicalServerInfoUpdateMain.o:  $(PHYSICAL_SERVER_INFO_UPDATE_MAIN)
	$(CC) -c $(PHYSICAL_SERVER_INFO_UPDATE_MAIN)
VirtualServerInfoUpdateMain.o:  $(VIRTUAL_SERVER_INFO_UPDATE_MAIN)
	$(CC) -c $(VIRTUAL_SERVER_INFO_UPDATE_MAIN)
DivisionInfoUpdateMain.o:  $(DIVISION_INFO_UPDATE_MAIN)
	$(CC) -c $(DIVISION_INFO_UPDATE_MAIN)
DepartmentInfoUpdateMain.o:  $(DEPARTMENT_INFO_UPDATE_MAIN)
	$(CC) -c $(DEPARTMENT_INFO_UPDATE_MAIN)
ProductInfoUpdateMain.o:  $(PRODUCT_INFO_UPDATE_MAIN)
	$(CC) -c $(PRODUCT_INFO_UPDATE_MAIN)
ProductNotificationMain.o:  $(PRODUCT_NOTIFICATION_MAIN)
	$(CC) -c $(PRODUCT_NOTIFICATION_MAIN)
PhysicalServerNotificationMain.o:  $(SERVER_NOTIFICATION_MAIN)
	$(CC) -c $(SERVER_NOTIFICATION_MAIN)
DivisionSynchronizationMain.o:  $(DIVISION_SYNCHRONIZATION_MAIN)
	$(CC) -c $(DIVISION_SYNCHRONIZATION_MAIN)
DepartmentSynchronizationMain.o:  $(DEPARTMENT_SYNCHRONIZATION_MAIN)
	$(CC) -c $(DEPARTMENT_SYNCHRONIZATION_MAIN)
UserSynchronizationMain.o:  $(USER_SYNCHRONIZATION_MAIN)
	$(CC) -c $(USER_SYNCHRONIZATION_MAIN)
ServerStatisticCheckerMain.o:  $(SERVER_STATISTIC_CHECKER_MAIN)
	$(CC) -c $(SERVER_STATISTIC_CHECKER_MAIN)
HardwareInfoCheckerMain.o:  $(HARDWARE_CHECKER_MAIN)
	$(CC) -c $(HARDWARE_CHECKER_MAIN)
InterfaceInfoCheckerMain.o: $(INTERFACE_CHECKER_MAIN)
	$(CC) -c $(INTERFACE_CHECKER_MAIN)
ProductTotalCrossCheckMain.o: $(PRODUCT_TOTAL_CROSS_CHECK_MAIN)
	$(CC) -c $(PRODUCT_TOTAL_CROSS_CHECK_MAIN)
RackInfoChangeMiningMain.o: $(RACK_INFO_MINING_MAIN)
	$(CC) -c $(RACK_INFO_MINING_MAIN)
RowInfoChangeMiningMain.o: $(ROW_INFO_MINING_MAIN)
	$(CC) -c $(ROW_INFO_MINING_MAIN)
AccessSwitchInfoChangeMiningMain.o: $(ACCESS_SWITCH_INFO_MINING_MAIN)
	$(CC) -c $(ACCESS_SWITCH_INFO_MINING_MAIN)
CoreSwitchInfoChangeMiningMain.o: $(CORE_SWITCH_INFO_MINING_MAIN)
	$(CC) -c $(CORE_SWITCH_INFO_MINING_MAIN)
AggregationSwitchInfoChangeMiningMain.o: $(AGGREGATION_SWITCH_INFO_MINING_MAIN)
	$(CC) -c $(AGGREGATION_SWITCH_INFO_MINING_MAIN)
PDUInfoChangeMiningMain.o: $(PDU_INFO_MINING_MAIN)
	$(CC) -c $(PDU_INFO_MINING_MAIN)
ChassisInfoChangeMiningMain.o: $(CHASSIS_INFO_MINING_MAIN)
	$(CC) -c $(CHASSIS_INFO_MINING_MAIN)
PeerLinkInfoChangeMiningMain.o: $(PEER_LINK_INFO_MINING_MAIN)
	$(CC) -c $(PEER_LINK_INFO_MINING_MAIN)
RackInfoIndexMain.o: $(RACK_INFO_INDEX_MAIN)
	$(CC) -c $(RACK_INFO_INDEX_MAIN)
CoreSwitchInfoIndexMain.o: $(CORE_SWITCH_INFO_INDEX_MAIN)
	$(CC) -c $(CORE_SWITCH_INFO_INDEX_MAIN)
AggregationSwitchInfoIndexMain.o: $(AGGREGATION_SWITCH_INFO_INDEX_MAIN)
	$(CC) -c $(AGGREGATION_SWITCH_INFO_INDEX_MAIN)
AccessSwitchInfoIndexMain.o: $(ACCESS_SWITCH_INFO_INDEX_MAIN)
	$(CC) -c $(ACCESS_SWITCH_INFO_INDEX_MAIN)
ChassisInfoIndexMain.o: $(CHASSIS_INFO_INDEX_MAIN)
	$(CC) -c $(CHASSIS_INFO_INDEX_MAIN)
PeerLinkInfoIndexMain.o: $(PEERLINK_INFO_INDEX_MAIN)
	$(CC) -c $(PEERLINK_INFO_INDEX_MAIN)
PDUInfoIndexMain.o: $(PDU_INFO_INDEX_MAIN)
	$(CC) -c $(PDU_INFO_INDEX_MAIN)
RowInfoIndexMain.o: $(ROW_INFO_INDEX_MAIN)
	$(CC) -c $(ROW_INFO_INDEX_MAIN)
RowInfoUpdateMain.o: $(ROW_INFO_UPDATE_MAIN)
	$(CC) -c $(ROW_INFO_UPDATE_MAIN)
CoreSwitchInfoUpdateMain.o: $(CORE_SWITCH_INFO_UPDATE_MAIN)
	$(CC) -c $(CORE_SWITCH_INFO_UPDATE_MAIN)
AggregationSwitchInfoUpdateMain.o: $(AGGREGATION_SWITCH_INFO_UPDATE_MAIN)
	$(CC) -c $(AGGREGATION_SWITCH_INFO_UPDATE_MAIN)
AccessSwitchInfoUpdateMain.o: $(ACCESS_SWITCH_INFO_UPDATE_MAIN)
	$(CC) -c $(ACCESS_SWITCH_INFO_UPDATE_MAIN)
ChassisInfoUpdateMain.o: $(CHASSIS_INFO_UPDATE_MAIN)
	$(CC) -c $(CHASSIS_INFO_UPDATE_MAIN)
PeerLinkInfoUpdateMain.o: $(PEERLINK_INFO_UPDATE_MAIN)
	$(CC) -c $(PEERLINK_INFO_UPDATE_MAIN)
PDUInfoUpdateMain.o: $(PDU_INFO_UPDATE_MAIN)
	$(CC) -c $(PDU_INFO_UPDATE_MAIN)
RackInfoUpdateMain.o: $(RACK_INFO_UPDATE_MAIN)
	$(CC) -c $(RACK_INFO_UPDATE_MAIN)
ServerInfoMappingMain.o: $(SERVER_MODEL_MAPPING_MAIN)
	$(CC) -c $(SERVER_MODEL_MAPPING_MAIN)
ChassisInfoMappingMain.o: $(CHASSIS_MODEL_MAPPING_MAIN)
	$(CC) -c $(CHASSIS_MODEL_MAPPING_MAIN)
UpdateServerUSpaceMain.o: $(SERVER_USPACE_UPDATE_MAIN)
	$(CC) -c $(SERVER_USPACE_UPDATE_MAIN)
UpdateChassisUSpaceMain.o: $(CHASSIS_USPACE_UPDATE_MAIN)
	$(CC) -c $(CHASSIS_USPACE_UPDATE_MAIN)		
UpdateAggregationSwitchUSpaceMain.o: $(AGGREGATIONSWITCH_USPACE_UPDATE_MAIN)
	$(CC) -c $(AGGREGATIONSWITCH_USPACE_UPDATE_MAIN)		
UpdateAccessSwitchUSpaceMain.o: $(ACCESSSWITCH_USPACE_UPDATE_MAIN)
	$(CC) -c $(ACCESSSWITCH_USPACE_UPDATE_MAIN)		
UpdateCoreSwitchUSpaceMain.o: $(CORESWITCH_USPACE_UPDATE_MAIN)
	$(CC) -c $(CORESWITCH_USPACE_UPDATE_MAIN)		
UpdateCIUSpaceMain.o: $(USPACE_UPDATE_MAIN)
	$(CC) -c $(USPACE_UPDATE_MAIN)		
AggregationSwitchInfoMappingMain.o: $(AGGREGATIONSWITCH_MODEL_MAPPING_MAIN)
	$(CC) -c $(AGGREGATIONSWITCH_MODEL_MAPPING_MAIN)	
AccessSwitchInfoMappingMain.o: $(ACCESSSWITCH_MODEL_MAPPING_MAIN)
	$(CC) -c $(ACCESSSWITCH_MODEL_MAPPING_MAIN)	
CoreSwitchInfoMappingMain.o: $(CORESWITCH_MODEL_MAPPING_MAIN)
	$(CC) -c $(CORESWITCH_MODEL_MAPPING_MAIN)
CIInfoMappingMain.o: $(MODEL_MAPPING_MAIN)
	$(CC) -c $(MODEL_MAPPING_MAIN)
AccessSwitchDataComputeMain.o: $(ACCESS_SWITCH_DATA_COMPUTE_MAIN)
	$(CC) -c $(ACCESS_SWITCH_DATA_COMPUTE_MAIN)
ComputeRackDataMain.o: $(RACK_DATA_COMPUTE_MAIN)
	$(CC) -c $(RACK_DATA_COMPUTE_MAIN)
AggregationSwitchDataComputeMain.o: $(AGGREGATION_SWITCH_DATA_COMPUTE_MAIN)
	$(CC) -c $(AGGREGATION_SWITCH_DATA_COMPUTE_MAIN)
InternalServerDataCheckMain.o: $(SERVER_INTERNAL_DATA_CHECK_MAIN)
	$(CC) -c $(SERVER_INTERNAL_DATA_CHECK_MAIN)
TechnicalOwnerServerComputeMain.o: $(TECHNICAL_OWNER_SERVER_DATA_COMPUTE_MAIN)
	$(CC) -c $(TECHNICAL_OWNER_SERVER_DATA_COMPUTE_MAIN)
ComputeRowDataMain.o: $(ROW_DATA_COMPUTE_MAIN)
	$(CC) -c $(ROW_DATA_COMPUTE_MAIN)
file:
	cd Model; make
	cd Controller; make
	cd Config; make
	cd Utilities; make
	cd Processor; make
	cd Notification; make
	cd Synchronization; make
	cd DataChecker; make
	cd External; make
	
	# $(CC) $(DIVISION_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbDivInfMinFix
	# $(CC) $(DEPARTMENT_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbDeptInfMinFix
	# $(CC) $(PRODUCT_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbProInfMinFix
	# $(CC) $(SERVER_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbServInfMinFix
	# $(CC) $(DIVISION_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbDivInfMin
	# $(CC) $(DEPARTMENT_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbDeptInfMin
	# $(CC) $(PRODUCT_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbProInfMin
	# $(CC) $(SERVER_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbServInfMin
	# $(CC) $(RACK_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbRackInfMin
	# $(CC) $(ROW_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbRowInfMin
	# $(CC) $(ACCESS_SWITCH_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbAccessSwitchInfMin
	# $(CC) $(CORE_SWITCH_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbCoreSwitchInfMin
	# $(CC) $(AGGREGATION_SWITCH_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbAggregationSwitchInfMin
	# $(CC) $(CHASSIS_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbChassisInfMin
	# $(CC) $(PDU_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbPDUInfMin
	# $(CC) $(PEER_LINK_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbPeerLinkInfMin
	# $(CC) $(PMM_INFO_MINING_FILE) $(CFLAGS) -o ./bin/cmdbPMMInfMin
	# $(CC) $(DIVISION_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbDivisionIndex	
	# $(CC) $(DEPARTMENT_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbDepartmentIndex
	# $(CC) $(PRODUCT_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbProductIndex
	# $(CC) $(SERVER_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbServerIndex
	# $(CC) $(RACK_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbRackIndex
	# $(CC) $(CORE_SWITCH_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbCoreSwitchIndex	
	# $(CC) $(AGGREGATION_SWITCH_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbAggregationSwitchIndex
	# $(CC) $(ACCESS_SWITCH_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbAccessSwitchIndex
	# $(CC) $(CHASSIS_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbChassisIndex
	# $(CC) $(PEERLINK_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbPeerLinkIndex
	# $(CC) $(PDU_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbPDUIndex
	# $(CC) $(ROW_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbRowIndex
	# $(CC) $(PMM_INFO_INDEX_FILE) $(CFLAGS) -o ./bin/cmdbPMMIndex
	$(CC) $(PHYSICAL_SERVER_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdatePhysicalSvr
	# $(CC) $(VIRTUAL_SERVER_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateVirtualSvr
	# $(CC) $(DIVISION_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateDivision
	# $(CC) $(DEPARTMENT_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateDepartment
	# $(CC) $(PRODUCT_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateProduct
	# $(CC) $(RACK_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateRack
	# $(CC) $(CORE_SWITCH_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateCoreSwitch	
	# $(CC) $(AGGREGATION_SWITCH_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateAggregationSwitch
	# $(CC) $(ACCESS_SWITCH_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateAccessSwitch
	# $(CC) $(CHASSIS_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateChassis
	# $(CC) $(PEERLINK_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdatePeerLink
	# $(CC) $(PDU_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdatePDU
	# $(CC) $(ROW_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateRow
	# $(CC) $(PMM_INFO_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdatePMM
	# $(CC) $(PRODUCT_NOTIFICATION_FILE) $(CFLAGS) -o ./bin/cmdbProdNoti
	# $(CC) $(DIVISION_SYNCHRONIZATION_FILE) $(CFLAGS) -o ./bin/cmdbDivSync
	# $(CC) $(DEPARTMENT_SYNCHRONIZATION_FILE) $(CFLAGS) -o ./bin/cmdbDeptSync
	$(CC) $(SERVER_NOTIFICATION_FILE) $(CFLAGS) -o ./bin/cmdbPhyServNotiV2
	# $(CC) $(USER_SYNCHRONIZATION_FILE) $(CFLAGS) -o ./bin/cmdbUserSync
	# $(CC) $(SERVER_STATISTIC_CHECKER_FILE) $(CFLAGS) -o ./bin/cmdbServStat
	# $(CC) $(HARDWARE_CHECKER_FILE) $(CFLAGS) -o ./bin/cmdbHardware
	# $(CC) $(INTERFACE_CHECKER_FILE) $(CFLAGS) -o ./bin/cmdbInterface
	# $(CC) $(PRODUCT_TOTAL_CROSS_CHECK_FILE) $(CFLAGS) -o ./bin/cmdbProductCrossCheck
	# $(CC) $(SERVER_MODEL_MAPPING_FILE) $(CFLAGS) -o ./bin/cmdbMapServerModel
	# $(CC) $(CHASSIS_MODEL_MAPPING_FILE) $(CFLAGS) -o ./bin/cmdbMapChassisModel 
	# $(CC) $(AGGREGATIONSWITCH_MODEL_MAPPING_FILE) $(CFLAGS) -o ./bin/cmdbMapAggregationSwitchModel 
	# $(CC) $(ACCESSSWITCH_MODEL_MAPPING_FILE) $(CFLAGS) -o ./bin/cmdbMapAccessSwitchModel 
	# $(CC) $(CORESWITCH_MODEL_MAPPING_FILE) $(CFLAGS) -o ./bin/cmdbMapCoreSwitchModel 
	# $(CC) $(MODEL_MAPPING_FILE) $(CFLAGS) -o ./bin/cmdbMapCIModel 
	# $(CC) $(SERVER_USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUSpaceServer
	# $(CC) $(CHASSIS_USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUSpaceChassis
	# $(CC) $(CHASSIS_USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbFloorChassis
	# $(CC) $(AGGREGATIONSWITCH_USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUSpaceAggregationSwitch
	# $(CC) $(ACCESSSWITCH_USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUSpaceAccessSwitch
	# $(CC) $(CORESWITCH_USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUSpaceCoreSwitch
	# $(CC) $(USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateUSpace
	# $(CC) $(USPACE_UPDATE_FILE) $(CFLAGS) -o ./bin/cmdbUpdateSwitchType
	# $(CC) $(ACCESS_SWITCH_DATA_COMPUTE_FILE) $(CFLAGS) -o ./bin/cmdbAccessSwitchDataCompute
	# $(CC) $(RACK_DATA_COMPUTE_FILE) $(CFLAGS) -o ./bin/cmdbComputeRack
	# $(CC) $(AGGREGATION_SWITCH_DATA_COMPUTE_FILE) $(CFLAGS) -o ./bin/cmdbAggregationSwitchDataCompute
	# $(CC) $(SERVER_INTERNAL_DATA_CHECK_FILE) $(CFLAGS) -o ./bin/cmdbServerInternalDataCheck
	# $(CC) $(TECHNICAL_OWNER_SERVER_DATA_COMPUTE_FILE)  $(CFLAGS) -o ./bin/cmdbTechnicalOwnerServerCompute
	# $(CC) $(ROW_DATA_COMPUTE_FILE) $(CFLAGS) -o ./bin/cmdbComputeRow
clean:
	cd Model; make clean
	cd Controller; make clean
	cd Config; make clean
	cd Utilities; make clean
	cd Processor; make clean
	cd Notification; make clean
	cd Synchronization; make clean
	cd DataChecker; make clean
	cd External; make clean
	rm -rf *o
	rm -rf ./bin/cmdb*

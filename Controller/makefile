CC=g++
MYSQLFLAGS=-I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto
ControllerFolder: MongodbController.o MySQLController.o CMDBController.o ServerController.o \
	DivisionController.o DepartmentController.o ProductController.o \
	CIInfoChangeController.o ServerInfoChangeController.o CIInfoIndexController.o ServerInfoIndexController.o \
	CIInfoUpdateController.o PhysicalServerInfoUpdateController.o VirtualServerInfoUpdateController.o \
	DepartmentInfoUpdateController.o ProductInfoUpdateController.o DivisionInfoUpdateController.o \
	CIHistoryLogController.o ServerHistoryLogController.o \
	DivisionHistoryLogController.o DepartmentHistoryLogController.o ProductHistoryLogController.o \
	DivisionInfoChangeController.o DivisionInfoIndexController.o \
	DepartmentInfoChangeController.o DepartmentInfoIndexController.o \
	ProductInfoChangeController.o ProductInfoIndexController.o \
	PartnerInfoController.o NotificationController.o \
	ProductNotificationController.o PhysicalServerNotificationController.o\
	CollectorController.o DepartmentNotificationController.o \
	CIRelationshipController.o \
	ProductNotificationController.o PhysicalServerNotificationController.o \
	CollectorController.o DepartmentNotificationController.o \
	CheckerController.o UserController.o ChassisController.o \
	ServerStatisticCheckerController.o \
	HardwareCheckerController.o \
	InterfaceCheckerController.o \
	CoreSwitchController.o AggregationSwitchController.o AccessSwitchController.o \
	PeerLinkController.o RackController.o RowController.o PDUController.o ChassisController.o \
	CoreSwitchInfoIndexController.o AggregationSwitchInfoIndexController.o AccessSwitchInfoIndexController.o \
	PeerLinkInfoIndexController.o RackInfoIndexController.o RowInfoIndexController.o PDUInfoIndexController.o \
	ChassisInfoIndexController.o MailboxController.o \
	CoreSwitchInfoChangeController.o AggregationSwitchInfoChangeController.o AccessSwitchInfoChangeController.o \
	PeerLinkInfoChangeController.o RackInfoChangeController.o RowInfoChangeController.o PDUInfoChangeController.o ChassisInfoChangeController.o \
	RowInfoUpdateController.o PDUInfoUpdateController.o PeerLinkInfoUpdateController.o ChassisInfoUpdateController.o \
	AggregationSwitchInfoUpdateController.o AccessSwitchInfoUpdateController.o CoreSwitchInfoUpdateController.o RackInfoUpdateController.o \
	RowHistoryLogController.o PDUHistoryLogController.o PeerLinkHistoryLogController.o ChassisHistoryLogController.o \
	AggregationSwitchHistoryLogController.o AccessSwitchHistoryLogController.o CoreSwitchHistoryLogController.o RackHistoryLogController.o \
	AdminController.o AdminProductOwnerController.o AdminProductRolesController.o AdminUserGroupsProductsController.o AdminUserGroupsUsersController.o \
	PMMController.o PMMHistoryLogController.o PMMInfoChangeController.o PMMInfoIndexController.o PMMInfoUpdateController.o \
	ZabbixAPIController.o

MongodbController.o : MongodbController.cpp MongodbController.h
	$(CC) -c MongodbController.cpp
MySQLController.o : MySQLController.cpp MySQLController.h
	$(CC) -c MySQLController.cpp $(MYSQLFLAGS)
CMDBController.o : CMDBController.cpp CMDBController.h
	$(CC) -c CMDBController.cpp
CIInfoChangeController.o : CIInfoChangeController.cpp CIInfoChangeController.h
	$(CC) -c CIInfoChangeController.cpp
ServerInfoChangeController.o : ServerInfoChangeController.cpp ServerInfoChangeController.h
	$(CC) -c ServerInfoChangeController.cpp
ServerController.o : ServerController.cpp ServerController.h
	$(CC) -c ServerController.cpp	
DivisionController.o : DivisionController.cpp DivisionController.h
	$(CC) -c DivisionController.cpp
DepartmentController.o : DepartmentController.cpp DepartmentController.h
	$(CC) -c DepartmentController.cpp
ProductController.o : ProductController.cpp ProductController.h
	$(CC) -c ProductController.cpp	
CIInfoIndexController.o : CIInfoIndexController.cpp CIInfoIndexController.h
	$(CC) -c CIInfoIndexController.cpp
ServerInfoIndexController.o : ServerInfoIndexController.cpp ServerInfoIndexController.h
	$(CC) -c ServerInfoIndexController.cpp
CIInfoUpdateController.o : CIInfoUpdateController.cpp CIInfoUpdateController.h
	$(CC) -c CIInfoUpdateController.cpp
PhysicalServerInfoUpdateController.o : PhysicalServerInfoUpdateController.cpp PhysicalServerInfoUpdateController.h
	$(CC) -c PhysicalServerInfoUpdateController.cpp
VirtualServerInfoUpdateController.o : VirtualServerInfoUpdateController.cpp VirtualServerInfoUpdateController.h
	$(CC) -c VirtualServerInfoUpdateController.cpp
DivisionInfoUpdateController.o : DivisionInfoUpdateController.cpp DivisionInfoUpdateController.h
	$(CC) -c DivisionInfoUpdateController.cpp
DepartmentInfoUpdateController.o : DepartmentInfoUpdateController.cpp DepartmentInfoUpdateController.h
	$(CC) -c DepartmentInfoUpdateController.cpp
ProductInfoUpdateController.o : ProductInfoUpdateController.cpp ProductInfoUpdateController.h
	$(CC) -c ProductInfoUpdateController.cpp
CIHistoryLogController.o : CIHistoryLogController.cpp CIHistoryLogController.h
	$(CC) -c CIHistoryLogController.cpp
ServerHistoryLogController.o : ServerHistoryLogController.cpp ServerHistoryLogController.h
	$(CC) -c ServerHistoryLogController.cpp
DivisionHistoryLogController.o : DivisionHistoryLogController.cpp DivisionHistoryLogController.h
	$(CC) -c DivisionHistoryLogController.cpp
DepartmentHistoryLogController.o : DepartmentHistoryLogController.cpp DepartmentHistoryLogController.h
	$(CC) -c DepartmentHistoryLogController.cpp
ProductHistoryLogController.o : ProductHistoryLogController.cpp ProductHistoryLogController.h
	$(CC) -c ProductHistoryLogController.cpp
DivisionInfoChangeController.o : DivisionInfoChangeController.cpp DivisionInfoChangeController.h
	$(CC) -c DivisionInfoChangeController.cpp
DivisionInfoIndexController.o: DivisionInfoIndexController.cpp DivisionInfoIndexController.h
	$(CC) -c DivisionInfoIndexController.cpp
DepartmentInfoChangeController.o: DepartmentInfoChangeController.cpp DepartmentInfoChangeController.h
	$(CC) -c DepartmentInfoChangeController.cpp
DepartmentInfoIndexController.o: DepartmentInfoIndexController.cpp DepartmentInfoIndexController.h
	$(CC) -c DepartmentInfoIndexController.cpp
ProductInfoChangeController.o: ProductInfoChangeController.cpp ProductInfoChangeController.h
	$(CC) -c ProductInfoChangeController.cpp
ProductInfoIndexController.o: ProductInfoIndexController.cpp ProductInfoIndexController.h
	$(CC) -c ProductInfoIndexController.cpp
PartnerInfoController.o: PartnerInfoController.cpp PartnerInfoController.h
	$(CC) -c PartnerInfoController.cpp
NotificationController.o: NotificationController.cpp NotificationController.h
	$(CC) -c NotificationController.cpp
ProductNotificationController.o: ProductNotificationController.cpp ProductNotificationController.h
	$(CC) -c ProductNotificationController.cpp
PhysicalServerNotificationController.o: PhysicalServerNotificationController.cpp PhysicalServerNotificationController.h
	$(CC) -c PhysicalServerNotificationController.cpp
DepartmentNotificationController.o: DepartmentNotificationController.cpp DepartmentNotificationController.h
	$(CC) -c DepartmentNotificationController.cpp
CollectorController.o: CollectorController.cpp CollectorController.h
	$(CC) -c CollectorController.cpp
CIRelationshipController.o: CIRelationshipController.cpp CIRelationshipController.h
	$(CC) -c CIRelationshipController.cpp
UserController.o: UserController.cpp UserController.h
	$(CC) -c UserController.cpp
CheckerController.o: CheckerController.cpp CheckerController.h
	$(CC) -c CheckerController.cpp
ServerStatisticCheckerController.o: ServerStatisticCheckerController.cpp ServerStatisticCheckerController.h
	$(CC) -c ServerStatisticCheckerController.cpp
HardwareCheckerController.o: HardwareCheckerController.cpp HardwareCheckerController.h
	$(CC) -c HardwareCheckerController.cpp
InterfaceCheckerController.o: InterfaceCheckerController.cpp InterfaceCheckerController.h
	$(CC) -c InterfaceCheckerController.cpp
ChassisController.o: ChassisController.cpp ChassisController.h
	$(CC) -c ChassisController.cpp
CoreSwitchController.o: CoreSwitchController.cpp CoreSwitchController.h
	$(CC) -c CoreSwitchController.cpp
AggregationSwitchController.o: AggregationSwitchController.cpp AggregationSwitchController.h
	$(CC) -c AggregationSwitchController.cpp
AccessSwitchController.o: AccessSwitchController.cpp AccessSwitchController.h
	$(CC) -c AccessSwitchController.cpp
PeerLinkController.o: PeerLinkController.cpp PeerLinkController.h
	$(CC) -c PeerLinkController.cpp
RackController.o: RackController.cpp RackController.h
	$(CC) -c RackController.cpp
RowController.o: RowController.cpp RowController.h
	$(CC) -c RowController.cpp
PDUController.o: PDUController.cpp PDUController.h
	$(CC) -c PDUController.cpp
CoreSwitchInfoIndexController.o: CoreSwitchInfoIndexController.cpp CoreSwitchInfoIndexController.h
	$(CC) -c CoreSwitchInfoIndexController.cpp
AggregationSwitchInfoIndexController.o: AggregationSwitchInfoIndexController.cpp AggregationSwitchInfoIndexController.h
	$(CC) -c AggregationSwitchInfoIndexController.cpp
AccessSwitchInfoIndexController.o: AccessSwitchInfoIndexController.cpp AccessSwitchInfoIndexController.h
	$(CC) -c AccessSwitchInfoIndexController.cpp
PeerLinkInfoIndexController.o: PeerLinkInfoIndexController.cpp PeerLinkInfoIndexController.h
	$(CC) -c PeerLinkInfoIndexController.cpp
RackInfoIndexController.o: RackInfoIndexController.cpp RackInfoIndexController.h
	$(CC) -c RackInfoIndexController.cpp
RowInfoIndexController.o: RowInfoIndexController.cpp RowInfoIndexController.h
	$(CC) -c RowInfoIndexController.cpp
PDUInfoIndexController.o: PDUInfoIndexController.cpp PDUInfoIndexController.h
	$(CC) -c PDUInfoIndexController.cpp
ChassisInfoIndexController.o: ChassisInfoIndexController.cpp ChassisInfoIndexController.h
	$(CC) -c ChassisInfoIndexController.cpp
MailboxController.o : MailboxController.cpp MailboxController.h
	$(CC) -c MailboxController.cpp
CoreSwitchInfoChangeController.o: CoreSwitchInfoChangeController.cpp CoreSwitchInfoChangeController.h
	$(CC) -c CoreSwitchInfoChangeController.cpp
AggregationSwitchInfoChangeController.o: AggregationSwitchInfoChangeController.cpp AggregationSwitchInfoChangeController.h
	$(CC) -c AggregationSwitchInfoChangeController.cpp
AccessSwitchInfoChangeController.o: AccessSwitchInfoChangeController.cpp AccessSwitchInfoChangeController.h
	$(CC) -c AccessSwitchInfoChangeController.cpp
PeerLinkInfoChangeController.o: PeerLinkInfoChangeController.cpp PeerLinkInfoChangeController.h
	$(CC) -c PeerLinkInfoChangeController.cpp
RackInfoChangeController.o: RackInfoChangeController.cpp RackInfoChangeController.h
	$(CC) -c RackInfoChangeController.cpp
RowInfoChangeController.o: RowInfoChangeController.cpp RowInfoChangeController.h
	$(CC) -c RowInfoChangeController.cpp
PDUInfoChangeController.o: PDUInfoChangeController.cpp PDUInfoChangeController.h
	$(CC) -c PDUInfoChangeController.cpp
ChassisInfoChangeController.o: ChassisInfoChangeController.cpp ChassisInfoChangeController.h
	$(CC) -c ChassisInfoChangeController.cpp
RackHistoryLogController.o: RackHistoryLogController.cpp RackHistoryLogController.h
	$(CC) -c RackHistoryLogController.cpp
CoreSwitchHistoryLogController.o: CoreSwitchHistoryLogController.cpp CoreSwitchHistoryLogController.h
	$(CC) -c CoreSwitchHistoryLogController.cpp
AccessSwitchHistoryLogController.o: AccessSwitchHistoryLogController.cpp AccessSwitchHistoryLogController.h
	$(CC) -c AccessSwitchHistoryLogController.cpp
AggregationSwitchHistoryLogController.o: AggregationSwitchHistoryLogController.cpp AggregationSwitchHistoryLogController.h
	$(CC) -c AggregationSwitchHistoryLogController.cpp
ChassisHistoryLogController.o: ChassisHistoryLogController.cpp ChassisHistoryLogController.h
	$(CC) -c ChassisHistoryLogController.cpp
PeerLinkHistoryLogController.o: PeerLinkHistoryLogController.cpp PeerLinkHistoryLogController.h
	$(CC) -c PeerLinkHistoryLogController.cpp
PDUHistoryLogController.o: PDUHistoryLogController.cpp PDUHistoryLogController.h
	$(CC) -c PDUHistoryLogController.cpp
RowHistoryLogController.o: RowHistoryLogController.cpp RowHistoryLogController.h
	$(CC) -c RowHistoryLogController.cpp
RackInfoUpdateController.o: RackInfoUpdateController.cpp RackInfoUpdateController.h
	$(CC) -c RackInfoUpdateController.cpp
CoreSwitchInfoUpdateController.o: CoreSwitchInfoUpdateController.cpp CoreSwitchInfoUpdateController.h
	$(CC) -c CoreSwitchInfoUpdateController.cpp
AccessSwitchInfoUpdateController.o: AccessSwitchInfoUpdateController.cpp AccessSwitchInfoUpdateController.h
	$(CC) -c AccessSwitchInfoUpdateController.cpp
AggregationSwitchInfoUpdateController.o: AggregationSwitchInfoUpdateController.cpp AggregationSwitchInfoUpdateController.h
	$(CC) -c AggregationSwitchInfoUpdateController.cpp
ChassisInfoUpdateController.o: ChassisInfoUpdateController.cpp ChassisInfoUpdateController.h
	$(CC) -c ChassisInfoUpdateController.cpp
PeerLinkInfoUpdateController.o: PeerLinkInfoUpdateController.cpp PeerLinkInfoUpdateController.h
	$(CC) -c PeerLinkInfoUpdateController.cpp
PDUInfoUpdateController.o: PDUInfoUpdateController.cpp PDUInfoUpdateController.h
	$(CC) -c PDUInfoUpdateController.cpp
RowInfoUpdateController.o: RowInfoUpdateController.cpp RowInfoUpdateController.h
	$(CC) -c RowInfoUpdateController.cpp
AdminController.o: AdminController.cpp AdminController.h
	$(CC) -c AdminController.cpp
AdminProductOwnerController.o: AdminProductOwnerController.cpp AdminProductOwnerController.h
	$(CC) -c AdminProductOwnerController.cpp
AdminProductRolesController.o: AdminProductRolesController.cpp AdminProductRolesController.h
	$(CC) -c AdminProductRolesController.cpp
AdminUserGroupsProductsController.o: AdminUserGroupsProductsController.cpp AdminUserGroupsProductsController.h
	$(CC) -c AdminUserGroupsProductsController.cpp
AdminUserGroupsUsersController.o: AdminUserGroupsUsersController.cpp AdminUserGroupsUsersController.h
	$(CC) -c AdminUserGroupsUsersController.cpp
PMMController.o: PMMController.cpp PMMController.h
	$(CC) -c PMMController.cpp
PMMHistoryLogController.o: PMMHistoryLogController.cpp PMMHistoryLogController.h
	$(CC) -c PMMHistoryLogController.cpp
PMMInfoChangeController.o: PMMInfoChangeController.cpp PMMInfoChangeController.h
	$(CC) -c PMMInfoChangeController.cpp
PMMInfoIndexController.o: PMMInfoIndexController.cpp PMMInfoIndexController.h
	$(CC) -c PMMInfoIndexController.cpp
PMMInfoUpdateController.o: PMMInfoUpdateController.cpp PMMInfoUpdateController.h
	$(CC) -c PMMInfoUpdateController.cpp
ZabbixAPIController.o: ZabbixAPIController.cpp ZabbixAPIController.h
	$(CC) -c ZabbixAPIController.cpp
clean:
	rm -rf *o ControllerFolder

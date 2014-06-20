CC=g++
MYSQLFLAGS=-I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto
ProcessorFolder: Processor.o CIInfoChangeProcessor.o ServerInfoChangeProcessor.o CIInfoIndexProcessor.o \
	ServerInfoIndexProcessor.o CIIndexPooler.o ServerIndexPooler.o \
	CIInfoUpdateProcessor.o PhysicalServerInfoUpdateProcessor.o VirtualServerInfoUpdateProcessor.o \
	DivisionInfoUpdateProcessor.o DepartmentInfoUpdateProcessor.o ProductInfoUpdateProcessor.o \
	DivisionInfoChangeProcessor.o DivisionIndexPooler.o DivisionInfoIndexProcessor.o \
	DepartmentInfoChangeProcessor.o DepartmentIndexPooler.o DepartmentInfoIndexProcessor.o \
	ProductInfoChangeProcessor.o ProductIndexPooler.o ProductInfoIndexProcessor.o \
	NotificationProcessor.o PhysicalServerNotificationProcessor.o ProductNotificationProcessor.o \
	SynchronizationProcessor.o DivisionInfoSynchronizationProcessor.o \
	DepartmentInfoSynchronizationProcessor.o UserInfoSynchronizationProcessor.o \
	Thread.o CheckerProcessor.o ServerCheckerProcessor.o ServerNotificationProcessor.o \
	HardwareCheckerProcessor.o InterfaceCheckerProcessor.o \
	CoreSwitchInfoChangeProcessor.o AccessSwitchInfoChangeProcessor.o AggregationSwitchInfoChangeProcessor.o \
	RackInfoChangeProcessor.o RowInfoChangeProcessor.o PDUInfoChangeProcessor.o PeerLinkInfoChangeProcessor.o \
	ChassisInfoChangeProcessor.o RackIndexPooler.o RowIndexPooler.o PDUIndexPooler.o PeerLinkIndexPooler.o \
	CoreSwitchIndexPooler.o AccessSwitchIndexPooler.o AggregationSwitchIndexPooler.o ChassisIndexPooler.o \
	RackInfoIndexProcessor.o CoreSwitchInfoIndexProcessor.o  PDUInfoIndexProcessor.o \
	AccessSwitchInfoIndexProcessor.o AggregationSwitchInfoIndexProcessor.o RowInfoIndexProcessor.o \
	ChassisInfoIndexProcessor.o PeerLinkInfoIndexProcessor.o \
	RowInfoUpdateProcessor.o PDUInfoUpdateProcessor.o PeerLinkInfoUpdateProcessor.o ChassisInfoUpdateProcessor.o \
	AccessSwitchInfoUpdateProcessor.o AggregationSwitchInfoUpdateProcessor.o CoreSwitchInfoUpdateProcessor.o RackInfoUpdateProcessor.o \
	CIInfoMappingProcessor.o ServerInfoMappingProcessor.o ChassisInfoMappingProcessor.o \
	CoreSwitchInfoMappingProcessor.o AccessSwitchInfoMappingProcessor.o AggregationSwitchInfoMappingProcessor.o \
	UpdateCIUSpaceProcessor.o UpdateServerUSpaceProcessor.o UpdateChassisUSpaceProcessor.o \
	UpdateCoreSwitchUSpaceProcessor.o UpdateAccessSwitchUSpaceProcessor.o UpdateAggregationSwitchUSpaceProcessor.o \
	ComputeDataProcessor.o ComputeRackDataProcessor.o \
	ComputeAccessSwitchDataProcessor.o ComputeAggregationSwitchDataProcessor.o \
	InternalDataCheckProcessor.o InternalServerDataCheckProcessor.o \
	ComputeRowDataProcessor.o ComputeServerDataProcessor.o IntergrateTechnicalOwnerProcessor.o \
	PMMInfoUpdateProcessor.o PMMInfoIndexProcessor.o PMMInfoChangeProcessor.o PMMIndexPooler.o \
	ZabbixAPIProcessor.o
	
Processor.o: Processor.cpp Processor.h
	$(CC) -c Processor.cpp $(MYSQLFLAGS)
CIInfoChangeProcessor.o: CIInfoChangeProcessor.cpp CIInfoChangeProcessor.h Processor.o
	$(CC) -c CIInfoChangeProcessor.cpp
ServerInfoChangeProcessor.o: ServerInfoChangeProcessor.cpp ServerInfoChangeProcessor.h
	$(CC) -c ServerInfoChangeProcessor.cpp
CIInfoIndexProcessor.o: CIInfoIndexProcessor.cpp CIInfoIndexProcessor.h
	$(CC) -c -lpthread CIInfoIndexProcessor.cpp
ServerInfoIndexProcessor.o: ServerInfoIndexProcessor.cpp ServerInfoIndexProcessor.h
	$(CC) -c -lpthread ServerInfoIndexProcessor.cpp
CIIndexPooler.o: CIIndexPooler.cpp CIIndexPooler.h
	$(CC) -c CIIndexPooler.cpp
ServerIndexPooler.o: ServerIndexPooler.cpp ServerIndexPooler.h
	$(CC) -c ServerIndexPooler.cpp
CIInfoUpdateProcessor.o: CIInfoUpdateProcessor.cpp CIInfoUpdateProcessor.h
	$(CC) -c CIInfoUpdateProcessor.cpp	
PhysicalServerInfoUpdateProcessor.o: PhysicalServerInfoUpdateProcessor.cpp PhysicalServerInfoUpdateProcessor.h
	$(CC) -c PhysicalServerInfoUpdateProcessor.cpp	
VirtualServerInfoUpdateProcessor.o: VirtualServerInfoUpdateProcessor.cpp VirtualServerInfoUpdateProcessor.h
	$(CC) -c VirtualServerInfoUpdateProcessor.cpp	
DivisionInfoUpdateProcessor.o: DivisionInfoUpdateProcessor.cpp DivisionInfoUpdateProcessor.h
	$(CC) -c DivisionInfoUpdateProcessor.cpp	
DepartmentInfoUpdateProcessor.o: DepartmentInfoUpdateProcessor.cpp DepartmentInfoUpdateProcessor.h
	$(CC) -c DepartmentInfoUpdateProcessor.cpp	
ProductInfoUpdateProcessor.o: ProductInfoUpdateProcessor.cpp ProductInfoUpdateProcessor.h
	$(CC) -c ProductInfoUpdateProcessor.cpp	
DivisionInfoChangeProcessor.o: DivisionInfoChangeProcessor.cpp DivisionInfoChangeProcessor.h
	$(CC) -c DivisionInfoChangeProcessor.cpp
DivisionIndexPooler.o: DivisionIndexPooler.cpp DivisionIndexPooler.h
	$(CC) -c DivisionIndexPooler.cpp
DivisionInfoIndexProcessor.o: DivisionInfoIndexProcessor.cpp DivisionInfoIndexProcessor.h
	$(CC) -c DivisionInfoIndexProcessor.cpp
DepartmentInfoChangeProcessor.o: DepartmentInfoChangeProcessor.cpp DepartmentInfoChangeProcessor.h
	$(CC) -c DepartmentInfoChangeProcessor.cpp
DepartmentIndexPooler.o: DepartmentIndexPooler.cpp DepartmentIndexPooler.h
	$(CC) -c DepartmentIndexPooler.cpp
DepartmentInfoIndexProcessor.o: DepartmentInfoIndexProcessor.cpp DepartmentInfoIndexProcessor.h
	$(CC) -c DepartmentInfoIndexProcessor.cpp
ProductInfoChangeProcessor.o: ProductInfoChangeProcessor.cpp ProductInfoChangeProcessor.h
	$(CC) -c ProductInfoChangeProcessor.cpp
ProductIndexPooler.o: ProductIndexPooler.cpp ProductIndexPooler.h
	$(CC) -c ProductIndexPooler.cpp
ProductInfoIndexProcessor.o: ProductInfoIndexProcessor.cpp ProductInfoIndexProcessor.h
	$(CC) -c ProductInfoIndexProcessor.cpp
NotificationProcessor.o: NotificationProcessor.cpp NotificationProcessor.h
	$(CC) -c NotificationProcessor.cpp
PhysicalServerNotificationProcessor.o: PhysicalServerNotificationProcessor.cpp PhysicalServerNotificationProcessor.h
	$(CC) -c PhysicalServerNotificationProcessor.cpp
ProductNotificationProcessor.o: ProductNotificationProcessor.cpp ProductNotificationProcessor.h
	$(CC) -c ProductNotificationProcessor.cpp
SynchronizationProcessor.o:  SynchronizationProcessor.cpp SynchronizationProcessor.h
	$(CC) -c SynchronizationProcessor.cpp
DivisionInfoSynchronizationProcessor.o: DivisionInfoSynchronizationProcessor.cpp DivisionInfoSynchronizationProcessor.h
	$(CC) -c DivisionInfoSynchronizationProcessor.cpp
DepartmentInfoSynchronizationProcessor.o: DepartmentInfoSynchronizationProcessor.cpp DepartmentInfoSynchronizationProcessor.h
	$(CC) -c DepartmentInfoSynchronizationProcessor.cpp
UserInfoSynchronizationProcessor.o: UserInfoSynchronizationProcessor.cpp UserInfoSynchronizationProcessor.h
	$(CC) -c UserInfoSynchronizationProcessor.cpp
Thread.o: Thread.cpp Thread.h
	$(CC) -c Thread.cpp
CheckerProcessor.o: CheckerProcessor.cpp CheckerProcessor.h
	$(CC) -c CheckerProcessor.cpp
ServerCheckerProcessor.o: ServerCheckerProcessor.cpp ServerCheckerProcessor.h
	$(CC) -c ServerCheckerProcessor.cpp
HardwareCheckerProcessor.o: HardwareCheckerProcessor.cpp HardwareCheckerProcessor.h
	$(CC) -c HardwareCheckerProcessor.cpp
InterfaceCheckerProcessor.o: InterfaceCheckerProcessor.cpp InterfaceCheckerProcessor.h
	$(CC) -c InterfaceCheckerProcessor.cpp
ServerNotificationProcessor.o: ServerNotificationProcessor.cpp ServerNotificationProcessor.h
	$(CC) -c ServerNotificationProcessor.cpp
CITotalCrossCheckProcessor.o: CITotalCrossCheckProcessor.cpp CITotalCrossCheckProcessor.h
	$(CC) -c CITotalCrossCheckProcessor.cpp
ProductTotalCrossCheckProcessor.o: ProductTotalCrossCheckProcessor.cpp ProductTotalCrossCheckProcessor.h
	$(CC) -c ProductTotalCrossCheckProcessor.cpp
CoreSwitchInfoChangeProcessor.o: CoreSwitchInfoChangeProcessor.cpp CoreSwitchInfoChangeProcessor.h
	$(CC) -c CoreSwitchInfoChangeProcessor.cpp
AccessSwitchInfoChangeProcessor.o: AccessSwitchInfoChangeProcessor.cpp AccessSwitchInfoChangeProcessor.h
	$(CC) -c AccessSwitchInfoChangeProcessor.cpp
AggregationSwitchInfoChangeProcessor.o: AggregationSwitchInfoChangeProcessor.cpp AggregationSwitchInfoChangeProcessor.h
	$(CC) -c AggregationSwitchInfoChangeProcessor.cpp
RackInfoChangeProcessor.o: RackInfoChangeProcessor.cpp RackInfoChangeProcessor.h
	$(CC) -c RackInfoChangeProcessor.cpp
RowInfoChangeProcessor.o: RowInfoChangeProcessor.cpp RowInfoChangeProcessor.h
	$(CC) -c RowInfoChangeProcessor.cpp
PDUInfoChangeProcessor.o: PDUInfoChangeProcessor.cpp PDUInfoChangeProcessor.h
	$(CC) -c PDUInfoChangeProcessor.cpp
PeerLinkInfoChangeProcessor.o: PeerLinkInfoChangeProcessor.cpp PeerLinkInfoChangeProcessor.h
	$(CC) -c PeerLinkInfoChangeProcessor.cpp
ChassisInfoChangeProcessor.o: ChassisInfoChangeProcessor.cpp ChassisInfoChangeProcessor.h
	$(CC) -c ChassisInfoChangeProcessor.cpp
RackIndexPooler.o: RackIndexPooler.cpp RackIndexPooler.h
	$(CC) -c RackIndexPooler.cpp
RowIndexPooler.o: RowIndexPooler.cpp RowIndexPooler.h
	$(CC) -c RowIndexPooler.cpp
PDUIndexPooler.o: PDUIndexPooler.cpp PDUIndexPooler.h
	$(CC) -c PDUIndexPooler.cpp
PeerLinkIndexPooler.o: PeerLinkIndexPooler.cpp PeerLinkIndexPooler.h
	$(CC) -c PeerLinkIndexPooler.cpp
CoreSwitchIndexPooler.o: CoreSwitchIndexPooler.cpp CoreSwitchIndexPooler.h
	$(CC) -c CoreSwitchIndexPooler.cpp
AccessSwitchIndexPooler.o: AccessSwitchIndexPooler.cpp AccessSwitchIndexPooler.h
	$(CC) -c AccessSwitchIndexPooler.cpp
AggregationSwitchIndexPooler.o: AggregationSwitchIndexPooler.cpp AggregationSwitchIndexPooler.h
	$(CC) -c AggregationSwitchIndexPooler.cpp
ChassisIndexPooler.o: ChassisIndexPooler.cpp ChassisIndexPooler.h
	$(CC) -c ChassisIndexPooler.cpp
RackInfoIndexProcessor.o: RackInfoIndexProcessor.cpp RackInfoIndexProcessor.h
	$(CC) -c RackInfoIndexProcessor.cpp
CoreSwitchInfoIndexProcessor.o: CoreSwitchInfoIndexProcessor.cpp CoreSwitchInfoIndexProcessor.h
	$(CC) -c CoreSwitchInfoIndexProcessor.cpp
AccessSwitchInfoIndexProcessor.o: AccessSwitchInfoIndexProcessor.cpp AccessSwitchInfoIndexProcessor.h
	$(CC) -c AccessSwitchInfoIndexProcessor.cpp
AggregationSwitchInfoIndexProcessor.o: AggregationSwitchInfoIndexProcessor.cpp AggregationSwitchInfoIndexProcessor.h
	$(CC) -c AggregationSwitchInfoIndexProcessor.cpp
ChassisInfoIndexProcessor.o: ChassisInfoIndexProcessor.cpp ChassisInfoIndexProcessor.h
	$(CC) -c ChassisInfoIndexProcessor.cpp
PeerLinkInfoIndexProcessor.o: PeerLinkInfoIndexProcessor.cpp PeerLinkInfoIndexProcessor.h
	$(CC) -c PeerLinkInfoIndexProcessor.cpp
PDUInfoIndexProcessor.o: PDUInfoIndexProcessor.cpp PDUInfoIndexProcessor.h
	$(CC) -c PDUInfoIndexProcessor.cpp
RowInfoIndexProcessor.o: RowInfoIndexProcessor.cpp RowInfoIndexProcessor.h
	$(CC) -c RowInfoIndexProcessor.cpp
RackInfoUpdateProcessor.o: RackInfoUpdateProcessor.cpp RackInfoUpdateProcessor.h
	$(CC) -c RackInfoUpdateProcessor.cpp
CoreSwitchInfoUpdateProcessor.o: CoreSwitchInfoUpdateProcessor.cpp CoreSwitchInfoUpdateProcessor.h
	$(CC) -c CoreSwitchInfoUpdateProcessor.cpp
AggregationSwitchInfoUpdateProcessor.o: AggregationSwitchInfoUpdateProcessor.cpp AggregationSwitchInfoUpdateProcessor.h
	$(CC) -c AggregationSwitchInfoUpdateProcessor.cpp
AccessSwitchInfoUpdateProcessor.o: AccessSwitchInfoUpdateProcessor.cpp AccessSwitchInfoUpdateProcessor.h
	$(CC) -c AccessSwitchInfoUpdateProcessor.cpp
ChassisInfoUpdateProcessor.o: ChassisInfoUpdateProcessor.cpp ChassisInfoUpdateProcessor.h
	$(CC) -c ChassisInfoUpdateProcessor.cpp
PDUInfoUpdateProcessor.o: PDUInfoUpdateProcessor.cpp PDUInfoUpdateProcessor.h
	$(CC) -c PDUInfoUpdateProcessor.cpp
PeerLinkInfoUpdateProcessor.o: PeerLinkInfoUpdateProcessor.cpp PeerLinkInfoUpdateProcessor.h
	$(CC) -c PeerLinkInfoUpdateProcessor.cpp
RowInfoUpdateProcessor.o: RowInfoUpdateProcessor.cpp RowInfoUpdateProcessor.h
	$(CC) -c RowInfoUpdateProcessor.cpp
CIInfoMappingProcessor.o: CIInfoMappingProcessor.cpp CIInfoMappingProcessor.h
	$(CC) -c CIInfoMappingProcessor.cpp
ServerInfoMappingProcessor.o: ServerInfoMappingProcessor.cpp ServerInfoMappingProcessor.h
	$(CC) -c ServerInfoMappingProcessor.cpp
ChassisInfoMappingProcessor.o: ChassisInfoMappingProcessor.cpp ChassisInfoMappingProcessor.h
	$(CC) -c ChassisInfoMappingProcessor.cpp
UpdateCIUSpaceProcessor.o: UpdateCIUSpaceProcessor.cpp UpdateCIUSpaceProcessor.h
	$(CC) -c UpdateCIUSpaceProcessor.cpp
UpdateServerUSpaceProcessor.o: UpdateServerUSpaceProcessor.cpp UpdateServerUSpaceProcessor.h
	$(CC) -c UpdateServerUSpaceProcessor.cpp
UpdateChassisUSpaceProcessor.o: UpdateChassisUSpaceProcessor.cpp UpdateChassisUSpaceProcessor.h
	$(CC) -c UpdateChassisUSpaceProcessor.cpp
CoreSwitchInfoMappingProcessor.o: CoreSwitchInfoMappingProcessor.cpp CoreSwitchInfoMappingProcessor.h
	$(CC) -c CoreSwitchInfoMappingProcessor.cpp
AccessSwitchInfoMappingProcessor.o: AccessSwitchInfoMappingProcessor.cpp AccessSwitchInfoMappingProcessor.h
	$(CC) -c AccessSwitchInfoMappingProcessor.cpp
AggregationSwitchInfoMappingProcessor.o: AggregationSwitchInfoMappingProcessor.cpp AggregationSwitchInfoMappingProcessor.h
	$(CC) -c AggregationSwitchInfoMappingProcessor.cpp
UpdateCoreSwitchUSpaceProcessor.o: UpdateCoreSwitchUSpaceProcessor.cpp UpdateCoreSwitchUSpaceProcessor.h
	$(CC) -c -lpthread UpdateCoreSwitchUSpaceProcessor.cpp
UpdateAccessSwitchUSpaceProcessor.o: UpdateAccessSwitchUSpaceProcessor.cpp UpdateAccessSwitchUSpaceProcessor.h
	$(CC) -c -lpthread UpdateAccessSwitchUSpaceProcessor.cpp
UpdateAggregationSwitchUSpaceProcessor.o: UpdateAggregationSwitchUSpaceProcessor.cpp UpdateAggregationSwitchUSpaceProcessor.h
	$(CC) -c -lpthread UpdateAggregationSwitchUSpaceProcessor.cpp
ComputeDataProcessor.o: ComputeDataProcessor.cpp ComputeDataProcessor.h
	$(CC) -c ComputeDataProcessor.cpp
ComputeRackDataProcessor.o: ComputeRackDataProcessor.cpp ComputeRackDataProcessor.h
	$(CC) -c ComputeRackDataProcessor.cpp
ComputeAccessSwitchDataProcessor.o: ComputeAccessSwitchDataProcessor.cpp ComputeAccessSwitchDataProcessor.h
	$(CC) -c ComputeAccessSwitchDataProcessor.cpp
ComputeAggregationSwitchDataProcessor.o: ComputeAggregationSwitchDataProcessor.cpp ComputeAggregationSwitchDataProcessor.h
	$(CC) -c ComputeAggregationSwitchDataProcessor.cpp
InternalDataCheckProcessor.o: InternalDataCheckProcessor.cpp InternalDataCheckProcessor.h
	$(CC) -c InternalDataCheckProcessor.cpp
InternalServerDataCheckProcessor.o: InternalServerDataCheckProcessor.cpp InternalServerDataCheckProcessor.h
	$(CC) -c InternalServerDataCheckProcessor.cpp
ComputeRowDataProcessor.o: ComputeRowDataProcessor.cpp ComputeRowDataProcessor.h
	$(CC) -c ComputeRowDataProcessor.cpp
ComputeServerDataProcessor.o: ComputeServerDataProcessor.cpp ComputeServerDataProcessor.h
	$(CC) -c ComputeServerDataProcessor.cpp
PMMInfoUpdateProcessor.o: PMMInfoUpdateProcessor.cpp PMMInfoUpdateProcessor.h
	$(CC) -c PMMInfoUpdateProcessor.cpp
PMMInfoIndexProcessor.o: PMMInfoIndexProcessor.cpp PMMInfoIndexProcessor.h
	$(CC) -c PMMInfoIndexProcessor.cpp
PMMInfoChangeProcessor.o: PMMInfoChangeProcessor.cpp PMMInfoChangeProcessor.h
	$(CC) -c PMMInfoChangeProcessor.cpp
PMMIndexPooler.o: PMMIndexPooler.cpp PMMIndexPooler.h
	$(CC) -c PMMIndexPooler.cpp
IntergrateTechnicalOwnerProcessor.o: IntergrateTechnicalOwnerProcessor.cpp IntergrateTechnicalOwnerProcessor.h
	$(CC) -c IntergrateTechnicalOwnerProcessor.cpp
ZabbixAPIProcessor.o: ZabbixAPIProcessor.cpp ZabbixAPIProcessor.h
	$(CC) -c ZabbixAPIProcessor.cpp

clean:
	rm -rf *o ProcessorFolder

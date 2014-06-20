//====Table Name====
#define TBL_DIVISION "division"
#define TBL_DIVISION_INFO_CHANGE "info_change_division"
#define TBL_DIVISION_INFO_CHANGE_HISTORY "info_change_division_history"
#define TBL_DIVISION_INVERTED_INDEX "inverted_index_division"
#define TBL_TMP_DIVISION "tmp_division"
#define TBL_DIVISION_HISTORY_LOG "division_log"

#define TBL_DEPARTMENT "department"
#define TBL_DEPARTMENT_INFO_CHANGE "info_change_department"
#define TBL_DEPARTMENT_INFO_CHANGE_HISTORY "info_change_department_history"
#define TBL_DEPARTMENT_INVERTED_INDEX "inverted_index_department"
#define TBL_TMP_DEPARTMENT "tmp_department"
#define TBL_DEPARTMENT_HISTORY_LOG "department_log"
#define TBL_DEPARTMENT_NOTI "notification_department"

#define TBL_PRODUCT "product"
#define TBL_PRODUCT_INFO_CHANGE "info_change_product"
#define TBL_PRODUCT_INFO_CHANGE_HISTORY "info_change_product_history"
#define TBL_PRODUCT_INVERTED_INDEX "inverted_index_product"
#define TBL_TMP_PRODUCT "tmp_product"
#define TBL_PRODUCT_HISTORY_LOG "product_log"
#define TBL_PRODUCT_NOTI "notification_product"

#define TBL_SERVER "server"
#define TBL_SERVER_INFO_CHANGE "info_change_server"
#define TBL_SERVER_INFO_CHANGE_HISTORY "info_change_server_history"
#define TBL_SERVER_INVERTED_INDEX "inverted_index_server"
#define TBL_TMP_SERVER_VIRTUAL  "tmp_server_vm"
#define TBL_TMP_SERVER_PHYSICAL "tmp_server_physical"
#define TBL_SERVER_HISTORY_LOG "server_log"
#define TBL_PHYSICAL_SERVER_NOTI "notification_server_physical"
#define TBL_VIRTUAL_SERVER_NOTI "notification_server_virtual"
#define TBL_TMP_PHYSICAL_SERVER_NOTI "tmp_notification_server_physical"
#define TBL_SERVER_DATA_ERROR "server_data_error"

#define TBL_CHASSIS "chassis"
#define TBL_CHASSIS_INFO_CHANGE "info_change_chassis"
#define TBL_CHASSIS_INVERTED_INDEX "inverted_index_chassis"
#define TBL_TMP_CHASSIS "tmp_chassis"
#define TBL_CHASSIS_HISTORY_LOG "chassis_log"

#define TBL_CORE_SWITCH "core_switch"
#define TBL_CORE_SWITCH_INFO_CHANGE "info_change_core_switch"
#define TBL_CORE_SWITCH_INVERTED_INDEX "inverted_index_core_switch"
#define TBL_TMP_CORE_SWITCH "tmp_core_switch"
#define TBL_CORE_SWITCH_HISTORY_LOG "core_switch_log"

#define TBL_AGGREGATION_SWITCH "aggregation_switch"
#define TBL_AGGREGATION_SWITCH_INFO_CHANGE "info_change_aggregation_switch"
#define TBL_AGGREGATION_SWITCH_INVERTED_INDEX "inverted_index_aggregation_switch"
#define TBL_TMP_AGGREGATION_SWITCH "tmp_aggregation_switch"
#define TBL_AGGREGATION_SWITCH_HISTORY_LOG "aggregation_switch_log"

#define TBL_ACCESS_SWITCH "access_switch"
#define TBL_ACCESS_SWITCH_INFO_CHANGE "info_change_access_switch"
#define TBL_ACCESS_SWITCH_INVERTED_INDEX "inverted_index_access_switch"
#define TBL_TMP_ACCESS_SWITCH "tmp_access_switch"
#define TBL_ACCESS_SWITCH_HISTORY_LOG "access_switch_log"

#define TBL_PEER_LINK "peer_link"
#define TBL_PEER_LINK_INFO_CHANGE "info_change_peer_link"
#define TBL_PEER_LINK_INVERTED_INDEX "inverted_index_peer_link"
#define TBL_TMP_PEER_LINK "tmp_peer_link"
#define TBL_PEER_LINK_HISTORY_LOG "peer_link_log"

#define TBL_RACK "rack"
#define TBL_RACK_INFO_CHANGE "info_change_rack"
#define TBL_RACK_INVERTED_INDEX "inverted_index_rack"
#define TBL_TMP_RACK "tmp_rack"
#define TBL_RACK_HISTORY_LOG "rack_log"

#define TBL_ROW "row"
#define TBL_ROW_INFO_CHANGE "info_change_row"
#define TBL_ROW_INVERTED_INDEX "inverted_index_row"
#define TBL_TMP_ROW "tmp_row"
#define TBL_ROW_HISTORY_LOG "row_log"

#define TBL_PDU "pdu"
#define TBL_PDU_INFO_CHANGE "info_change_pdu"
#define TBL_PDU_INVERTED_INDEX "inverted_index_pdu"
#define TBL_TMP_PDU "tmp_pdu"
#define TBL_PDU_HISTORY_LOG "pdu_log"

#define TBL_PMM "pmm"
#define TBL_PMM_INFO_CHANGE "info_change_pmm"
#define TBL_PMM_INVERTED_INDEX "inverted_index_pmm"
#define TBL_TMP_PMM "tmp_pmm"
#define TBL_PMM_HISTORY_LOG "pmm_log"


#define TBL_CI_CHANGES "ci_changes"
#define TBL_PARTNER_INFO "partner_info"
#define TBL_COLLECTOR_INFO "collector_info"
#define TBL_CI_RELATIONSHIP "ci_relationship"
#define TBL_MAIL_BOX "mail_box"
#define TBL_USER "user"

#define TBL_CI_SPACE "ci_space"
#define TBL_MAIL_CONFIG "mail_config"
//==== ADMIN define =====//
#define TBL_PM_ROLES "pm_roles"
#define TBL_PRODUCT_OWNER "product_owner"
#define TBL_PRODUCT_ROLES "product_roles"
#define TBL_USER_GROUPS_PRODUCTS "user_groups_products"
#define TBL_USER_GROUPS_USERS "user_groups_users"

//===Config Define===
#define HOST "Host"
#define USER "User"
#define PASS "Password"
#define SRC "Source"
#define PORT "Port"
#define DB_TYPE "DBType"
#define MONGODB_CMDB_GROUP "MONGODB_CMDB"
#define MONGODB_MAILBOX_GROUP "MONGODB_MAILBOX"
#define MONGODB_CMDB_ADMIN_GROUP "MONGODB_CMDB_ADMIN" 
#define REPLICA_SET "ReplicaSet"
#define READ_REFERENCE "ReadReference"
#define READ_REFERENCE_SECONDARY "secondary"
#define DB_GROUP_MONGODB_DEFAULT MONGODB_CMDB_GROUP
#define DB_GROUP_MYSQL_DEFAULT "MYSQL_CMDB"

//=== DBType ===
#define DBTYPE_MONGODB "MongoDB"
#define DBTYPE_MYSQL "MySQL"

//=== Config Synchronize ===
#define SYNC_FULL "full"
#define SYNC_CHANGE "change"

//=== Define action type ===
#define ACTION_INSERT 1
#define ACTION_UPDATE 2
#define ACTION_DELETE 3
#define ACTION_REINSERT 4
#define UNKNOWN -1
#define API_ACTION_SUCCESS 1
//=== ACTIVE Or INACTIVE
#define ACTIVE 1
#define INACTIVE 0
//=== MATCH Or NOTMATCH
#define MATCH 1
#define NOTMATCH 0
//=== DEFINE FUNCITON CHECKER ===
#define SERVER_STATISTIC "server_statistic"
#define HARDWARE_INFO "hardware_info"
#define INTERFACE_INFO "interface_info"
//=== DEFINE SERVER TYPE ===
#define SERVER_UNKNOWN -1
#define SERVER_VIRTUAL 1
#define SERVER_U 2
#define SERVER_CHASSIS 3
//=== DEFINE SWITCH TYPE ===
#define SWITCH_U 1
#define SWITCH_MODULE 2
//=== DEFINE API NAME ===
#define API_GET_HARDWARE_BY_SERIALNUMBER "GetHardwareInfoBySerialNumber"
#define MSG_SOCKET_ERROR "Socket connection error"

//=== DEFINE MANUFACTURE ===
#define IBM "ibm"
#define INTEL "intel"
#define DELL_INC "dell inc."
#define DELL "Dell"

//=== DEFINE SDK AUTH WS ===
#define SDK_AUTH "SDK_AUTH"
#define CLIENT_ID "ClientId"
#define CLIENT_PASSWD "Passwd"

//=== DEFINE INVALiD IP & MAC ADDRESS ===
#define INVALID_MAC_ADDRESS "00:00:00:00:00:00"
#define INVALID_IP_ADDRESS "127.0.0.1"

//===Other===
#define HOTFIX "HOTFIX"
#define CI_ID "ci_id"

//=== DEFINE DIVISION EXCEPTION ===//
#define VNG_DIVISION "VNG"

//=== DEFINE FLAG DELETE OR UNDELETE
#define DELETED_FLAG 1
#define UNDELETED_FLAG 0

//=== DEFINE U_SPACE_DEFAULT ===//
#define U_SPACE_DEFAULT 1
#define U_DEFAULT		0

/*-- DEFINE SERVER STATUS --*/
#define	SERVER_UNUSED 0
#define	SERVER_IN_USED 1
#define	SERVER_BORROW 2
#define	SERVER_TRANSFER 3
#define	SERVER_ERROR 4

//=== DEFINE FUNCTION & APPLICATION TO NOTIFY ===//
#define APP_BACKEND_HANDLE_PHYSICAL_SERVER "backend_handle_physical_server"
#define FUNCTION_GRAPHIC_SERVER_CHASSIS "graphic_server_chassis"
#define APP_BACKEND_HANDEL_ACCESS_SWITCH "backend_handle_access_switch"
#define FUNCTION_GRAPHIC_SWITCH_CHASSIS "graphic_switch_chassis"
#define APP_BACKEND_HANDLE_DATA_MIS "backend_handle_data_mis"
#define FUNCTION_NOTIFY_LOST_DATA_SERVICE "notify_lost_data_service"

//=== DEFINE FIELD IN DATABASE
#define FIELD_RACK_SWITCH_TYPE "rack_switch_type"


//=== DEFINE ROLE IGNORE =====
#define ROLE_AUTHENTICATED_USER "Authenticated User"
#define ROLE_ADMINISTRATOR "Administrator"
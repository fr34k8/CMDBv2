#include <string>

#ifndef DCServiceReference_H__
#define DCServiceReference_H__

#define CODE_ERROR_SSL_INIT "1"
#define MSG_ERROR_SSL_INIT "Cannot init ssl to DC service"

#define CODE_ERROR_CRYPTO_THREAD_SETUP "2"
#define MSG_ERROR_CRYPTO_THREAD_SETUP "Cannot setup thread mutex for OpenSSL"

#define CODE_ERROR_INIT "3"
#define MSG_ERROR_INIT "Cannot access to DC service"

#define CODE_ERROR_SSL_CLIENT_CONTEXT "4"
#define MSG_ERROR_SSL_CLIENT_CONTEXT "SSL client authentication fail"

#define CODE_ERROR_UPDATE_STATUS_INC "5"
#define MSG_ERROR_UPDATE_STATUS_INC "Cannot call update status inc to DC"

// #define SECKEY "V34qG36hWwRxbff2ZeGH"
//#define SECKEY "V34qG36h"

// extern std::string CallNewProduct(char *ProductCode, char *ProductAlias, char *ProductName, char *ProductDepartment, char *ProductDivision, char *ProductOwner);
extern std::string CallNewProduct(const char* cJsonProdInfo);
#endif

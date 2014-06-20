#include "stdio.h"
#include <iostream>
#include <string.h>
#include <unistd.h>		/* defines _POSIX_THREADS if pthreads are available */
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
#include <pthread.h>
#endif
#include <signal.h>		/* defines SIGPIPE */
#include "soapH.h"
#include "sdk_USCOREmodelBinding.nsmap"
using namespace std;

#define MSG_ERROR_SSL_INIT "Soap SSL Init Fail"
#define MSG_ERROR_CRYPTO_THREAD_SETUP "Cannot setup thread mutex for OpenSSL"
#define MSG_ERROR_INIT "Cannot soap init"
#define MSG_ERROR_SSL_CLIENT_CONTEXT "SSL client authentication fail"
#define MSG_ERROR_SERVER_STATISTIC "Cannot call API ws_get_server_statictis"
#define MSG_ERROR_HARDWARE_INFO "Cannot call API ws_get_hardware_info_by_serialnumber"

int CRYPTO_thread_setup();
void CRYPTO_thread_cleanup();
void sigpipe_handle(int);

extern "C" char* GetServerStatistic(string& strErrorMsg)
{
	struct soap soap;
	char* pResponse = NULL;
	char* pTmpResponse = NULL;
	int nDataLength = 0;
	
	try
	{
		soap_ssl_init();
	}
	catch(exception& ex)
	{
		strErrorMsg = MSG_ERROR_SSL_INIT;
	}
	
	if (CRYPTO_thread_setup())
	{	
		strErrorMsg = MSG_ERROR_CRYPTO_THREAD_SETUP;
	}
	
	try
	{
		soap_init(&soap);
	}
	catch(exception& ex)
	{
		strErrorMsg = MSG_ERROR_INIT;
	}
	
	if (soap_ssl_client_context(&soap,
		/* SOAP_SSL_NO_AUTHENTICATION, */ /* for encryption w/o authentication */
		/* SOAP_SSL_DEFAULT | SOAP_SSL_SKIP_HOST_CHECK, */	/* if we don't want the host name checks since these will change from machine to machine */
		SOAP_SSL_DEFAULT,	/* use SOAP_SSL_DEFAULT in production code */
		NULL, 		/* keyfile (cert+key): required only when client must authenticate to server (see SSL docs to create this file) */
		NULL, 		/* password to read the keyfile */
		NULL,	/* optional cacert file to store trusted certificates, use cacerts.pem for all public certificates issued by common CAs */
		NULL,		/* optional capath to directory with trusted certificates */
		NULL		/* if randfile!=NULL: use a file with random data to seed randomness */ 
		))
	{	
		strErrorMsg = MSG_ERROR_SSL_CLIENT_CONTEXT;
	}
	
	soap.connect_timeout = 60;	/* try to connect for 1 minute */
	soap.send_timeout = soap.recv_timeout = 90;	/* if I/O stalls, then timeout after 30 seconds */
	
	if(soap_call_ns1__ws_USCOREget_USCOREserver_USCOREstatictis(&soap, 
							NULL  /*endpoint address*/, 
							NULL  /*soapAction*/, 
							&pTmpResponse
						   )== SOAP_OK)
	{
		if (NULL != pTmpResponse)
		{
			// Allocate memory to store result
			nDataLength = strlen(pTmpResponse);
			pResponse = new char[nDataLength + 1];
			pResponse[nDataLength] = '\0';

			// Copy result to memory
			strcpy(pResponse, pTmpResponse);
		}
	}
	else
	{   
		strErrorMsg = MSG_ERROR_SERVER_STATISTIC;
	}             
    
	soap_destroy(&soap); 
	soap_end(&soap); 
	soap_done(&soap);	
	CRYPTO_thread_cleanup();
	
	return pResponse;	
}

extern "C" char* GetHardwareInfoBySerialNumber(string& strErrorMsg, char* pSerialNumber)
{
	struct soap soap;
	char* pResponse = NULL;
	char* pTmpResponse = NULL;
	int nDataLength = 0;
	
	try
	{
		soap_ssl_init();
	}
	catch(exception& ex)
	{
		strErrorMsg = MSG_ERROR_SSL_INIT;
	}
	
	if (CRYPTO_thread_setup())
	{	
		strErrorMsg = MSG_ERROR_CRYPTO_THREAD_SETUP;
	}
	
	try
	{
		soap_init(&soap);
	}
	catch(exception& ex)
	{
		strErrorMsg = MSG_ERROR_INIT;
	}
	
	if (soap_ssl_client_context(&soap,
		/* SOAP_SSL_NO_AUTHENTICATION, */ /* for encryption w/o authentication */
		/* SOAP_SSL_DEFAULT | SOAP_SSL_SKIP_HOST_CHECK, */	/* if we don't want the host name checks since these will change from machine to machine */
		SOAP_SSL_DEFAULT,	/* use SOAP_SSL_DEFAULT in production code */
		NULL, 		/* keyfile (cert+key): required only when client must authenticate to server (see SSL docs to create this file) */
		NULL, 		/* password to read the keyfile */
		NULL,	/* optional cacert file to store trusted certificates, use cacerts.pem for all public certificates issued by common CAs */
		NULL,		/* optional capath to directory with trusted certificates */
		NULL		/* if randfile!=NULL: use a file with random data to seed randomness */ 
		))
	{	
		strErrorMsg = MSG_ERROR_SSL_CLIENT_CONTEXT;
	}
	
	soap.connect_timeout = 60;	/* try to connect for 1 minute */
	soap.send_timeout = soap.recv_timeout = 90;	/* if I/O stalls, then timeout after 30 seconds */
	
	if(soap_call_ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber(&soap, 
							NULL  /*endpoint address*/, 
							NULL  /*soapAction*/, 
							pSerialNumber,
							&pTmpResponse
						   )== SOAP_OK)
	{
		if (NULL != pTmpResponse)
		{
			// Allocate memory to store result
			nDataLength = strlen(pTmpResponse);
			pResponse = new char[nDataLength + 1];
			pResponse[nDataLength] = '\0';

			// Copy result to memory
			strcpy(pResponse, pTmpResponse);
		}
	}
	else
	{   
		strErrorMsg = MSG_ERROR_HARDWARE_INFO;
	}             
    
	soap_destroy(&soap); 
	soap_end(&soap); 
	soap_done(&soap);	
	CRYPTO_thread_cleanup();
	
	return pResponse;	
}

#ifdef WITH_OPENSSL

#if defined(WIN32)
# define MUTEX_TYPE		HANDLE
# define MUTEX_SETUP(x)		(x) = CreateMutex(NULL, FALSE, NULL)
# define MUTEX_CLEANUP(x)	CloseHandle(x)
# define MUTEX_LOCK(x)		WaitForSingleObject((x), INFINITE)
# define MUTEX_UNLOCK(x)	ReleaseMutex(x)
# define THREAD_ID		GetCurrentThreadId()
#elif defined(_POSIX_THREADS) || defined(_SC_THREADS)
# define MUTEX_TYPE		pthread_mutex_t
# define MUTEX_SETUP(x)		pthread_mutex_init(&(x), NULL)
# define MUTEX_CLEANUP(x)	pthread_mutex_destroy(&(x))
# define MUTEX_LOCK(x)		pthread_mutex_lock(&(x))
# define MUTEX_UNLOCK(x)	pthread_mutex_unlock(&(x))
# define THREAD_ID		pthread_self()
#else
# error "You must define mutex operations appropriate for your platform"
# error	"See OpenSSL /threads/th-lock.c on how to implement mutex on your platform"
#endif

struct CRYPTO_dynlock_value
{ MUTEX_TYPE mutex;
};

static MUTEX_TYPE *mutex_buf;

static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{ struct CRYPTO_dynlock_value *value;
  value = (struct CRYPTO_dynlock_value*)malloc(sizeof(struct CRYPTO_dynlock_value));
  if (value)
    MUTEX_SETUP(value->mutex);
  return value;
}

static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(l->mutex);
  else
    MUTEX_UNLOCK(l->mutex);
}

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l, const char *file, int line)
{ MUTEX_CLEANUP(l->mutex);
  free(l);
}

void locking_function(int mode, int n, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}

unsigned long id_function()
{ return (unsigned long)THREAD_ID;
}

int CRYPTO_thread_setup()
{ int i;
  mutex_buf = (MUTEX_TYPE*)malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
  if (!mutex_buf)
    return SOAP_EOM;
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  CRYPTO_set_dynlock_create_callback(dyn_create_function);
  CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
  CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);
  return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ int i;
  if (!mutex_buf)
    return;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  CRYPTO_set_dynlock_create_callback(NULL);
  CRYPTO_set_dynlock_lock_callback(NULL);
  CRYPTO_set_dynlock_destroy_callback(NULL);
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  free(mutex_buf);
  mutex_buf = NULL;
}

#else

/* OpenSSL not used, e.g. GNUTLS is used */

int CRYPTO_thread_setup()
{ return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ }

#endif

/******************************************************************************\
 *
 *	SIGPIPE
 *
\******************************************************************************/

void sigpipe_handle(int x) { }
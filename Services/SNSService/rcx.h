/* rcx.h
   Generated by wsdl2h 2.8.16 from https://icloud.vng.com.vn/services/sdk/index/wsdl and typemap.dat
   2014-03-06 04:34:38 GMT

   DO NOT INCLUDE THIS FILE DIRECTLY INTO YOUR PROJECT BUILDS
   USE THE soapcpp2-GENERATED SOURCE CODE FILES FOR YOUR PROJECT BUILDS

   gSOAP XML Web services tools.
   Copyright (C) 2000-2013 Robert van Engelen, Genivia Inc. All Rights Reserved.
   Part of this software is released under one of the following licenses:
   GPL or Genivia's license for commercial use.
*/

/** @page page_notes Usage Notes

NOTE:

 - Run soapcpp2 on rcx.h to generate the SOAP/XML processing logic.
   Use soapcpp2 -I to specify paths for #import
   To build with STL, 'stlvector.h' is imported from 'import' dir in package.
   Use soapcpp2 -j to generate improved proxy and server classes.
 - Use wsdl2h -c and -s to generate pure C code or C++ code without STL.
 - Use 'typemap.dat' to control namespace bindings and type mappings.
   It is strongly recommended to customize the names of the namespace prefixes
   generated by wsdl2h. To do so, modify the prefix bindings in the Namespaces
   section below and add the modified lines to 'typemap.dat' to rerun wsdl2h.
 - Use Doxygen (www.doxygen.org) on this file to generate documentation.
 - Use wsdl2h -R to generate REST operations.
 - Use wsdl2h -nname to use name as the base namespace prefix instead of 'ns'.
 - Use wsdl2h -Nname for service prefix and produce multiple service bindings
 - Use wsdl2h -d to enable DOM support for xsd:anyType.
 - Use wsdl2h -g to auto-generate readers and writers for root elements.
 - Use wsdl2h -b to auto-generate bi-directional operations (duplex ops).
 - Struct/class members serialized as XML attributes are annotated with a '@'.
 - Struct/class members that have a special role are annotated with a '$'.

WARNING:

   DO NOT INCLUDE THIS ANNOTATED FILE DIRECTLY IN YOUR PROJECT SOURCE CODE.
   USE THE FILES GENERATED BY soapcpp2 FOR YOUR PROJECT'S SOURCE CODE:
   THE soapStub.h FILE CONTAINS THIS CONTENT WITHOUT ANNOTATIONS.

LICENSE:

@verbatim
--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.

This software is released under one of the following licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial-use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
@endverbatim

*/


//gsoapopt cw

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   https://icloud.vng.com.vn/services/sdk/index                             *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/


/* NOTE:

It is strongly recommended to customize the names of the namespace prefixes
generated by wsdl2h. To do so, modify the prefix bindings below and add the
modified lines to typemap.dat to rerun wsdl2h:

ns1 = "https://icloud.vng.com.vn/services/sdk/index"

*/

#define SOAP_NAMESPACE_OF_ns1	"https://icloud.vng.com.vn/services/sdk/index"
//gsoap ns1   schema namespace:	https://icloud.vng.com.vn/services/sdk/index
//gsoap ns1   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/



/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   https://icloud.vng.com.vn/services/sdk/index                             *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   https://icloud.vng.com.vn/services/sdk/index                             *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   https://icloud.vng.com.vn/services/sdk/index                             *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   https://icloud.vng.com.vn/services/sdk/index                             *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns1  service name:	sdk_USCOREmodelBinding 
//gsoap ns1  service type:	sdk_USCOREmodelPort 
//gsoap ns1  service port:	https://icloud.vng.com.vn/services/sdk/index 
//gsoap ns1  service namespace:	https://icloud.vng.com.vn/services/sdk/index 
//gsoap ns1  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage sdk_model Definitions

@section sdk_USCOREmodel_bindings Service Bindings

  - @ref sdk_USCOREmodelBinding

@section sdk_USCOREmodel_more More Information

  - @ref page_notes "Usage Notes"

  - @ref page_XMLDataBinding "XML Data Binding"

  - @ref SOAP_ENV__Header "SOAP Header Content" (when applicable)

  - @ref SOAP_ENV__Detail "SOAP Fault Detail Content" (when applicable)


*/

/**

@page sdk_USCOREmodelBinding Binding "sdk_USCOREmodelBinding"

@section sdk_USCOREmodelBinding_operations Operations of Binding  "sdk_USCOREmodelBinding"

  - @ref ns1__ws_USCOREget_USCOREvmkey

  - @ref ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber

  - @ref ns1__ws_USCOREget_USCOREall_USCOREphysical_USCOREserver

  - @ref ns1__ws_USCOREget_USCOREserver_USCOREstatictis

  - @ref ns1__get_USCOREtotalserver_USCOREper_USCOREproduct

  - @ref ns1__ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber

@section sdk_USCOREmodelBinding_ports Endpoints of Binding  "sdk_USCOREmodelBinding"

  - https://icloud.vng.com.vn/services/sdk/index

Note: use wsdl2h option -Nname to change the service binding prefix name


*/

/******************************************************************************\
 *                                                                            *
 * Service Binding                                                            *
 *   sdk_USCOREmodelBinding                                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__ws_USCOREget_USCOREvmkey                                            *
 *                                                                            *
\******************************************************************************/


/// Operation "ns1__ws_USCOREget_USCOREvmkey" of service binding "sdk_USCOREmodelBinding"

/**

Operation details:
@param string $list //list mac address : mac1,mac2,mac3

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_vmkey"

  - Addressing input action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_vmkey"

  - Addressing output action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_vmkeyResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__ws_USCOREget_USCOREvmkey(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    char*                               list,
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__ws_USCOREget_USCOREvmkey(
    struct soap *soap,
    // input parameters:
    char*                               list,
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns1  service method-protocol:	ws_USCOREget_USCOREvmkey SOAP
//gsoap ns1  service method-style:	ws_USCOREget_USCOREvmkey rpc
//gsoap ns1  service method-encoding:	ws_USCOREget_USCOREvmkey http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-input-action:	ws_USCOREget_USCOREvmkey https://icloud.vng.com.vn/services/sdk/index#ws_get_vmkey
//gsoap ns1  service method-output-action:	ws_USCOREget_USCOREvmkey https://icloud.vng.com.vn/services/sdk/index#ws_get_vmkeyResponse
int ns1__ws_USCOREget_USCOREvmkey(
    char*                               list,	///< Input parameter
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber  *
 *                                                                            *
\******************************************************************************/


/// Operation "ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber" of service binding "sdk_USCOREmodelBinding"

/**

Operation details:
@param string $serial_number

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_hardware_info_by_serialnumber"

  - Addressing input action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_hardware_info_by_serialnumber"

  - Addressing output action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_hardware_info_by_serialnumberResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    char*                               serial_USCOREnumber,
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber(
    struct soap *soap,
    // input parameters:
    char*                               serial_USCOREnumber,
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns1  service method-protocol:	ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber SOAP
//gsoap ns1  service method-style:	ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber rpc
//gsoap ns1  service method-encoding:	ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-input-action:	ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber https://icloud.vng.com.vn/services/sdk/index#ws_get_hardware_info_by_serialnumber
//gsoap ns1  service method-output-action:	ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber https://icloud.vng.com.vn/services/sdk/index#ws_get_hardware_info_by_serialnumberResponse
int ns1__ws_USCOREget_USCOREhardware_USCOREinfo_USCOREby_USCOREserialnumber(
    char*                               serial_USCOREnumber,	///< Input parameter
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__ws_USCOREget_USCOREall_USCOREphysical_USCOREserver                  *
 *                                                                            *
\******************************************************************************/


/// Operation "ns1__ws_USCOREget_USCOREall_USCOREphysical_USCOREserver" of service binding "sdk_USCOREmodelBinding"

/**

Operation details:
@return string

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_all_physical_server"

  - Addressing input action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_all_physical_server"

  - Addressing output action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_all_physical_serverResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__ws_USCOREget_USCOREall_USCOREphysical_USCOREserver(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__ws_USCOREget_USCOREall_USCOREphysical_USCOREserver(
    struct soap *soap,
    // input parameters:
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns1  service method-protocol:	ws_USCOREget_USCOREall_USCOREphysical_USCOREserver SOAP
//gsoap ns1  service method-style:	ws_USCOREget_USCOREall_USCOREphysical_USCOREserver rpc
//gsoap ns1  service method-encoding:	ws_USCOREget_USCOREall_USCOREphysical_USCOREserver http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-input-action:	ws_USCOREget_USCOREall_USCOREphysical_USCOREserver https://icloud.vng.com.vn/services/sdk/index#ws_get_all_physical_server
//gsoap ns1  service method-output-action:	ws_USCOREget_USCOREall_USCOREphysical_USCOREserver https://icloud.vng.com.vn/services/sdk/index#ws_get_all_physical_serverResponse
int ns1__ws_USCOREget_USCOREall_USCOREphysical_USCOREserver(
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__ws_USCOREget_USCOREserver_USCOREstatictis                           *
 *                                                                            *
\******************************************************************************/


/// Operation "ns1__ws_USCOREget_USCOREserver_USCOREstatictis" of service binding "sdk_USCOREmodelBinding"

/**

Operation details:
@return string

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_server_statictis"

  - Addressing input action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_server_statictis"

  - Addressing output action: "https://icloud.vng.com.vn/services/sdk/index#ws_get_server_statictisResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__ws_USCOREget_USCOREserver_USCOREstatictis(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__ws_USCOREget_USCOREserver_USCOREstatictis(
    struct soap *soap,
    // input parameters:
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns1  service method-protocol:	ws_USCOREget_USCOREserver_USCOREstatictis SOAP
//gsoap ns1  service method-style:	ws_USCOREget_USCOREserver_USCOREstatictis rpc
//gsoap ns1  service method-encoding:	ws_USCOREget_USCOREserver_USCOREstatictis http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-input-action:	ws_USCOREget_USCOREserver_USCOREstatictis https://icloud.vng.com.vn/services/sdk/index#ws_get_server_statictis
//gsoap ns1  service method-output-action:	ws_USCOREget_USCOREserver_USCOREstatictis https://icloud.vng.com.vn/services/sdk/index#ws_get_server_statictisResponse
int ns1__ws_USCOREget_USCOREserver_USCOREstatictis(
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__get_USCOREtotalserver_USCOREper_USCOREproduct                       *
 *                                                                            *
\******************************************************************************/


/// Operation "ns1__get_USCOREtotalserver_USCOREper_USCOREproduct" of service binding "sdk_USCOREmodelBinding"

/**

Operation details:
@return string

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://icloud.vng.com.vn/services/sdk/index#get_totalserver_per_product"

  - Addressing input action: "https://icloud.vng.com.vn/services/sdk/index#get_totalserver_per_product"

  - Addressing output action: "https://icloud.vng.com.vn/services/sdk/index#get_totalserver_per_productResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__get_USCOREtotalserver_USCOREper_USCOREproduct(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__get_USCOREtotalserver_USCOREper_USCOREproduct(
    struct soap *soap,
    // input parameters:
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns1  service method-protocol:	get_USCOREtotalserver_USCOREper_USCOREproduct SOAP
//gsoap ns1  service method-style:	get_USCOREtotalserver_USCOREper_USCOREproduct rpc
//gsoap ns1  service method-encoding:	get_USCOREtotalserver_USCOREper_USCOREproduct http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-input-action:	get_USCOREtotalserver_USCOREper_USCOREproduct https://icloud.vng.com.vn/services/sdk/index#get_totalserver_per_product
//gsoap ns1  service method-output-action:	get_USCOREtotalserver_USCOREper_USCOREproduct https://icloud.vng.com.vn/services/sdk/index#get_totalserver_per_productResponse
int ns1__get_USCOREtotalserver_USCOREper_USCOREproduct(
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber        *
 *                                                                            *
\******************************************************************************/


/// Operation "ns1__ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber" of service binding "sdk_USCOREmodelBinding"

/**

Operation details:
@param string $serial_number

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://icloud.vng.com.vn/services/sdk/index#ws_update_servername_by_serialnumber"

  - Addressing input action: "https://icloud.vng.com.vn/services/sdk/index#ws_update_servername_by_serialnumber"

  - Addressing output action: "https://icloud.vng.com.vn/services/sdk/index#ws_update_servername_by_serialnumberResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    char*                               serial_USCOREnumber,
    _XML                                servername,
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber(
    struct soap *soap,
    // input parameters:
    char*                               serial_USCOREnumber,
    _XML                                servername,
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns1  service method-protocol:	ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber SOAP
//gsoap ns1  service method-style:	ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber rpc
//gsoap ns1  service method-encoding:	ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-input-action:	ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber https://icloud.vng.com.vn/services/sdk/index#ws_update_servername_by_serialnumber
//gsoap ns1  service method-output-action:	ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber https://icloud.vng.com.vn/services/sdk/index#ws_update_servername_by_serialnumberResponse
int ns1__ws_USCOREupdate_USCOREservername_USCOREby_USCOREserialnumber(
    char*                               serial_USCOREnumber,	///< Input parameter
    _XML                                servername,	///< Input parameter
    char*                              *return_	///< Output parameter
);

/**

@page sdk_USCOREmodelBinding Binding "sdk_USCOREmodelBinding"

@section sdk_USCOREmodelBinding_policy_enablers Policy Enablers of Binding  "sdk_USCOREmodelBinding"

Based on policies, this service imports

  - WS-Policy reminders and enablers:
    - WS-Addressing 1.0 (2005/08, accepts 2004/08):
	@code
	#import "wsa5.h" // to be added to this header file for the soapcpp2 build step
	@endcode
	@code
	#include "plugin/wsaapi.h"
	soap_register_plugin(soap, soap_wsa); // register the wsa plugin in your code
	// See the user guide gsoap/doc/wsa/html/index.html
	@endcode
    - WS-Addressing (2004/08):
	@code
	#import "wsa.h" // to be added to this header file for the soapcpp2 build step
	@endcode
	@code
	#include "plugin/wsaapi.h"
	soap_register_plugin(soap, soap_wsa); // register the wsa plugin in your code
	// See the user guide gsoap/doc/wsa/html/index.html
	@endcode
    - WS-ReliableMessaging 1.0:
	@code
	#import "wsrm5.h" // to be added to this header file for the soapcpp2 build step
	@endcode
	@code
	#include "plugin/wsrmapi.h"
	soap_register_plugin(soap, soap_wsa); // register the wsa plugin in your code
	soap_register_plugin(soap, soap_wsrm); // register the wsrm plugin in your code
	// See the user guide gsoap/doc/wsrm/html/index.html
	@endcode
    - WS-ReliableMessaging 1.1:
	@code
	#import "wsrm.h" // to be added to this header file for the soapcpp2 build step
	@endcode
	@code
	#include "plugin/wsrmapi.h"
	soap_register_plugin(soap, soap_wsa); // register the wsa plugin in your code
	soap_register_plugin(soap, soap_wsrm); // register the wsrm plugin in your code
	// See the user guide gsoap/doc/wsrm/html/index.html
	@endcode
    - WS-Security (SOAP Message Security) 1.0 (accepts 1.1):
	@code
	#import "wsse.h" // to be added to this header file for the soapcpp2 build step
	@endcode
	@code
	#include "plugin/wsseapi.h"
	soap_register_plugin(soap, soap_wsse); // register the wsse plugin in your code
	// See the user guide gsoap/doc/wsse/html/index.html
	@endcode
    - WS-Security (SOAP Message Security) 1.1 (accepts 1.0):
	@code
	#import "wsse11.h" // to be added to this header file for the soapcpp2 build step
	@endcode
	@code
	#include "plugin/wsseapi.h"
	soap_register_plugin(soap, soap_wsse); // register the wsse plugin in your code
	// See the user guide gsoap/doc/wsse/html/index.html
	@endcode
    - HTTP Digest Authentication:
	@code
	#include "plugin/httpda.h"
	soap_register_plugin(soap, soap_http_da); // register the HTTP DA plugin in your code
	// See the user guide gsoap/doc/httpda/html/index.html
	@endcode
*/


/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/**

@page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings contractually bound by WSDL and auto-
generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data bindings
are adopted from XML schemas as part of the WSDL types section or when running
wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

The following readers and writers are C/C++ data type (de)serializers auto-
generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

Data can be read in XML and deserialized from:
  - a file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->is = ...
  - a buffer, using the soap->frecv() callback

Data can be serialized in XML and written to:
  - a file descriptor, using soap->sendfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->os = ...
  - a buffer, using the soap->fsend() callback

The following options are available for (de)serialization control:
  - soap->encodingStyle = NULL; to remove SOAP 1.1/1.2 encodingStyle
  - soap_mode(soap, SOAP_XML_TREE); XML without id-ref (no cycles!)
  - soap_mode(soap, SOAP_XML_GRAPH); XML with id-ref (including cycles)
  - soap_set_namespaces(soap, struct Namespace *nsmap); to set xmlns bindings


@section ns1 Top-level root elements of schema "https://icloud.vng.com.vn/services/sdk/index"

*/

/* End of rcx.h */

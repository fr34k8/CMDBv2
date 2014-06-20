/* rcx.h
   Generated by wsdl2h 2.8.16 from https://dcim.vng.com.vn/APIServer/server.php?wsdl and typemap.dat
   2014-02-21 09:10:38 GMT

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
 *   http://dcim.vng.com.vn/soap/server.php                                   *
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

ns1 = "http://dcim.vng.com.vn/soap/server.php"

*/

#define SOAP_NAMESPACE_OF_ns1	"http://dcim.vng.com.vn/soap/server.php"
//gsoap ns1   schema namespace:	http://dcim.vng.com.vn/soap/server.php
//gsoap ns1   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/



/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   http://dcim.vng.com.vn/soap/server.php                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   http://dcim.vng.com.vn/soap/server.php                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   http://dcim.vng.com.vn/soap/server.php                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   http://dcim.vng.com.vn/soap/server.php                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns2  service name:	server_x002ephpBinding 
//gsoap ns2  service type:	server_x002ephpPortType 
//gsoap ns2  service port:	https://dcim.vng.com.vn:443/APIServer/server.php 
//gsoap ns2  service namespace:	 
//gsoap ns2  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage Service Definitions

@section Service_bindings Service Bindings

  - @ref server_x002ephpBinding

@section Service_more More Information

  - @ref page_notes "Usage Notes"

  - @ref page_XMLDataBinding "XML Data Binding"

  - @ref SOAP_ENV__Header "SOAP Header Content" (when applicable)

  - @ref SOAP_ENV__Detail "SOAP Fault Detail Content" (when applicable)


*/

/**

@page server_x002ephpBinding Binding "server_x002ephpBinding"

@section server_x002ephpBinding_operations Operations of Binding  "server_x002ephpBinding"

  - @ref ns2__newServer

  - @ref ns2__updateServer

  - @ref ns2__removeServer

@section server_x002ephpBinding_ports Endpoints of Binding  "server_x002ephpBinding"

  - https://dcim.vng.com.vn:443/APIServer/server.php

Note: use wsdl2h option -Nname to change the service binding prefix name


*/

/******************************************************************************\
 *                                                                            *
 * Service Binding                                                            *
 *   server_x002ephpBinding                                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns2__newServer                                                           *
 *                                                                            *
\******************************************************************************/


/// Operation "ns2__newServer" of service binding "server_x002ephpBinding"

/**

Operation details:

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://dcim.vng.com.vn/APIServer/server.php/newServer"

  - Addressing input action: "https://dcim.vng.com.vn/APIServer/server.php/newServer"

  - Addressing output action: "https://dcim.vng.com.vn/APIServer/server.php/newServerResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns2__newServer(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    char*                               infoServer,
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns2__newServer(
    struct soap *soap,
    // input parameters:
    char*                               infoServer,
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns2  service method-protocol:	newServer SOAP
//gsoap ns2  service method-style:	newServer rpc
//gsoap ns2  service method-encoding:	newServer http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns2  service method-input-action:	newServer https://dcim.vng.com.vn/APIServer/server.php/newServer
//gsoap ns2  service method-output-action:	newServer https://dcim.vng.com.vn/APIServer/server.php/newServerResponse
int ns2__newServer(
    char*                               infoServer,	///< Input parameter
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns2__updateServer                                                        *
 *                                                                            *
\******************************************************************************/


/// Operation "ns2__updateServer" of service binding "server_x002ephpBinding"

/**

Operation details:

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://dcim.vng.com.vn/APIServer/server.php/updateServer"

  - Addressing input action: "https://dcim.vng.com.vn/APIServer/server.php/updateServer"

  - Addressing output action: "https://dcim.vng.com.vn/APIServer/server.php/updateServerResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns2__updateServer(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    char*                               infoServer,
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns2__updateServer(
    struct soap *soap,
    // input parameters:
    char*                               infoServer,
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns2  service method-protocol:	updateServer SOAP
//gsoap ns2  service method-style:	updateServer rpc
//gsoap ns2  service method-encoding:	updateServer http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns2  service method-input-action:	updateServer https://dcim.vng.com.vn/APIServer/server.php/updateServer
//gsoap ns2  service method-output-action:	updateServer https://dcim.vng.com.vn/APIServer/server.php/updateServerResponse
int ns2__updateServer(
    char*                               infoServer,	///< Input parameter
    char*                              *return_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns2__removeServer                                                        *
 *                                                                            *
\******************************************************************************/


/// Operation "ns2__removeServer" of service binding "server_x002ephpBinding"

/**

Operation details:

  - http://schemas.xmlsoap.org/soap/encoding/ RPC encodingStyle="SOAP"

  - Action: "https://dcim.vng.com.vn/APIServer/server.php/removeServer"

  - Addressing input action: "https://dcim.vng.com.vn/APIServer/server.php/removeServer"

  - Addressing output action: "https://dcim.vng.com.vn/APIServer/server.php/removeServerResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns2__removeServer(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    char*                               serialNumber,
    // output parameters:
    char*                              *return_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns2__removeServer(
    struct soap *soap,
    // input parameters:
    char*                               serialNumber,
    // output parameters:
    char*                              *return_
  );
@endcode

*/

//gsoap ns2  service method-protocol:	removeServer SOAP
//gsoap ns2  service method-style:	removeServer rpc
//gsoap ns2  service method-encoding:	removeServer http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns2  service method-input-action:	removeServer https://dcim.vng.com.vn/APIServer/server.php/removeServer
//gsoap ns2  service method-output-action:	removeServer https://dcim.vng.com.vn/APIServer/server.php/removeServerResponse
int ns2__removeServer(
    char*                               serialNumber,	///< Input parameter
    char*                              *return_	///< Output parameter
);

/**

@page server_x002ephpBinding Binding "server_x002ephpBinding"

@section server_x002ephpBinding_policy_enablers Policy Enablers of Binding  "server_x002ephpBinding"

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


@section ns1 Top-level root elements of schema "http://dcim.vng.com.vn/soap/server.php"

*/

/* End of rcx.h */

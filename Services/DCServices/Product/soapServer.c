/* soapServer.c
   Generated by gSOAP 2.8.16 from rcx.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"
#ifdef __cplusplus
extern "C" {
#endif

SOAP_SOURCE_STAMP("@(#) soapServer.c ver 2.8.16 2014-02-28 06:41:33 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	unsigned int k = soap->max_keep_alive;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (soap->max_keep_alive > 0 && !--k)
			soap->keep_alive = 0;
#endif
		if (soap_begin_serve(soap))
		{	if (soap->error >= SOAP_STOP)
				continue;
			return soap->error;
		}
		if (soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns2:newProduct"))
		return soap_serve_ns2__newProduct(soap);
	if (!soap_match_tag(soap, soap->tag, "ns2:updateProduct"))
		return soap_serve_ns2__updateProduct(soap);
	if (!soap_match_tag(soap, soap->tag, "ns2:removeProduct"))
		return soap_serve_ns2__removeProduct(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns2__newProduct(struct soap *soap)
{	struct ns2__newProduct soap_tmp_ns2__newProduct;
	struct ns2__newProductResponse soap_tmp_ns2__newProductResponse;
	char * soap_tmp_string;
	soap_default_ns2__newProductResponse(soap, &soap_tmp_ns2__newProductResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__newProductResponse.return_ = &soap_tmp_string;
	soap_default_ns2__newProduct(soap, &soap_tmp_ns2__newProduct);
	if (!soap_get_ns2__newProduct(soap, &soap_tmp_ns2__newProduct, "ns2:newProduct", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns2__newProduct(soap, soap_tmp_ns2__newProduct.infoProduct, soap_tmp_ns2__newProductResponse.return_);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_serializeheader(soap);
	soap_serialize_ns2__newProductResponse(soap, &soap_tmp_ns2__newProductResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__newProductResponse(soap, &soap_tmp_ns2__newProductResponse, "ns2:newProductResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__newProductResponse(soap, &soap_tmp_ns2__newProductResponse, "ns2:newProductResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns2__updateProduct(struct soap *soap)
{	struct ns2__updateProduct soap_tmp_ns2__updateProduct;
	struct ns2__updateProductResponse soap_tmp_ns2__updateProductResponse;
	char * soap_tmp_string;
	soap_default_ns2__updateProductResponse(soap, &soap_tmp_ns2__updateProductResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__updateProductResponse.return_ = &soap_tmp_string;
	soap_default_ns2__updateProduct(soap, &soap_tmp_ns2__updateProduct);
	if (!soap_get_ns2__updateProduct(soap, &soap_tmp_ns2__updateProduct, "ns2:updateProduct", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns2__updateProduct(soap, soap_tmp_ns2__updateProduct.infoProduct, soap_tmp_ns2__updateProductResponse.return_);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_serializeheader(soap);
	soap_serialize_ns2__updateProductResponse(soap, &soap_tmp_ns2__updateProductResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__updateProductResponse(soap, &soap_tmp_ns2__updateProductResponse, "ns2:updateProductResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__updateProductResponse(soap, &soap_tmp_ns2__updateProductResponse, "ns2:updateProductResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns2__removeProduct(struct soap *soap)
{	struct ns2__removeProduct soap_tmp_ns2__removeProduct;
	struct ns2__removeProductResponse soap_tmp_ns2__removeProductResponse;
	char * soap_tmp_string;
	soap_default_ns2__removeProductResponse(soap, &soap_tmp_ns2__removeProductResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__removeProductResponse.return_ = &soap_tmp_string;
	soap_default_ns2__removeProduct(soap, &soap_tmp_ns2__removeProduct);
	if (!soap_get_ns2__removeProduct(soap, &soap_tmp_ns2__removeProduct, "ns2:removeProduct", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns2__removeProduct(soap, soap_tmp_ns2__removeProduct.ProductCode, soap_tmp_ns2__removeProductResponse.return_);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_serializeheader(soap);
	soap_serialize_ns2__removeProductResponse(soap, &soap_tmp_ns2__removeProductResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__removeProductResponse(soap, &soap_tmp_ns2__removeProductResponse, "ns2:removeProductResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__removeProductResponse(soap, &soap_tmp_ns2__removeProductResponse, "ns2:removeProductResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

#ifdef __cplusplus
}
#endif

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapServer.c */

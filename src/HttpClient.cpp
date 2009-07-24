/*
 ============================================================================
 Name	: HttpClient.cpp
 Author	: John Kern
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symbian Foundation Ltd - initial contribution.
 
 Contributors:
 - John Kern
 - Symsource
 
 Description : Web client 
 ============================================================================
 */

#include <activeapdb.h>
#include <HttpStringConstants.h>  // HTTP

#include "HttpClient.h"

// HTTP header values
_LIT8(KUserAgent, "NPR 1.0");		// Name of the client app.
_LIT8(KAccept, "text/*");	// Accept any (but only) text content (errors may not be sent as "text/x-visto-ota-activation").

CHttpClient* CHttpClient::NewL(MHTTPObserver& aObserver)
	{
	CHttpClient* self = new (ELeave)CHttpClient(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CHttpClient::CHttpClient(MHTTPObserver& aObserver)
	:iObserver(aObserver)
	{
	}

CHttpClient::~CHttpClient()
	{
	if (iTransactionActive)
		{
		iHttpTransaction.Cancel();
		iTransactionActive = EFalse;
		}

	iHTTPSession.Close();
	iConnection.Close();
	iSocketServ.Close();
	delete iResponseBuffer;
	delete iUri;
	}

void CHttpClient::ConstructL()
	{
	// Open the Http session
	iHTTPSession.OpenL();
    User::LeaveIfError(iSocketServ.Connect());
    User::LeaveIfError(iConnection.Open(iSocketServ));
    User::LeaveIfError(iConnection.Start());
	}


void CHttpClient::SendRequestL(const TDesC& aUri)
	{
	if(iUri)
		{
		delete iUri;
		iUri = NULL;
		}
	
	iUri = HBufC8::NewL(aUri.Length());
	TPtr8 uriPtr = iUri->Des();
	uriPtr.Copy(aUri);

	TUriParser8 uriParser;
	User::LeaveIfError(uriParser.Parse(uriPtr));
	
	TBuf8<256> buf;
	buf.Copy(uriParser.UriDes());
			
	RStringPool strPool = iHTTPSession.StringPool();
	iHttpConnInfo = iHTTPSession.ConnectionInfo();
	iHttpConnInfo.SetPropertyL(strPool.StringF(HTTP::EHttpSocketServ, RHTTPSession::GetTable() ), THTTPHdrVal(iSocketServ.Handle()));
	iHttpConnInfo.SetPropertyL(strPool.StringF(HTTP::EHttpSocketConnection, RHTTPSession::GetTable() ),THTTPHdrVal (REINTERPRET_CAST(TInt, &(iConnection))));
	
	if(iTransactionActive)
		{
		iHttpTransaction.Cancel();
		iHttpTransaction.Close();
		iTransactionActive = EFalse;
		}

	// Create transaction
	iHttpTransaction = iHTTPSession.OpenTransactionL(
		uriParser, 
		*this,
		iHTTPSession.StringPool().StringF(HTTP::EPOST, RHTTPSession::GetTable()));
	iTransactionActive = ETrue;
	
	
	// Set transaction headers.
	RHTTPHeaders headers = iHttpTransaction.Request().GetHeaderCollection();
	AddHeaderL(headers, HTTP::EUserAgent, KUserAgent);
	AddHeaderL(headers, HTTP::EAccept, KAccept);
	
	// Delete any previous response.
	delete iResponseBuffer;
	iResponseBuffer = NULL;
	
	// Set the body.
	iHttpTransaction.Request().SetBody(*this);
	
	// Submit the request
	iHttpTransaction.SubmitL();
	}

/**
* Add a header to a header set
*
* @param aHeaders The header set to be modified
* @param aHeaderField The name of the header to be added
* @param aHeaderValue The value for the header to be added
*/
void CHttpClient::AddHeaderL(RHTTPHeaders aHeaders,
								TInt aHeaderField,
								const TDesC8& aHeaderValue)
	{
	RStringPool stringPool = iHTTPSession.StringPool();	// Do not close this session here.
	RStringF valStr = stringPool.OpenFStringL(aHeaderValue);
	CleanupClosePushL(valStr);
	THTTPHdrVal headerVal(valStr);
	aHeaders.SetFieldL(stringPool.StringF(aHeaderField, RHTTPSession::GetTable()), headerVal);
	CleanupStack::PopAndDestroy();	// valStr
	}

/**
 * Add a header to a header set
 *
 * @param aHeaders The header set to be modified
 * @param aHeaderField The name of the header to be added
 * @param aHeaderValue The value for the header to be added
 * @param aExtensionValue The extension value for the header
 */
void CHttpClient::AddHeaderL(RHTTPHeaders aHeaders, 
								TInt aHeaderField, 
								const TDesC8& aHeaderValue,
								TInt aExtensionField,
								const TDesC8& aExtensionValue)
	{
	RStringPool stringPool = iHTTPSession.StringPool();	// Do not close this session here.
	RStringF valStr = stringPool.OpenFStringL(aHeaderValue);
	CleanupClosePushL(valStr);
	THTTPHdrVal headerVal(valStr);
	RStringF extensionStr = stringPool.OpenFStringL(aExtensionValue);
	CleanupClosePushL(extensionStr);
	THTTPHdrVal extensionVal(extensionStr);
	aHeaders.SetFieldL(
		stringPool.StringF(aHeaderField, RHTTPSession::GetTable()), 
		headerVal,
		stringPool.StringF(aExtensionField, RHTTPSession::GetTable()),
		extensionVal);
	CleanupStack::PopAndDestroy(2);	// extensionStr, valStr
	}

void CHttpClient::MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent &aEvent)
	{
	switch (aEvent.iStatus){
		case THTTPEvent::EGotResponseHeaders:
			{
			// HTTP response headers have been received.
			// Pass status information to observer.
			RHTTPResponse resp = aTransaction.Response();
			// Get status code
			TInt statusCode = resp.StatusCode();

			// Get status text
			RStringF statusStr = resp.StatusText();
			HBufC* statusBuf = HBufC::NewLC(statusStr.DesC().Length());
			statusBuf->Des().Copy(statusStr.DesC());

			// Inform observer
			iObserver.ResponseStatusL(statusCode, *statusBuf);

			CleanupStack::PopAndDestroy(statusBuf);
			break;
			}
	    case THTTPEvent::EGotResponseBodyData:
	    	{
			// Get text of response body
			MHTTPDataSupplier* dataSupplier = aTransaction.Response().Body();
			TPtrC8 ptr;
			dataSupplier->GetNextDataPart(ptr);

			// Append to iResponseBuffer
			if (!iResponseBuffer)
				{
				iResponseBuffer = ptr.AllocL();
				}
			else
				{
				iResponseBuffer = iResponseBuffer->ReAllocL(iResponseBuffer->Length() + ptr.Length());
				iResponseBuffer->Des().Append(ptr);
				}

			// Release the body data
			dataSupplier->ReleaseData();
			break;
			}
	    case THTTPEvent::EResponseComplete:
			iObserver.ResponseReceivedL(*iResponseBuffer);
	    	break;
	    case THTTPEvent::ESucceeded:
	    case THTTPEvent::EFailed:
	    	{
	    	aTransaction.Close();
			iTransactionActive = EFalse;
	    	break;
	    	}
		case THTTPEvent::ERedirectedPermanently:
			break;
		case THTTPEvent::ERedirectedTemporarily:
			break;
		default:
			{
			if (aEvent.iStatus < 0)
				{
				aTransaction.Close();
				iTransactionActive = EFalse;
				}
			break;
			}
		}
	}

TInt CHttpClient::MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& /*aEvent*/)
	{
	if(!aError)
		{
		aTransaction.Close();
		iTransactionActive = EFalse;
		}
	return KErrNone;
	}

TBool CHttpClient::GetNextDataPart(TPtrC8& /*aDataPart*/)
	{
	// Not implemented for now as assuming that chunked response won't be sent 
	// by the server
	return ETrue;
	}

void CHttpClient::ReleaseData()
	{
	// Not implemented for now as assuming that chunked response won't be sent 
	// by the server
	}

TInt CHttpClient::OverallDataSize()
	{
	// Not implemented for now as assuming that chunked response won't be sent 
	// by the server
	return 0;
	}

TInt CHttpClient::Reset()
	{
	// Not implemented for now as assuming that chunked response won't be sent 
	// by the server
	return KErrNone;
	}

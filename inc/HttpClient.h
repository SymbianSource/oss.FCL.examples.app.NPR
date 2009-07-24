/*
 ============================================================================
 Name	: HttpClient.h
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
 
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __HTTP_CLIENT_H_
#define __HTTP_CLIENT_H_

#include <es_sock.h>
#include <http/mhttpdatasupplier.h>
#include <http/mhttptransactioncallback.h>
#include <http/rhttpheaders.h>
#include <http/RHTTPSession.h>

#include "NPRStoryXmlParser.h"

class MHTTPObserver
	{
	public:
		virtual void ResponseStatusL(TInt aStatusCode, const TDesC& aStatusText) = 0;
		virtual void ResponseReceivedL(const TDesC8& aResponseBuffer) = 0;
	};

/*
 * This class implements the http request response sequence using RHTTPSession
 * class. The IAP selection is not done silently and needs user input.
 */

class CHttpClient : public CBase,
					public MHTTPTransactionCallback,
					public MHTTPDataSupplier
	{
public:
	static CHttpClient* NewL(MHTTPObserver& aObserver);
	virtual ~CHttpClient();
	
public:
	void SendRequestL(const TDesC& aUri);

	//From MHTTPTransactionCallback
	void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent &aEvent);
	TInt MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent &aEvent);
	
	//From MHTTPDataSupplier
	TBool GetNextDataPart(TPtrC8& aDataPart);
	void ReleaseData();
	TInt OverallDataSize();
	TInt Reset();

private:
	void AddHeaderL(RHTTPHeaders aHeaders, TInt aHeaderField, const TDesC8& aHeaderValue);
	void AddHeaderL(RHTTPHeaders aHeaders, TInt aHeaderField, const TDesC8& aHeaderValue, TInt aExtensionField, const TDesC8& aExtensionValue);
	
private:
	CHttpClient(MHTTPObserver& aObserver);
	void ConstructL();

private:
	RHTTPSession 			iHTTPSession;
	MHTTPObserver& 			iObserver;
	RSocketServ 			iSocketServ;
	RConnection 			iConnection;
	RHTTPTransaction		iHttpTransaction;
	RHTTPConnectionInfo 	iHttpConnInfo;
	HBufC8* 				iResponseBuffer; // The buffers to hold the request and response bodies.
	HBufC8* 				iUri;
	TBool 					iTransactionActive;
	};

#endif /* __HTTP_CLIENT_H_ */

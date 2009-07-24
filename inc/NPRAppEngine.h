/*
 ============================================================================
 Name	: NPRAppEngine.h
 Author	: Symsource
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symsource
 
 Contributors:
 - Symsource
 
 Description:
 ============================================================================
 */

#ifndef __NPR_APP_ENGINE_H__
#define __NPR_APP_ENGINE_H__

#include <e32base.h>
#include "HttpClient.h"
#include "NPR.hrh"

class CAknWaitDialog;
class CDocumentHandler;
class CNPRAppUi;
class CNPRStation;
class CNPRStories;


class CNPRAppEngine : public CBase, public MHTTPObserver
	{
public:
	static CNPRAppEngine* NewL(CNPRAppUi& aNPRAppUi);
 	virtual ~CNPRAppEngine();
 	
public:
	void SendNPRCommandL(const TNPRCommands aCommand, const TDesC& aField);
	const RPointerArray<CNPRStation>* Stations();
	const RPointerArray<CNPRStory>* Stories();

public:
	//From MHTTPObserver
	void ResponseStatusL(TInt aStatusCode, const TDesC& aStatusText);
	void ResponseReceivedL(const TDesC8& aResponseBuffer) ;

private:
	void SearchStationsL(const TDesC& aField);
	void SearchNewsL(const TDesC& aField);
    void LaunchFileL(const TDesC& aFilename);
    void RefreshDocumentFileL(const TUid& aUid, const TDesC& aFileName);
    void ShowWaitingDialogL(const TDesC& aText);
    void DismissWaitingDialogL();
	
private:
	CNPRAppEngine(CNPRAppUi& aNPRAppUi);
	void ConstructL();
	
private:
	CNPRAppUi& 					iNPRAppUi;
	CHttpClient* 				iHttp;
	TNPRCommands 				iNPRCommand;
	CDocumentHandler* 			iDocHandler;
	RPointerArray<CNPRStation> 	iStationArray;
	RPointerArray<CNPRStory> 	iStoryArray;
	CAknWaitDialog* 			iWaitDialog;
	};

#endif // __NPR_APP_ENGINE_H__


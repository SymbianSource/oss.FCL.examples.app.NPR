/*
 ============================================================================
 Name	: NPRAppEngine.cpp
 Author	: Symsourcce
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symsource
 
 Contributors:
 - Symsource
 
 Description :
 ============================================================================
 */

#include <DocumentHandler.h>
#include <aknwaitdialog.h>
#include <NPR_0xEEB0E481.rsg>

#include "NPRAppEngine.h"
#include "NPRAppUi.h"
#include "NPRStationXmlParser.h"
#include "NPRStation.h"
#include "NPRStory.h"

_LIT(KNPRQuery, "http://api.npr.org/query?id=1001&apiKey=MDAzNTk1Nzk0MDEyNDQ2NjI1NzgyNGExNg001");
_LIT(KNPRApiKey, "MDAzNTk1Nzk0MDEyNDQ2NjI1NzgyNGExNg001");
_LIT(KNPRStationQuery,"http://api.npr.org/stations?%S&apiKey=%S");
_LIT(KSearching, "Searching...");

_LIT(KStationStreamFile, "c:\\data\\npr_station_stream.rm");
_LIT(KNewsStreamFile, "c:\\data\\npr_news_stream.rm");

_LIT8(KDataTypeRAM,"audio/x-pn-realaudio-plugin");
_LIT8(KXmlMimeType, "text/xml");


CNPRAppEngine* CNPRAppEngine::NewL(CNPRAppUi& aNPRAppUi)
	{	
	CNPRAppEngine* self = new (ELeave) CNPRAppEngine(aNPRAppUi);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CNPRAppEngine::CNPRAppEngine(CNPRAppUi& aNPRAppUi)
	:iNPRAppUi(aNPRAppUi)
	{
	}

CNPRAppEngine::~CNPRAppEngine()
	{
	delete iDocHandler;
	delete iHttp;
	iStationArray.ResetAndDestroy();
	iStationArray.Close();
	iStoryArray.ResetAndDestroy();
	iStoryArray.Close();
	if(iWaitDialog)
		{		
	    delete iWaitDialog;
	    iWaitDialog = NULL;
		}
	}

void CNPRAppEngine::ConstructL()
	{
	this->iHttp = CHttpClient::NewL(*this);
    // Create the document handler
    iDocHandler = CDocumentHandler::NewL(CEikonEnv::Static()->Process());
	}


void CNPRAppEngine::SendNPRCommandL(const TNPRCommands aCommand, const TDesC& aField)
	{
	switch(aCommand)
		{
		case ENewsCmd:
			{
			SearchNewsL(aField);
			ShowWaitingDialogL(KSearching());
			break;
			}
		case EStationsCmd:
			{
			SearchStationsL(aField);
			ShowWaitingDialogL(KSearching());
			break;
			}
		case EPlayStationStream:
			{
			TFileName filename(KStationStreamFile);
			LaunchFileL(filename);
			break;
			}
		case EPlayNewsStream:
			{
			TFileName filename(KNewsStreamFile);
			LaunchFileL(filename);
			break;
			}
		default:
			return;
		}
	}

const RPointerArray<CNPRStation>* CNPRAppEngine::Stations()
	{
	return &iStationArray;
	}

const RPointerArray<CNPRStory>* CNPRAppEngine::Stories()
	{
	return &iStoryArray;
	}

void CNPRAppEngine::SearchStationsL(const TDesC& aField)
	{
	HBufC *uri = HBufC::NewLC(KNPRStationQuery().Length()
			+ aField.Length() 
			+ KNPRApiKey().Length()
			);
	TPtr uriPtr = uri->Des();
	uriPtr.Format(KNPRStationQuery,&aField, &KNPRApiKey());
	iHttp->SendRequestL(uriPtr);
	CleanupStack::PopAndDestroy(uri);
	iNPRCommand = EStationsCmd;
	}

void CNPRAppEngine::SearchNewsL(const TDesC& /*aField*/)
	{
	iHttp->SendRequestL(KNPRQuery());
	iNPRCommand = ENewsCmd;
	}

void CNPRAppEngine::ResponseStatusL(TInt /*aStatusCode*/, const TDesC& /*aStatusText*/)
	{
	DismissWaitingDialogL();
	}

void CNPRAppEngine::ResponseReceivedL(const TDesC8& aResponseBuffer)
	{
	switch(iNPRCommand)
		{
		case ENewsCmd:
			{
			iStoryArray.ResetAndDestroy();
			CNPRStoryXmlParser* newsParser = CNPRStoryXmlParser::NewLC(&iStoryArray);
			CParser* parser = CParser::NewLC(KXmlMimeType, *newsParser);
			parser->ParseL(aResponseBuffer);
			CleanupStack::PopAndDestroy(parser); 
			CleanupStack::PopAndDestroy(newsParser);
			iNPRAppUi.ActivateLocalViewL(TUid::Uid(ENPRStoryListBoxViewId));
			break;
			}
		case EStationsCmd:
			{
			DismissWaitingDialogL();
			iStationArray.ResetAndDestroy();
			CNPRStationXmlParser* stationParser = CNPRStationXmlParser::NewLC(&iStationArray);
			CParser* parser = CParser::NewLC(KXmlMimeType, *stationParser);
			parser->ParseL(aResponseBuffer);
			CleanupStack::PopAndDestroy(parser); 
			CleanupStack::PopAndDestroy(stationParser);
			iNPRAppUi.ActivateLocalViewL(TUid::Uid(ENPRStationListBoxViewId));
			break;
			}
		default:
			DismissWaitingDialogL();
			break;
		}
	}

void CNPRAppEngine::LaunchFileL(const TDesC& aFilename)
    {
    TDataType dataType = TDataType(KDataTypeRAM());
    // Open a file in a standalone handler application
    TRAPD(err,iDocHandler->OpenFileL(aFilename, dataType));
 
    TUid handlerUid; 
    err = iDocHandler->HandlerAppUid(handlerUid);
    if (!err)
        {
        RefreshDocumentFileL(handlerUid, aFilename);
        }
    }

/**
 * Refreshes the file opened in a standalone handler. Does nothing if the file
 * has not been already opened.
 */
void CNPRAppEngine::RefreshDocumentFileL(const TUid& aUid, const TDesC& aFileName)
    {
    TApaTaskList taskList(CEikonEnv::Static()->WsSession());
    TApaTask task = taskList.FindApp(aUid);
 
    // If the standalone handler is already running, then update the file
    if (task.Exists())
        {
        User::LeaveIfError(task.SwitchOpenFile(aFileName));
        }
    }

void CNPRAppEngine::ShowWaitingDialogL(const TDesC& aText)
	{
	DismissWaitingDialogL();
	iWaitDialog = new(ELeave)CAknWaitDialog((REINTERPRET_CAST(CEikDialog**,&iWaitDialog)), EFalse );
	iWaitDialog->SetTextL(aText); 
	iWaitDialog->ExecuteLD(R_SINGULAR_WAIT_NOTE);
	}

void CNPRAppEngine::DismissWaitingDialogL()
	{
	if(iWaitDialog)
		{			
		iWaitDialog->ProcessFinishedL();
		iWaitDialog=NULL;
		}
	}

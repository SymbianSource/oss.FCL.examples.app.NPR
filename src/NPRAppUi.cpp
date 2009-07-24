/*
 ============================================================================
 Name	: NPRAppUi.cpp
 Author	: John Kern
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symbian Foundation Ltd - initial contribution.
 - Symsource
 
 Contributors:
 - John Kern
 - Symsource
 
 Description : CNPRAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknmessagequerydialog.h>
#include <s32file.h>
#include <Xml/Parser.h> 
#include <NPR_0xEEB0E481.rsg>

#include "NPR_0xEEB0E481.hlp.hrh"
#include "NPR.hrh"
#include "NPR.pan"
#include "NPRApplication.h"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"
#include "NPRListBoxView.h"
#include "NPRStoryListBoxView.h"
#include "NPRStationListBoxView.h"
#include "NPRSearchStationListBoxView.h"
#include "NPRBrowserAknView.h"


_LIT( KFileName, "C:\\private\\EEB0E481\\NPR.txt" );
_LIT( KText, "Hello World!");

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CNPRAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CNPRAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);
	
	// Create a file to write the text to
	TInt err = CCoeEnv::Static()->FsSession().MkDirAll(KFileName);
	if ((KErrNone != err) && (KErrAlreadyExists != err))
		{
		Exit();
		}

	RFile file;
	err = file.Replace(CCoeEnv::Static()->FsSession(), KFileName, EFileWrite);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		Exit();
		}

	RFileWriteStream outputFileStream(file);
	CleanupClosePushL(outputFileStream);
	outputFileStream << KText;
	this->Document();
	CleanupStack::PopAndDestroy(2); // outputFileStream, file

	TRAP(err, this->iNPRAppEngine = CNPRAppEngine::NewL(*this));
	if(err != KErrNone)
		{
		Exit();
		}
	
	CNPRListBoxView* mainListBoxView = CNPRListBoxView::NewL();
	AddViewL(mainListBoxView);

	CNPRStoryListBoxView* storyListBoxView = CNPRStoryListBoxView::NewL();
	AddViewL(storyListBoxView);

	CNPRStationListBoxView* StationListBoxView = CNPRStationListBoxView::NewL();
	AddViewL(StationListBoxView);

	CNPRSearchStationListBoxView* searchStationListBoxView = CNPRSearchStationListBoxView::NewL();
	AddViewL(searchStationListBoxView);
	
	CBrowserAknView* browserView = CBrowserAknView::NewL(*iNPRAppEngine);
	AddViewL(browserView);

	ActivateLocalViewL(TUid::Uid(ENPRListBoxViewId));
	}
// -----------------------------------------------------------------------------
// CNPRAppUi::CNPRAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CNPRAppUi::CNPRAppUi()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CNPRAppUi::~CNPRAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CNPRAppUi::~CNPRAppUi()
	{
	delete iNPRAppEngine;
	}

// -----------------------------------------------------------------------------
// CNPRAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CNPRAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			{
			Exit();
			}
			break;
		case EAbout:
			{
			CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
			dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy(); //title
			HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy(); //msg
			dlg->RunLD();
			}
			break;
		default:
			Panic(ENPRUi);
			break;
		}
	}

CNPRAppEngine& CNPRAppUi::Engine()
	{
	return *iNPRAppEngine;
	}

// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CNPRAppUi::HandleStatusPaneSizeChange()
	{
	//iAppView->SetRect(ClientRect());
	}

CArrayFix<TCoeHelpContext>* CNPRAppUi::HelpContextL() const
	{
#warning "Please see comment about help and UID3..."
	// Note: Help will not work if the application uid3 is not in the
	// protected range.  The default uid3 range for projects created
	// from this template (0xE0000000 - 0xEFFFFFFF) are not in the protected range so that they
	// can be self signed and installed on the device during testing.
	// Once you get your official uid3 from Symbian Ltd. and find/replace
	// all occurrences of uid3 in your project, the context help will
	// work. Alternatively, a patch now exists for the versions of 
	// HTML help compiler in SDKs and can be found here along with an FAQ:
	// http://www3.symbian.com/faq.nsf/AllByDate/E9DF3257FD565A658025733900805EA2?OpenDocument
	CArrayFixFlat<TCoeHelpContext>* array = new (ELeave) CArrayFixFlat<
			TCoeHelpContext> (1);
	CleanupStack::PushL(array);
	array->AppendL(TCoeHelpContext(KUidNPRApp, KGeneral_Information));
	CleanupStack::Pop(array);
	return array;
	}

// End of File

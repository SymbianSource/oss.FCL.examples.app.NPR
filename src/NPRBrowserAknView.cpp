/*
 ===============================================================================
 Name	: NPRBrowserAknView.cpp
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
 
 Description : AknView for containing Nokia browser control to show NPR's Story 
 ================================================================================
 */

#include <aknviewappui.h>
#include <NPR_0xEEB0E481.rsg>
#include "NPR.hrh"
#include "NPRBrowserAknView.h"
#include "NPRBrowserContainer.h"
#include "NPRAppUi.h"


CBrowserAknView* CBrowserAknView::NewL(CNPRAppEngine& aEngine)
	{
	CBrowserAknView* p = new (ELeave) CBrowserAknView(aEngine);
	CleanupStack::PushL(p);
	p->ConstructL();
	CleanupStack::Pop(p);
	return p;
	}

CBrowserAknView::CBrowserAknView(CNPRAppEngine& aEngine)
	: iEngine(aEngine)
	{
	}

CBrowserAknView::~CBrowserAknView()
	{
	delete iContainer;
	}


void CBrowserAknView::ConstructL()
	{
	BaseConstructL(R_AKN_BROWSER_VIEW);
	iContainer = new (ELeave) CBrowserContainer();
	iContainer->ConstructL(ClientRect());
	iContainer->SetMopParent( this );
	}

TUid CBrowserAknView::Id() const
	{
	return TUid::Uid(ENPRBrowserViewId);
	}

void CBrowserAknView::HandleCommandL(TInt aCommand)
	{
	switch(aCommand)
		{
		case EListen:
			{
			iContainer->Listen();
			break;
			}
		case EAknSoftkeyBack:
			{
			static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->ActivateLocalViewL(TUid::Uid(ENPRStoryListBoxViewId));
			break;
			}
		default:
			{
			iContainer->ProcessCommandL(aCommand);
			break;
			}
		}
	}


void CBrowserAknView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,	const TDesC8& /*aCustomMessage*/)
	{
	AppUi()->AddToStackL(*this, iContainer);
	iContainer->MakeVisible(ETrue);
	iContainer->ActivateL();
	iContainer->ProcessCommandL(ELoadPage);
	}

void CBrowserAknView::DoDeactivate()
	{
	iContainer->MakeVisible(EFalse);
	AppUi()->RemoveFromViewStack(*this, iContainer);
	}

void CBrowserAknView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	}

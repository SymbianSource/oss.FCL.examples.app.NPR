/*
 ===============================================================================
 Name	: NPRBrowserConatiner.cpp
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
 
 Description :  Container for Nokia browser control to show NPR's Story 
 ================================================================================
 */

#include <avkon.hrh>
#include <aknwaitdialog.h>
#include <BrCtlInterface.h>
#include <aknmessagequerydialog.h>

#include "NPRBrowserContainer.h"
#include "npr.hrh"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"


_LIT(KStoryHtmlFile, "file:///c:\\data\\npr\\story.html");

void CBrowserContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
   
    iCommandBase = TBrCtlDefs::ECommandIdBase;
    iBrowserCaps = TBrCtlDefs::ECapabilityDisplayScrollBar | TBrCtlDefs::ECapabilityLoadHttpFw |
						TBrCtlDefs::ECapabilityGraphicalHistory | TBrCtlDefs::ECapabilityGraphicalPage;
    
    iBrowser = CreateBrowserControlL(this, Rect(), iBrowserCaps, iCommandBase, NULL, NULL, NULL, NULL, NULL);

    TRAP_IGNORE(iBrowser->SetBrowserSettingL(TBrCtlDefs::ESettingsAutoLoadImages,1));
    iBrowser->AddLoadEventObserverL(this);
    iBrowser->ActivateL();
    }

CBrowserContainer::~CBrowserContainer()
    {
    if (iBrowser)
    	iBrowser->RemoveLoadEventObserver(this);
    delete iBrowser;
    }

void CBrowserContainer::SizeChanged()
    {
    if(iBrowser)
        {
        iBrowser->SetRect(Rect());
        }
    }

TInt CBrowserContainer::CountComponentControls() const
    {
    if(iBrowser)
        return 1;
    return 0;
    }

CCoeControl* CBrowserContainer::ComponentControl(TInt aIndex) const
    {
    switch(aIndex)
        {
        case 0:
            return iBrowser; // Could be NULL
        default:
            return NULL;
        }
    }

void CBrowserContainer::Draw(const TRect& /*aRect*/) const
    {
	CWindowGc& gc=SystemGc(); // graphics context we draw to
	gc.Clear();
    }

void CBrowserContainer::HandleControlEventL(CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
    {
    }

TKeyResponse CBrowserContainer::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/)
    {
    return EKeyWasNotConsumed;
    }


void CBrowserContainer::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
   } 

void CBrowserContainer::ProcessCommandL(TInt aCommandId)
    {
    switch(aCommandId)
        {
        case ELoadPage:
        	if (iBrowser!=NULL)
        		iBrowser->LoadUrlL(KStoryHtmlFile());  
            break;
        default:
            if (aCommandId >= iCommandBase && aCommandId < iCommandBase + TBrCtlDefs::ECommandIdWMLBase && iBrowser)
                {
                iBrowser->HandleCommandL(aCommandId);
                }

            if (aCommandId >= iCommandBase + TBrCtlDefs::ECommandIdWMLBase && aCommandId < iCommandBase + TBrCtlDefs::ECommandIdRange && iBrowser)
                {
                iBrowser->HandleCommandL(aCommandId);
                }              
            break;      
        }
    }

TKeyResponse CBrowserContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if(iBrowser)
        {
        return iBrowser->OfferKeyEventL(aKeyEvent, aType);
        }
    return EKeyWasConsumed;
    }

void CBrowserContainer::DynInitMenuPaneL(TInt /*aResourceId*/, CEikMenuPane* /*aMenuPane*/)
    {
    }

void CBrowserContainer::HandleBrowserLoadEventL(TBrCtlDefs::TBrCtlLoadEvent aLoadEvent, TUint /*aSize*/, TUint16 /*aTransactionId*/)
	{	
	if(aLoadEvent == TBrCtlDefs::EEventLoadFinished)
		{
		iBrowser->DrawNow();
		}
	}


void CBrowserContainer::Listen()
	{
	static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->Engine().SendNPRCommandL(EPlayNewsStream, KNullDesC());
	}

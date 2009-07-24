/*
 ==========================================================================================
 Name	: NPRStationListBoxView.h
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
 
 Description :  AknView for wrapping the container to show the NPR's station list
 ==========================================================================================
 */

#include <barsread.h>
#include <akncontext.h>
#include <akntitle.h>
#include <NPR_0xEEB0E481.rsg>

#include "NPR.hrh"
#include "NPRStationListBoxView.h"
#include "NPRStationListBox.h"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CNPRStationListBoxView::CNPRStationListBoxView()
	{
	iNPRStationListBox = NULL;
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CNPRStationListBoxView::~CNPRStationListBoxView()
	{
	delete iNPRStationListBox;
	iNPRStationListBox = NULL;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CNPRStationListBoxView
 */
CNPRStationListBoxView* CNPRStationListBoxView::NewL()
	{
	CNPRStationListBoxView* self = CNPRStationListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CNPRStationListBoxView
 */
CNPRStationListBoxView* CNPRStationListBoxView::NewLC()
	{
	CNPRStationListBoxView* self = new ( ELeave ) CNPRStationListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}

/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CNPRStationListBoxView::ConstructL()
	{
	BaseConstructL( R_NPRSTATION_LIST_BOX_NPRSTATION_LIST_BOX_VIEW);
	}

/**
 * @return The UID for this view
 */
TUid CNPRStationListBoxView::Id() const
	{
	return TUid::Uid( ENPRStationListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CNPRStationListBoxView::HandleCommandL( TInt aCommand )
	{
	TBool commandHandled = EFalse;
	switch(aCommand)
		{// code to dispatch to the AknView's menu and CBA commands is generated here
		case EListen:
			{
			iNPRStationListBox->Listen();
			commandHandled = ETrue;
			break;
			}
		case EAknSoftkeyBack:
			{
			static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->ActivateLocalViewL(TUid::Uid(ENPRSearchStationListBoxViewId));
			commandHandled = ETrue;
			break;
			}
		default:
			break;
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CNPRStationListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	SetupStatusPaneL();
	if ( iNPRStationListBox == NULL )
		{
		iNPRStationListBox = CreateContainerL();
		iNPRStationListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iNPRStationListBox );
		} 
	}

/**
 */
void CNPRStationListBoxView::DoDeactivate()
	{
	CleanupStatusPane();
	if ( iNPRStationListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iNPRStationListBox );
		delete iNPRStationListBox;
		iNPRStationListBox = NULL;
		}
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CNPRStationListBoxView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	}

void CNPRStationListBoxView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_NPRSTATION_LIST_BOX_TITLE_RESOURCE);
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

void CNPRStationListBoxView::CleanupStatusPane()
	{
	}

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CNPRStationListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CNPRStationListBox
 */
CNPRStationListBox* CNPRStationListBoxView::CreateContainerL()
	{
	return CNPRStationListBox::NewL( ClientRect(), NULL, this );
	}

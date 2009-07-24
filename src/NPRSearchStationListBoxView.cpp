/*
 ===================================================================================================
 Name	: NPRSearchStationListBoxView.h
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
 
 Description : AknView for wrapping the container to show the NPR's station search options
 ===================================================================================================
 */

#include <barsread.h>
#include <aknlists.h>
#include <akncontext.h>
#include <akntitle.h>
#include <NPR_0xEEB0E481.rsg>

#include "NPR.hrh"
#include "NPRSearchStationListBoxView.h"
#include "NPRSearchStationListBox.h"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CNPRSearchStationListBoxView::CNPRSearchStationListBoxView()
	{
	iNPRSearchStationListBox = NULL;
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CNPRSearchStationListBoxView::~CNPRSearchStationListBoxView()
	{
	delete iNPRSearchStationListBox;
	iNPRSearchStationListBox = NULL;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CNPRSearchStationListBoxView
 */
CNPRSearchStationListBoxView* CNPRSearchStationListBoxView::NewL()
	{
	CNPRSearchStationListBoxView* self = CNPRSearchStationListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CNPRSearchStationListBoxView
 */
CNPRSearchStationListBoxView* CNPRSearchStationListBoxView::NewLC()
	{
	CNPRSearchStationListBoxView* self = new ( ELeave ) CNPRSearchStationListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CNPRSearchStationListBoxView::ConstructL()
	{
	BaseConstructL( R_NPRSEARCH_STATION_LIST_BOX_NPRSEARCH_STATION_LIST_BOX_VIEW );
	}

/**
 * @return The UID for this view
 */
TUid CNPRSearchStationListBoxView::Id() const
	{
	return TUid::Uid( ENPRSearchStationListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CNPRSearchStationListBoxView::HandleCommandL( TInt aCommand )
	{
	switch(aCommand)
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case ESelect:
			{
			iNPRSearchStationListBox->SendStationQueryL();
			break;
			}
		case EAknSoftkeyBack:
			{
			static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->ActivateLocalViewL(TUid::Uid(ENPRListBoxViewId));
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
void CNPRSearchStationListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	SetupStatusPaneL();
	if ( iNPRSearchStationListBox == NULL )
		{
		iNPRSearchStationListBox = CreateContainerL();
		iNPRSearchStationListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iNPRSearchStationListBox );
		} 
	}

/**
 */
void CNPRSearchStationListBoxView::DoDeactivate()
	{
	CleanupStatusPane();
	
	if ( iNPRSearchStationListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iNPRSearchStationListBox );
		delete iNPRSearchStationListBox;
		iNPRSearchStationListBox = NULL;
		}
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CNPRSearchStationListBoxView::HandleStatusPaneSizeChange()
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

void CNPRSearchStationListBoxView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_NPRSEARCH_STATION_LIST_BOX_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}		
	}

void CNPRSearchStationListBoxView::CleanupStatusPane()
	{
	}

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CNPRSearchStationListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CNPRSearchStationListBox
 */
CNPRSearchStationListBox* CNPRSearchStationListBoxView::CreateContainerL()
	{
	return CNPRSearchStationListBox::NewL( ClientRect(), NULL, this );
	}

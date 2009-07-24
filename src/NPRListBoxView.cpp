/*
 ============================================================================
 Name	: NPRListBoxView.cpp
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
 
 Description : AknView to wrap the Series60 container to show the NPR's main options
 ============================================================================
 */

#include <barsread.h>
#include <akncontext.h>
#include <akntitle.h>
#include <NPR_0xEEB0E481.rsg>

#include "NPR.hrh"
#include "NPRListBoxView.h"
#include "NPRListBox.h"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"


/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CNPRListBoxView
 */
CNPRListBoxView* CNPRListBoxView::NewL()
	{
	CNPRListBoxView* self = CNPRListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CNPRListBoxView
 */
CNPRListBoxView* CNPRListBoxView::NewLC()
	{
	CNPRListBoxView* self = new ( ELeave ) CNPRListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CNPRListBoxView::CNPRListBoxView()
	:iNPRListBox(NULL)
	{
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CNPRListBoxView::~CNPRListBoxView()
	{
	delete iNPRListBox;
	iNPRListBox = NULL;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CNPRListBoxView::ConstructL()
	{
	BaseConstructL( R_NPRLIST_BOX_NPRLIST_BOX_VIEW );
	}

/**
 * @return The UID for this view
 */
TUid CNPRListBoxView::Id() const
	{
	return TUid::Uid( ENPRListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CNPRListBoxView::HandleCommandL(TInt aCommand)
	{
	TBool commandHandled = EFalse;
	switch(aCommand)
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case ESelect:
			{
			commandHandled = ETrue;
			TInt index = iNPRListBox->CurrentItemIndex();
			switch(index)
				{
				case ENews:
					{
					iNPRListBox->SendNewsQueryL();
					break;
					}
				case EStations:
					{
					static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->ActivateLocalViewL(TUid::Uid(ENPRSearchStationListBoxViewId));
					break;
					}
				case EPrograms:
					break;
				default:
					break;
				}
			break;
			}
		default:
			break;
		}
	
		
	if (!commandHandled) 
		{
		if ( aCommand == EAknSoftkeyExit )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CNPRListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	SetupStatusPaneL();
					
	if ( iNPRListBox == NULL )
		{
		iNPRListBox = CreateContainerL();
		iNPRListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iNPRListBox );
		}
	}

/**
 */
void CNPRListBoxView::DoDeactivate()
	{
	CleanupStatusPane();
	
	if ( iNPRListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iNPRListBox );
		delete iNPRListBox;
		iNPRListBox = NULL;
		}
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CNPRListBoxView::HandleStatusPaneSizeChange()
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

void CNPRListBoxView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_NPRLIST_BOX_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}				
	}

void CNPRListBoxView::CleanupStatusPane()
	{
	}


/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CNPRListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CNPRListBox
 */
CNPRListBox* CNPRListBoxView::CreateContainerL()
	{
	return CNPRListBox::NewL( ClientRect(), NULL, this );
	}

/*
 ============================================================================
 Name	: NPRStationListBox.cpp
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
 
 Description : Container for Series60 double style list box to show the NPR's station list
 ============================================================================
 */

#include <barsread.h>
#include <aknlists.h>
#include <NPR_0xEEB0E481.rsg>

#include "NPRStationListBox.h"
#include "NPRStationListBoxView.h"
#include "NPR.hrh"
#include "NPRStation.h"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"

const TInt KFrequencyTab = 20;
/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CNPRStationListBox::CNPRStationListBox()
	{
	iListBox = NULL;
	iStationArray = static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->Engine().Stations();
	}
/** 
 * Destroy child controls.
 */
CNPRStationListBox::~CNPRStationListBox()
	{
	delete iListBox;
	iListBox = NULL;
	}
				
/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CNPRStationListBox
 */
CNPRStationListBox* CNPRStationListBox::NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CNPRStationListBox* self = CNPRStationListBox::NewLC( 
			aRect, 
			aParent, 
			aCommandObserver );
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CNPRStationListBox
 */
CNPRStationListBox* CNPRStationListBox::NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CNPRStationListBox* self = new ( ELeave ) CNPRStationListBox();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aParent, aCommandObserver );
	return self;
	}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CNPRStationListBox::ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	if ( aParent == NULL )
	    {
		CreateWindowL();
	    }
	else
	    {
	    SetContainerWindowL( *aParent );
	    }
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	InitializeControlsL();
	SetRect( aRect );
	ActivateL();
	}
			
/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CNPRStationListBox::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CNPRStationListBox::ComponentControl( TInt aIndex ) const
	{
	switch ( aIndex )
		{
	case EListBox:
		return iListBox;
		}
	return NULL;
	}
				
/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */				
void CNPRStationListBox::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	}
				
/**
 * Layout components as specified in the UI Designer
 */
void CNPRStationListBox::LayoutControls()
	{
	iListBox->SetExtent( TPoint( 0, 0 ), iListBox->MinimumSize() );
	}

void CNPRStationListBox::Listen()
	{
	static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->Engine().SendNPRCommandL(EPlayStationStream, KNullDesC());
	}

/**
 *	Handle key events.
 */				
TKeyResponse CNPRStationListBox::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		// Listbox takes all events even if it doesn't use them
		return EKeyWasNotConsumed;
		}
	
	if ( iFocusControl != NULL
		&& iFocusControl->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
	}
				
/**
 *	Initialize each control upon creation.
 */				
void CNPRStationListBox::InitializeControlsL()
	{
	iListBox = new ( ELeave ) CAknDoubleStyle2ListBox;
	iListBox->SetContainerWindowL( *this );
	TResourceReader reader;
	iEikonEnv->CreateResourceReaderLC( reader, R_NPRSTATION_LIST_BOX_LIST_BOX);
	iListBox->ConstructFromResourceL( reader );
	CleanupStack::PopAndDestroy(); // reader internal state
	// the listbox owns the items in the list and will free them
	iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iListBox->CreateScrollBarFrameL(ETrue);
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto);
	
	// setup the icon array so graphics-style boxes work
	SetupListBoxIconsL();
	
	// add list items
	for(TInt i=0; i<iStationArray->Count(); i++)
		{
		TInt nameLength = (*iStationArray)[i]->Name().Length();
		TBuf<64> namePlusFrequency((*iStationArray)[i]->Name());
		if((*iStationArray)[i]->Frequency().Length()!=0)
			{
			for(TInt j=0; j<KFrequencyTab-nameLength;j++)
				{
				namePlusFrequency.Append(_L(" "));				
				}
			namePlusFrequency.Append((*iStationArray)[i]->Frequency());		
			}
	    TBuf<128> listString;
		CreateListBoxItemL(listString, namePlusFrequency, (*iStationArray)[i]->MarketCity());
		AddListBoxItemL(iListBox, listString);
		}
	
	iListBox->SetFocus( ETrue );
	iFocusControl = iListBox;
	}

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CNPRStationListBox::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( ENPRStationListBoxViewId ) )->ClientRect() );
	}
				
/**
 *	Draw container contents.
 */				
void CNPRStationListBox::Draw( const TRect& aRect ) const
	{
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	}
				
/**
 *	Add a list box item to a list.
 */
void CNPRStationListBox::AddListBoxItemL( 
		CEikTextListBox* aListBox,
		const TDesC& aString )
	{
	CTextListBoxModel* model = aListBox->Model();
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	itemArray->AppendL( aString );
	aListBox->HandleItemAdditionL();
	}

/**
 * Get the array of selected item indices, with respect to the list model.
 * The array is sorted in ascending order.
 * The array should be destroyed with two calls to CleanupStack::PopAndDestroy(),
 * the first with no argument (referring to the internal resource) and the
 * second with the array pointer.
 * @return newly allocated array, which is left on the cleanup stack;
 *	or NULL for empty list. 
 */
RArray< TInt >* CNPRStationListBox::GetSelectedListBoxItemsLC( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return NULL;
		
	// get currently selected indices
	const CListBoxView::CSelectionIndexArray* selectionIndexes =
		aListBox->SelectionIndexes();
	TInt selectedIndexesCount = selectionIndexes->Count();
	if ( selectedIndexesCount == 0 )
		return NULL;
		
	// copy the indices and sort numerically
	RArray<TInt>* orderedSelectedIndices = 
		new (ELeave) RArray< TInt >( selectedIndexesCount );
	
	// push the allocated array
	CleanupStack::PushL( orderedSelectedIndices );
	
	// dispose the array resource
	CleanupClosePushL( *orderedSelectedIndices );
	
	// see if the search field is enabled
	CAknListBoxFilterItems* filter = model->Filter();
	if ( filter != NULL )
		{
		// when filtering enabled, translate indices back to underlying model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			{
			TInt filteredItem = ( *selectionIndexes ) [ idx ];
			TInt actualItem = filter->FilteredItemIndex ( filteredItem );
			orderedSelectedIndices->InsertInOrder( actualItem );
			}
		}
	else
		{
		// the selection indices refer directly to the model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			orderedSelectedIndices->InsertInOrder( ( *selectionIndexes ) [ idx ] );
		}	
		
	return orderedSelectedIndices;
	}

/**
 * Delete the selected item or items from the list box.
 */
void CNPRStationListBox::DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return;
	
	RArray< TInt >* orderedSelectedIndices = GetSelectedListBoxItemsLC( aListBox );		
	if ( !orderedSelectedIndices )
		return;
		
	// Delete selected items from bottom up so indices don't change on us
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	TInt currentItem = 0;
	
	for ( TInt idx = orderedSelectedIndices->Count(); idx-- > 0; ) 
		{
		currentItem = ( *orderedSelectedIndices )[ idx ];
		itemArray->Delete ( currentItem );
		}
	
	// dispose the array resources
	CleanupStack::PopAndDestroy();
	
	// dispose the array pointer
	CleanupStack::PopAndDestroy( orderedSelectedIndices );
	
	// refresh listbox's cursor now that items are deleted
	AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
		aListBox, currentItem, ETrue );
	}

/**
 *	Get the listbox.
 */
CAknDoubleStyle2ListBox* CNPRStationListBox::ListBox()
	{
	return iListBox;
	}

/**
 *	Create a list box item with the given column values.
 */
void CNPRStationListBox::CreateListBoxItemL( TDes& aBuffer, 
		const TDesC& aMainText,
		const TDesC& aSecondaryText )
	{
	_LIT ( KStringHeader, "\t%S\t%S" );
	
	aBuffer.Format( KStringHeader(), &aMainText, &aSecondaryText );
	} 
				
/**
 *	Add an item to the list by reading the text items from the array resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	
 */
void CNPRStationListBox::AddListBoxResourceArrayItemL( TInt aResourceId )
	{
	CDesCArray* array = iCoeEnv->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf<512> listString; 
	CreateListBoxItemL( listString, ( *array ) [ 0 ], ( *array ) [ 1 ] );
	AddListBoxItemL( iListBox, listString );
	CleanupStack::PopAndDestroy( array );
	} 
				
/**
 *	Set up the list's icon array.
 */
void CNPRStationListBox::SetupListBoxIconsL()
	{
	CArrayPtr< CGulIcon >* icons = NULL;		
	
	if(icons != NULL)
		{
		iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
		}
	}

/** 
 *	Handle commands relating to markable lists.
 */
TBool CNPRStationListBox::HandleMarkableListCommandL(TInt /*aCommand*/)
	{
	TBool result = EFalse;
	return result;
	}

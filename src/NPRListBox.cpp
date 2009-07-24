/*
 ===============================================================================================
 Name	: NPRListBox.cpp
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
 
 Description : Container for Series60 single large style list box to show the NPR's main options
 ===============================================================================================
 */

#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <NPR_0xEEB0E481.rsg>

#include "NPRListBox.h"
#include "NPRListBoxView.h"
#include "NPR.hrh"
#include "NPRAppUi.h"
#include "NPRAppEngine.h"

_LIT(KNPR_0xEEB0E481File, "\\resource\\apps\\NPR_0xEEB0E481.mif");
_LIT ( KStringHeader, "%d\t%S" );

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CNPRListBox::CNPRListBox()
	{
	iListBox = NULL;
	}

/** 
 * Destroy child controls.
 */
CNPRListBox::~CNPRListBox()
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
 * @return initialized instance of CNPRListBox
 */
CNPRListBox* CNPRListBox::NewL(const TRect& aRect,  const CCoeControl* aParent, MEikCommandObserver* aCommandObserver )
	{
	CNPRListBox* self = CNPRListBox::NewLC(aRect, aParent, aCommandObserver);
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
 * @return new instance of CNPRListBox
 */
CNPRListBox* CNPRListBox::NewLC(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
	{
	CNPRListBox* self = new (ELeave) CNPRListBox();
	CleanupStack::PushL(self);
	self->ConstructL(aRect, aParent, aCommandObserver);
	return self;
	}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CNPRListBox::ConstructL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
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
TInt CNPRListBox::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CNPRListBox::ComponentControl( TInt aIndex ) const
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
void CNPRListBox::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	}
				
/**
 * Layout components as specified in the UI Designer
 */
void CNPRListBox::LayoutControls()
	{
	iListBox->SetExtent( TPoint( 0, 0 ), iListBox->MinimumSize() );
	}

/**
 *	Handle key events.
 */				
TKeyResponse CNPRListBox::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		return EKeyWasNotConsumed;
		}

	if ( aKeyEvent.iCode == EKeyDevice3)
		{
		TInt index = CurrentItemIndex();
		switch(index)
			{
			case ENews:
				{
				SendNewsQueryL();
				break;
				}
			case EStations:
				{
				static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->ActivateLocalViewL(TUid::Uid(ENPRSearchStationListBoxViewId));
				break;
				}
			case EPrograms:
			case EPlaylist:
			case ESettings:
				break;
			default:
				break;
			}
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
void CNPRListBox::InitializeControlsL()
	{
	iListBox = new ( ELeave ) CAknSingleLargeStyleListBox;
	iListBox->SetContainerWindowL( *this );
	TResourceReader reader;
	iEikonEnv->CreateResourceReaderLC( reader, R_NPRLIST_BOX_LIST_BOX );
	iListBox->ConstructFromResourceL( reader );
	CleanupStack::PopAndDestroy(); // reader internal state
	
	// the listbox owns the items in the list and will free them
	iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
	
	// setup the icon array so graphics-style boxes work
	SetupListBoxIconsL();
	
	// add list items
	AddListBoxResourceArrayItemL( R_NPRLIST_BOX_LISTBOX_ITEM1,
			EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex );
	AddListBoxResourceArrayItemL( R_NPRLIST_BOX_LISTBOX_ITEM2,
			EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex );
	AddListBoxResourceArrayItemL( R_NPRLIST_BOX_LISTBOX_ITEM3,
			EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex );
	AddListBoxResourceArrayItemL( R_NPRLIST_BOX_LISTBOX_ITEM4,
			EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex );
	AddListBoxResourceArrayItemL( R_NPRLIST_BOX_LISTBOX_ITEM5,
			EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex );
	
	iListBox->SetFocus( ETrue );
	iFocusControl = iListBox;
	}

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CNPRListBox::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( ENPRListBoxViewId ) )->ClientRect() );
	}
				
/**
 *	Draw container contents.
 */				
void CNPRListBox::Draw(const TRect& aRect) const
	{
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	}
				
/**
 *	Add a list box item to a list.
 */
void CNPRListBox::AddListBoxItemL( 
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
RArray< TInt >* CNPRListBox::GetSelectedListBoxItemsLC( CEikTextListBox* aListBox )
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
void CNPRListBox::DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox )
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
CAknSingleLargeStyleListBox* CNPRListBox::ListBox()
	{
	return iListBox;
	}

/**
 *	Create a list box item with the given column values.
 */
void CNPRListBox::CreateListBoxItemL( TDes& aBuffer, 
		TInt aIconIndex,
		const TDesC& aMainText )
	{
	aBuffer.Format( KStringHeader(), aIconIndex, &aMainText );
	} 

/**
 *	Add an item to the list by reading the text items from the array resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	@param aIconIndex the index in the icon array, or -1
 */
void CNPRListBox::AddListBoxResourceArrayItemL( TInt aResourceId, TInt aIconIndex )
	{
	CDesCArray* array = iCoeEnv->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf<512> listString; 
	CreateListBoxItemL( listString, aIconIndex, ( *array ) [ 0 ] );
	AddListBoxItemL( iListBox, listString );
	CleanupStack::PopAndDestroy( array );
	} 
				
/**
 *	Set up the list's icon array.
 */
void CNPRListBox::SetupListBoxIconsL()
	{
	/*
	CArrayPtr< CGulIcon >* icons = NULL;		
	icons = new (ELeave) CAknIconArray( 1 );
	CleanupStack::PushL( icons );
	CGulIcon* icon;
	// for EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex
	icon = LoadAndScaleIconL(
			KNPR_0xEEB0E481File, EMbmNpr_0xeeb0e481Qgn_menu_npr, -1,
			NULL, EAspectRatioPreserved );
	CleanupStack::PushL( icon );
	icons->AppendL( icon );
	CleanupStack::Pop( icon );
	CleanupStack::Pop( icons );
	
	if ( icons != NULL )
		{
		iListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );
		}
	*/
	}

/** 
 *	Handle commands relating to markable lists.
 */
TBool CNPRListBox::HandleMarkableListCommandL(TInt /*aCommand*/)
	{
	return EFalse;
	}

/**
 *	This routine loads and scales a bitmap or icon.
 *
 *	@param aFileName the MBM or MIF filename
 *	@param aBitmapId the bitmap id
 *	@param aMaskId the mask id or -1 for none
 *	@param aSize the TSize for the icon, or NULL to use real size
 *	@param aScaleMode one of the EAspectRatio* enums when scaling
 *
 */
CGulIcon* CNPRListBox::LoadAndScaleIconL( 
		const TDesC& aFileName,
		TInt aBitmapId, 
		TInt aMaskId, 
		TSize* aSize, 
		TScaleMode aScaleMode )
	{
	CFbsBitmap* bitmap;
	CFbsBitmap* mask;
	AknIconUtils::CreateIconL( bitmap, mask, aFileName, aBitmapId, aMaskId );
	
	TSize size;
	if ( aSize == NULL )
		{
		// Use size from the image header.  In case of SVG,
		// we preserve the image data for a while longer, since ordinarily
		// it is disposed at the first GetContentDimensions() or SetSize() call.
		AknIconUtils::PreserveIconData( bitmap );
		AknIconUtils::GetContentDimensions( bitmap, size );
		}
	else
		{
		size = *aSize;
		}
	
	AknIconUtils::SetSize( bitmap, size, aScaleMode );
	AknIconUtils::SetSize( mask, size, aScaleMode );
	
	if ( aSize == NULL )
		{
		AknIconUtils::DestroyIconData( bitmap );
		}
	
	return CGulIcon::NewL( bitmap, mask );
	}

TInt CNPRListBox::CurrentItemIndex()
	{
	return iListBox->CurrentItemIndex();
	}

void CNPRListBox::SendNewsQueryL()
	{
	static_cast<CNPRAppUi*>(CEikonEnv::Static()->EikAppUi())->Engine().SendNPRCommandL(ENewsCmd, KNullDesC());
	}

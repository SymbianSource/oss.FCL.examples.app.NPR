/*
 ===================================================================================================
 Name	: NPRSearchStationListBox.h
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
 
 Description : Container for Series60 single style list box to show the NPR's station search options
 ===================================================================================================
 */

#ifndef __NPR_SEARCH_STATION_LISTBOX_H__
#define __NPR_SEARCH_STATION_LISTBOX_H__

#include <coecntrl.h>		
class MEikCommandObserver;		
class CAknSingleLargeStyleListBox;
class CEikTextListBox;

_LIT(KNPRZipQuery, "zip=%S");
_LIT(KNPRCurrentLocationZip, "94102");//San Francisco ZIP codes


/**
 * Container class for NPRSearchStationListBox
 * 
 * @class	CNPRSearchStationListBox NPRSearchStationListBox.h
 */
class CNPRSearchStationListBox : public CCoeControl
	{
public: 
	enum TControls
		{
		EListBox,
		ELastControl
		};
	
	enum TListBoxImages
		{
		EListBoxFirstUserImageIndex
		};
public:
	static CNPRSearchStationListBox* NewL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	static CNPRSearchStationListBox* NewLC(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	virtual ~CNPRSearchStationListBox();

public:
	TInt CurrentItemIndex();
	void SendStationQueryL();
	
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleResourceChange(TInt aType);

	static void AddListBoxItemL(CEikTextListBox* aListBox, const TDesC& aString);
	static RArray< TInt >* GetSelectedListBoxItemsLC(CEikTextListBox* aListBox);
	static void DeleteSelectedListBoxItemsL(CEikTextListBox* aListBox);
	CAknSingleStyleListBox* ListBox();
	static void CreateListBoxItemL(TDes& aBuffer, TInt aIconIndex, const TDesC& aMainText);
	void AddListBoxResourceArrayItemL(TInt aResourceId, TInt aIconIndex);
	void SetupListBoxIconsL();
	TBool HandleMarkableListCommandL(TInt aCommand);
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw(const TRect& aRect) const;

private:
	void InitializeControlsL();
	void LayoutControls();
	
private:
	// constructors
	CNPRSearchStationListBox();
	void ConstructL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);

private: 
	CAknSingleStyleListBox* iListBox;
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	};
				
#endif // __NPR_SEARCH_STATION_LISTBOX_H__

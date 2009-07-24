/*
 ============================================================================
 Name	: NPRStationListBox.h
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

#ifndef __NPR_STATION_LIST_BOX_H__
#define __NPR_STATION_LIST_BOX_H__

#include <coecntrl.h>

class MEikCommandObserver;		
class CAknDoubleStyle2ListBox;
class CEikTextListBox;
class CNPRStation;

/**
 * Container class for NPRStationListBox
 * 
 * @class	CNPRStationListBox NPRStationListBox.h
 */
class CNPRStationListBox : public CCoeControl
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
	static CNPRStationListBox* NewL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	static CNPRStationListBox* NewLC(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	virtual ~CNPRStationListBox();

public:
	void Listen();
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleResourceChange(TInt aType);
	static void AddListBoxItemL(CEikTextListBox* aListBox, const TDesC& aString);
	static RArray< TInt >* GetSelectedListBoxItemsLC( CEikTextListBox* aListBox);
	static void DeleteSelectedListBoxItemsL(CEikTextListBox* aListBox);
	CAknDoubleStyle2ListBox* ListBox();
	static void CreateListBoxItemL(TDes& aBuffer, const TDesC& aMainText, const TDesC& aSecondaryText);
	void AddListBoxResourceArrayItemL(TInt aResourceId);
	void SetupListBoxIconsL();
	TBool HandleMarkableListCommandL(TInt aCommand);

protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	void InitializeControlsL();
	void LayoutControls();
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
	// constructors
	CNPRStationListBox();
	void ConstructL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);

private: 
	CAknDoubleStyle2ListBox* 			iListBox;
	const RPointerArray<CNPRStation>* 	iStationArray;
	CCoeControl* 						iFocusControl;
	MEikCommandObserver* 				iCommandObserver;
	};
				
#endif // __NPR_STATION_LIST_BOX_H__

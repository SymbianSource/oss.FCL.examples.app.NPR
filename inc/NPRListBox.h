/*
 ===============================================================================================
 Name	: NPRListBox.h
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

#ifndef NPR_LIST_BOX_H
#define NPR_LIST_BOX_H

#include <coecntrl.h>		
#include <akniconutils.h>
#include <gulicon.h>

class MEikCommandObserver;		
class CAknSingleLargeStyleListBox;
class CEikTextListBox;


class CNPRListBox : public CCoeControl
	{
public: 
	enum TControls
		{
		EListBox,
		ELastControl
		};
	enum TListBoxImages
		{
		EListBoxNpr_0xeeb0e481Qgn_menu_nprIndex = 0,
		EListBoxFirstUserImageIndex
		};
public:
	static CNPRListBox* NewL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver );
	static CNPRListBox* NewLC(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver );
	virtual ~CNPRListBox();
	
public:
	void SendNewsQueryL();
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleResourceChange(TInt aType);
	
protected:
	// from base class CCoeControl
	void SizeChanged();

public:
	TInt CurrentItemIndex();
	static void AddListBoxItemL(CEikTextListBox* aListBox, const TDesC& aString);
	static RArray< TInt >* GetSelectedListBoxItemsLC(CEikTextListBox* aListBox);
	static void DeleteSelectedListBoxItemsL(CEikTextListBox* aListBox);
	CAknSingleLargeStyleListBox* ListBox();
	static void CreateListBoxItemL(TDes& aBuffer, TInt aIconIndex, const TDesC& aMainText);
	void AddListBoxResourceArrayItemL(TInt aResourceId, TInt aIconIndex);
	void SetupListBoxIconsL();
	static CGulIcon* LoadAndScaleIconL(const TDesC& aFileName, TInt aBitmapId, TInt aMaskId, TSize* aSize, TScaleMode aScaleMode );
	TBool HandleMarkableListCommandL( TInt aCommand );
	
private:
	void InitializeControlsL();
	void LayoutControls();

	// from base class CCoeControl
	void Draw(const TRect& aRect) const;
	
private:
	// constructors
	CNPRListBox();
	void ConstructL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	
private: 
	CCoeControl* 					iFocusControl;
	MEikCommandObserver* 			iCommandObserver;
	CAknSingleLargeStyleListBox* 	iListBox;
	};
				
#endif // NPR_LIST_BOX_H

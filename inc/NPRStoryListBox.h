/*
 ============================================================================
 Name	: NPRStoryListBox.h
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
 
 Description : Container for Series60 double style list box to show the NPR's story list
 ============================================================================
 */

#ifndef __NPR_STORY_LIST_BOX_H__
#define __NPR_STORY_LIST_BOX_H__

#include <coecntrl.h>
#include <gulicon.h>


class MEikCommandObserver;		
class CAknDoubleLargeStyleListBox;
class CEikTextListBox;
class CNPRStory;
class CNPRHtmlCreator;

/**
 * Container class for NPRStoryListBox
 * 
 * @class	CNPRStoryListBox NPRStoryListBox.h
 */
class CNPRStoryListBox : public CCoeControl
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
	static CNPRStoryListBox* NewL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	static CNPRStoryListBox* NewLC(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	virtual ~CNPRStoryListBox();

public:
	void ShowSelectedStoryL();
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleResourceChange(TInt aType);
	static void AddListBoxItemL(CEikTextListBox* aListBox, const TDesC& aString);
	static RArray< TInt >* GetSelectedListBoxItemsLC(CEikTextListBox* aListBox);
	static void DeleteSelectedListBoxItemsL(CEikTextListBox* aListBox);
	CAknDoubleLargeStyleListBox* ListBox();
	static void CreateListBoxItemL(TDes& aBuffer, TInt aIconIndex, const TDesC& aMainText, const TDesC& aSecondaryText);
	void AddListBoxResourceArrayItemL(TInt aResourceId, TInt aIconIndex);
	void SetupListBoxIconsL();
	TBool HandleMarkableListCommandL(TInt aCommand);
	static CGulIcon* LoadAndScaleIconL(const TDesC& aFileName, TInt aBitmapId, TInt aMaskId, TSize* aSize, TScaleMode aScaleMode);
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	TInt CurrentItemIndex();
	void InitializeControlsL();
	void LayoutControls();

	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
	// constructors
	CNPRStoryListBox();
	void ConstructL(const TRect& aRect, const CCoeControl* aParent, MEikCommandObserver* aCommandObserver);
	
private: 
	CCoeControl* 					iFocusControl;
	MEikCommandObserver*			iCommandObserver;
	CAknDoubleLargeStyleListBox* 	iListBox;
	const RPointerArray<CNPRStory>* iStoryArray;
	CNPRHtmlCreator* 				iHtmlCreator;
	};
				
#endif // __NPR_STORY_LIST_BOX_H__

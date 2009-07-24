/*
 ===============================================================================
 Name	: NPRBrowserConatiner.h
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

#ifndef __NPR_BROWSER_H__
#define __NPR_BROWSER_H__

#include <coecntrl.h>
#include "BrCtlInterface.h"

class CBrowserContainer : public CCoeControl, 
                          public MCoeControlObserver,
                          public MBrCtlLoadEventObserver,
    					  public MEikCommandObserver
    {
public:
	void ConstructL(const TRect& aRect);
	~CBrowserContainer();

public: 
	inline CBrCtlInterface* Browser() const {return iBrowser;}
	void ProcessCommandL(TInt aCommandId);
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
	//From MBrCtlLoadEventObserver
	void HandleBrowserLoadEventL(TBrCtlDefs::TBrCtlLoadEvent aLoadEvent, TUint aSize, TUint16 aTransactionId);
	void Listen();
	
private:
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	void HandleResourceChange(TInt aType);
   
private:  	
	CBrCtlInterface* iBrowser;
	TUint			 iBrowserCaps;
	TInt			 iCommandBase;
	};

#endif // __NPR_BROWSER_H__




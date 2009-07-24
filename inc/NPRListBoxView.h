/*
 ============================================================================
 Name	: NPRListBoxView.h
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
 
 Description : AknView for wrapping the container to show the NPR's main options
 ============================================================================
 */

#ifndef __NPR_LIST_BOX_VIEW_H__
#define __NPR_LIST_BOX_VIEW_H__

#include <aknview.h>

class CNPRListBox;
class CNPRAppEngine;

/**
 * Avkon view class for NPRListBoxView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CNPRListBoxView NPRListBoxView.h
 */						
			
class CNPRListBoxView : public CAknView
	{

public:
	static CNPRListBoxView* NewL();
	static CNPRListBoxView* NewLC();      
	virtual ~CNPRListBoxView();

public:						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	CNPRListBox* CreateContainerL();
protected:
	// from base class CAknView
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
private:
	CNPRListBoxView();
	void ConstructL();

private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
private:
	CNPRListBox*	iNPRListBox;
	};

#endif // __NPR_LIST_BOX_VIEW_H__

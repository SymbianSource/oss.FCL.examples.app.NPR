/*
 ==========================================================================================
 Name	: NPRStationListBoxView.h
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
 
 Description :  AknView for wrapping the container to show the NPR's station list
 ==========================================================================================
 */

#ifndef __NPR_STATION_LIST_BOX_VIEW_H__
#define __NPR_STATION_LIST_BOX_VIEW_H__

#include <aknview.h>
class CNPRStationListBox;

/**
 * Avkon view class for NPRStationListBoxView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CNPRStationListBoxView NPRStationListBoxView.h
 */						
			
class CNPRStationListBoxView : public CAknView
	{
public:
	static CNPRStationListBoxView* NewL();
	static CNPRStationListBoxView* NewLC();        
	virtual ~CNPRStationListBoxView();

public:	
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	CNPRStationListBox* CreateContainerL();
	
protected:
	// from base class CAknView
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();

private:
	// constructors
	CNPRStationListBoxView();
	void ConstructL();

private:
	CNPRStationListBox* iNPRStationListBox;
	};

#endif // __NPR_STATION_LIST_BOX_VIEW_H__

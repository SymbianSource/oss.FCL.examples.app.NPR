/*
 ===============================================================================
 Name	: NPRBrowserAknView.h
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
 
 Description : AknView for containing Nokia browser control to show NPR's Story 
 ================================================================================
 */

#ifndef __NPR_BROWSER_AKN_VIEW_H__
#define __NPR_BROWSER_AKN_VIEW_H__

#include <aknview.h>

class CBrowserContainer;
class CNPRAppEngine;

class CBrowserAknView : public CAknView
	{
public:
	static CBrowserAknView* NewL(CNPRAppEngine& aEngine);
 	virtual ~CBrowserAknView();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
		
protected:
	void DoActivateL(const TVwsViewId& aPrevViewId,	TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();
	void HandleStatusPaneSizeChange();

private:
	CBrowserAknView(CNPRAppEngine& aEngine);
	void ConstructL();

private:	
	CBrowserContainer*	iContainer;
	CNPRAppEngine&		iEngine;
	};

#endif //  __NPR_BROWSER_AKN_VIEW_H__


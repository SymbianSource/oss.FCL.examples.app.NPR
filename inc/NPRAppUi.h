/*
 ============================================================================
 Name	: NPRAppUi.h
 Author	: John Kern
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symbian Foundation Ltd - initial contribution.
 - Symsource
 
 Contributors:
 - John Kern
 - Symsource
 
 Description : Declares UI class for application.
 ============================================================================
 */

/*
 ============================================================================
 Name		: NPRAppUi.h
 Author	  : John Kern
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 Symbian Foundation Ltd - initial contribution.
 
 Contributors: John Kern
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __NPR_APP_UI_h__
#define __NPR_APP_UI_h__

// INCLUDES
#include <aknviewappui.h>

// FORWARD DECLARATIONS
class CNPRAppView;
class CNPRAppEngine;

// CLASS DECLARATION
/**
 * CNPRAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CNPRAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CNPRAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CNPRAppUi();

	/**
	 * ~CNPRAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CNPRAppUi();

	CNPRAppEngine& Engine();
	void ResponseStatusL(TInt aStatusCode, const TDesC& aStatusText);
	void ResponseReceivedL(const TDesC8& aResponseBuffer) ;
	
private:
	// Functions from base classes

	/**
	 * From CEikAppUi, HandleCommandL.
	 * Takes care of command handling.
	 * @param aCommand Command to be handled.
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 *  HandleStatusPaneSizeChange.
	 *  Called by the framework when the application status pane
	 *  size is changed.
	 */
	void HandleStatusPaneSizeChange();

	/**
	 *  From CCoeAppUi, HelpContextL.
	 *  Provides help context for the application.
	 *  size is changed.
	 */
	CArrayFix<TCoeHelpContext>* HelpContextL() const;

private:
	// Data
	CNPRAppEngine* iNPRAppEngine;
	};

#endif // __NPR_APP_UI_h__
// End of File

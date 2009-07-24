/*
 ============================================================================
 Name	: NPRApplication.h
 Author	: John Kern
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symbian Foundation Ltd - initial contribution.
 
 Contributors:
 - John Kern
 
 Description : Declares main application class.
 ============================================================================
 */


#ifndef __NPR_APPLICATION_H__
#define __NPR_APPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "NPR.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidNPRApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CNPRApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CNPRApplication is the application part of the
 * AVKON application framework for the NPR example application.
 */
class CNPRApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidNPRApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CNPRDocument document object. The returned
	 * pointer in not owned by the CNPRApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __NPR_APPLICATION_H__
// End of File

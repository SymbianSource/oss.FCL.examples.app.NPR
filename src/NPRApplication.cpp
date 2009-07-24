/*
 ============================================================================
 Name	: NPRApplication.cpp
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
 
 Description : This file contains panic codes.
 ============================================================================
 */


// INCLUDE FILES
#include "NPR.hrh"
#include "NPRDocument.h"
#include "NPRApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CNPRApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CNPRApplication::CreateDocumentL()
	{
	// Create an NPR document, and return a pointer to it
	return CNPRDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CNPRApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CNPRApplication::AppDllUid() const
	{
	// Return the UID for the NPR application
	return KUidNPRApp;
	}

// End of File

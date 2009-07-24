/*
 ============================================================================
 Name	: NPRDocument.cpp
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
 - Symsource
 
 Description : Declares document class for application.
 ============================================================================
 */

// INCLUDE FILES
#include "NPRAppUi.h"
#include "NPRDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CNPRDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CNPRDocument* CNPRDocument::NewL(CEikApplication& aApp)
	{
	CNPRDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CNPRDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CNPRDocument* CNPRDocument::NewLC(CEikApplication& aApp)
	{
	CNPRDocument* self = new (ELeave) CNPRDocument(aApp);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CNPRDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CNPRDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CNPRDocument::CNPRDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CNPRDocument::CNPRDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CNPRDocument::~CNPRDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CNPRDocument::~CNPRDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CNPRDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CNPRDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CNPRAppUi;
	}

// End of File

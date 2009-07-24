/*
 ============================================================================
 Name	: NPRDocument.h
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
 

#ifndef __NPR_DOCUMENT_H__
#define __NPR_DOCUMENT_H__

// INCLUDES
#include <akndoc.h>

#include "NPRStory.h"

// FORWARD DECLARATIONS
class CNPRAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CNPRDocument application class.
 * An instance of class CNPRDocument is the Document part of the
 * AVKON application framework for the NPR example application.
 */
class CNPRDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CNPRDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CNPRDocument.
	 */
	static CNPRDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CNPRDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CNPRDocument.
	 */
	static CNPRDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CNPRDocument
	 * Virtual Destructor.
	 */
	virtual ~CNPRDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CNPRAppUi object and return a pointer to it.
	 * The object returned is owned by the Uikon framework.
	 * @return Pointer to created instance of AppUi.
	 */
	CEikAppUi* CreateAppUiL();
		
private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CNPRDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CNPRDocument(CEikApplication& aApp);
	};

#endif // __NPR_DOCUMENT_H__
// End of File

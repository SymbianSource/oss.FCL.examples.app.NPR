/*
 ============================================================================
 Name	: NPRHtmlCreator.h
 Author	: Symsource
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symbian Foundation Ltd - initial contribution.
 
 Contributors:
 - Symsource
 
 Description : HTML composer
 ============================================================================
 */

#ifndef _NPR_HTML_CREATOR_H
#define _NPR_HTML_CREATOR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

// CLASS DECLARATION
class CNPRStory;

/**
 *  CNPRHtmlCreator
 * 
 */
class CNPRHtmlCreator : public CBase
	{
public:
	/**
	 * Two-phased constructor.
	 */
	static CNPRHtmlCreator* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CNPRHtmlCreator* NewLC();
	
	/**
	 * Destructor.
	 */
	~CNPRHtmlCreator();

public:
	/**
	 * Create the HTML file in the c:/data/npr directory
	 */
	void CreateHtmlFileL(CNPRStory* aStory);

private:
	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
private:
	//Member variables
	RFs iFs;
	static TInt iCurrentImage;
	};

#endif // _NPR_HTML_CREATOR_H

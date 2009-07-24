/*
 ============================================================================
 Name	: NPRStory.cpp
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
 
 Description : NPR's xml story parser
 ============================================================================
 */

#include "NPRStory.h"

const int KUrlLength = 256; 

CNPRStory* CNPRStory::NewLC()
	{
	CNPRStory* self = new (ELeave) CNPRStory();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CNPRStory* CNPRStory::NewL()
	{
	CNPRStory* self = CNPRStory::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

CNPRStory::CNPRStory()
:iTitle(NULL),iTeaser(NULL),iMp3Url(NULL)
	{
	// No implementation required
	}

CNPRStory::~CNPRStory()
	{
	iTitle.Close();
	iTeaser.Close();
	iText.Close();
	iMp3Url.Close(); 
	iThumbnailUrl.Close();
	}

void CNPRStory::ConstructL()
	{
	}

void CNPRStory::SetTitleL(const TDesC8& aTitle)
	{
	HBufC* temp = HBufC::NewLC(aTitle.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aTitle);

	if(iTitle.MaxLength() < temp->Length())
		{
		iTitle.ReAlloc(temp->Length());
		}
	iTitle.Copy(temp->Des());
	CleanupStack::PopAndDestroy();
	}

void CNPRStory::SetTeaserL(const TDesC8& aTeaser)
	{
	HBufC* temp = HBufC::NewLC(aTeaser.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aTeaser);

	// append it 
	const TInt newLength = iTeaser.Length() + temp->Length();
	if(iTeaser.MaxLength() < newLength)
		{
		iTeaser.ReAlloc(newLength);
		}
	iTeaser.Append(temp->Des());
	CleanupStack::PopAndDestroy();
	}

void CNPRStory::SetTextL(const TDesC8& aText)
	{
	HBufC* temp = HBufC::NewLC(aText.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aText);
	// append it 

	const TInt newLength = iText.Length() + temp->Length();
	if(iText.MaxLength() < newLength)
		{
		iText.ReAlloc(newLength);
		}
	iText.Append(temp->Des());

	CleanupStack::PopAndDestroy();
	}

// The XML parser will call this multiple times to construct the mp3url. 
void CNPRStory::SetMp3UrlL(const TDesC8& aMp3Url)
	{
	HBufC* temp = HBufC::NewLC(aMp3Url.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aMp3Url);
	
	// append it 
	const TInt newLength = iMp3Url.Length() + temp->Length();
	if(iMp3Url.MaxLength() < newLength)
		{
		iMp3Url.ReAlloc(newLength);
		}
	iMp3Url.Append(temp->Des());
	CleanupStack::PopAndDestroy();
	}

void CNPRStory::SetThumbnailUrlL(const TDesC8& aThumbUrl)
	{
	HBufC* temp = HBufC::NewLC(aThumbUrl.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aThumbUrl);

	if(iThumbnailUrl.MaxLength() < temp->Length())
		{
		iThumbnailUrl.ReAlloc(temp->Length());
		}
	iThumbnailUrl.Copy(temp->Des());
	CleanupStack::PopAndDestroy();
	}
//End of file

/*
 ============================================================================
 Name	: NPRHtmlCreator.cpp
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

#include "NPRHtmlCreator.h"
#include "NPRStory.h"

//Constants
_LIT(KPath, "c:\\data\\npr\\story.html");
_LIT8(KHtml, "<html><body><h2>%S</h2><img vspace=\"2\" hspace=\"10\" src=\"file:///c:/data/npr/pic%d.jpg\" width=\"125\" height=\"125\" align=\"left\"/>%S</body></html>");

TInt CNPRHtmlCreator::iCurrentImage=6;

CNPRHtmlCreator* CNPRHtmlCreator::NewLC()
	{
	CNPRHtmlCreator* self = new (ELeave) CNPRHtmlCreator();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CNPRHtmlCreator* CNPRHtmlCreator::NewL()
	{
	CNPRHtmlCreator* self = CNPRHtmlCreator::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

CNPRHtmlCreator::~CNPRHtmlCreator()
	{
	iFs.Close();
	}


void CNPRHtmlCreator::ConstructL()
	{
	User::LeaveIfError(iFs.Connect());
	}

void CNPRHtmlCreator::CreateHtmlFileL(CNPRStory* aStory)
	{
	TInt err = iFs.MkDirAll(KPath);
	if ((KErrNone != err) && (KErrAlreadyExists != err))
		{
		User::Leave(err);
		}
	
	//Open the file, replacing if necessary
	RFile file;
	User::LeaveIfError(file.Replace(iFs,KPath,EFileWrite));
	CleanupClosePushL(file);
	
	HBufC8* title=HBufC8::NewLC(aStory->Title().Length());
	title->Des().Copy(aStory->Title());
	
	TInt textLength=aStory->Text().Length();
	HBufC8* text;
	if (textLength!=0)
		{
		text=HBufC8::NewLC(textLength);
		text->Des().Copy(aStory->Text());
		}
	else
		{
		//There was no story, so just display the teaser
		textLength=aStory->Teaser().Length();
		text=HBufC8::NewLC(textLength);
		text->Des().Copy(aStory->Teaser());
		}
	
	HBufC8 *buf = HBufC8::NewLC(KHtml().Length()
			+ title->Length() 
			+ textLength +1
			);
	
	--iCurrentImage;
	if (iCurrentImage<=0)
		{
		iCurrentImage=6;
		}
	
	TPtr8 ptr = buf->Des();
	ptr.Format(KHtml,title, iCurrentImage,text);

	//Write into the file
	User::LeaveIfError(file.Write(ptr));
	CleanupStack::PopAndDestroy(3); //buf,teaser,title
	CleanupStack::PopAndDestroy(&file);
	}

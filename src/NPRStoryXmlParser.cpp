/*
 ============================================================================
 Name	: NPRStoryXmlParser.cpp
 Author	: John Kern
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 - Symbian Foundation Ltd - initial contribution
 - Symsource
 
 Contributors:
 - John Kern
 - Symsource
 
 Description : Story xml parser
 ============================================================================
 */

#include "NPRDocument.h"
#include "NPRStoryXmlParser.h"
#include "NPRStory.h"

CNPRStoryXmlParser* CNPRStoryXmlParser::NewLC(RPointerArray<CNPRStory>* aStoryArray)
	{
	CNPRStoryXmlParser* self = new (ELeave) CNPRStoryXmlParser(aStoryArray);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CNPRStoryXmlParser* CNPRStoryXmlParser::NewL(RPointerArray<CNPRStory>* aStoryArray)
	{
	CNPRStoryXmlParser* self = CNPRStoryXmlParser::NewLC(aStoryArray);
	CleanupStack::Pop(); // self;
	return self;
	}

CNPRStoryXmlParser::CNPRStoryXmlParser(RPointerArray<CNPRStory>* aStoryArray)
:iStoryArray(aStoryArray)
	{
	// No implementation required
	}

CNPRStoryXmlParser::~CNPRStoryXmlParser()
	{
	delete iTagName;
	}


void CNPRStoryXmlParser::ConstructL()
	{
	iState = ENPRNewsStateIdle;
	}

void CNPRStoryXmlParser::OnStartDocumentL(
		const RDocumentParameters& /* aDocParam */, 
		TInt aErrorCode )
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStoryXmlParser::OnEndDocumentL(TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

HBufC* CNPRStoryXmlParser::Copy8To16LC(const TDesC8& aDes)
        {
        HBufC* buf16 = HBufC::NewLC(aDes.Length());
        buf16->Des().Copy(aDes);
        return buf16;
        }

void CNPRStoryXmlParser::OnStartElementL(
		const RTagInfo& aElement, 
		const RAttributeArray& aAttributes, 
		TInt  aErrorCode	)
	{
	User::LeaveIfError(aErrorCode);
	const TDesC8& tagName = aElement.LocalName().DesC();
	if (tagName.CompareF(_L8("story"))==0)
		{
		iStory = ETrue;
		if(iTagName)
			{
			delete iTagName;
			}
		iState = ENPRNewsStateStory;
		iCurrentStory = CNPRStory::NewL(); 
		// find the story Id attribute
		TInt count = aAttributes.Count();
		for (TInt i = 0 ; i < count ; i++)
			{
			 const RAttribute& attribute = aAttributes[i];
			 const RTagInfo& nameInfo = attribute.Attribute();

			 const TDesC8& localName8 = nameInfo.LocalName().DesC();
			 const TDesC8& value8 = attribute.Value().DesC();

			 HBufC* localName16 = Copy8To16LC(localName8);
			 HBufC* value16 = Copy8To16LC(value8);
			 if (localName16->CompareF(_L("id")) == 0 )
				 {
				 TLex lex(value16->Des());
				 TInt v = 0;
				 lex.Val(v);
				 iCurrentStory->SetStoryId( v );
				 }
			 CleanupStack::PopAndDestroy(2); // value16 and localName16
			}
		}
	else if(iStory)
		{
		if(!iTagName && ((iState != ENPRNewsStateText) || (iState != ENPRNewsStateParagraph)))
			{
			iTagName = tagName.AllocL();
			}
		
		if (iTagName->CompareF(_L8("title"))==0 && iState == ENPRNewsStateStory)
			{
			iState = ENPRNewsStateTitle;
			}
		else if (iTagName->CompareF(_L8("teaser"))==0 && iState == ENPRNewsStateStory)
			{
			iState = ENPRNewsStateTeaser;
			}
		else if (iTagName->CompareF(_L8("thumbnail"))==0 && iState == ENPRNewsStateStory)
			{
			iState = ENPRNewsStateThumbnail;
			}
		else if (iTagName->CompareF(_L8("text"))== 0 && iState == ENPRNewsStateStory)
			{
			iState = ENPRNewsStateText;
			}	
		else if (tagName.CompareF(_L8("paragraph"))== 0 && iTagName->CompareF(_L8("text"))==0)
			{
			iState = ENPRNewsStateParagraph;
			}
		else
			{
			iState = ENPRNewsStateIdle;
			}
		}
	}

void CNPRStoryXmlParser::OnEndElementL(const RTagInfo& aElement, TInt aErrorCode )
	{
	User::LeaveIfError(aErrorCode);
	const TDesC8& tagName = aElement.LocalName().DesC();
	
	TBool result = EFalse;
	
	if (tagName.CompareF(_L8("story"))== 0 && iState == ENPRNewsStateStory)
		{
		iStory = EFalse;
		iState = ENPRNewsStateIdle;
		iStoryArray->AppendL(iCurrentStory);
		iCurrentStory = NULL;
		} 
	else if(iTagName)
		{//TO DO we can have a switch here
		if (iTagName->CompareF(tagName)== 0 && iState == ENPRNewsStateTitle)
			{ 
			result = ETrue;
			}
		else if (iTagName->CompareF(tagName)== 0 && iState == ENPRNewsStateTeaser)
			{
			result = ETrue;
			}	
		else if (iTagName->CompareF(tagName)== 0 && iState == ENPRNewsStateThumbnail)
			{
			result = ETrue;
			}	
		else if (iTagName->CompareF(tagName)== 0 && iState == ENPRNewsStateText)
			{
			result = ETrue;
			}	
		else if (tagName.CompareF(_L8("paragraph"))== 0 && iTagName->CompareF(_L8("text"))==0)
			{
			iState = ENPRNewsStateText;
			}	
		else if (iTagName->CompareF(tagName)== 0 && iState == ENPRNewsStateIdle)
			{
			result = ETrue;
			}
		}
	
	if(result)
		{
		if(iTagName)
			{
			delete iTagName;
			iTagName = NULL;
			}
		iState = ENPRNewsStateStory;
		}
	}

void CNPRStoryXmlParser::OnContentL(const TDesC8&  aBytes, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	
	switch(iState)
		{
		case ENPRNewsStateTitle:
			{
			iCurrentStory->SetTitleL(aBytes);
			break;
			}
		case ENPRNewsStateTeaser:
			{
			iCurrentStory->SetTeaserL(aBytes);
			break; 
			}
		case ENPRNewsStateParagraph:
			{
			iCurrentStory->SetTextL(aBytes);
			break;
			}
		default:
			iState = iState; // for debugging. 
			break;
		}
	}

void CNPRStoryXmlParser::OnStartPrefixMappingL(
		const RString& /* aPrefix */, 
		const RString& /* aUri */, 
		TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStoryXmlParser::OnEndPrefixMappingL(const RString& /* aPrefix */, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStoryXmlParser::OnIgnorableWhiteSpaceL(const TDesC8& /* aBytes */, TInt /* aErrorCode*/)
	{
	}

void CNPRStoryXmlParser::OnSkippedEntityL(const RString& /* aName */, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStoryXmlParser::OnProcessingInstructionL(
		const TDesC8& /* aTarget */ , 
		const TDesC8& /* aData */ , 
		TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStoryXmlParser::OnError(TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

TAny* CNPRStoryXmlParser::GetExtendedInterface(const TInt32 /* aUid */) 
	{
	return NULL;
	}

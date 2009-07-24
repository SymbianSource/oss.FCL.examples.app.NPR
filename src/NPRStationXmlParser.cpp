/*
 ============================================================================
 Name	: NPRStationXmlParser.cpp
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
 
 Description : Station xml parser
 ============================================================================
 */

#include "NPRDocument.h"
#include "NPRStationXmlParser.h"
#include "NPRStation.h"

CNPRStationXmlParser* CNPRStationXmlParser::NewLC(RPointerArray<CNPRStation>* aStationArray)
	{
	CNPRStationXmlParser* self = new (ELeave) CNPRStationXmlParser(aStationArray);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CNPRStationXmlParser* CNPRStationXmlParser::NewL(RPointerArray<CNPRStation>* aStationArray)
	{
	CNPRStationXmlParser* self = CNPRStationXmlParser::NewLC(aStationArray);
	CleanupStack::Pop(); // self;
	return self;
	}

CNPRStationXmlParser::CNPRStationXmlParser(RPointerArray<CNPRStation>* aStationArray)
:iStationArray(aStationArray)
	{
	// No implementation required
	}

CNPRStationXmlParser::~CNPRStationXmlParser()
	{
	}

void CNPRStationXmlParser::ConstructL()
	{
	iState = ENPRStationStateIdle;
	}

void CNPRStationXmlParser::OnStartDocumentL(const RDocumentParameters& /* aDocParam */, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStationXmlParser::OnEndDocumentL(TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

HBufC* CNPRStationXmlParser::Copy8To16LC(const TDesC8& aDes)
        {
        HBufC* buf16 = HBufC::NewLC(aDes.Length());
        buf16->Des().Copy(aDes);
        return buf16;
        }

void CNPRStationXmlParser::OnStartElementL(
		const RTagInfo& aElement, 
		const RAttributeArray& aAttributes, 
		TInt  aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	const TDesC8& tagName = aElement.LocalName().DesC();
	if (tagName.CompareF(_L8("station"))==0)
		{
		iState = ENPRStationStateStation;
		iCurrentStation = CNPRStation::NewL(); 
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
				 iCurrentStation->SetStationId( v );
				 }
			 CleanupStack::PopAndDestroy(2); // value16 and localName16
			}
		}
	else if (tagName.CompareF(_L8("name"))==0 && iState == ENPRStationStateStation)
			{
			iState = ENPRStationStateName;
			}
	else if (tagName.CompareF(_L8("frequency"))==0 && iState == ENPRStationStateNameEnd)
			{
			iState = ENPRStationStateFrequency;
			}
	else if (tagName.CompareF(_L8("marketCity"))==0 && iState == ENPRStationStateFrequencyEnd)
			{
			iState = ENPRStationStateMarketCity;
			}
	}

void CNPRStationXmlParser::OnEndElementL(const RTagInfo& aElement, TInt aErrorCode )
	{
	User::LeaveIfError(aErrorCode);
	const TDesC8& tagName = aElement.LocalName().DesC();
	if (tagName.CompareF(_L8("station"))== 0 && iState == ENPRStationStateMarketCityEnd) 
		{
		iState = ENPRStationStateIdle; 
		iStationArray->AppendL(iCurrentStation);
		iCurrentStation = NULL;
		} 
	else if (tagName.CompareF(_L8("name"))== 0 && iState == ENPRStationStateName)
		{ 
		iState = ENPRStationStateNameEnd;
		} 	
	else if (tagName.CompareF(_L8("frequency"))== 0 && iState == ENPRStationStateFrequency)
		{
		iState = ENPRStationStateFrequencyEnd;
		}	
	else if (tagName.CompareF(_L8("marketCity"))== 0 && iState == ENPRStationStateMarketCity)
		{
		iState = ENPRStationStateMarketCityEnd;
		}
	}

void CNPRStationXmlParser::OnContentL(const TDesC8&  aBytes, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	
	switch(iState)
		{
		case ENPRStationStateName:
			{
			iCurrentStation->SetNameL(aBytes);
			break;
			}
		case ENPRStationStateFrequency:
			{
			iCurrentStation->SetFrequencyL(aBytes);
			break; 
			}
		case ENPRStationStateMarketCity:
			{
			iCurrentStation->SetMarketCityL(aBytes);
			break;
			}
		
		default:
			iState = iState; // for debugging. 
			break;
		}
	}

void CNPRStationXmlParser::OnStartPrefixMappingL(
		const RString& /* aPrefix */, 
		const RString& /* aUri */, 
		TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStationXmlParser::OnEndPrefixMappingL(const RString& /* aPrefix */, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStationXmlParser::OnIgnorableWhiteSpaceL(const TDesC8& /* aBytes */, TInt /* aErrorCode*/ )
	{
	}

void CNPRStationXmlParser::OnSkippedEntityL(const RString& /* aName */, TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStationXmlParser::OnProcessingInstructionL(
		const TDesC8& /* aTarget */ , 
		const TDesC8& /* aData */ , 
		TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

void CNPRStationXmlParser::OnError(TInt aErrorCode)
	{
	User::LeaveIfError(aErrorCode);
	}

TAny* CNPRStationXmlParser::GetExtendedInterface(const TInt32 /* aUid */ ) 
	{
	return NULL;
	}

/*
 ============================================================================
 Name	: NPRStationXmlParser.h
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

#ifndef __NPR_STATION_XML_PARSER_H__
#define __NPR_STATION_XML_PARSER_H__

// INCLUDES
#include <Xml/ContentHandler.h>

#include "NPRStation.h"

using namespace Xml;
// CLASS DECLARATION

/**
 *  CNPRStationXmlParser
 * The SAX parser will use this handler and associated enums to create story objects.  
 */

// used by SAX parser. States of the XML response from NPR server. 
enum TNPRStationParserState
		{
        ENPRStationStateIdle = 0,
        ENPRStationStateStation,
        ENPRStationStateStationEnd,
        ENPRStationStateName,
        ENPRStationStateNameEnd,
        ENPRStationStateFrequency,
        ENPRStationStateFrequencyEnd,
        ENPRStationStateMarketCity,
        ENPRStationStateMarketCityEnd
		};

class CNPRStationXmlParser : public CBase, public MContentHandler
	{
public:
	static CNPRStationXmlParser* NewL(RPointerArray<CNPRStation>* aStationArray);
	static CNPRStationXmlParser* NewLC(RPointerArray<CNPRStation>* aStationArray);
	~CNPRStationXmlParser();

public:
	void OnStartDocumentL(const RDocumentParameters& aDocParam, TInt aErrorCode); 
	void OnEndDocumentL(TInt aErrorCode); 
	void OnStartElementL(const RTagInfo& aElement, const RAttributeArray& aAttributes, TInt aErrorCode);
	void OnEndElementL(const RTagInfo& aElement, TInt aErrorCode);
	void OnContentL(const TDesC8& aBytes, TInt aErrorCode);
	void OnStartPrefixMappingL(const RString& aPrefix, const RString& aUri, TInt aErrorCode);
	void OnEndPrefixMappingL(const RString& aPrefix, TInt aErrorCode);
	void OnIgnorableWhiteSpaceL(const TDesC8& aBytes, TInt aErrorCode);
	void OnSkippedEntityL(const RString& aName, TInt aErrorCode);
	void OnProcessingInstructionL(const TDesC8& aTarget, const TDesC8& aData, TInt aErrorCode);
	void OnError(TInt aErrorCode);
	TAny* GetExtendedInterface(const TInt32 aUid);

private:
	HBufC* Copy8To16LC(const TDesC8& aDes);
	
private:
	CNPRStationXmlParser(RPointerArray<CNPRStation>* aStationArray);
	void ConstructL();

private:
	CNPRStation 				*iCurrentStation; 
	TNPRStationParserState		iState;
	RPointerArray<CNPRStation>* iStationArray; //it doesn't take ownership, do not delete
	};

#endif // __NPR_STATION_XML_PARSER_H__

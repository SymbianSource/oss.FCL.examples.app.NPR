/*
 ============================================================================
 Name	: NPRStoryXmlParser.h
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

#ifndef __NPR_STORY_XML_PARSER_H__
#define __NPR_STORY_XML_PARSER_H__

// INCLUDES
#include <Xml/ContentHandler.h>
#include <Xml/Parser.h>

#include "NPRStory.h"

using namespace Xml;

/**
 *  CNPRStoryXmlParser
 * The SAX parser will use this handler and associated enums to create story objects.  
 */

// used by SAX parser. States of the XML response from NPR server. 
enum TNPRNewsState
		{
		ENPRNewsStateIdle = 0,
        ENPRNewsStateStory,
        ENPRNewsStateTitle,
        ENPRNewsStateTeaser,
        ENPRNewsStateThumbnail,
        ENPRNewsStateMedium,
        ENPRNewsStateText,
        ENPRNewsStateParagraph,
        ENPRNewsStateDate,
        ENPRNewsStateAudio,
        ENPRNewsStateAudioMp3,
        ENPRNewsStateAudioReal,
        ENPRNewsStateAudioWM,
		};

class CNPRStoryXmlParser : public CBase, public MContentHandler
	{
public:
	static CNPRStoryXmlParser* NewL(RPointerArray<CNPRStory>* aStoryArray);
	static CNPRStoryXmlParser* NewLC(RPointerArray<CNPRStory>* aStoryArray);
	~CNPRStoryXmlParser();

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
	TAny* GetExtendedInterface(const TInt32 aUid) ;
	
private:
	// Constructors and destructor
	HBufC* Copy8To16LC(const TDesC8& aDes);
	
private:
	CNPRStoryXmlParser(RPointerArray<CNPRStory>* aStoryArray);
	void ConstructL();
	
private:
	CNPRStory*					iCurrentStory; 
	TNPRNewsState 				iState;
	RPointerArray<CNPRStory>* 	iStoryArray; //it doesn't take ownership, do not delete
	HBufC8* 					iTagName;
	TBool 						iStory;
	};

#endif // __NPR_STORY_XML_PARSER_H__

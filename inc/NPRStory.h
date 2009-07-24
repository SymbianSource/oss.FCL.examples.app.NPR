/*
 ============================================================================
 Name	: NPRStory.h
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

#ifndef __NPR_STORY_H__
#define __NPR_STORY_H__

// INCLUDES
#include <e32base.h>

/**
 *  CNPRStory
 * 
 */
class CNPRStory : public CBase
	{
public:
	static CNPRStory* NewL();
	static CNPRStory* NewLC();
	~CNPRStory();

public:	
	void SetStoryId(TInt aStoryId) {iStoryId = aStoryId;}
	inline TInt StoryId() {return iStoryId;} 

	void SetTitleL(const TDesC8& aTitle);
	inline const TDesC& Title() {return iTitle;};
	
	void SetTeaserL(const TDesC8& aTeaser);
	inline const TDesC& Teaser() {return iTeaser;};

	void SetTextL(const TDesC8& aText);
	inline const TDesC& Text() {return iText;};	
	
	void SetMp3UrlL(const TDesC8& aMp3Url);
	inline const TDesC& Mp3Url() {return iMp3Url;};
	
	void SetThumbnailUrlL(const TDesC8& aThumbUrl);
	inline const TDesC& ThumbnailUrl() {return iThumbnailUrl;};
	
private:
	//Constructors
	CNPRStory();
	void ConstructL();

private:
	TInt iStoryId; 
	RBuf iTitle;
	RBuf iTeaser;
	RBuf iText;
	RBuf iMp3Url; 
	RBuf iThumbnailUrl;
	};

#endif // __NPR_STORY_H__

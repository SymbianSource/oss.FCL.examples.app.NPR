/*
 ============================================================================
 Name	: NPRStation.h
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
 
 Description : Class to wrap all the Station fields 
 ============================================================================
 */

#ifndef __NPR_STATION_H__
#define __NPR_STATION_H__

// INCLUDES
#include <e32std.h>
#include <e32base.h>


// CLASS DECLARATION

/**
 *  CNPRStation
 * 
 */
class CNPRStation : public CBase
	{
public:
	/**
	 * Two-phased constructor.
	 */
	static CNPRStation* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CNPRStation* NewLC();
	
	/**
	 * Destructor.
	 */
	~CNPRStation();

public:	
	inline void SetStationId(TInt aId) {iStationId = aId;};
	inline TInt StationId() {return iStationId;};
	
	void SetNameL(const TDesC8& aName);
	inline const TDesC& Name() {return iName;};

	void SetFrequencyL(const TDesC8& aFrequency);
	inline const TDesC& Frequency() {return iFrequency;};

	void SetMarketCityL(const TDesC8& aMarketCity);
	inline const TDesC& MarketCity() {return iMarketCity;};
		
private:
	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
private:
	TInt	iStationId;
	RBuf	iName;
	RBuf	iFrequency;
	RBuf	iMarketCity; 
	};

#endif // __NPR_STATION_H__

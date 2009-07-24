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

#include "NPRStation.h"


CNPRStation* CNPRStation::NewLC()
	{
	CNPRStation* self = new (ELeave) CNPRStation();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CNPRStation* CNPRStation::NewL()
	{
	CNPRStation* self = CNPRStation::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

CNPRStation::~CNPRStation()
	{
	iName.Close();
	iFrequency.Close();
	iMarketCity.Close();
	}

void CNPRStation::ConstructL()
	{
	}

void CNPRStation::SetNameL(const TDesC8& aName)
	{
	HBufC* temp = HBufC::NewLC(aName.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aName);

	if(iName.MaxLength() < temp->Length())
		{
		iName.ReAlloc(temp->Length());
		}
	iName.Copy(temp->Des());
	CleanupStack::PopAndDestroy();
	}

void CNPRStation::SetFrequencyL(const TDesC8& aFrequency)
	{
	HBufC* temp = HBufC::NewLC(aFrequency.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aFrequency);

	if(iFrequency.MaxLength() < temp->Length())
		{
		iFrequency.ReAlloc(temp->Length());
		}
	iFrequency.Copy(temp->Des());
	CleanupStack::PopAndDestroy();
	}

void CNPRStation::SetMarketCityL(const TDesC8& aMarketCity)
	{
	HBufC* temp = HBufC::NewLC(aMarketCity.Length());
	// copy from 8 to 16 bit descriptor. 
	temp->Des().Copy(aMarketCity);

	if(iMarketCity.MaxLength() < temp->Length())
		{
		iMarketCity.ReAlloc(temp->Length());
		}
	iMarketCity.Copy(temp->Des());
	CleanupStack::PopAndDestroy();
	}



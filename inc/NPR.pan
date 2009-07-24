/*
 ============================================================================
 Name	: NPR.pan
 Author	: John Kern
 
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 Symbian Foundation Ltd - initial contribution.
 
 Contributors: John Kern
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __NPR_PAN__
#define __NPR_PAN__

/** NPR application panic codes */
enum TNPRPanics
	{
	ENPRUi = 1
	// add further panics here
	};

inline void Panic(TNPRPanics aReason)
	{
	_LIT(applicationName, "NPR");
	User::Panic(applicationName, aReason);
	}

#endif // __NPR_PAN__

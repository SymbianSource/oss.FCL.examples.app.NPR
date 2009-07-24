/*
 ============================================================================
 Name		: NPR.cpp
 Author	  : John Kern
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 Symbian Foundation Ltd - initial contribution.
 
 Contributors: John Kern
Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "NPRApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CNPRApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}


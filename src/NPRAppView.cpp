/*
 ============================================================================
 Name		: NPRAppView.cpp
 Author	  : John Kern
 Copyright (c) 2009 Symbian Foundation Ltd
 This component and the accompanying materials are made available
 under the terms of the License "Eclipse Public License v1.0"
 which accompanies this distribution, and is available
 at the URL "http://www.eclipse.org/legal/epl-v10.html".

 Initial Contributors:
 Symbian Foundation Ltd - initial contribution.
 
 Contributors: John Kern
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "NPRAppView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CNPRAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CNPRAppView* CNPRAppView::NewL(const TRect& aRect)
	{
	CNPRAppView* self = CNPRAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CNPRAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CNPRAppView* CNPRAppView::NewLC(const TRect& aRect)
	{
	CNPRAppView* self = new (ELeave) CNPRAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CNPRAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CNPRAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect(aRect);

	// Activate the window, which makes it ready to be drawn
	ActivateL();
	}

// -----------------------------------------------------------------------------
// CNPRAppView::CNPRAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CNPRAppView::CNPRAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CNPRAppView::~CNPRAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CNPRAppView::~CNPRAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CNPRAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CNPRAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.Clear(drawRect);

	}

// -----------------------------------------------------------------------------
// CNPRAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CNPRAppView::SizeChanged()
	{
	DrawNow();
	}

// -----------------------------------------------------------------------------
// CNPRAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CNPRAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{

	// Call base class HandlePointerEventL()
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}

// End of File

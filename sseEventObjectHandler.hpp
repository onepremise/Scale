//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Object Event Handler
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#ifndef __SSEEVENTOBJHANDLE__
#define __SSEEVENTOBJHANDLE__

#include "sseInclude.hpp"
#include "sseEventMappings.hpp"

class sseEventObjectHandler
{
public:
	sseEventObjectHandler();
	~sseEventObjectHandler();

	void AcceptEvents();
	void DeclineEvents();

	virtual String getName() = 0;
	virtual void setName(String strName) = 0;

public:
	virtual void HandleKeyPressEvents(SDL_Scancode *pKeyEvent) {return;}
	virtual void HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent) {return;}
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion) {return;}
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton) {return;}

protected:
	sseEventMappings *m_pEventMappings;
	sseEventMappings m_EmptyMap;
};

#endif

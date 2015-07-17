//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Event Handler Queue
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#ifndef __SSEEVENTHANDLER__
#define __SSEEVENTHANDLER__

#include "sseInclude.hpp"
#include "sseEventMappings.hpp"
#include "sseEventObjectHandler.hpp"
#include "SDL_events.h"

class sseEngine;
class sseDisplayManager;

typedef deque<sseEventObjectHandler *> objEventHandlerQueue;
typedef deque<sseEventObjectHandler *>::iterator objEHQIter;

class sseEventHandler
{
public:
	sseEventHandler(sseEngine *pEngine);

    static void AddObjectToQueue(sseEventObjectHandler *pOEH);
	static void RemoveObjectFromQueue(sseEventObjectHandler *pOEH);
	static sseEventMappings *GetEventMappings() { return &m_EventMappings; } 

public:
	void HandleEvents();

protected:
	void printHelp();

	virtual void HandleKeyPressEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	void objHandleKeyPressEvents(SDL_Scancode *pKeyEvent);
	void objHandleKeyReleaseEvents(SDL_Scancode *pKeyEvent);
	void objHandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	void objHandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	static sseEventMappings m_EventMappings;

private:
	void AssignCurMouseCoordinates(SDL_MouseMotionEvent *pMotion);
	void AssignLastMouseCoordinates(SDL_MouseMotionEvent *pMotion);

	void ProcessEvents(SDL_Event &sdlEvent);

	void cycleHandling();

private:
	static objEventHandlerQueue m_objEHQueue;
	static objEventHandlerQueue m_objInactiveEHQueue;

	sseEngine         *m_pEngine;
	sseDisplayManager *m_pDisplay;

	static float m_fCurrentX;
	static float m_fCurrentY;
	static float m_fLastX;
	static float m_fLastY;

	bool m_bHasFocus;
};

#endif

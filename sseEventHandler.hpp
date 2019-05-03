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
	void Initialize();
	void HandleEvents();
    void GetCursorPos(double & xpos, double & ypos);

protected:
	void printHelp();

	virtual void HandleKeyPressEvents(int key);
	virtual void HandleKeyReleaseEvents(int key);
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	void objHandleKeyPressEvents(int key);
	void objHandleKeyReleaseEvents(int key);
	void objHandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	void objHandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	static sseEventMappings m_EventMappings;

private:
	void AssignCurMouseCoordinates(SDL_MouseMotionEvent *pMotion);
	void AssignLastMouseCoordinates(SDL_MouseMotionEvent *pMotion);

	void ProcessEvents();

	void cycleHandling();

private:
    static int eventTable[GLFW_KEY_LAST] = {0};
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

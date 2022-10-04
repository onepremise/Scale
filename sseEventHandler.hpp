//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Event Handler Queue
//
// Notes:
//
//    Y+
//    |
//    |__ X+
//   /
//  Z+ 
//
// License:
//
// Licensed under the Apache License, Version 2.0 
// (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of 
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in 
// writing, software distributed under the License is 
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing 
// permissions and limitations under the License.
//
//=========================================================
#ifndef __SSEEVENTHANDLER__
#define __SSEEVENTHANDLER__

#include <SDL2/SDL.h>

#include "sseInclude.hpp"
#include "sseEventMappings.hpp"
#include "sseEventObjectHandler.hpp"

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

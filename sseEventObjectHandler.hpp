//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Object Event Handler
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

//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Debris Field
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
#pragma once

#include "sseObject.hpp"
#include "sseDebris.h"

class sseDebrisField : public sseObject
{
public:
	sseDebrisField(void);

	void LoadExplosion();
	void LoadFragments(String strFilename);

	virtual void HandleKeyPressEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	void setColor(int R, int G, int B);

protected:
	virtual void Load(sseTexture *pTextureLoader);

	void ProcessRow(String strRow);
	void ProcessField(int iIndex, String StrFld, sseDebris &debris);
	void ProcessObject(int i,bool bPause);

private:
	String m_strDelimiter;
	bool m_bStart;
	float color[3];
};


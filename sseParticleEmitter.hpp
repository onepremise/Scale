//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Particle Emmitter
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
#pragma once
#include "sseObject.hpp"

class sseParticleEmitter : public sseObject
{
public:
	sseParticleEmitter(void);
	virtual ~sseParticleEmitter(void);

	void LoadExplosion();

    virtual void HandleKeyPressEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

protected:
	virtual void Load(sseTexture *pTextureLoader);
	virtual void affineTransform();

private:
	dMatrix44 m_camRotate;
};

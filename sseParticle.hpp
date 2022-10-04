//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Particles
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

class sseParticle :
	public sseObject
{
public:
	sseParticle(void);
	virtual ~sseParticle(void);

	void SetSize(float size);
	float GetSize();

	void SetLife(float length);
	float GetLife();

	void SetColor(int R, int G, int B);

	bool isAlive() {return m_life>0.0;};

	virtual void Destroy();

protected:
	virtual void Load(sseTexture *pTextureLoader);
	virtual void processPhysics();
	virtual void affineTransform();
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);

private:
	dMatrix44 m_camRotate;
	int m_texture_id;
	float m_size;
	float m_life; // Life span of particle in seconds
	float m_color[3];
};
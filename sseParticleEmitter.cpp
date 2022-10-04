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
#include "sseParticleEmitter.hpp"
#include "sseParticle.hpp"
#include "sseTexture.h"
#include "sseCamera.hpp"
#include "sseCommand.hpp"

#define MAX_PARTICLES        150

sseParticleEmitter::sseParticleEmitter(void) : sseObject()
{
	stringstream sstm;
	sstm << "ParticleEmitter-" << getID();
	setName(sstm.str());
	//m_materialDefault.setMode(MAT_UPDATE_FRONT);
	//m_materialDefault.setShine(100.0);
}

sseParticleEmitter::~sseParticleEmitter(void)
{

}

void sseParticleEmitter::Load(sseTexture *pTextureLoader)
{
	LoadExplosion();
}

void sseParticleEmitter::LoadExplosion()
{
	for(int i = 0; i < MAX_PARTICLES; ++i)
    {
		sseParticle *particle=new sseParticle();

		particle->SetEnabled(false);
		particle->SetLife(RAND(1.0f, 2.0f));
		//particle->SetLife(20.0);
		particle->SetSize(1.0f);
		particle->SetColor(215, 115, 40);
		particle->SetXVelocity(RAND(-0.8f, 0.8));
		particle->SetYVelocity(RAND(-0.8f, 0.8));
		particle->SetZVelocity(RAND(-0.8f, 0.8f));
		particle->SetRotationalVel(0.0, 0.0, RAND(-1.0f, 1.0f));

		AddNode(particle, false, false);
	}
}

void sseParticleEmitter::affineTransform() 
{
	sseCamera *c=m_command->GetActiveCamera();

	dMatrix44 camMatrix=*c->GetViewTransformation();
	dMatrix transpose=camMatrix.Transpose();

	dQuaternion qRotX(vRight,m_Pitch);
	dQuaternion qRotY(vUp,m_Yaw);
	dQuaternion qRotZ(vLookAt,m_Roll);

	m_objectMatrix=(qRotX*qRotY*qRotZ).Get4x4Matrix();

	transpose[3]=m_vPos;
	transpose[0][3]=0;
	transpose[1][3]=0;
	transpose[2][3]=0;
	transpose[3][3]=1;
	
	//TRST
	m_objectMatrix*=transpose;
}


void sseParticleEmitter::HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion)
{

}

void sseParticleEmitter::HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton)
{

}

void sseParticleEmitter::HandleKeyPressEvents(SDL_Scancode *pKeyEvent)
{

}

void sseParticleEmitter::HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent)
{

}

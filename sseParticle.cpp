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
#include "sseParticle.hpp"
#include "sseTexture.h"
#include "sseCamera.hpp"
#include "sseCommand.hpp"

sseParticle::sseParticle(void) : sseObject()
{
	stringstream sstm;
	sstm << "Particle-" << getID();
	setName(sstm.str());
	//m_materialDefault.setMode(MAT_UPDATE_FRONT);
	//m_materialDefault.setShine(100.0);
	m_size=5;
}

sseParticle::~sseParticle(void)
{

}

void sseParticle::SetSize(float size)
{
	m_size=size;
}

float sseParticle::GetSize()
{
	return m_size;
}

void sseParticle::SetLife(float length)
{
	m_life=length;
}

float sseParticle::GetLife()
{
	return m_life;
}

void sseParticle::SetColor(int R, int G, int B)
{
	m_color[0]=R;
	m_color[1]=G;
	m_color[2]=B;
}

void sseParticle::Load(sseTexture *pTextureLoader)
{
 	m_texture_id=pTextureLoader->LoadWrap("Data\\entities\\img\\particle\\particle.bmp", -1, GL_RGB);
}

void sseParticle::Destroy() 
{
	if (!m_destroy)
	{
		m_destroy=true;
	}
}

void sseParticle::processPhysics()
{
	if (!m_destroy) {
		double dt = m_pClock->GetElapsedTime();

		m_life -= dt;

		m_destroy=!isAlive();

		m_Pitch+=m_rotationalVelX*dt;
		m_Roll+=m_rotationalVelZ*dt;
		m_Yaw+=m_rotationalVelY*dt;

		m_vPos[0]+=(m_velocity[0]/m_fTime)*dt;
		m_vPos[1]+=(m_velocity[1]/m_fTime)*dt;
		m_vPos[2]+=(m_velocity[2]/m_fTime)*dt;
	}
}

void sseParticle::affineTransform() 
{
	dQuaternion qRotZ(vLookAt,m_Roll);

	m_objectMatrix=qRotZ.Get4x4Matrix();

	m_objectMatrix[3]=m_vPos;
	m_objectMatrix[0][3]=0;
	m_objectMatrix[1][3]=0;
	m_objectMatrix[2][3]=0;
	m_objectMatrix[3][3]=1;
}

void sseParticle::PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PreProcess(pRenderer, pTextureLoader);

	if (!m_destroy) {
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR, GL_ONE);
	}
}

void sseParticle::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	if (!m_destroy) { 
		//gluSphere(m_quadTexture,m_radius,1000,1000);// Draw the Planet
		float halfSize = m_size * 0.5f;

		glColor4ub(m_color[0], m_color[1], m_color[2], 1);

		pTextureLoader->Bind(m_texture_id);
			
		// Draw the particle
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-halfSize, halfSize, 0.0f); // Top left vertex
			
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-halfSize, -halfSize, 0.0f); // Bottom left vertex
			
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(halfSize, -halfSize, 0.0f); // Bottom right vertex
			
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(halfSize, halfSize, 0.0f); // Top right vertex
		glEnd();
	}
}

void sseParticle::PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PostProcess(pRenderer, pTextureLoader);

	if (!m_destroy) {
		glDepthMask(true);
		glDisable(GL_BLEND);
	}
}

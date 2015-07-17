#include "ssePlanet.hpp"
#include "sseTexture.h"

ssePlanet::ssePlanet(void) : sseObject()
{
	stringstream sstm;
	sstm << "Planet-" << getID();
	setName(sstm.str());
	m_materialDefault.setMode(MAT_UPDATE_FRONT);
	m_materialDefault.setShine(100.0);
	m_radius=3;
	m_PitchAdjust=deg_to_rad(100);
}

ssePlanet::~ssePlanet(void)
{
}

void ssePlanet::SetRadius(double radius)
{
	m_radius = radius;
}

double ssePlanet::GetRadius()
{
	return m_radius;
}

void ssePlanet::Load(sseTexture *pTextureLoader)
{
 	m_texture_id=pTextureLoader->LoadWrap(GetTexturePath(), -1, GL_RGB);
}

void ssePlanet::Destroy() 
{
	if (!m_destroy)
	{
		m_destroy=true;
	}
}

void ssePlanet::PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PreProcess(pRenderer, pTextureLoader);

	if (!m_destroy) {
		pTextureLoader->Bind(m_texture_id);
		m_quadTexture = gluNewQuadric();
		gluQuadricTexture(m_quadTexture,GL_TRUE);
	}
}

void ssePlanet::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	if (!m_destroy) {
		gluSphere(m_quadTexture,m_radius,1000,1000);// Draw the Planet
	}
}

void ssePlanet::PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PostProcess(pRenderer, pTextureLoader);
	gluDeleteQuadric(m_quadTexture);
}

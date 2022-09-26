#include "sseSun.h"
#include "sseTexture.h"

sseSun::sseSun(void) : sseObject()
{
	stringstream sstm;
	sstm << "Sun-" << getID();
	setName(sstm.str());

	sseColor sAC(100.0f, 100.0f, 100.0f);
	sseColor sSC(0.0,0.0,0.0);
	sseColor sDC(0.8f,0.8f,0.8f);

	m_materialDefault.setAmbientColor(sAC);
	m_materialDefault.setSpecularColor(sSC);
	m_materialDefault.setDiffuseColor(sDC);
	m_materialDefault.setMode(MAT_UPDATE_FRONT);

	m_lightPos[0]= 0.0f;
	m_lightPos[1] = 0.0f;
	m_lightPos[2] = 0.0f;
	m_lightPos[3] = 1.0f;

	m_light_ambient[0]= 0.0f;
	m_light_ambient[1] = 0.0f;
	m_light_ambient[2] = 0.0f;
	m_light_ambient[3] = 1.0f;

	m_light_diffuse[0]= 1.0f;
	m_light_diffuse[1] = 1.0f;
	m_light_diffuse[2] = 1.0f;
	m_light_diffuse[3] = 1.0f;

	m_light_specular[0]= 1.0f;
	m_light_specular[1] = 1.0f;
	m_light_specular[2] = 1.0f;
	m_light_specular[3] = 1.0f;

	m_radius = 695000;
}

sseSun::~sseSun(void)
{
}

double sseSun::GetRadius()
{
	return m_radius;
}

void sseSun::SetRadius(double radius)
{
	m_radius = radius;
}

void sseSun::Load(sseTexture *pTextureLoader)
{
	texture_id=pTextureLoader->LoadWrap("Data/entities/img/sun.png", -1, GL_RGB);
}

void sseSun::PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PreProcess(pRenderer, pTextureLoader);

	if (!m_destroy) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, m_light_ambient);   
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, m_light_diffuse);   
		glLightfv(GL_LIGHT0, GL_SPECULAR, m_light_specular);

		pTextureLoader->Bind(texture_id);

		m_quadTexture = gluNewQuadric();

		gluQuadricTexture(m_quadTexture,GL_TRUE);
	}
}

void sseSun::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	if (!m_destroy) {
		this->getPosition().GetGLArray(m_lightPos);

		//m_lightPos[1] += 40.0f;
		m_lightPos[3] = 1.0f;

		gluSphere(m_quadTexture,m_radius,1000,1000);// Draw the Sun

		glLightfv(GL_LIGHT0,GL_POSITION,m_lightPos);
	}
}

void sseSun::PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PostProcess(pRenderer, pTextureLoader);
	gluDeleteQuadric(m_quadTexture);
}

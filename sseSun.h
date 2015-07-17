#pragma once
#include "sseObject.hpp"

class sseSun :
	public sseObject
{
public:
	sseSun(void);
	virtual ~sseSun(void);

	void SetRadius(double radius);
	double GetRadius();

protected:
	virtual void Load(sseTexture *pTextureLoader);
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);
	virtual void PostProcess(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);

protected:
	double m_radius;

private:
	float  m_lightPos[4];
	int texture_id;
	GLUquadricObj* m_quadTexture;

	float m_light_ambient[4];   
	float m_light_diffuse[4];   
	float m_light_specular[4]; 
};

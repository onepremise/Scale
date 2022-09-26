#pragma once
#include "sseObject.hpp"

class ssePlanet :
	public sseObject
{
public:
	ssePlanet(void);
	virtual ~ssePlanet(void);

	void SetRadius(double radius);
	double GetRadius();

	virtual void Load(sseTexture *pTextureLoader);
	virtual void Destroy();
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);

	virtual const char *GetTexturePath()=0;

protected:
	double m_radius;

private:
	int m_texture_id;
	GLUquadricObj* m_quadTexture;
};

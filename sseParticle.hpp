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
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

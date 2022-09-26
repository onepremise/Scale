#pragma once

#include "sseObject.hpp"
#include "sseDebris.h"

class sseDebrisField : public sseObject
{
public:
	sseDebrisField(void);

	void LoadExplosion();
	void LoadFragments(String strFilename);

	virtual void HandleKeyPressEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	void setColor(int R, int G, int B);

protected:
	virtual void Load(sseTexture *pTextureLoader);

	void ProcessRow(String strRow);
	void ProcessField(int iIndex, String StrFld, sseDebris &debris);
	void ProcessObject(int i,bool bPause);

private:
	String m_strDelimiter;
	bool m_bStart;
	float color[3];
};


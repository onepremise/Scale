#pragma once
#include "sseObject.hpp"
class sseDebris : public sseObject
{
public:
	sseDebris(void);
	~sseDebris(void);

	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);

	void SetColor(int R, int G, int B);

	void SetWidth(double w);
	void SetHeight(double h);
	void SetLength(double l);

	double GetWidth() { return dWidth; };
	double GetHeight() { return dHeight; };
	double GetLength() { return dLength; };

	void DrawTriangle(sseGrafxInterface *pRenderer);
	void DrawCube(sseGrafxInterface *pRenderer);

private:
	double dWidth;
	double dHeight;
	double dLength;
	int    m_random;

	float color[3];
};


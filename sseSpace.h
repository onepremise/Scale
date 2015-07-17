#pragma once
#include "sseObject.hpp"

class sseSpace :
	public sseObject
{
public:
	sseSpace(void);
	virtual ~sseSpace(void);

	void SetSize(double size);
	double GetSize();

protected:
	virtual void Load(sseTexture *pTextureLoader);
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);
	virtual void PostProcess(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);

private:
	int tex_front_id;
	int tex_back_id;
	int tex_left_id;
	int tex_right_id;
	int tex_up_id;
	int tex_down_id;

	double m_size;
};

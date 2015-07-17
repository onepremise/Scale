#pragma once

#include "..\sseGrafxInterface.hpp"

class sseOpenGLRenderer : public sseGrafxInterface
{
public:
	sseOpenGLRenderer();
	virtual ~sseOpenGLRenderer();

	virtual int getTicks();

	virtual void enableCulling(bool cull);
	virtual void setCullMode(CullingMode mode);
	virtual void setMaterial(sseMaterial material);
};

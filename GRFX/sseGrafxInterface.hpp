#pragma once

#include "../sseMaterial.h"

enum CullingMode {
        CULL_FRONT = 0,
        CULL_BACK,
		CULL_BOTH
};

class sseGrafxInterface
{
public:
	virtual ~sseGrafxInterface() {};

	virtual int getTicks() = 0;

	virtual void enableCulling(bool cull) = 0;
	virtual void setCullMode(CullingMode mode) = 0;
	virtual void setMaterial(sseMaterial material) = 0;
};

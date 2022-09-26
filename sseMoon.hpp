#pragma once
#include "ssePlanet.hpp"

class sseMoon :
	public ssePlanet
{
public:
	sseMoon(void);
	virtual ~sseMoon(void);

	virtual const char *GetTexturePath();
};

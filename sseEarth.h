#pragma once
#include "ssePlanet.hpp"

class sseEarth :
	public ssePlanet
{
public:
	sseEarth(void);
	virtual ~sseEarth(void);

	virtual char *GetTexturePath();
};

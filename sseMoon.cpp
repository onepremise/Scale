#include "sseMoon.hpp"
#include "sseTexture.h"

sseMoon::sseMoon(void) : ssePlanet()
{
	m_radius=1738.0;
	setName("moon");
}

sseMoon::~sseMoon(void)
{

}

const char *sseMoon::GetTexturePath()
{
	return "Data/entities/img/moon.jpg";
}

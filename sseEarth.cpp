#include "sseEarth.h"
#include "sseTexture.h"

sseEarth::sseEarth(void) : ssePlanet()
{
	m_radius=6378.0;
	setName("earth");
}

sseEarth::~sseEarth(void)
{
}

char *sseEarth::GetTexturePath()
{
	return "Data\\entities\\img\\earthColor4096.jpg";
}

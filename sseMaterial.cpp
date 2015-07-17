#include "sseMaterial.h"

sseMaterial::sseMaterial(void)
{
	m_mode = MAT_UPDATE_NONE;
	
	m_materialColorAmbient.setColor(1.0f, 1.0f, 1.0f);
	m_materialColorSpecular.setColor(1.0f, 1.0f, 1.0f);
	m_materialDiffuse.setColor(0.8f, 0.8f, 0.8f, 1.0f);
	m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_materialShine=0.0;
}

sseMaterial::sseMaterial(sseMaterialPresets predefinedColor)
{
	presetColor(predefinedColor);
}

sseMaterial::~sseMaterial(void)
{
}

sseMaterial::sseMaterial(sseMaterial &m)
{
	m_materialColorAmbient=m.getAmbientColor();
	m_materialColorSpecular=m.getSpecularColor();
	m_materialDiffuse=m.getDiffuseColor();
	m_materialEmission=m.getEmissionColor();
	m_materialShine=m.getShine();
}

void sseMaterial::presetColor(sseMaterialPresets predefinedColor)
{
	switch (predefinedColor)
	{
	case NONE:
		m_materialColorAmbient.setColor(0.0f, 0.0f, 1.0f);
		m_materialColorSpecular.setColor(0.0f, 0.0f, 1.0f);
		m_materialDiffuse.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.0;
		break;
	case EMERALD:
		m_materialColorAmbient.setColor(0.0215, 0.1745, 0.0215);
		m_materialColorSpecular.setColor(0.633, 0.727811, 0.633);
		m_materialDiffuse.setColor(0.07568, 0.61424, 0.07568);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.6;
		break;
	case JADE:
		m_materialColorAmbient.setColor(0.135, 0.2225, 0.1575);
		m_materialDiffuse.setColor(0.54, 0.89, 0.63);
		m_materialColorSpecular.setColor(0.316228, 0.316228, 0.316228);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.1;
		break;
	case OBSIDIAN:
		m_materialColorAmbient.setColor(0.05375,0.05,0.06625);
		m_materialDiffuse.setColor(0.18275,0.17,0.22525);
		m_materialColorSpecular.setColor(0.332741,0.328634,0.346435);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.3;
		break;
	case PEARL:
		m_materialColorAmbient.setColor(0.25,0.20725,0.20725);
		m_materialDiffuse.setColor(1,0.829,0.829);
		m_materialColorSpecular.setColor(0.296648,0.296648,0.296648);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.088;
		break;
	case RUBY:
		m_materialColorAmbient.setColor(0.1745,0.01175,0.01175);
		m_materialDiffuse.setColor(0.61424,0.04136,0.04136);
		m_materialColorSpecular.setColor(0.727811,0.626959,0.626959);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.6;
		break;
	case TURQUOISE:
		m_materialColorAmbient.setColor(0.1,0.18725,0.1745);
		m_materialDiffuse.setColor(0.396,0.74151,0.69102);
		m_materialColorSpecular.setColor(0.297254,0.30829,0.306678);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.1;
		break;
	case BRASS:
		m_materialColorAmbient.setColor(0.329412,0.223529,0.027451);
		m_materialDiffuse.setColor(0.780392,0.568627,0.113725);
		m_materialColorSpecular.setColor(0.992157,0.941176,0.807843);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.21794872;
		break;
	case BRONZE:
		m_materialColorAmbient.setColor(0.2125,0.1275,0.054);
		m_materialDiffuse.setColor(0.714,0.4284,0.18144);
		m_materialColorSpecular.setColor(0.393548,0.271906,0.166721);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.2;
		break;
	case CHROME:
		m_materialColorAmbient.setColor(0.25,0.25,0.25);
		m_materialDiffuse.setColor(0.4,0.4,0.4);
		m_materialColorSpecular.setColor(0.774597,0.774597,0.774597);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.6;
		break;
	case COPPER:
		m_materialColorAmbient.setColor(0.19125,0.0735,0.0225);
		m_materialDiffuse.setColor(0.7038,0.27048,0.0828);
		m_materialColorSpecular.setColor(0.256777,0.137622,0.086014);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.1;
		break;
	case GOLD:
		m_materialColorAmbient.setColor(0.24725,0.1995,0.0745);
		m_materialDiffuse.setColor(0.75164,0.60648,0.22648);
		m_materialColorSpecular.setColor(0.628281,0.555802,0.366065);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.4;
		break;
	case SILVER:
		m_materialColorAmbient.setColor(0.19225,0.19225,0.19225);
		m_materialDiffuse.setColor(0.50754,0.50754,0.50754);
		m_materialColorSpecular.setColor(0.508273,0.508273,0.508273);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.4;
		break;
	case PLASTIC_BLACK:
		m_materialColorAmbient.setColor(0.0,0.0,0.0);
		m_materialDiffuse.setColor(0.01,0.01,0.01);
		m_materialColorSpecular.setColor(0.50,0.50,0.50);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.25;
		break;
	case PLASTIC_CYAN:
		m_materialColorAmbient.setColor(0.0,0.1,0.06);
		m_materialDiffuse.setColor(0.0,0.50980392,0.50980392);
		m_materialColorSpecular.setColor(0.50196078,0.50196078,0.50196078);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.25;
		break;
	case PLASTIC_GREEN:
		m_materialColorAmbient.setColor(0.0,0.0,0.0);
		m_materialDiffuse.setColor(0.1,0.35,0.1);
		m_materialColorSpecular.setColor(0.45,0.55,0.45);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.25;
		break;
	case PLASTIC_RED:
		m_materialColorAmbient.setColor(0.0,0.0,0.0);
		m_materialDiffuse.setColor(0.5,0.0,0.0);
		m_materialColorSpecular.setColor(0.7,0.6,0.6);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.25;
		break;
	case PLASTIC_WHITE:
		m_materialColorAmbient.setColor(0.0,0.0,0.0);
		m_materialDiffuse.setColor(0.55,0.55,0.55);
		m_materialColorSpecular.setColor(0.70,0.70,0.70);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.25;
		break;
	case PLASTIC_YELLOW:
		m_materialColorAmbient.setColor(0.0,0.0,0.0);
		m_materialDiffuse.setColor(0.5,0.5,0.0);
		m_materialColorSpecular.setColor(0.60,0.60,0.50);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=0.25;
		break;
	case RUBBER_BLACK:
		m_materialColorAmbient.setColor(0.02,0.02,0.02);
		m_materialDiffuse.setColor(0.01,0.01,0.01);
		m_materialColorSpecular.setColor(0.4,0.4,0.4);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=.078125;
		break;
	case RUBBER_CYAN:
		m_materialColorAmbient.setColor(0.0,0.05,0.05);
		m_materialDiffuse.setColor(0.4,0.5,0.5);
		m_materialColorSpecular.setColor(0.04,0.7,0.7);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=.078125;
		break;
	case RUBBER_GREEN:
		m_materialColorAmbient.setColor(0.0,0.05,0.0);
		m_materialDiffuse.setColor(0.4,0.5,0.4);
		m_materialColorSpecular.setColor(0.04,0.7,0.04);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=.078125;
		break;
	case RUBBER_RED:
		m_materialColorAmbient.setColor(0.05,0.0,0.0);
		m_materialDiffuse.setColor(0.5,0.4,0.4);
		m_materialColorSpecular.setColor(0.7,0.04,0.04);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=.078125;
		break;
	case RUBBER_WHITE:
		m_materialColorAmbient.setColor(0.05,0.05,0.05);
		m_materialDiffuse.setColor(0.5,0.5,0.5);
		m_materialColorSpecular.setColor(0.7,0.7,0.7);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=.078125;
		break;
	case RUBBER_YELLOW:
		m_materialColorAmbient.setColor(0.05,0.05,0.0);
		m_materialDiffuse.setColor(0.5,0.5,0.4);
		m_materialColorSpecular.setColor(0.7,0.7,0.04);
		m_materialEmission.setColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_materialShine=.078125;
		break;
	default:
		return;
	}
}

sseColor sseMaterial::getAmbientColor()
{
	return m_materialColorAmbient;
}

sseColor sseMaterial::getSpecularColor()
{
	return m_materialColorSpecular;
}

sseColor sseMaterial::getDiffuseColor()
{
	return m_materialDiffuse;
}

sseColor sseMaterial::getEmissionColor()
{
	return m_materialEmission;
}

void sseMaterial::setAmbientColor(sseColor &c)
{
	m_materialColorAmbient.setColor(c);
}

void sseMaterial::setSpecularColor(sseColor &c)
{
	m_materialColorSpecular.setColor(c);
}

void sseMaterial::setDiffuseColor(sseColor &c)
{
	m_materialDiffuse.setColor(c);
}
	
void sseMaterial::setEmissionColor(sseColor &c)
{
	m_materialEmission.setColor(c);
}

float sseMaterial::getShine()
{
	return m_materialShine;
}

void  sseMaterial::setShine(float shine)
{
	m_materialShine=shine;
}

void sseMaterial::setMode(MaterialMode mode)
{
	m_mode = mode;
}

MaterialMode sseMaterial::getMode()
{
	return m_mode;
}

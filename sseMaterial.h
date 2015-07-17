#pragma once

#include "sseInclude.hpp"
#include "sseColor.hpp"

enum MaterialMode {
        MAT_UPDATE_NONE = 1,
        MAT_UPDATE_FRONT = 2,
        MAT_UPDATE_BACK = 3,
		MAT_UPDATE_BOTH = 4
};

enum sseMaterialPresets {
	NONE = 0,
	EMERALD,
	JADE,
	OBSIDIAN,
	PEARL,
	RUBY,
	TURQUOISE,
	BRASS,
	BRONZE,
	CHROME,
	COPPER,
	GOLD,
	SILVER,
	PLASTIC_BLACK,
	PLASTIC_CYAN,
	PLASTIC_GREEN,
	PLASTIC_RED,
	PLASTIC_WHITE,
	PLASTIC_YELLOW,
	RUBBER_BLACK,
	RUBBER_CYAN,
	RUBBER_GREEN,
	RUBBER_RED,
	RUBBER_WHITE,
	RUBBER_YELLOW
};

class sseMaterial
{
public:
	sseMaterial(void);
	sseMaterial(sseMaterialPresets predefinedColor);
	sseMaterial(sseMaterial &m);
	~sseMaterial(void);

	void presetColor(sseMaterialPresets predefinedColor);

	sseColor getAmbientColor();
	sseColor getSpecularColor();
	sseColor getDiffuseColor();
	sseColor getEmissionColor();

	void setAmbientColor(sseColor &c);
	void setSpecularColor(sseColor &c);
	void setDiffuseColor(sseColor &c);
	void setEmissionColor(sseColor &c);

	float getShine();
	void  setShine(float shine);

	void setMode(MaterialMode mode);
	MaterialMode getMode();

public:
	MaterialMode m_mode;

	sseColor  m_materialColorAmbient;
	sseColor  m_materialColorSpecular;
	sseColor  m_materialDiffuse; 
	sseColor  m_materialEmission;

	float  m_materialShine;
};

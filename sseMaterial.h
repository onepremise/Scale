//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Materials
//
// Notes:
//
//    Y+
//    |
//    |__ X+
//   /
//  Z+ 
//
// License:
//
// Licensed under the Apache License, Version 2.0 
// (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of 
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in 
// writing, software distributed under the License is 
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing 
// permissions and limitations under the License.
//
//=========================================================
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

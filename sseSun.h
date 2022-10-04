//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Sun
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
#include "sseObject.hpp"

class sseSun :
	public sseObject
{
public:
	sseSun(void);
	virtual ~sseSun(void);

	void SetRadius(double radius);
	double GetRadius();

protected:
	virtual void Load(sseTexture *pTextureLoader);
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);
	virtual void PostProcess(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);

protected:
	double m_radius;

private:
	float  m_lightPos[4];
	int texture_id;
	GLUquadricObj* m_quadTexture;

	float m_light_ambient[4];   
	float m_light_diffuse[4];   
	float m_light_specular[4]; 
};

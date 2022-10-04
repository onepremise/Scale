//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Space
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

class sseSpace :
	public sseObject
{
public:
	sseSpace(void);
	virtual ~sseSpace(void);

	void SetSize(double size);
	double GetSize();

protected:
	virtual void Load(sseTexture *pTextureLoader);
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);
	virtual void PostProcess(sseGrafxInterface *pRenderer,sseTexture *pTextureLoader);

private:
	int tex_front_id;
	int tex_back_id;
	int tex_left_id;
	int tex_right_id;
	int tex_up_id;
	int tex_down_id;

	double m_size;
};

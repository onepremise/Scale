//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Grafix library adapter
//
// Notes:
//
//    Y+
//    |
//    |__ X+
//   /
//  Z+ 
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

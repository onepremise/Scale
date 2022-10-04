//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Transformations for Scene Graphing
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
#ifndef __SSESPATIAL__
#define __SSESPATIAL__

#include "sseInclude.hpp"
#include "sseMathEngine.hpp"

using namespace ssemath;

class sseSpatial
{
public:
	sseSpatial();
	~sseSpatial() {}

	void UpdateTransforms();

protected:
	sseSpatial* mParent;

    float       mLocalScale;
    fMatrix44   mLocalRotate;
    fMatrix44   mLocalTranslate;

    float       mWorldScale;
    fMatrix44   mWorldRotate;
    fMatrix44   mWorldTranslate;
};

#endif
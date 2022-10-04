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

#include "sseSpatial.hpp"

sseSpatial::sseSpatial()
{
	mParent = 0;

    mLocalScale = 1.0f;
    mLocalRotate.Identity();
    mLocalTranslate.Identity();

    mWorldScale = 1.0f;
    mWorldRotate.Identity();
    mWorldTranslate.Identity();
}

void sseSpatial::UpdateTransforms()
{
    if (mParent)
    {
        mWorldScale = mParent->mWorldScale * mLocalScale;
        mWorldRotate = mParent->mWorldRotate * mLocalRotate;
        mWorldTranslate = mParent->mWorldTranslate + mParent->mWorldRotate * 
			              mLocalTranslate * mParent->mWorldScale;
    }
    else
    {
        mWorldScale = mLocalScale;
        mWorldRotate = mLocalRotate;
        mWorldTranslate = mLocalTranslate;
    }
}

//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Transformations for Scene Graphing
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
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

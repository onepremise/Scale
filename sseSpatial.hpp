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
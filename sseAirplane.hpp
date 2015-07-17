//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Airplane Class
//
//  Notes:
//
//    Y
//    |
//    |__ X
//   /
//  Z 
//
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  1/28/2004     Initial Coding          JAH
//=========================================================
#ifndef __SSEAIRPLANE__
#define __SSEAIRPLANE__

#include "sseObject.hpp"

class sseAirplane: public sseObject
{
public:
	sseAirplane(): sseObject()
	{

	}

	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);


};

#endif

//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Test Objects
//
//  Notes:
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
#ifndef __SSETESTOBJECTS__
#define __SSETESTOBJECTS__

#include "sseObject.hpp"

class objAirplane: public sseObject
{
public:
	objAirplane();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};


class objTriangle: public sseObject
{
public:
	objTriangle();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};

class obj3DGrid: public sseObject
{
public:
	obj3DGrid();
protected:
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};

class objPolygon: public sseObject
{
public:
	objPolygon();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};

class objIcosahedron: public sseObject
{
public:
	objIcosahedron();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};

class objCube: public sseObject
{
public:
	objCube();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};

class objSphere: public sseObject
{
public:
	objSphere();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
};

class objSolarSystem: public sseObject
{
public:
	objSolarSystem();
protected:
	void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
private:
	int m_year;
	int m_day;
};

#endif

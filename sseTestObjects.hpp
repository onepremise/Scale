//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Test Objects
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

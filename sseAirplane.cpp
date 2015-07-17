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
#include "sseAirplane.hpp"

void sseAirplane::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	double glfPos[4]={0};

	list <dVector> vtrFront;
	list <dVector>::iterator iter;

	vtrFront.push_back(dVector(0.25,0.25,-1.5,0));
	vtrFront.push_back(dVector(0.75,0.25,-1.5,0));
	vtrFront.push_back(dVector(0.75,0.25,-2.0,0));
	vtrFront.push_back(dVector(0.25,0.25,-2.0,0));

	vtrFront.push_back(dVector(0.25,0.60,-1.5,0));
	vtrFront.push_back(dVector(0.75,0.60,-1.5,0));
	vtrFront.push_back(dVector(0.75,0.60,-2.0,0));
	vtrFront.push_back(dVector(0.25,0.60,-2.0,0));

	vtrFront.push_back(dVector(0.25,0.60,-1.5,0));
	vtrFront.push_back(dVector(0.25,0.60,-2.0,0));
	vtrFront.push_back(dVector(0.25,0.25,-2.0,0));
	vtrFront.push_back(dVector(0.25,0.25,-1.5,0));

	vtrFront.push_back(dVector(0.75,0.60,-1.5,0));
	vtrFront.push_back(dVector(0.75,0.60,-2.0,0));
	vtrFront.push_back(dVector(0.75,0.25,-2.0,0));
	vtrFront.push_back(dVector(0.75,0.25,-1.5,0));

	glColor3f(0.3,0.5,1.0);

    glBegin(GL_LINE_LOOP);
	for (iter=vtrFront.begin(); iter!=vtrFront.end(); iter++)
	{
		(*iter)+=m_objectMatrix[0];
		glVertex3dv((*iter).GetGLArray(glfPos));
	}
    glEnd();

	list <dVector> vtrFslg;

	vtrFslg.push_back(dVector(0.25,0.25,-1.5,0));
	vtrFslg.push_back(dVector(0.75,0.25,-1.5,0));

	vtrFslg.push_back(dVector(0.25,0.25,-1.5,0));
	vtrFslg.push_back(dVector(0.25,0.60,-1.5,0));

	vtrFslg.push_back(dVector(0.25,0.60,-1.5,0));
	vtrFslg.push_back(dVector(0.75,0.60,-1.5,0));

	vtrFslg.push_back(dVector(0.75,0.25,-1.5,0));
	vtrFslg.push_back(dVector(0.75,0.60,-1.5,0));

	vtrFslg.push_back(dVector(0.25,0.25,-1.5,0));
	vtrFslg.push_back(dVector(0.25,0.25,-1.2,0));

	vtrFslg.push_back(dVector(0.75,0.25,-1.5,0));
	vtrFslg.push_back(dVector(0.75,0.25,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.60,-1.5,0));
	vtrFslg.push_back(dVector(0.25,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.75,0.60,-1.5,0));
	vtrFslg.push_back(dVector(0.75,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.25,-1.2,0));
	vtrFslg.push_back(dVector(0.75,0.25,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.75,-1.2,0));
	vtrFslg.push_back(dVector(0.75,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.25,-1.2,0));
	vtrFslg.push_back(dVector(0.25,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.75,0.25,-1.2,0));
	vtrFslg.push_back(dVector(0.75,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.25,0.0,0));
	vtrFslg.push_back(dVector(0.25,0.25,-1.2,0));

	vtrFslg.push_back(dVector(0.75,0.25,0.0,0));
	vtrFslg.push_back(dVector(0.75,0.25,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.75,0.0,0));
	vtrFslg.push_back(dVector(0.25,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.75,0.75,0.0,0));
	vtrFslg.push_back(dVector(0.75,0.75,-1.2,0));

	vtrFslg.push_back(dVector(0.25,0.25,0.0,0));
	vtrFslg.push_back(dVector(0.75,0.25,0.0,0));

	vtrFslg.push_back(dVector(0.75,0.25,0.0,0));
	vtrFslg.push_back(dVector(0.75,0.75,0.0,0));

	vtrFslg.push_back(dVector(0.75,0.75,0.0,0));
	vtrFslg.push_back(dVector(0.25,0.75,0.0,0));

	vtrFslg.push_back(dVector(0.25,0.75,0.0,0));
	vtrFslg.push_back(dVector(0.25,0.25,0.0,0));

	vtrFslg.push_back(dVector(0.25,0.25,0.0,0));
	vtrFslg.push_back(dVector(0.25,0.75,3.0,0));

	vtrFslg.push_back(dVector(0.25,0.75,0.0,0));
	vtrFslg.push_back(dVector(0.25,0.75,3.0,0));

	vtrFslg.push_back(dVector(0.25,0.75,3.0,0));
	vtrFslg.push_back(dVector(0.75,0.75,3.0,0));

	vtrFslg.push_back(dVector(0.75,0.75,3.0,0));
	vtrFslg.push_back(dVector(0.75,0.75,0.0,0));

	vtrFslg.push_back(dVector(0.75,0.75,3.0,0));
	vtrFslg.push_back(dVector(0.75,0.25,0.0,0));

    glColor3d(0.3,0.5,1.0);

    glBegin(GL_LINES);
	for (iter=vtrFslg.begin(); iter!=vtrFslg.end(); iter++)
	{
		(*iter)+=m_objectMatrix[0];
		glVertex3dv((*iter).GetGLArray(glfPos));
	}
    glEnd();

	glColor3d(1.0,1.0,1.0);

	list <dVector> vtrWing;

	vtrWing.push_back(dVector(-2.2, 0.75, -1.1,0));
	vtrWing.push_back(dVector(3.2, 0.75, -1.1,0));
	vtrWing.push_back(dVector(3.2, 0.75, -0.1,0));
	vtrWing.push_back(dVector(-2.2, 0.75, -0.1,0));

	glBegin(GL_POLYGON);
	for (iter=vtrWing.begin(); iter!=vtrWing.end(); iter++)
	{
		(*iter)+=m_objectMatrix[0];
		glVertex3dv((*iter).GetGLArray(glfPos));
	}
	glEnd();

	list <dVector> vtrRE;

	vtrRE.push_back(dVector(0.50, 0.75, 2.4,0));
	vtrRE.push_back(dVector(-0.3, 0.75, 3.0,0));
	vtrRE.push_back(dVector(1.3, 0.75, 3.0,0));

	vtrRE.push_back(dVector(0.5, 0.75, 2.5,0));
	vtrRE.push_back(dVector(0.5, 1.2, 3.0,0));
	vtrRE.push_back(dVector(0.5, 0.75, 3.0,0));

	glBegin(GL_TRIANGLES);
	for (iter=vtrRE.begin(); iter!=vtrRE.end(); iter++)
	{
		(*iter)+=m_objectMatrix[0];
		glVertex3dv((*iter).GetGLArray(glfPos));
	}
	glEnd();

    return;
}

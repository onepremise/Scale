//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Airplane Class
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

//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Debris Field
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
#include "sseDebris.h"

#define GET_A(c) ((c >> 24) & 0xFF)
#define GET_R(c) ((c >> 16) & 0xFF)
#define GET_G(c) ((c >> 8) & 0xFF)
#define GET_B(c) (c & 0xFF)

sseDebris::sseDebris(void): sseObject()
{
	stringstream sstm;

	sstm << "Debris-" << getID();

	setName(sstm.str());

	color[0]=0.7;
	color[1]=0.7;
	color[2]=0.7;

	dWidth=1;
	dHeight=1;
	dLength=1;

	int min=0;
	int max=10;

	m_random = min + (rand() % (int)(max - min + 1));
}


sseDebris::~sseDebris(void)
{

}

void sseDebris::SetWidth(double w)
{
	dWidth=w;
}

void sseDebris::SetHeight(double h)
{
	dHeight=h;
}

void sseDebris::SetLength(double l)
{
	dLength=l;
}

void sseDebris::SetColor(int R, int G, int B)
{
	color[0]=R;
	color[1]=G;
	color[2]=B;
}

void sseDebris::DrawTriangle(sseGrafxInterface *pRenderer)
{
	double halfLength=dLength/2;
	double halfWidth=dWidth/2;
	double halfHeight=dHeight/2;

	glBegin(GL_TRIANGLES);
  //Triangle 1
    glVertex3f( 0.0f, halfHeight, 0.0f);   //V0(red)
    glVertex3f(-dWidth/2,-halfHeight, halfLength);   //V1(green)
    glVertex3f( dWidth/2,-halfHeight, halfLength);   //V2(blue)
  //Triangle 2
    glVertex3f( 0.0f, halfHeight, 0.0f);   //V0(red)
    glVertex3f( halfWidth,-halfHeight, halfLength);   //V2(blue)
    glVertex3f( halfWidth,-halfHeight,-halfLength);   //V3(green)
  //Triangle 3
    glVertex3f( 0.0f, halfHeight, 0.0f);   //V0(red)
    glVertex3f( halfWidth,-halfHeight,-halfLength);   //V3(green)
    glVertex3f(-halfWidth,-halfHeight,-halfLength);   //V4(blue)
  //Triangle 4
    glVertex3f( 0.0f, halfHeight, 0.0f);   //V0(red)
    glVertex3f(-halfWidth,-halfHeight,-halfLength);   //V4(blue)
    glVertex3f(-halfWidth,-halfHeight, halfLength);   //V1(green)

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(-halfWidth,-halfHeight, halfLength);   //V7
    glVertex3f(-halfWidth,-halfHeight,-halfLength);   //V5
    glVertex3f( halfWidth,-halfHeight,-halfLength);   //V3
    glVertex3f( halfWidth,-halfHeight, halfLength);   //V1

	glEnd();
}

void sseDebris::DrawCube(sseGrafxInterface *pRenderer)
{
	double halfLength=dLength/2;
	double halfWidth=dWidth/2;
	double halfHeight=dHeight/2;

	glBegin(GL_QUADS);
    //Quad 1
    glVertex3f( halfWidth, halfHeight, halfLength);   //V2
    glVertex3f( halfWidth,-halfHeight, halfLength);   //V1
    glVertex3f( halfWidth,-halfHeight,-halfLength);   //V3
    glVertex3f( halfWidth, halfHeight,-halfLength);   //V4
    //Quad 2
    glVertex3f( halfWidth, halfHeight,-halfLength);   //V4
    glVertex3f( halfWidth,-halfHeight,-halfLength);   //V3
    glVertex3f(-halfWidth,-halfHeight,-halfLength);   //V5
    glVertex3f(-halfWidth, halfHeight,-halfLength);   //V6
    //Quad 3
    glVertex3f(-halfWidth, halfHeight,-halfLength);   //V6
    glVertex3f(-halfWidth,-halfHeight,-halfLength);   //V5
    glVertex3f(-halfWidth,-halfHeight, halfLength);   //V7
    glVertex3f(-halfWidth, halfHeight, halfLength);   //V8
    //Quad 4
    glVertex3f(-halfWidth, halfHeight, halfLength);   //V8
    glVertex3f(-halfWidth,-halfHeight, halfLength);   //V7
    glVertex3f( halfWidth,-halfHeight, halfLength);   //V1
    glVertex3f( halfWidth, halfHeight, halfLength);   //V2
    //Quad 5
    glVertex3f(-halfWidth, halfHeight,-halfLength);   //V6
    glVertex3f(-halfWidth, halfHeight, halfLength);   //V8
    glVertex3f( halfWidth, halfHeight, halfLength);   //V2
    glVertex3f( halfWidth, halfHeight,-halfLength);   //V4
    //Quad 6
    glVertex3f(-halfWidth,-halfHeight, halfLength);   //V7
    glVertex3f(-halfWidth,-halfHeight,-halfLength);   //V5
    glVertex3f( halfWidth,-halfHeight,-halfLength);   //V3
    glVertex3f( halfWidth,-halfHeight, halfLength);   //V1

	glEnd();
}

void sseDebris::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	glDisable(GL_LIGHTING);

	glColor3fv (color);

	if (m_random>=6)
		DrawTriangle(pRenderer);
	else
		DrawCube(pRenderer);
	
	glEnable(GL_LIGHTING);
}
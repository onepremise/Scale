//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Space
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
#include "sseSpace.h"
#include "sseTexture.h"


sseSpace::sseSpace(void)
{
	sseColor sAC(2.4f, 2.4f, 2.4f);
	sseColor sSC(0.0,0.0,0.0);

	m_materialDefault.setAmbientColor(sAC);
	m_materialDefault.setSpecularColor(sSC);
 	m_materialDefault.setMode(MAT_UPDATE_BACK);

	m_size=1000;

	this->enableCulling(false);
}

sseSpace::~sseSpace(void)
{
}

void sseSpace::SetSize(double size)
{
	m_size=size;
}

double sseSpace::GetSize()
{
	return m_size;
}

void sseSpace::Load(sseTexture *pTextureLoader)
{
 	tex_front_id=pTextureLoader->LoadWrap("Data/entities/img/calmspace/Front.tif", -1, GL_RGB);
	tex_back_id=pTextureLoader->LoadWrap("Data/entities/img/calmspace/Back.tif", -1, GL_RGB);
	tex_left_id=pTextureLoader->LoadWrap("Data/entities/img/calmspace/Left.tif", -1, GL_RGB);
	tex_right_id=pTextureLoader->LoadWrap("Data/entities/img/calmspace/Right.tif", -1, GL_RGB);
	tex_up_id=pTextureLoader->LoadWrap("Data/entities/img/calmspace/Up.tif", -1, GL_RGB);
	tex_down_id=pTextureLoader->LoadWrap("Data/entities/img/calmspace/Down.tif", -1, GL_RGB);

	//tex_front_id=textures->LoadWrap("Data/entities/img/calmspace/white.tif", -1, GL_RGB);
	//tex_back_id=textures->LoadWrap("Data/entities/img/calmspace/white.tif", -1, GL_RGB);
	//tex_left_id=textures->LoadWrap("Data/entities/img/calmspace/white.tif", -1, GL_RGB);
	//tex_right_id=textures->LoadWrap("Data/entities/img/calmspace/white.tif", -1, GL_RGB);
	//tex_up_id=textures->LoadWrap("Data/entities/img/calmspace/white.tif", -1, GL_RGB);
	//tex_down_id=textures->LoadWrap("Data/entities/img/calmspace/white.tif", -1, GL_RGB);
}

void sseSpace::PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) 
{
	sseObject::PreProcess(pRenderer, pTextureLoader);
}

void sseSpace::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	pTextureLoader->Bind(tex_front_id);

	// Render the front quad
	glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3d(  -m_size, -m_size, -m_size );
        glTexCoord2d(0, 1); glVertex3d( -m_size, m_size, -m_size );
        glTexCoord2d(1, 1); glVertex3d( m_size,  m_size, -m_size );
        glTexCoord2d(1, 0); glVertex3d(  m_size,  -m_size, -m_size );
    glEnd();

	// Render the left quad
    pTextureLoader->Bind(tex_left_id);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3d(  m_size, -m_size,  -m_size );
        glTexCoord2d(0, 1); glVertex3d(  m_size, m_size, -m_size );
        glTexCoord2d(1, 1); glVertex3d(  m_size,  m_size, m_size );
        glTexCoord2d(1, 0); glVertex3d(  m_size,  -m_size,  m_size );
    glEnd();

    // Render the back quad
    pTextureLoader->Bind(tex_back_id);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3d( m_size, -m_size,  m_size );
        glTexCoord2d(0, 1); glVertex3d(  m_size, m_size,  m_size );
        glTexCoord2d(1, 1); glVertex3d(  -m_size,  m_size,  m_size );
        glTexCoord2d(1, 0); glVertex3d( -m_size,  -m_size,  m_size );
    glEnd();
 
    //// Render the right quad
    pTextureLoader->Bind(tex_right_id);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3d( -m_size, -m_size, m_size );
        glTexCoord2d(0, 1); glVertex3d( -m_size, m_size,  m_size );
        glTexCoord2d(1, 1); glVertex3d( -m_size,  m_size,  -m_size );
        glTexCoord2d(1, 0); glVertex3d( -m_size,  -m_size, -m_size );
    glEnd();
 
    //// Render the top quad
    pTextureLoader->Bind(tex_up_id);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3d( -m_size,  m_size, m_size );
        glTexCoord2d(0, 1); glVertex3d( m_size,  m_size,  m_size );
        glTexCoord2d(1, 1); glVertex3d(  m_size,  m_size,  -m_size );
        glTexCoord2d(1, 0); glVertex3d(  -m_size,  m_size, -m_size );
    glEnd();
 
    //// Render the bottom quad
    pTextureLoader->Bind(tex_down_id);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3d( m_size, -m_size, m_size );
        glTexCoord2d(0, 1); glVertex3d( -m_size, -m_size,  m_size );
        glTexCoord2d(1, 1); glVertex3d(  -m_size, -m_size,  -m_size );
        glTexCoord2d(1, 0); glVertex3d(  m_size, -m_size, -m_size );
    glEnd();
}

void sseSpace::PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	sseObject::PostProcess(pRenderer, pTextureLoader);
}

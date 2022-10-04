//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Grafix library adapter
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
#include "sseOpenGLRenderer.hpp"
#include "../../sseErrorHandler.hpp"
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <GL/glut.h>

sseOpenGLRenderer::sseOpenGLRenderer()
{

}

sseOpenGLRenderer::~sseOpenGLRenderer()
{

}

int sseOpenGLRenderer::getTicks()
{
	return SDL_GetTicks();
}

void sseOpenGLRenderer::enableCulling(bool cull)
{
	if (cull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void sseOpenGLRenderer::setCullMode(CullingMode mode)
{
	GLenum face=GL_FRONT_AND_BACK;

	switch (mode)
	{
	case CULL_FRONT:
		face=GL_FRONT;
		break;
	case CULL_BACK:
		face=GL_BACK;
		break;
	case CULL_BOTH:
		face=GL_FRONT_AND_BACK;
		break;
	}

	glCullFace(face);

	sseErrorHandler::_ThrowIfOGLRendererError();
}

void sseOpenGLRenderer::setMaterial(sseMaterial material)
{
	GLenum face=GL_FRONT_AND_BACK;

	switch (material.getMode())
	{
	case MAT_UPDATE_NONE:
		face=GL_NONE;
		break;
	case MAT_UPDATE_FRONT:
		face=GL_FRONT;
		break;
	case MAT_UPDATE_BACK:
		face=GL_BACK;
		break;
	case MAT_UPDATE_BOTH:
		face=GL_FRONT_AND_BACK;
		break;
	}

	glMaterialfv(face, GL_AMBIENT, material.getAmbientColor().getColor());
	glMaterialfv(face, GL_DIFFUSE, material.getDiffuseColor().getColor());
	glMaterialfv(face, GL_SPECULAR, material.getSpecularColor().getColor());
	glMaterialfv(face, GL_EMISSION, material.getEmissionColor().getColor());
	glMaterialf(face, GL_SHININESS, material.getShine()); 

	sseErrorHandler::_ThrowIfOGLRendererError();
}
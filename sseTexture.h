//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Textures
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
#pragma once
#ifndef __sseTexture__
#define __sseTexture__

#include "sseInclude.hpp"
#include "GRFX/sseGrafxInterface.hpp"
#include "FreeImage.h"

class sseTexture
{
public:
	sseTexture();
	sseTexture(const sseTexture& tm);
	sseTexture& operator=(const sseTexture& tm);

	~sseTexture();

	void SetRenderer(sseGrafxInterface *pRenderer);

	FIBITMAP *OpenImage(const char* filename);

	void CloseImage(FIBITMAP *dib);

	int Load(String filename, int textureID=-1, GLenum image_format = GL_RGB,
		GLint internal_format = GL_RGB,	GLint level = 0, GLint border = 0);

	int LoadWrap(String filename, int textureID=-1, GLenum image_format = GL_RGB, 
		int wraps= GL_CLAMP, int wrapt = GL_REPEAT, int magf= GL_LINEAR, 
		int minf = GL_LINEAR, bool mipmap = false);

	bool Unload(int iTexID);
	void Unload();

	void Bind(int iTexID);

private:
	BYTE* convertToRGBA(BYTE* bits, int components, int width, int height);

	static int idCounter;

	map<int, GLuint> m_IDs;

	sseGrafxInterface *m_pRenderer;
};

#endif
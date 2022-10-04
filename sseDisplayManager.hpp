//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Display Mannager
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
#ifndef __sseDisplayManager__
#define __sseDisplayManager__

#include "sseInclude.hpp"

enum FONTI18NMODE {
	RENDER_LATIN1,
	RENDER_UTF8,
	RENDER_UNICODE
};

#define DEFAULT_PTSIZE	18
#define NUM_COLORS      256

class sseDisplayManager
{
public:
	static sseDisplayManager *Instance();
	~sseDisplayManager();

protected:
	sseDisplayManager();

public:
	void InitializeWindow();
	void ConfigurePixelFormat(void);
	void CreateSDLWindow(void);
	void Clear(void);
	void ReSizeOpenGLWindow(int width, int height);
	void Flip(void);
	void UpdateRenderer(void);
	void SwitchToFullScreen(void);
	void GetVideoInfo(void);
	SDL_Window *GetWindow() {return m_ParentWindow;}
	int  GetWidth(void) {return m_width;}
	int  GetHeight(void) {return m_height;}
	int  GetDepth(void) {return m_depth;}
	int  GetCenterX(void) {return m_iCenterX;}
	int  GetCenterY(void) {return m_iCenterY;}
	void SetCursorCenter(void);
	void SetCursor(int x, int y);
	void SetProjectionMatrix(float zDistance=1);

private:
	static sseDisplayManager *_instance;

private:
	int m_SDL_Vid_Flags;

	// SDL window
	int m_numDisplays;
	SDL_Window* m_ParentWindow;
	SDL_GLContext m_Context;
	SDL_Surface   *m_ParentSurface;
	SDL_Renderer *m_Renderer;
	//SDL_RendererInfo *m_pstVideoInfo;

	int m_width;
	int m_height;
	int m_depth;

	double m_nearClip, m_farClip;

	float m_zDistance;

	int m_iCenterX;
	int m_iCenterY;

	GLuint m_texture;
	SDL_Color *m_fontColor;
};

#endif

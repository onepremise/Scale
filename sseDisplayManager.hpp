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
	SDL_Window* m_ParentWindow;
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

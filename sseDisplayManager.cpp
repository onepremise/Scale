//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Display Mannager
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseDisplayManager.hpp"
#include <SDL2/SDL_opengl.h>
#include "sseMath.hpp"

//  Y
//  |
//  |__ X
// /
//Z

sseDisplayManager *sseDisplayManager::_instance=0;

sseDisplayManager *sseDisplayManager::Instance()
{
	if (_instance == 0)
		_instance = new sseDisplayManager;

	return _instance;
}

sseDisplayManager::sseDisplayManager()
{
	m_SDL_Vid_Flags=0;

	m_ParentWindow=NULL;
	m_ParentSurface=NULL;
	m_Renderer=NULL;

	//m_width=1280;
	//m_height=1024;
	m_width=800;
	m_height=640;
	m_depth=32;

	m_nearClip=1;
	//m_farClip=150;
	m_farClip=59135200;
	m_zDistance=1;

	m_iCenterX = m_width  >> 1;
	m_iCenterY = m_height >> 1;
}

sseDisplayManager::~sseDisplayManager()
{
    SDL_DestroyWindow(m_ParentWindow);
}

void sseDisplayManager::SetCursorCenter()
{
	SDL_WarpMouseInWindow(m_ParentWindow, m_iCenterX, m_iCenterY);
}

void sseDisplayManager::SetCursor(int x, int y)
{
	SDL_WarpMouseInWindow(m_ParentWindow, x, y);
}

void sseDisplayManager::InitializeWindow()
{
	//sseErrorHandler::_ThrowIfSDLInitFailed(SDL_Init( SDL_INIT_VIDEO ));
	sseErrorHandler::_ThrowIfSDLInitFailed(SDL_Init(SDL_INIT_EVERYTHING));

	GetVideoInfo();

	ConfigurePixelFormat();

	CreateSDLWindow();

    //sseErrorHandler::_LogIfSDLCursorFail(SDL_ShowCursor(SDL_DISABLE));

    //SDL2 no longer has SDL_EnableKeyRepeat
	//sseErrorHandler::_ThrowIfEnableKeyRepFail(SDL_EnableKeyRepeat(100,SDL_DEFAULT_REPEAT_INTERVAL));

	SetCursorCenter();
}

void sseDisplayManager::GetVideoInfo(void)
{
	//m_pstVideoInfo = (SDL_RendererInfo *)SDL_GetVideoInfo();
	//sseErrorHandler::_ThrowIfSDLQueryFailed(m_pstVideoInfo);
	sseLog *log=sseLog::Instance();

	SDL_RendererInfo info;

    log->Info("Drivers: ");
    for ( int i = 0; i < SDL_GetNumRenderDrivers(); i++)
    {
		
		if ( SDL_GetRenderDriverInfo(i,&info) == 0 )
		{
			log->Info("%i. %s", i, info.name);
		}
		i++;
	}
}

void sseDisplayManager::ConfigurePixelFormat(void)
{

	m_SDL_Vid_Flags = SDL_WINDOW_RESIZABLE;

			//if (fullscreen) {
			//	m_SDL_Vid_Flags |= SDL_WINDOW_FULLSCREEN;
			//}

    //if(m_pstVideoInfo -> hw_available)
    //    m_SDL_Vid_Flags |= SDL_HWSURFACE;
    //else
    //    m_SDL_Vid_Flags |= SDL_SWSURFACE;
    
    //if(m_pstVideoInfo -> blit_hw)
    //    m_SDL_Vid_Flags |= SDL_HWACCEL;

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,   m_depth);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1); 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);// Antialiasing
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//SDL_GL_SetAttribute( SDL_GL_RED_SIZE, m_depth/4);
	//SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, m_depth/4);
	//SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, m_depth/4);
	//SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, m_depth/4);


   // SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 0);
    //SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0);
    //SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0);
    //SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0);
    //SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0);

    // glEnable(GL_FOG);                                   // Fog
    // glFogi(GL_FOG_MODE, GL_EXP2);
    // glHint(GL_FOG_HINT, GL_NICEST);
    // glFogf(GL_FOG_DENSITY, 0.025f);
    // glFogfv(GL_FOG_COLOR, color);
}

void sseDisplayManager::CreateSDLWindow(void)
{
	// Gone in SDL2
    // SDL_WM_SetCaption("Scaled Simulator", "Scaled Simulator");
	m_numDisplays = SDL_GetNumVideoDisplays();

	m_ParentWindow = SDL_CreateWindow("Scaled Simulator",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
										  m_width,
										  m_height,
                                          m_SDL_Vid_Flags);

	// m_ParentSurface = SDL_GetWindowSurface(m_ParentWindow);
	SDL_SetWindowTitle(m_ParentWindow, "Scaled Simulator");

	m_Renderer = SDL_CreateRenderer(m_ParentWindow, 0, SDL_RENDERER_ACCELERATED);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	// m_Renderer = SDL_CreateRenderer(m_ParentWindow, -1, 0);

	sseErrorHandler::_ThrowIfSDLRendererFail(m_Renderer);

	m_Context = SDL_GL_CreateContext(m_ParentWindow);

	SDL_GL_MakeCurrent(m_ParentWindow, m_Context);
	
    SDL_GL_SetSwapInterval(0);

    SDL_SetWindowSize(m_ParentWindow, m_width, m_height);

	ReSizeOpenGLWindow(m_width, m_height);
}

void sseDisplayManager::Clear(void)
{
	SDL_RenderClear(m_Renderer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void sseDisplayManager::ReSizeOpenGLWindow(int iwidth, int iheight)
{
    if (iheight==0) iheight=1;

	m_width = iwidth;
	m_height= iheight;

	m_iCenterX = m_width  >> 1;
	m_iCenterY = m_height >> 1;

	// SDL_SetWindowSize(m_ParentWindow, m_width, m_height);

	glViewport(0,0,m_width,m_height);

	SetProjectionMatrix(m_zDistance);

	// Clear();

	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // Type of depth test

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // SDL_UpdateWindowSurface(m_ParentWindow);
	// sseErrorHandler::_ThrowIfSDLWindowFail(m_ParentSurface);
    // SDL_RenderSetLogicalSize(m_Renderer, m_width, m_height);
	// Flip();
}

void sseDisplayManager::SetProjectionMatrix(float zDistance)
{
	m_zDistance=zDistance;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective (60.0f*m_zDistance, (float)m_width/(float)m_height, m_nearClip, m_farClip);
	glMatrixMode (GL_MODELVIEW);
}

void sseDisplayManager::Flip(void)
{
	SDL_GL_SwapWindow(m_ParentWindow);
	// SDL_UpdateWindowSurface(m_ParentWindow);
	//SDL2 removed flip
	//sseErrorHandler::_ThrowIfSDLUpdateFail(SDL_Flip(m_ParentSurface));
}

void sseDisplayManager::UpdateRenderer(void)
{
	SDL_RenderPresent(m_Renderer);
}

void sseDisplayManager::SwitchToFullScreen(void)
{
	m_SDL_Vid_Flags |= SDL_WINDOW_FULLSCREEN;

	sseErrorHandler::_ThrowIfSDLFullScreenSwitch(SDL_SetWindowFullscreen(m_ParentWindow, m_SDL_Vid_Flags));

    //sseErrorHandler::_ThrowIfSDLFullScreenSwitch(SDL_WM_ToggleFullScreen(m_ParentSurface));
	//m_ParentSurface = SDL_SetVideoMode(m_width, m_height, m_depth, m_SDL_Vid_Flags);
	//sseErrorHandler::_ThrowIfSDLWindowFail(m_ParentSurface);

	//char gamestr [256]={0};
	//sprintf (gamestr, "%dx%d:%d", m_width, m_height, m_depth);
	//glutGameModeString (gamestr);
	//if (glutGameModeGet (GLUT_GAME_MODE_POSSIBLE))
 //   {
 //     glutEnterGameMode ();
 //   }
	// glViewport (0, 0, (GLint) m_width, (GLint) m_height);
}

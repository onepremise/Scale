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
	m_log = sseLog::Instance();

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
	glfwTerminate();
}

void sseDisplayManager::SetCursorCenter()
{
	//SDL_WarpMouseInWindow(m_ParentWindow, m_iCenterX, m_iCenterY);
}

void sseDisplayManager::SetCursor(int x, int y)
{
	//SDL_WarpMouseInWindow(m_ParentWindow, x, y);
}

void sseDisplayManager::InitializeWindow()
{
	sseErrorHandler::_ThrowIfInitFailed(glfwInit());
	//sseErrorHandler::_ThrowIfSDLInitFailed(SDL_Init( SDL_INIT_VIDEO ));
	//sseErrorHandler::_ThrowIfSDLInitFailed(SDL_Init(SDL_INIT_EVERYTHING));

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	//GetVideoInfo();

	ConfigurePixelFormat();

	CreateSDLWindow();

    //sseErrorHandler::_LogIfSDLCursorFail(SDL_ShowCursor(SDL_DISABLE));

    //SDL2 no longer has SDL_EnableKeyRepeat
	//sseErrorHandler::_ThrowIfEnableKeyRepFail(SDL_EnableKeyRepeat(100,SDL_DEFAULT_REPEAT_INTERVAL));

	SetCursorCenter();
}

void sseDisplayManager::GetVideoInfo(void)
{
	int count;

	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	//GLFWvidmode* modes = glfwGetVideoModes(primary, &count);
	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	int widthMM, heightMM;

	//The physical size of a monitor in millimetres, or an estimation
	//of it, can be retrieved with glfwGetMonitorPhysicalSize. This has
	//no relation to its current resolution, i.e. the width and height
	//of its current video mode.
	glfwGetMonitorPhysicalSize(primary, &widthMM, &heightMM);

	//calculate the DPI of a monitor.
	const double dpi = mode->width / (widthMM / 25.4);

	int xpos, ypos;
	//Virtual position
	glfwGetMonitorPos(primary, &xpos, &ypos);

	const char* name = glfwGetMonitorName(primary);

	//The gamma ramp of a monitor
	const GLFWgammaramp* ramp = glfwGetGammaRamp(primary);
}

void sseDisplayManager::ConfigurePixelFormat(void)
{
	glfwWindowHint(GLFW_DEPTH_BITS,32);
}

void sseDisplayManager::CreateSDLWindow(void)
{
	m_window = glfwCreateWindow(m_width, m_height, "Scaled Simulator", NULL, NULL);

	sseErrorHandler::_ThrowIfWindowFail(m_window);

	InstallHooks(m_window);

	glfwMakeContextCurrent(m_window); // Initialize GLEW

	//glewExperimental=true; // Needed in core profile

	//ReSizeOpenGLWindow(m_width, m_height);

	int bpp=glfwGetWindowAttrib(m_window, GLFW_DEPTH_BITS);

	m_log->Info("OpenGL bpp: %i\nOpenGL w x h: %i x %i", bpp, m_width, m_height);
}

void sseDisplayManager::Clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void sseDisplayManager::InstallHooks(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, this);

	glfwSetWindowSizeCallback(window, onResizeCallback);
	glfwSetFramebufferSizeCallback(window, onFrameBuffResizeCallback);
	glfwSetWindowRefreshCallback(window, onRefreshCallback);
	glfwSetWindowPosCallback(window,onMoveCallback);
	glfwSetWindowFocusCallback(window, onFocusCallback);
	glfwSetWindowCloseCallback(window, onCloseCallback);
	glfwSetWindowIconifyCallback(window, onIconifyCallback);
}

void sseDisplayManager::onMove(int xPos, int yPos) {

}

void sseDisplayManager::onFocus(int focused) {
    //GL_TRUE
}

void sseDisplayManager::onClose() {
    //GL_TRUE
}

void sseDisplayManager::onIconify(int iconified) {
    //GL_TRUE
}

void sseDisplayManager::onResize(int iwidth, int iheight)
{
    if (iheight==0) iheight=1;

	m_width = iwidth;
	m_height= iheight;

	m_iCenterX = m_width  >> 1;
	m_iCenterY = m_height >> 1;

	glfwSetWindowSize(m_window, m_width, m_height);

	glViewport(0,0,m_width,m_height);

	sseErrorHandler::_ThrowIfOGLDisplayError();

	SetProjectionMatrix(m_zDistance);

	Clear();

	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // Type of depth test

	sseErrorHandler::_ThrowIfOGLDisplayError();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void sseDisplayManager::onFrameBufferResize(int iwidth, int iheight) {

}

void sseDisplayManager::onRefresh(void) {

}

void sseDisplayManager::SetProjectionMatrix(float zDistance)
{
	m_zDistance=zDistance;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective (60.0f*m_zDistance, (float)m_width/(float)m_height, m_nearClip, m_farClip);
	glMatrixMode (GL_MODELVIEW);
	sseErrorHandler::_ThrowIfOGLDisplayError();
}

void sseDisplayManager::Flip(void)
{
	glfwSwapBuffers(m_window);
}

void sseDisplayManager::SwitchToFullScreen(void)
{
	GLFWwindow *fsDisplayHandle = glfwCreateWindow(m_width, m_height, "Scaled Simulator", true ? glfwGetPrimaryMonitor() : NULL, m_window);

	sseErrorHandler::_ThrowIfWindowFail(fsDisplayHandle);

	InstallHooks(fsDisplayHandle);

	glfwDestroyWindow(m_window);

	m_window = fsDisplayHandle;

	glfwMakeContextCurrent(m_window);
}

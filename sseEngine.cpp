//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Simulator Engine
//
//  Notes:
//
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseEngine.hpp"
#include "GRFX/OpenGL/sseOpenGLRenderer.hpp"
#include "sseUnitTests.hpp"

sseEngine *sseEngine::_instance = 0;

#define PAUSE 0
#define NORMALIZE_SPEED 1
#define QUIT 2

sseEngine *sseEngine::Instance()
{
    if (_instance == 0)
        _instance = new sseEngine;

    return _instance;
}

sseEngine::sseEngine()
{
    m_bSimulating = true;

    m_fFramesPerSecond = 0.0f;
    m_lastCompleteFrame = 0.0f;

    m_pDisplay = sseDisplayManager::Instance();
    m_pRenderer = new sseOpenGLRenderer();
    m_pSystemClock = new sseClock(m_pRenderer);
    m_pSceneLoader = new sseSceneLoader(m_pDisplay, m_pRenderer, m_pSystemClock);
    m_pEventHandler = new sseEventHandler(this);
}

sseEngine::~sseEngine()
{
    SDL_Quit();

    delete m_pDisplay;
    delete m_pEventHandler;
    delete m_pRenderer;
    delete m_pSceneLoader;
    delete m_pSystemClock;
}

void sseEngine::LogRasterEngineInfo()
{
    sseLog *log = sseLog::Instance();

    char *p = (char *)glGetString(GL_VERSION);
    char *v = (char *)glGetString(GL_VENDOR);
    char *ext = (char *)glGetString(GL_EXTENSIONS);

    log->Info("OGL Version: %s", p);

    log->Info("OGL Vendor: %s", v);

    // log->Info("OGL Extensions: %s", ext);
}

int sseEngine::StartSimulation()
{
    m_pDisplay->InitializeWindow();

    LogRasterEngineInfo();

    RunTests();

    ManageSimulator();

    return 0;
}

void sseEngine::RunTests()
{
    sseUnitTests unitTests;

    unitTests.Run();
}

void sseEngine::PauseSimulation()
{
    m_pSceneLoader->Pause();
}

void sseEngine::ResetSimulation()
{
    m_pSceneLoader->Reset();
}

void menuSelect(int value)
{
    switch (value)
    {
    case PAUSE:
        break;

    case NORMALIZE_SPEED:
        break;

    case QUIT:
        exit(0);
        break;
    }
}

void sseEngine::ManageSimulator()
{
    // not supported on windows 7
    // glutCreateMenu (menuSelect);
    // glutAddMenuEntry ("Pause", 0);
    // glutAddMenuEntry ("Toggle normalized speed vectors", 1);
    // glutAddMenuEntry ("Quit", 2);
    // glutAttachMenu (GLUT_RIGHT_BUTTON);

    m_pSceneLoader->Initialize();

    sseErrorHandler::_ThrowIfSDLTextureLoadError();

    m_pSceneLoader->Build();

    sseErrorHandler::_ThrowIfSDLTextureLoadError();

    m_pSceneLoader->Load();

    while (m_bSimulating)
    {
        m_pEventHandler->HandleEvents();
        m_pSceneLoader->Render();
        GetFrameRate();
    }
}

void sseEngine::GetFrameRate()
{
    m_pSystemClock->Update();

    ++m_fFramesPerSecond;

    if (m_pSystemClock->GetCurrentTime() - m_lastCompleteFrame > 1.0)
    {
        char strTemp[25] = {0};
        m_lastCompleteFrame = m_pSystemClock->GetCurrentTime();

        sprintf(strTemp, "%s %d", "Frames Per Second: ", (int)m_fFramesPerSecond);

        // SDL_SetWindowTitle(strTemp);

        m_fFramesPerSecond = 0;
    }
}

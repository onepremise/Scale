//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Rendering Queue
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseSceneLoader.hpp"
#include "sseSpace.h"
#include "sseSun.h"
#include "sseEarth.h"
#include "sseMoon.hpp"

sseSceneLoader::sseSceneLoader(sseDisplayManager *display, sseGrafxInterface *pRenderer, sseClock *pClock)
{
	m_pause=true;
	m_pDisplay=display;
	m_pRenderer=pRenderer;
	m_pSystemClock = pClock;
	m_pGraph = new sseSceneGraph(pRenderer, m_pSystemClock);
	m_pGraph->setScale(1);
	m_camera.SetClock(pClock);
}

sseSceneLoader::~sseSceneLoader()
{
	m_pause=true;
	m_pGraph->clearScene();
}

void sseSceneLoader::Reset()
{
	m_pause=true;
	m_pGraph->pause(m_pause);
	m_pGraph->clearScene();
	Build();
	Load();
}

void sseSceneLoader::Pause()
{
	m_pause=!m_pause;
	m_pGraph->pause(m_pause);
}

void sseSceneLoader::Initialize()
{
	InitLighting();
}

void sseSceneLoader::Build()
{
	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	m_pDisplay->Clear();

	m_pGraph->setCamera(&m_camera);

	const double SCALE=.01;
/*
	sseSpace *space=new sseSpace();
	space->SetSize(59135200*SCALE);
	space->setPosition(0.0,0.0,0.0);
	m_pGraph->addObject(space, false, true);

	sseSun *sun=new sseSun();
	sun->SetRadius(695000.0*SCALE);
	sun->setPosition(0.0,0.0,0.0);
	//sun->SetRotationalVel(0,.001,0);
	m_pGraph->addObject(sun, false, true);

	sseEarth *earth=new sseEarth();
	earth->SetRadius(6378.0*SCALE);
	earth->setPosition(14960000*SCALE,0.0,0.0);
	//earth->SetRotationalVel(0,1674*SCALE/1200,0);

	sun->AddNode(earth, false, true);

	sseMoon *moon=new sseMoon();
	moon->SetRadius(1738.0*SCALE);
	moon->setPosition(38400*SCALE,0.0,0.0f);
	moon->SetRotationalVel(0,1023*SCALE/1200,0);
	earth->AddNode(moon, false, true);
*/
	obj3DGrid *grid=new obj3DGrid();

	m_camera.SetView(0, 0.5, 0,  0, 0, 0.5,  0, 0.5, 0 );
	m_camera.SetPosition(grid->getWorldPosition());
}

void sseSceneLoader::Load()
{
	m_pGraph->loadScene();
}

void sseSceneLoader::InitLighting() {
	// Light values and coordinates
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	glEnable(GL_LIGHTING);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void sseSceneLoader::ClearDisplay()
{
	m_pDisplay->Clear();
}

void sseSceneLoader::Render()
{
	ClearDisplay();
	m_pGraph->renderScene();
}



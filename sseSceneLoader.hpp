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
#ifndef __SSERENDER__
#define __SSERENDER__

#include "sseInclude.hpp"
#include "sseObjectClasses.hpp"
#include "sseSceneGraph.hpp"
#include "sseClock.hpp"

class sseSceneLoader
{
public:
	sseSceneLoader(sseDisplayManager *display, sseGrafxInterface *pRenderer, sseClock *pClock);

public:
	~sseSceneLoader();

	void Reset();

	void Pause();

	void Initialize();

	void Build();

	void Load();

	void Render();

private:
	void InitLighting();
	void ClearDisplay();

private:
	bool m_pause;

	sseDisplayManager *m_pDisplay;
	sseGrafxInterface *m_pRenderer;
	sseClock *m_pSystemClock;

	sseCamera m_camera;
	sseSceneGraph *m_pGraph;

};

#endif

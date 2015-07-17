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
#ifndef __SSEENGINE__
#define __SSEENGINE__

#include "sseInclude.hpp"
#include "sseSceneLoader.hpp"
#include "sseEventHandler.hpp"
#include "sseDisplayManager.hpp"
#include "GRFX\sseGrafxInterface.hpp"
#include "sseClock.hpp"

class sseEngine
{
public:
	static sseEngine *Instance();

protected:
	sseEngine();

public:
	~sseEngine();

public:
	void RunTests();

	int StartSimulation();

	void PauseSimulation();

	void ResetSimulation();

	void ManageSimulator();

	void ShutdownSimulator() {m_bSimulating=false;}

	void GetFrameRate();

private:
	void LogRasterEngineInfo();

	static sseEngine *_instance;

	sseEventHandler   *m_pEventHandler;
	sseDisplayManager *m_pDisplay;
	sseSceneLoader    *m_pSceneLoader;
	sseGrafxInterface *m_pRenderer;

	bool  m_bSimulating;
	float m_fFramesPerSecond;
    float m_lastCompleteFrame;

	sseClock *m_pSystemClock;
};


#endif

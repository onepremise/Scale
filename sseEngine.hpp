//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Simulator Engine
//
// Notes:
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
#ifndef __SSEENGINE__
#define __SSEENGINE__

#include "sseInclude.hpp"
#include "sseSceneLoader.hpp"
#include "sseEventHandler.hpp"
#include "sseDisplayManager.hpp"
#include "GRFX/sseGrafxInterface.hpp"
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

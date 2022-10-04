//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Rendering Queue
//
// Notes:
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

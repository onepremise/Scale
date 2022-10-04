//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Scene Graph
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
#ifndef __SSESCENEGRAPH__
#define __SSESCENEGRAPH__

#include "sseInclude.hpp"
#include "sseObject.hpp"
#include "sseCamera.hpp"
#include "sseConcurrentContextGuard.hpp"
#include "sseClock.hpp"
#include "sseCommand.hpp"

class sseSceneGraph
{
	friend class sseCommand;
public:
	sseSceneGraph(sseGrafxInterface *pRenderer, sseClock *pClock);
	~sseSceneGraph();

	void setScale(double fScale);

	sseCamera *getCamera() {return m_pCamera;};
	void setCamera(sseCamera *cam) { m_pCamera=cam; };

	void processCollisions(sseObject* pObject);

	void addObject(sseObject* pObject, bool bCollidable, bool enabled=true);

	void renderLevels(sseObject *pObject);
	void renderScene();

	void loadScene();
	void clearScene();

	void pause(bool pause) {m_paused=pause;};

private:
	void loadScene(sseObject* pObject);

protected:
	deque<sseObject*> getObjectQueue() {return m_objectQueue;};

protected:
	dMatrix44 m_world;

	double m_dScale;

	sseGrafxInterface *m_pRenderer;

	sseClock *m_pSystemClock;

	sseCamera *m_pCamera;

	deque<sseObject*> m_objectQueue;
	deque<sseObject*> m_renderingQueue;
	deque<sseObject*> m_collisionQueue;

	sseCommand *m_command;

	bool m_paused;
};

#endif

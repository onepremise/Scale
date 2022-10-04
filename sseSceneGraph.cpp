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
#include "sseSceneGraph.hpp"
#include "sseConcurrentContextGuard.hpp"

sseSceneGraph::sseSceneGraph(sseGrafxInterface *pRenderer, sseClock *pClock)
{
	m_pRenderer = pRenderer;
	m_pSystemClock = pClock;
	m_world.Identity();
	m_dScale=1.0;
	m_command=new sseCommand(this);
}

sseSceneGraph::~sseSceneGraph()
{
	delete m_command;
}

void sseSceneGraph::setScale(double scale)
{
	m_dScale=scale;
}

void sseSceneGraph::loadScene()
{
	deque<sseObject*>::iterator pObject;

	for(int i=0; i<m_objectQueue.size(); i++)
	{
		sseObject* pObject=m_objectQueue[i];
		loadScene(pObject);
	}
}

void sseSceneGraph::loadScene(sseObject* pObject)
{
	pObject->SetCommandProcessor(m_command);

	((sseConcurrentContextGuard*)pObject)->Load(m_pRenderer);

	if (pObject->isCollisionEnabled())
		m_collisionQueue.push_back(pObject);

	sseObject** nodes=pObject->getNodes();

	for (int i=0; i<pObject->getNumNodes(); i++) {
		sseObject *child=nodes[i];
		loadScene(child);
	}
}

void sseSceneGraph::clearScene()
{
	m_renderingQueue.clear();
	m_collisionQueue.clear();

	deque<sseObject*>::iterator pObject;

	for(pObject=m_objectQueue.begin(); pObject!=m_objectQueue.end(); pObject++)
		if (!(*pObject)->isLocalNode())
			delete (*pObject);

	m_objectQueue.clear();
}

void sseSceneGraph::addObject(sseObject* pObject, bool bCollidable, bool enabled)
{
	pObject->SetEnabled(enabled);

	pObject->SetClock(m_pSystemClock);

	pObject->SetCommandProcessor(m_command);

	m_renderingQueue.push_back(pObject);

	pObject->SetCollisionEnabled(bCollidable);

	m_objectQueue.push_back(pObject);

	((sseConcurrentContextGuard*)pObject)->affineTransform();
}

void sseSceneGraph::processCollisions(sseObject* pObject)
{
	if (!pObject->isDestroyed())
	{
		deque<sseObject*>::iterator itObject;
		for(itObject=m_collisionQueue.begin(); itObject!=m_collisionQueue.end(); itObject++)
		{
			if (*itObject!=pObject)
			{
				double distance=pObject->getPosition().Distance((*itObject)->getPosition());

				if (distance<.8) {
 					pObject->Destroy();
					(*itObject)->Destroy();
				}
			}
		}
	}
}

void sseSceneGraph::renderLevels(sseObject *pObject)
{
	sseLog *log=sseLog::Instance();
	sseObject** nodes=pObject->getNodes();

	for (int i=0; i<pObject->getNumNodes(); i++) {
		sseObject *child=nodes[i];
		if (child->isEnabled() && child->isLocalNode()) {
			((sseConcurrentContextGuard*)child)->Update(m_paused);

			if (child->isCollisionEnabled()) {
				processCollisions(child);
			}

			glPushMatrix();

			::glMultMatrixd((*child->getLocalTransform()).GetOGLMatrix());

			((sseConcurrentContextGuard*)child)->Render(m_pRenderer);

			if (child->getNumNodes()>0)
  				renderLevels(child);

			glPopMatrix();
		}
	}
}

void sseSceneGraph::renderScene()
{
	sseLog *log=sseLog::Instance();
	m_pCamera->Update();

	::glLoadMatrixd(m_world.GetOGLMatrix());
	::glScaled(m_dScale,m_dScale,m_dScale);

	dMatrix copy;
	GLdouble modelMatrix[16]={0};

	::glMultMatrixd(m_pCamera->GetViewTransformation()->GetOGLMatrix());

	deque<sseObject*>::iterator itObject;
	for(itObject=m_renderingQueue.begin(); itObject!=m_renderingQueue.end(); itObject++)
	{
		sseObject* pObject=(*itObject);
		if (pObject->isEnabled())
		{
			if (pObject->isCollisionEnabled() && !m_paused)
				processCollisions(pObject);

			glPushMatrix();

			((sseConcurrentContextGuard*)pObject)->Update(m_paused);

			::glMultMatrixd(pObject->getLocalTransform()->GetOGLMatrix());

			((sseConcurrentContextGuard*)pObject)->Render(m_pRenderer);

			renderLevels(pObject);

			glPopMatrix();
		}
	}

	//glPushMatrix();
	//m_pDisplay->RenderText();
	//glPopMatrix();
}

//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Command interface for engine
//
// Notes:
//
//    Y+
//    |
//    |__ X+
//   /
//  Z+ 
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
#include "sseCommand.hpp"

sseCommand::sseCommand(sseSceneGraph * pGraph)
{
	m_pGraph=pGraph;
}

sseCamera *sseCommand::GetActiveCamera()
{
	return m_pGraph->getCamera();
}

sseObject *sseCommand::GetObjectByName(String name)
{
	deque<sseObject*> dq=m_pGraph->getObjectQueue();
	
	deque<sseObject*>::iterator itObject;
	for(itObject=dq.begin(); itObject!=dq.end(); itObject++)
	{
		sseObject *pFound=FindObjectByName(*itObject, name);

		if (pFound!=NULL)
			return pFound;
	}

	return NULL;
}

void sseCommand::addSceneGraphNode(sseObject *object)
{
	m_pGraph->addObject(object, object->isCollisionEnabled(), object->isEnabled());
}

void sseCommand::addSceneGraphNode(sseObject *parent, sseObject *child)
{
	//m_pGraph->
}

sseObject *sseCommand::FindObjectByName(sseObject *pObject, String name)
{
	if (pObject->getName().compare(name) == 0)
		return pObject;

	sseObject** nodes=pObject->getNodes();

	for (int i=0; i<pObject->getNumNodes(); i++) {
		sseObject *child=nodes[i];
		FindObjectByName(child, name);
	}

	return NULL;
}
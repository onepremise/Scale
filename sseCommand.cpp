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
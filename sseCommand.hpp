#ifndef __SSECOMMAND__
#define __SSECOMMAND__

#include "sseCamera.hpp"
#include "sseSceneGraph.hpp"

class sseSceneGraph;

class sseCommand
{
public:
	sseCommand(sseSceneGraph * pGraph);

	sseCamera *GetActiveCamera();
	sseObject *GetObjectByName(String name);

	void addSceneGraphNode(sseObject *object);
	void addSceneGraphNode(sseObject *parent, sseObject *child);

private:
	sseObject *FindObjectByName(sseObject *pObject, String name);

private:
	sseSceneGraph *m_pGraph;
};

#endif

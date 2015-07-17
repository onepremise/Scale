//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Node for Scene Graphing
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#ifndef __SSESCENENODE__
#define __SSESCENENODE__

#include "sseInclude.hpp"
#include "sseSpatial.hpp"

class sseSceneNode: public sseSpatial
{
public:
	sseSceneNode() {}

	// destructor - calls destroy
	virtual ~sseSceneNode() { Destroy(); }

	void Release() { delete this; }

	virtual void Update()
	{
		for( std::list<sseSceneNode*>::iterator i = m_lstChildren.begin(); i != m_lstChildren.end(); i++ )
		{
			(*i)->Update();
		}
	}

	void Destroy()
	{
		for( std::list<sseSceneNode*>::iterator i = m_lstChildren.begin(); i != m_lstChildren.end(); i++ )
			(*i)->Release();
		m_lstChildren.clear();
	}

	void AddChild( sseSceneNode* pNode )
	{
		m_lstChildren.push_back(pNode);
	}

protected:
	list<CSceneNode*> m_lstChildren;
};

#endif
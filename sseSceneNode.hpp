//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Node for Scene Graphing
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
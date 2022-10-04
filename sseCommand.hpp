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

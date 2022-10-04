//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Object Event Handler
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
#include "sseEventObjectHandler.hpp"
#include "sseEventHandler.hpp"

sseEventObjectHandler::sseEventObjectHandler()
{
	DeclineEvents();
}

sseEventObjectHandler::~sseEventObjectHandler()
{
	DeclineEvents();
}

void sseEventObjectHandler::AcceptEvents()
{
	sseEventHandler::AddObjectToQueue(this);
	m_pEventMappings=sseEventHandler::GetEventMappings();
}

void sseEventObjectHandler::DeclineEvents()
{
	sseEventHandler::RemoveObjectFromQueue(this);
	m_pEventMappings=&m_EmptyMap;
}
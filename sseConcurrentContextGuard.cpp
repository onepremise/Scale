//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Concurrent Context Proxy Guard. Ensures 
//               threaded procdures don't get access to 
//               syncronous objects.
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
#include "sseConcurrentContextGuard.hpp"

sseConcurrentContextGuard::sseConcurrentContextGuard()
{
	m_pTextureLoader = NULL;
}

sseConcurrentContextGuard::~sseConcurrentContextGuard()
{
	if (m_pTextureLoader!=NULL)
		delete m_pTextureLoader;
}

void sseConcurrentContextGuard::Load(sseGrafxInterface *pRenderer)
{
	m_pTextureLoader=new sseTexture();

	m_pTextureLoader->SetRenderer(pRenderer);

	Load(m_pTextureLoader);
}

void sseConcurrentContextGuard::Update(bool bPause)
{
	if (!bPause)
	{
		processPhysics();
	}

	affineTransform();
}

void sseConcurrentContextGuard::Render(sseGrafxInterface *pRenderer)
{
	PreProcess(pRenderer, m_pTextureLoader);
	DrawObject(pRenderer, m_pTextureLoader);
	PostProcess(pRenderer, m_pTextureLoader);
}
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
#ifndef __SSECONCURRENTGUARD__
#define __SSECONCURRENTGUARD__

#include "sseTexture.h"

class sseConcurrentContextGuard
{
friend class sseSceneGraph;
public:
	sseConcurrentContextGuard();
	~sseConcurrentContextGuard();

protected:
	void Load(sseGrafxInterface *pRenderer);
	void Update(bool bPause);
	void Render(sseGrafxInterface *pRenderer);

protected:
	virtual void Load(sseTexture *pTextureLoader) = 0;
	virtual void processPhysics() = 0;
	virtual void affineTransform() = 0;
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) = 0;
	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) = 0;
	virtual void PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) = 0;

private:
	sseTexture *m_pTextureLoader;
};

#endif
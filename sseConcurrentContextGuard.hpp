//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Concurrent Context Proxy Guard. Ensures 
//                threaded procdures don't get access to 
//                syncronous objects.
//
//  Notes:
//
//    Y
//    |
//    |__ X
//   /
//  Z 
//
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  11/07/2012    Initial Coding          JAH
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
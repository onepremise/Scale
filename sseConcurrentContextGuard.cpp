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
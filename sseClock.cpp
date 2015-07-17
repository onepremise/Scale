#include "sseClock.hpp"

sseClock::sseClock(sseGrafxInterface *renderer)
{
	m_pRenderer=renderer;
}

sseClock::~sseClock()
{

}

void sseClock::Update()
{
	double time=m_pRenderer->getTicks() * 0.001f;
	m_elapsedTime = time - m_currentTime;
    m_currentTime = time;
	m_total+=m_elapsedTime;
}
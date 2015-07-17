#pragma once

#include "GRFX\sseGrafxInterface.hpp"

class sseClock
{
public:
	sseClock(sseGrafxInterface *renderer);
	~sseClock();

	void Update();

    double GetCurrentTime() { return m_currentTime; };
    double GetElapsedTime() { return m_elapsedTime; };
	double GetTotalTime() { return m_total; };

protected:
	double m_currentTime;
	double m_elapsedTime;
	double m_total;

private:
	sseGrafxInterface *m_pRenderer;
};
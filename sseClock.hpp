//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Clock
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
//========================================================
#pragma once

#include "GRFX/sseGrafxInterface.hpp"

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
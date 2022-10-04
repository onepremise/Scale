//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Event Mappings to Keyboard
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
#ifndef __SSEEVENTMAPPINGS__
#define __SSEEVENTMAPPINGS__

class sseEventMappings
{
public:
	sseEventMappings()
	{
		m_bKeyEventFoward=false;
		m_bKeyEventBackward=false;
		m_bKeyEventDown=false;
		m_bKeyEventUp=false;
		m_bKeyEventLeft=false;
		m_bKeyEventRight=false;

		m_bMouseEventRight=false;
		m_bMouseEventUp=false;
		m_bMouseEventLeft=false;
		m_bMouseEventDown=false;

		m_bMouseLBttnDown=false;
		m_bMouseMBttnDown=false;
		m_bMouseRBttnDown=false;

		m_bMouseLBttnUp=false;
		m_bMouseMBttnUp=false;
		m_bMouseRBttnUp=false;

		m_eScrollButton=SSENOMOTION;
	}

public:
	bool m_bKeyEventFoward;
	bool m_bKeyEventBackward;
	bool m_bKeyEventDown;
	bool m_bKeyEventUp;
	bool m_bKeyEventLeft;
	bool m_bKeyEventRight;

	bool m_bMouseEventRight;
	bool m_bMouseEventLeft;
	bool m_bMouseEventUp;
	bool m_bMouseEventDown;

	bool m_bMouseLBttnDown;
	bool m_bMouseMBttnDown;
	bool m_bMouseRBttnDown;

	bool m_bMouseLBttnUp;
	bool m_bMouseMBttnUp;
	bool m_bMouseRBttnUp;

public:
	enum ScrollButton
	{
		SSESCROLLUP,
		SSENOMOTION,
		SSESCROLLDOWN
	};

	ScrollButton m_eScrollButton;
};

#endif

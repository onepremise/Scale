//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Colors
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
#pragma once

class sseColor
{
public:
	sseColor(void);
	sseColor(sseColor &c);
	sseColor(float r, float g, float b, float a);
	sseColor(float r, float g, float b);
	~sseColor(void);

	float operator[] (int index)
	{
		return color[index];
	}

	void setRed(float r);
	void setGreen(float r);
	void setBlue(float b);
	void setAlpha(float a);

	float getRed();
	float getGreen();
	float getBlue();
	float getAlpha();

	void setColor(sseColor &c);
	void setColor(float r, float g, float b, float a);
	void setColor(float r, float g, float b);
	float *getColor();

public:
	float  color[4];
};
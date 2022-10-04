
//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Logs
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
#pragma once

#include "sseInclude.hpp"

class sseLog
{
public:
	static sseLog *Instance();

protected:
	sseLog();
	virtual ~sseLog(void);

public:
	// void Info(char *str, ...);
	// void Warn(char *str, ...);
	// void Error(char *str, ...);

	void Info(const char *str, ...);
	void Warn(const char *str, ...);
	void Error(const char *str, ...);

	void Info(basic_string<char> msg);
	void Warn(basic_string<char> msg);
	void Error(basic_string<char> msg);

private:
	void Write(char *str, ...);

private:
	static sseLog *_instance;
	ofstream m_logFile;

private:
	FILE* m_cLogFile;
	basic_string<char> m_test;

};

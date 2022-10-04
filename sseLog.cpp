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
#include "sseLog.h"

sseLog *sseLog::_instance=0;

#define LOG_FILE "sse-diagnostics.log"

sseLog *sseLog::Instance()
{
	if (_instance == 0)
		_instance = new sseLog;

	return _instance;
}

sseLog::sseLog(void)
{
	m_logFile.open(LOG_FILE, ofstream::binary);
	m_logFile.close();
}

sseLog::~sseLog(void)
{

}

void sseLog::Write(char *str, ...)
{
	m_logFile.open(LOG_FILE, ofstream::app);
    m_logFile.write(str, strlen(str));
    m_logFile.close();

	/*fopen_s(&m_cLogFile, LOG_FILE, "wb");
	if (m_cLogFile != NULL)
	{
		fprintf ( m_cLogFile, str );
		fclose(m_cLogFile);
	}*/
}

void sseLog::Info(const char *str, ...)
{
	char szInfo [4096]={0};

	va_list arg_ptr;

	va_start(arg_ptr, str);

	vsprintf(szInfo, str, arg_ptr);

	va_end(arg_ptr);

	strcat(szInfo, "\n");

	Write(szInfo);
}

void sseLog::Warn(const char *str, ...)
{
	char szInfo [4096]={0};

	va_list arg_ptr;

	va_start(arg_ptr, str);

	vsprintf(szInfo, str, arg_ptr);

	va_end(arg_ptr);

	strcat(szInfo, "\n");

	Write(szInfo);
}

void sseLog::Error(const char *str, ...)
{
	char szInfo [4096]={0};

	va_list arg_ptr;

	va_start(arg_ptr, str);

	vsprintf(szInfo, str, arg_ptr);

	va_end(arg_ptr);

	strcat(szInfo, "\n");

	Write(szInfo);
}

void sseLog::Info(basic_string<char> msg)
{
	m_logFile.open(LOG_FILE, ofstream::app);
    m_logFile.write(msg.c_str(), strlen(msg.c_str()));
    m_logFile.close();
}

void sseLog::Warn(basic_string<char> msg)
{
	m_logFile.open(LOG_FILE, ofstream::app);
    m_logFile.write(msg.c_str(), strlen(msg.c_str()));
    m_logFile.close();
}

void sseLog::Error(basic_string<char> msg)
{
	m_logFile.open(LOG_FILE, ofstream::app);
    m_logFile.write(msg.c_str(), strlen(msg.c_str()));
    m_logFile.close();
}
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

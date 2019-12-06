#pragma once

#include <string>
#include <iostream>
#include <atomic>
#include <chrono>

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

//#define NDEBUG

namespace cat {

//the max string size including the null terminator
#define MAX_DEBUG_STR_SIZE 256

void debug_print(const char *fmt, ...);

#if !defined(NDEBUG) | defined(_DEBUG)
#define DEBUG_PRINT(format, ...) debug_print(format, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(format, ...)
#endif //_DEBUG

class debug {
public:
	debug();
	debug(std::string &&scope);
	void info(const char *format, ...);
	void error(const char *format, ...);
	void warn(const char *format, ...);
	void die(const char *format, ...);
	const std::string &get_scope() const;
	~debug();
private:
	int make_prefix(char *buff, int size, const char *category);
	void output_debug_message(char *message, int len);
	std::string scope_;
	std::chrono::time_point<std::chrono::system_clock> tstart_;
	pid_t pid_;
	bool has_scope_ = false;
	//pid_t tid_;
	//static std::atomic<int> level_; 
};

}
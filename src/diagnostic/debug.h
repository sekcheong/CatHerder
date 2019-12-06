#pragma once

#include <string>
#include <iostream>
#include <atomic>
#include <chrono>

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
	void info(const char *fmt, ...);
	void error(const char *fmt, ...);
	void warning(const char *fmt, ...);
	void die(const char *fmt, ...);
	const std::string &get_scope() const;
	~debug();
private:
	std::string scope_;
	std::chrono::time_point<std::chrono::system_clock> tstart_;
	//static std::atomic<int> level_; 
};

}
#include <iostream>
#include <cstdarg>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>
#include "debug.h"

namespace cat {

void output_debug_string(const char *message) {
 	struct timeval tv;
 	time_t nowtime;
 	struct tm *nowtm;
 	char tmbuf[64]; 
 	char buf[64];
	pid_t pid = getpid();
 	gettimeofday(&tv, NULL);
 	nowtime = tv.tv_sec;
 	nowtm = localtime(&nowtime);
 	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
 	snprintf(buf, sizeof buf, "%s.%06ld", tmbuf, (long) tv.tv_usec);
  	std::cout << "[" << buf << "]:[" << pid << "]:" << message ;
}


void debug_print(const char *fmt, ...) {
	char buff[MAX_DEBUG_STR_SIZE];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buff, MAX_DEBUG_STR_SIZE - 1, fmt, args);
	strncat(buff, "\n", MAX_DEBUG_STR_SIZE - 1);
	va_end(args);
	output_debug_string(buff);
}


//std::atomic<int> debug::level_{0}; 


debug::debug() {
//	level_++;
	tstart_ = std::chrono::system_clock::now();
	std::cout << "debug()" << std::endl;
}


debug::debug(std::string &&scope) {
//	level_++;
	tstart_ = std::chrono::system_clock::now();
	scope_ = std::move(scope);
	std::cout << "debug(): " << scope << std::endl;	
}


void debug::info(const char *fmt, ...) {
	std::cout << "info" << std::endl;
}


void debug::error(const char *fmt, ...) {
	std::cout << "error" << std::endl;
}


void debug::warning(const char *fmt, ...) {
	std::cout << "warning" << std::endl;
}


void debug::die(const char *fmt, ...) {
	std::cout << "die" << std::endl;
}


const std::string &debug::get_scope() const {
	return scope_;
}


debug::~debug() {
	std::cout << "~debug()" << std::endl;
}


}
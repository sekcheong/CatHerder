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
 	strftime(tmbuf, sizeof tmbuf, "%Y%m%d %H.%M.%S", nowtm);
 	snprintf(buf, sizeof buf, "%s.%06ld", tmbuf, (long) tv.tv_usec);
  	std::cout << "[" << buf << "]:[" << pid << "]:" << message ;
}


void debug_print(const char *format, ...) {
	char buff[MAX_DEBUG_STR_SIZE];
	va_list args;
	va_start(args, format);
	vsnprintf(buff, MAX_DEBUG_STR_SIZE - 1, format, args);
	strncat(buff, "\n", MAX_DEBUG_STR_SIZE - 1);
	va_end(args);
	output_debug_string(buff);
}


//std::atomic<int> debug::level_{0}; 


debug::debug() {
//	level_++;
	pid_ = getpid();
	//tid_ = gettid();
	tstart_ = std::chrono::system_clock::now();
	//std::cout << "debug()" << std::endl;
}


debug::debug(std::string &&scope) {
//	level_++;
	scope_ = std::move(scope);
	//std::cout << "debug(): " << scope << std::endl;	
	has_scope_ = true;
	info("<begin>");
	pid_ = getpid();
	tstart_ = std::chrono::system_clock::now();
}

void debug::info(const char *format, ...) {
	char pbuff[128];
	int plen = make_prefix(pbuff, sizeof pbuff,  "I");

	char buff[MAX_DEBUG_STR_SIZE];
	va_list args;
 	va_start(args, format);
	int msglen = vsnprintf(buff, MAX_DEBUG_STR_SIZE - 1, format, args);
	strncat(buff, "\n", MAX_DEBUG_STR_SIZE - 1);
	va_end(args);
	output_debug_message(pbuff, plen);
	output_debug_message(buff, msglen);
}


void debug::error(const char *format, ...) {
	char pbuff[128];
	int plen = make_prefix(pbuff, sizeof pbuff,  "E");

	char buff[MAX_DEBUG_STR_SIZE];
	va_list args;
 	va_start(args, format);
	int msglen = vsnprintf(buff, MAX_DEBUG_STR_SIZE - 1, format, args);
	strncat(buff, "\n", MAX_DEBUG_STR_SIZE - 1);
	va_end(args);
	output_debug_message(pbuff, plen);
	output_debug_message(buff, msglen);
}


void debug::warn(const char *format, ...) {
	char pbuff[128];
	int plen = make_prefix(pbuff, sizeof pbuff,  "W");

	char buff[MAX_DEBUG_STR_SIZE];
	va_list args;
 	va_start(args, format);
	int msglen = vsnprintf(buff, MAX_DEBUG_STR_SIZE - 1, format, args);
	strncat(buff, "\n", MAX_DEBUG_STR_SIZE - 1);
	va_end(args);
	output_debug_message(pbuff, plen);
	output_debug_message(buff, msglen);
}


void debug::die(const char *format, ...) {
	char pbuff[128];
	int plen = make_prefix(pbuff, sizeof pbuff,  "X");

	char buff[MAX_DEBUG_STR_SIZE];
	va_list args;
 	va_start(args, format);
	int msglen = vsnprintf(buff, MAX_DEBUG_STR_SIZE - 1, format, args);
	strncat(buff, "\n", MAX_DEBUG_STR_SIZE - 1);
	va_end(args);
	output_debug_message(pbuff, plen);
	output_debug_message(buff, msglen);
	exit(-1);
}


const std::string &debug::get_scope() const {
	return scope_;
}

int debug::make_prefix(char *buff, int size, const char *category) {
	struct timeval tv;
	time_t nowtime;
	struct tm *nowtm;
	char tmbuf[64]; 
	pid_t pid = getpid();
	
	gettimeofday(&tv, NULL);
	nowtime = tv.tv_sec;
	nowtm = localtime(&nowtime);
	
	//strftime(tmbuf, sizeof tmbuf, "[%Y%m%d]:[%H%M%S", nowtm);
	
	strftime(tmbuf, sizeof tmbuf, "[%H%M%S", nowtm);
	
	if (has_scope_) {
		return snprintf(buff, size, "[%s]:%s.%06ld][%d][%s]:", category, tmbuf, (long) tv.tv_usec, pid, scope_.c_str());
	}
	else {
		return snprintf(buff, size, "[%s]:%s.%06ld][%d]:", category, tmbuf, (long) tv.tv_usec, pid);
	}
}

void debug::output_debug_message(char *message, int len) {
	std::cout << message;
}

debug::~debug() {
	if (has_scope_) {
		info("<end>", scope_.c_str());
	}
}


}
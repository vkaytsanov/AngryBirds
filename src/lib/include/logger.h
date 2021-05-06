#ifndef LOGGER
#define LOGGER

class Logger {
public:
	Logger() = default;
	void log(const char* tag, const char* message);
	void debug(const char* tag, const char* message);
	void error(const char* tag, const char* message);
};

#endif
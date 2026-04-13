#pragma once

#include <iostream>

class Logger {
    public:
        Logger();
		~Logger();
        static Logger &getLogger() {
            static Logger logger;
	        return logger;
        };
        void info(std::string msg);
        void error(std::string msg);

    private:
		Logger(const Logger&) = delete;
		Logger &operator=(const Logger&) = delete;
};
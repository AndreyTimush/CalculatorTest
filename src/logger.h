#pragma once

#include <iostream>

class Logger {
    public:
        Logger() = default;
        Logger(Logger&& other) noexcept = default;
        Logger& operator=(Logger&& other) noexcept = default;
		~Logger() = default;
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
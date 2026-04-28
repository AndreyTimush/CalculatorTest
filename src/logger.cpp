#include <spdlog/spdlog.h>
#include "logger.h"

void Logger::info(std::string msg)
{
    spdlog::info(msg);
}

void Logger::error(std::string msg)
{
    spdlog::error(msg);
}
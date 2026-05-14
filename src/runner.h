#pragma once
#include "data.h"
#include "parser.h"
#include "checker.h"
#include "printer.h"
#include "logger.h"
#include "calculator.h"
#include "database.h"

class Runner
{
    Data data;
    Parser parser;
    Checker checker;
    Printer printer;
    Calculator calculator;
    Logger &logger = Logger::getLogger();
    public:
        Runner();
        Runner(const Runner& other); 
        Runner& operator=(const Runner& other);
        Runner(Runner&& other) noexcept;
        Runner& operator=(Runner&& other) noexcept;
        ~Runner() = default;
        void running(int argc, char *argv[]);
};
#pragma once
#include "data.h"
#include "parser.h"
#include "checker.h"
#include "printer.h"
#include "logger.h"
#include "calculator.h"

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
        ~Runner();
        void running(int argc, char *argv[]);
};
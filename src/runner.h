#pragma once
#include "data.h"
#include "parser.h"
#include "checker.h"
#include "printer.h"
#include "logger.h"

class Runner
{
    Data data;
    Parser parser;
    Checker checker;
    Printer printer;
    Logger logger;
    public:
        Runner();
        ~Runner();
        void running(int argc, char *argv[]);
};
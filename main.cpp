#include <nlohmann/json.hpp>
#include <iostream>
#include <cstring>
#include "runner.h"
#include "parser.h"
#include "calculator.h"
#include "checker.h"
#include "printer.h"
#include "logger.h"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
	Runner runner;
	runner.running(argc, argv);
	// Logger &logger = Logger::getLogger();
	// logger.info("Start!");
	// Printer printer;
	// if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
	// 		printer.printHelp();
	// 		return 0;
	// }
	// Runner runner;
	// runner.running(argc, argv);
	return 0;
}



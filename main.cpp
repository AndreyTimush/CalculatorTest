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
	try {
		Runner runner;
		runner.running(argc, argv);
	} catch(std::exception &e) {
		std::string msg = "Error! ";
		Logger &logger = Logger::getLogger();
		logger.error(msg + e.what());
	}
	return 0;
}
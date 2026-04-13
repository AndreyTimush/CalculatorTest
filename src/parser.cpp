#include <cerrno>
#include <climits>
#include "parser.h"
#include "logger.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Parser::Parser(){}

void Parser::parsing(Data &data, int argc, char *argv[]) 
{
	Logger &logger = Logger::getLogger();
	logger.info("func parsing");
	json jsonArgs;
	long long firstArg = 0;
	long long secondArg = 0;
	char operation;
	try {
		jsonArgs = json::parse(argv[1]);
		firstArg = jsonArgs["firstArgument"].get<long long>();
		if (firstArg > INT_MAX || firstArg < INT_MIN) {
			throw std::runtime_error("integer overflow");
		} else {
			data.setFirstArg(static_cast<int>(firstArg));
		}
		
		std::string str = jsonArgs["operation"];
		if (str.length() != 1) {
			throw std::runtime_error("wrong operation");
		} else {
			operation = str[0];
		}

		data.setOperation(operation);
		if (jsonArgs.contains("secondArgument")) {
			secondArg = jsonArgs["secondArgument"].get<long long>();
			if (secondArg > INT_MAX || secondArg < INT_MIN) {
				throw std::runtime_error("integer overflow");
			} else {
				data.setSecondArg(static_cast<int>(secondArg));
			}
		} else {
			if (operation != '!') {
				throw std::runtime_error("Write correct operation or add second argument");
			}
		}
	} catch (const json::exception& e) {
		throw std::runtime_error(e.what());
	}
}

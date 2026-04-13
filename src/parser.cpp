#include <cerrno>
#include <climits>
#include "parser.h"
#include "logger.h"
#include <nlohmann/json.hpp>
#include <getopt.h>
#include "printer.h"

using json = nlohmann::json;

Parser::Parser(){}

void Parser::parsing(Data &data, int argc, char *argv[]) 
{
	int opt;

    int c;
    int option_index = 0;
    static struct option long_options[] = {{"help", no_argument, 0, 'h'}, {0, 0, 0, 0}};
	Printer printer;

	
    while (true) {
        c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;  // Конец опций

        switch (c) {
            case 'h':
                printer.printHelp();
                return;
            default:
                printf("Неожиданный код: %d\n", c);
                printf("Для отрицательных чисел используйте '--'\n");
                printf("Пример: ./calculator -- -5 + 3\n");
                return;
        }
    }

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

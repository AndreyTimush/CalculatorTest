#include "checker.h"
#include "logger.h"

bool Checker::checkData(Data &data)
{
	Logger &logger = Logger::getLogger();
	logger.info("func checkData");
	char op = data.getOperation();

	switch (op) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '!':
		case '^':
			return true;
			break;
		default:
			throw std::runtime_error("Write correct operation");
			break;
	}
}
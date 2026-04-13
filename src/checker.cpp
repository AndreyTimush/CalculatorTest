#include "checker.h"
#include "logger.h"

Checker::Checker(){}

void Checker::checkData(Data &data)
{
	Logger &logger = Logger::getLogger();
	logger.info("func checkData");
	// Calculator calculator;
	// char op = data.getOperation();

	// switch (op) {
	// 	case '+':
	// 	case '-':
	// 	case '*':
	// 	case '/':
	// 	case '!':
	// 	case '^':
	// 		calculator.calculating(data);
	// 		break;
	// 	default:
	// 		throw std::runtime_error("Write correct operation");
	// 		break;
	// }
}
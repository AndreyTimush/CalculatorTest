#include "calculator.h"
#include "mathlib.h"
#include "logger.h"
#include "codeException.h"

void Calculator::calculating(Data &data)
{
	Logger &logger = Logger::getLogger();
	logger.info("func calculating");
	float res = 0;
	try {
		switch (data.getOperation()) {
			case '+': 
				logger.info("func sum");
				res = mathlib::sum(data.getFirstArg(), data.getSecondArg());
				break;
			case '-':
				logger.info("func subtraction");
				res = mathlib::subtraction(data.getFirstArg(), data.getSecondArg());
				break;
			case '*':
				logger.info("func multiply");
				res = mathlib::multiply(data.getFirstArg(), data.getSecondArg());
				break;
			case '/':
				logger.info("func division");
				res = mathlib::division(data.getFirstArg(), data.getSecondArg());
				break;
			case '^':
				logger.info("func pow");
				res = mathlib::pow(data.getFirstArg(), data.getSecondArg());
				break;
			case '!':
				logger.info("func factorial");
				res = mathlib::factorial(data.getFirstArg());
				break;
			default:
				logger.error("Error! Wrong operation!");
				break;
		}
	} catch(const std::overflow_error& e) {
		throw CodeException(1, "integer overflow");
	} catch(const std::runtime_error& e) {
		throw CodeException(3, "division by zero");
	} catch(const CodeException& e) {
		throw CodeException(e.code(), e.what());
	}
	data.setResult(res);
}
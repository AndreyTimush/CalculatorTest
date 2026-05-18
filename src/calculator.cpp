#include "calculator.h"
#include "mathlib.h"
#include "logger.h"
#include "codeException.h"
#include <string>
#include "cache.h"

void Calculator::calculating(Data &data)
{
	Logger &logger = Logger::getLogger();
	logger.info("func calculating");
	std::string firstArg = std::to_string(data.getFirstArg());
	std::string operationArg(1, data.getOperation());
	std::string secondArg = std::to_string(data.getSecondArg());
	std::string keyForCache = "";
	if (operationArg == "+" || operationArg == "*") {
		std::string min = std::min(firstArg, secondArg);
		std::string max = std::max(firstArg, secondArg);
		keyForCache = min + operationArg + max;
	} else {
		keyForCache = firstArg + operationArg + secondArg;
	}
	
	auto pair = Cache::getCache().findRec(keyForCache);
	float res = 0;

	try {
		if (pair.first == "-1" && pair.second == "-1") {
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
		} else {
			res = std::stof(pair.first);
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
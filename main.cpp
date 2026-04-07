#include <nlohmann/json.hpp>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <climits>
#include "runner.h"
#include "parser.h"
#include "calculator.h"
#include "checker.h"
#include "mathlib.h"
#include "printer.h"

using json = nlohmann::json;

void Runner::running(int argc, char *argv[])
{
	Data data;
	Parser parser;
	Checker checker;
	Printer printer;
	try {
		parser.parsing(data, argc, argv);
		checker.checkData(data);
		printer.printing(data);
	} catch (std::runtime_error &err) {
		std::cout << "Error: " << err.what() << std::endl;
		return;
	}
	
}

void Parser::parsing(Data &data, int argc, char *argv[]) 
{
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
				throw std::runtime_error("Введите правильную операцию или добавьте еще один аргумент");
			}
		}
	} catch (const json::exception& e) {
		throw std::runtime_error(e.what());
	}
}

void Checker::checkData(Data &data)
{
	Calculator calculator;
	char op = data.getOperation();

	switch (op) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '!':
		case '^':
			calculator.calculating(data);
			break;
		default:
			throw std::runtime_error("Введите правильную операцию");
			break;
	}
}

void Calculator::calculating(Data &data)
{
	float res = 0;
	try {
		switch (data.getOperation()) {
			case '+': 
				res = mathlib::sum(data.getFirstArg(), data.getSecondArg());
				break;
			case '-':
				res = mathlib::subtraction(data.getFirstArg(), data.getSecondArg());
				break;
			case '*':
				res = mathlib::multiply(data.getFirstArg(), data.getSecondArg());
				break;
			case '/':
				res = mathlib::division(data.getFirstArg(), data.getSecondArg());
				break;
			case '^':
				res = mathlib::pow(data.getFirstArg(), data.getSecondArg());
				break;
			case '!':
				res = mathlib::factorial(data.getFirstArg());
				break;
			default:
				std::cout << "Неверная операция";
				break;
		}
	} catch(const std::exception& e) {
				throw;
	}
	data.setResult(res);
}

void Printer::printing(Data &data)
{
	if (data.getOperation() != '!')
		std::cout << data.getFirstArg() << " " << data.getOperation() << " " << data.getSecondArg() << " = " << data.getResult() << std::endl;
	else {
		std::cout << data.getFirstArg() << data.getOperation() << " = " << data.getResult() << std::endl;
	}
}

void Printer::printHelp()
{
	printf("Калькулятор v1.0\n");
	printf("Использование: calculator [опции] [число1] [операция] [число2]\n");
	printf("Опции:\n");
	printf("  -h    Показать эту справку\n");
	printf("Операции:\n");
	printf("  +  сложение\n");
	printf("  -  вычитание\n");
	printf("  *  умножение\n");
	printf("  /  деление\n");
	printf("  ^  возведение в степень\n");
	printf("  !  факториал (требуется только одно число)\n");
	printf("Примеры:\n");
	printf("  calculator 5 + 3 \n");
	printf("  calculator 5 !\n");
}

int main(int argc, char *argv[])
{
	Printer printer;
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
			printer.printHelp();
			return 0;
	}
	Runner runner;
	runner.running(argc, argv);
	return 0;
}



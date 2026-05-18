#include "printer.h"
#include "logger.h"

void Printer::printing(Data &data)
{
	Logger &logger = Logger::getLogger();
	logger.info("func printing");
	if (data.getOperation() != '!')
		std::cout << data.getFirstArg() << " " << data.getOperation() << " " << data.getSecondArg() << " = " << data.getResult() << std::endl;
	else {
		std::cout << data.getFirstArg() << data.getOperation() << " = " << data.getResult() << std::endl;
	}
}

void Printer::printHelp()
{
	Logger &logger = Logger::getLogger();
	logger.info("func printHelp(helper for working)");
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
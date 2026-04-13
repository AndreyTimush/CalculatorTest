#include "runner.h"

Runner::Runner(){}

Runner::~Runner(){}

void Runner::running(int argc, char *argv[])
{
	Data data;
	Parser parser;
	Checker checker;
	Printer printer;
	Logger &logger = Logger::getLogger();
	logger.info("func running");
	try {
		parser.parsing(data, argc, argv);
		checker.checkData(data);
		printer.printing(data);
	} catch (std::runtime_error &err) {
		std::string msg = "Error! ";
		logger.error(msg + err.what());
		std::cout << "Error: " << err.what() << std::endl;
		return;
	}
	
}
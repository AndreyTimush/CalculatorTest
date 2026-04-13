#include "runner.h"

Runner::Runner(){}

Runner::~Runner(){}

void Runner::running(int argc, char *argv[])
{	
	logger.info("func running");
	try {
		parser.parsing(data, argc, argv);
		checker.checkData(data);
		calculator.calculating(data);
		printer.printing(data);
	} catch (std::runtime_error &err) {
		throw;
	}
	
}
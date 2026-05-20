#include "runner.h"
#include "codeException.h"
#include "cache.h"

Runner::Runner(): logger(Logger::getLogger()){}

Runner::Runner(const Runner& other)
{
	data = other.data;
	parser = other.parser;
	checker = other.checker;
	printer = other.printer;
	calculator = other.calculator;
}

Runner& Runner::operator=(const Runner& other) 
{
	if (this != &other) {
		data = other.data;
		parser = other.parser;
		checker = other.checker;
		printer = other.printer;
		calculator = other.calculator;
	}
	return *this;
}

Runner::Runner(Runner&& other) noexcept 
{
	data = std::move(other.data);
	parser = std::move(other.parser);
	checker = std::move(other.checker);
	printer = std::move(other.printer);
	calculator = std::move(other.calculator);
}

Runner& Runner::operator=(Runner&& other) noexcept
{
	if (this != &other) {
		data = std::move(other.data);
		parser = std::move(other.parser);
		checker = std::move(other.checker);
		printer = std::move(other.printer);
		calculator = std::move(other.calculator);
	}
	return *this;
}

void Runner::running(int argc, char *argv[])
{	
	if (Database::getDb().connectToDb()) {
		Database::getDb().loadCache();
	}
	logger.info("func running");
	try {
		parser.parsing(data, argc, argv);
		checker.checkData(data);
		calculator.calculating(data);
		printer.printing(data);
	} catch (const CodeException& err) {
		throw;
	}
	
}
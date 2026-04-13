#pragma once
#include "data.h"

class Parser
{
public:
	Parser();
	void parsing(Data &data, int argc, char *argv[]);
};
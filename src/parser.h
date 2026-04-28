#pragma once
#include "data.h"

class Parser
{
public:
	Parser() = default;
	Parser(const Parser& other) = default; 
    Parser& operator=(const Parser& other) = default;
    Parser(Parser&& other) noexcept = default;
    Parser& operator=(Parser&& other) noexcept = default;
    ~Parser() = default;
	void parsing(Data &data, int argc, char *argv[]);
};
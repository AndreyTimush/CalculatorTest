#pragma once
#include "data.h"

class Printer
{
    public:
        Printer() = default;
        Printer(const Printer& other) = default; 
        Printer& operator=(const Printer& other) = default;
        Printer(Printer&& other) noexcept = default;
        Printer& operator=(Printer&& other) noexcept = default;
        ~Printer() = default;
        void printing(Data &data);
        void printHelp();
};
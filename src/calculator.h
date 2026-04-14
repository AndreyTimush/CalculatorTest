#pragma once
#include "data.h"

class Calculator
{
public: 
    Calculator() = default;
    Calculator(const Calculator& other) = default; 
    Calculator& operator=(const Calculator& other) = default;
    Calculator(Calculator&& other) noexcept = default;
    Calculator& operator=(Calculator&& other) noexcept = default;
    ~Calculator() = default;
    void calculating(Data &data);
};
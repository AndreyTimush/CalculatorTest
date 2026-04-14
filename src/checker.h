#pragma once 
#include "data.h"

class Checker
{
public: 
    Checker() = default;
    Checker(const Checker& other) = default; 
    Checker& operator=(const Checker& other) = default;
    Checker(Checker&& other) noexcept = default;
    Checker& operator=(Checker&& other) noexcept = default;
    ~Checker() = default;
    bool checkData(Data &data);
};
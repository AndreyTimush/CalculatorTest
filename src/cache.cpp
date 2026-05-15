#include "cache.h"
#include <iostream>

std::string Cache::makeKey(std::string firstNumber, std::string operation, std::string secondNumber) 
{
    return firstNumber + operation + secondNumber;
}

void Cache::addRecordToCache(std::string key, std::pair<std::string, std::string> resStat)
{
    cashMap[key] = resStat;
}

Cache& Cache::getCache() {
    static Cache cache;
    return cache;
}
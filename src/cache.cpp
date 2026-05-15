#include "cache.h"
#include <iostream>

std::string Cache::makeKey(std::string firstNumber, std::string operation, std::string secondNumber) 
{
    std::string res = "";
    if (operation == "+" || operation == "*") {
        std::string min = std::min(firstNumber, secondNumber);
        std::string max = std::max(firstNumber, secondNumber);
        res = min + operation + max;
    } else {
        res = firstNumber + operation + secondNumber;
    } 

    return res;
}

void Cache::addRecordToCache(std::string key, std::pair<std::string, std::string> resStat)
{
    cashMap[key] = resStat;
}

Cache& Cache::getCache() 
{
    static Cache cache;
    return cache;
}

std::pair<std::string, std::string> Cache::findRec(std::string findRecord) 
{
    if (cashMap.find(findRecord) != cashMap.end()) {
        return cashMap[findRecord];
    }

    return {"-1", "-1"};
}
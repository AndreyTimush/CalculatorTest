#pragma once

class Data
{
    float firstArg = 0;
    std::string operation;
    float secondArg = 0;
public:
    float getFirstArg() {return firstArg;};
    std::string getOperation() {return operation;};
    float getSecondArg() {return secondArg;};
    void setFirstArg(float firstArg) {this->firstArg = firstArg;}
    void setOperation(std::string operation) {this->operation = operation;}
    void setSecondArg(float secondArg) {this->secondArg = secondArg;}
};
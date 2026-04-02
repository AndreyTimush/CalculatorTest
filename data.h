#pragma once

class Data
{
    int firstArg = 0;
    char operation;
    int secondArg = 0;
    float result = 0;
public:
    int getFirstArg() {return firstArg;};
    char getOperation() {return operation;};
    int getSecondArg() {return secondArg;};
    float getResult() {return result;}
    void setFirstArg(int firstArg) {this->firstArg = firstArg;}
    void setOperation(char operation) {this->operation = operation;}
    void setSecondArg(int secondArg) {this->secondArg = secondArg;}
    void setResult(float res) {this->result = res;}
};
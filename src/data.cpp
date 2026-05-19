#include "data.h"

#include <utility>

Data::Data(const Data& other) {
    firstArg  = other.firstArg;
    operation = other.operation;
    secondArg = other.secondArg;
    result    = other.result;
}

Data& Data::operator=(const Data& other) {
    if (this != &other) {
        firstArg  = other.firstArg;
        operation = other.operation;
        secondArg = other.secondArg;
        result    = other.result;
    }
    return *this;
}

Data::Data(Data&& other) noexcept {
    firstArg  = std::move(other.firstArg);
    operation = std::move(other.operation);
    secondArg = std::move(other.secondArg);
    result    = std::move(other.result);
}

Data& Data::operator=(Data&& other) noexcept {
    if (this != &other) {
        firstArg  = std::move(other.firstArg);
        operation = std::move(other.operation);
        secondArg = std::move(other.secondArg);
        result    = std::move(other.result);
    }
    return *this;
}
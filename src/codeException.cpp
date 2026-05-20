#include "codeException.h"

CodeException::CodeException(int code, const std::string& msg): errorCode(code), message(msg)
{
}

const char* CodeException::what() const noexcept
{
    return message.c_str();
}

int CodeException::code() const 
{
    return errorCode;
}
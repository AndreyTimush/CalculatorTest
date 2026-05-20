#include <string>

class CodeException : public std::exception
{
private:
    int errorCode;
    std::string message;

public:
    CodeException(int code, const std::string& msg);
    int code() const;
    const char* what() const noexcept override;
};
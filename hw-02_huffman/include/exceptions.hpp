#pragma once
#include <string>

namespace Exceptions {
    class MyException : std::exception {
    public:
        std::string message;
        MyException(std::string message);
    };
}
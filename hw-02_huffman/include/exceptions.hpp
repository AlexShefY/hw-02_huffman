#pragma once
#include <string>

namespace Exceptions {
    class MyException : std::exception {
        const char* message;
    public:
        explicit MyException(const char* message);
        const char* what() const noexcept override;
    };
}
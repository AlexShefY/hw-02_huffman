#include "exceptions.hpp"

Exceptions::MyException::MyException(const char* message) : message(message) {
}


const char* Exceptions::MyException::what() const noexcept {
    return message;
}

#ifndef ARGS_EXCEPTIONS_H
#define ARGS_EXCEPTIONS_H
#include <string>
class InvalidCommandLineException{
public:
    std::string message_;
    InvalidCommandLineException(const std::string &message) : message_(message) {}
};
class CommandNotFoundException{
public:
    std::string message_;
    CommandNotFoundException(const std::string &message) : message_(message) {}
};
#endif


#ifndef ARGS_EXCEPTIONS_H
#define ARGS_EXCEPTIONS_H
#include <string>
class Exception {
public:
    std::string message_;
    Exception(const std::string &message) : message_(message) {}
};
class InvalidCommandLineException : public Exception {
public:
    InvalidCommandLineException(const std::string &message) : Exception(message) {}
};
class CommandNotFoundException: public Exception {
public:
    std::string message_;
    CommandNotFoundException(const std::string &message) : Exception(message) {}
};
#endif


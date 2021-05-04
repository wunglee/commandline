#ifndef ARGS_EXCEPTIONS_H
#define ARGS_EXCEPTIONS_H
#include <string>
class Exception {
public:
    std::string message_;
    Exception(const std::string &message) : message_(message) {}
};
class CommandNotFoundException : public Exception {
public:
    CommandNotFoundException(const std::string &message) : Exception(message) {}
};
#endif


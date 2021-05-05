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
class ValueNotFoundException : public Exception {
public:
    ValueNotFoundException(const std::string &message) : Exception(message) {}
};
class InvalidValueException : public Exception {
public:
    InvalidValueException(const std::string &message) : Exception(message) {}
};
class AnytoTypeConvertException : public Exception {
public:
    AnytoTypeConvertException(const std::string &message) : Exception(message) {}
};

#endif


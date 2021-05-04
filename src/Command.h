#ifndef ARGS_COMMAND_H
#define ARGS_COMMAND_H
#include "string"
#include "boost/any.hpp"

class Command {
public:
    const std::string flag_;
    const boost::any value_;
    Command(const std::string &flag, const boost::any &value) : flag_(flag), value_(value) {}
};


#endif //ARGS_COMMAND_H

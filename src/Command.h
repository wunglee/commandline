#ifndef ARGS_COMMAND_H
#define ARGS_COMMAND_H
#include "string"
#include "boost/any.hpp"

class Command {
public:
    std::string flag;
    boost::any value;
    Command(const std::string &flag, const boost::any &value) : flag(flag), value(value) {}
};


#endif //ARGS_COMMAND_H

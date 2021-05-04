#ifndef ARGS_COMMANDPARSER_H
#define ARGS_COMMANDPARSER_H
#include "Command.h"
#include <boost/algorithm/string/regex.hpp>
class CommandParser {
public:
    Command parse(std::string commandLine);
};


#endif //ARGS_COMMANDPARSER_H

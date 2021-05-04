#ifndef ARGS_COMMANDPARSER_H
#define ARGS_COMMANDPARSER_H
#include "Command.h"

class CommandParser {
public:
    Command parse(std::string commandLine);
};


#endif //ARGS_COMMANDPARSER_H

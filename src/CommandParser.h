#ifndef ARGS_COMMANDPARSER_H
#define ARGS_COMMANDPARSER_H
#include "Command.h"
#include "CommandBuilder.h"
class CommandParser{
public:
    Command parse(std::string commandLine);
    void addCommandValueType(std::string flag,CommandBuilder::ValueType valueType);
private:
    std::map<std::string,CommandBuilder::ValueType> commandConfig;
    CommandBuilder::ValueType getType(std::string flag);
    Command toCommand(const std::pair<std::string, std::string> &parameterPair);
    std::pair<std::string, std::string> toParameterPair(std::string &commandLine) const;
};

#endif //ARGS_COMMANDPARSER_H

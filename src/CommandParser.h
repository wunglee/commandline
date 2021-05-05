#ifndef ARGS_COMMANDPARSER_H
#define ARGS_COMMANDPARSER_H
#include "Command.h"
#include "CommandBuilder.h"
class CommandParser{
public:
    std::vector<Command> parse(std::string &commandLine);
    void addCommandValueType(const std::string &flag,const CommandBuilder::ValueType &valueType);
private:
    Command parseOneCommand(std::string &commandLine);
    std::map<std::string,CommandBuilder::ValueType> commandConfig;
    CommandBuilder::ValueType getType(const std::string &flag);
    Command toCommand(const std::pair<std::string,std::string> &parameterPair);
    std::pair<std::string, std::string> toParameterPair(std::string &commandLine) const;
};

#endif //ARGS_COMMANDPARSER_H

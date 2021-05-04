#ifndef ARGS_COMMANDPARSER_H
#define ARGS_COMMANDPARSER_H
#include "Command.h"
class CommandParser{
public:
    enum ValueType{IntegerType, StringType};
    Command parse(std::string commandLine);
    void addCommandValueType(std::string flag,ValueType valueType);
private:
    std::map<std::string,ValueType> commandConfig;
    ValueType getType(std::string flag);

    Command toCommand(const std::pair<std::string, std::string> &parameterPair);

    std::pair<std::string, std::string> toParameterPair(std::string &commandLine) const;
};
#endif //ARGS_COMMANDPARSER_H

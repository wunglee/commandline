#ifndef ARGS_COMMANDPARSER_H
#define ARGS_COMMANDPARSER_H
#include "Command.h"
class CommandBuilder{
public:
    virtual Command buildCommand(const std::pair<std::string, std::string> &parameterPair)=0;
    virtual ~CommandBuilder() {};
};
class CommandParser{
public:
    enum ValueType{IntegerType, StringType,BoolType};
    Command parse(std::string commandLine);
    void addCommandValueType(std::string flag,ValueType valueType);
private:
    std::map<std::string,ValueType> commandConfig;
    ValueType getType(std::string flag);
    Command toCommand(const std::pair<std::string, std::string> &parameterPair);
    CommandBuilder* getCommandBuilder(ValueType valueType);
    std::pair<std::string, std::string> toParameterPair(std::string &commandLine) const;
};
class IntegerCommandBuilder: public CommandBuilder{
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override;
};
class StringCommandBuilder: public CommandBuilder{
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override;
};
class BoolCommandBuilder: public CommandBuilder{
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override;
};
#endif //ARGS_COMMANDPARSER_H

#ifndef ARGS_COMMANDBUILDER_H
#define ARGS_COMMANDBUILDER_H
#include "Exceptions.h"
class CommandBuilder{
public:
    enum ValueType{IntegerType, StringType,BoolType};
    virtual Command buildCommand(const std::pair<std::string, std::string> &parameterPair)=0;
    virtual ~CommandBuilder() {};
};
class IntegerCommandBuilder: public CommandBuilder{
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override{
        if (parameterPair.second == "") {
            throw ValueNotFoundException("数值命令没有提供参数");
        }
        return Command(parameterPair.first, stoi(parameterPair.second));
    }
};
class StringCommandBuilder: public CommandBuilder{
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("字符串命令没有提供参数");
        }
        return Command(parameterPair.first, parameterPair.second);
    }
};
class BoolCommandBuilder: public CommandBuilder{
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override{
        if (parameterPair.second == "") {
            return Command(parameterPair.first, true);
        }
        if (parameterPair.second == "true" || parameterPair.second == "false") {
            return Command(parameterPair.first, parameterPair.second == "true" ? true : false);
        }
        throw InvalidValueException("无效的布尔参数值");
    }
};
class CommandBuilderFactory{
public:
    static CommandBuilder* getCommandBuilder(CommandBuilder::ValueType valueType) {
        switch (valueType) {
            case CommandBuilder::StringType:
                return new StringCommandBuilder();
            case CommandBuilder::IntegerType:
                return new IntegerCommandBuilder();
            case CommandBuilder::BoolType:
                return new BoolCommandBuilder();
            default:
                return nullptr;
        }
    }
};
#endif //ARGS_COMMANDBUILDER_H

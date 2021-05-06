#ifndef ARGS_COMMANDBUILDER_H
#define ARGS_COMMANDBUILDER_H
#include "Convertors.h"
#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>

class CommandBuilder {
public:
    enum ValueType {
        IntegerType, StringType, BoolType, StringListType, IntegerListType,BoolListType
    };
    virtual Command buildCommand(const std::pair<std::string, std::string> &parameterPair) = 0;
    virtual ~CommandBuilder() {};
};
class ListCommandBuilder : public CommandBuilder {
public:
    template<class T>
    std::vector<T> toListValue(const std::pair<std::string, std::string> &parameterPair,
                               const std::function<T(std::string)> &convertToType) const {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("命令没有提供参数");
        }
        std::vector<std::string> stringTokens;
        split_regex(stringTokens, parameterPair.second, boost::regex(","));
        std::vector<T> result;
        for (std::string token:stringTokens) {
            boost::trim(token);
            if (token == "") continue;
            result.push_back(convertToType(token));
        }
        return result;
    }
};
class StringCommandBuilder : public CommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("字符串命令没有提供参数");
        }
        return Command(parameterPair.first, Convertors::converToString(parameterPair.second));
    }
};
class StringListCommandBuilder : public ListCommandBuilder {
protected:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        std::vector<std::string> result = toListValue<std::string>(parameterPair, Convertors::converToString);
        return Command(parameterPair.first, result);
    }
};
class IntegerCommandBuilder : public CommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("数值命令没有提供参数");
        }
        return Command(parameterPair.first, Convertors::convertToInt(parameterPair.second));
    }
};
class IntegerListCommandBuilder : public ListCommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        std::vector<int> result = toListValue<int>(parameterPair,Convertors::convertToInt);
        return Command(parameterPair.first, result);
    }
};
class BoolCommandBuilder : public CommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        bool value = true;
        if (parameterPair.second != "") {
            std::string boolString = parameterPair.second;
            value = Convertors::convertTobool(boolString);
        }
        return Command(parameterPair.first,value);
    }
};
class BoolListCommandBuilder : public ListCommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        std::vector<bool> result = toListValue<bool>(parameterPair,Convertors::convertTobool);
        return Command(parameterPair.first, result);
    }
};
class CommandBuilderFactory {
public:
    static CommandBuilder *getCommandBuilder(CommandBuilder::ValueType valueType) {
        switch (valueType) {
            case CommandBuilder::StringType:
                return new StringCommandBuilder();
            case CommandBuilder::IntegerType:
                return new IntegerCommandBuilder();
            case CommandBuilder::BoolType:
                return new BoolCommandBuilder();
            case CommandBuilder::StringListType:
                return new StringListCommandBuilder();
            case CommandBuilder::IntegerListType:
                return new IntegerListCommandBuilder();
            case CommandBuilder::BoolListType:
                return new BoolListCommandBuilder();
            default:
                return nullptr;
        }
    }
};
#endif //ARGS_COMMANDBUILDER_H

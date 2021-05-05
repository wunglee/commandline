#ifndef ARGS_COMMANDBUILDER_H
#define ARGS_COMMANDBUILDER_H

#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

class CommandBuilder {
public:
    enum ValueType {
        IntegerType, StringType, BoolType, StringListType, IntegerListType,BoolListType
    };

    virtual Command buildCommand(const std::pair<std::string, std::string> &parameterPair) = 0;

    virtual ~CommandBuilder() {};
};

class IntegerCommandBuilder : public CommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("数值命令没有提供参数");
        }
        return Command(parameterPair.first, stoi(parameterPair.second));
    }
};

class StringCommandBuilder : public CommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("字符串命令没有提供参数");
        }
        return Command(parameterPair.first, std::string(parameterPair.second));
    }
};

class BoolCommandBuilder : public CommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        if (parameterPair.second == "") {
            return Command(parameterPair.first, true);
        }
        if (parameterPair.second == "true" || parameterPair.second == "false") {
            return Command(parameterPair.first, parameterPair.second == "true" ? true : false);
        }
        throw InvalidValueException("无效的布尔参数值");
    }
};

class ListCommandBuilder : public CommandBuilder {
public:
    template<class T>
    std::vector<T> toListValue(const std::pair<std::string, std::string> &parameterPair,
                                         const std::function<T(std::string)> &convertToType) const {
        if (parameterPair.second == "") {
            throw ValueNotFoundException("命令没有提供参数");
        }
        std::__1::vector<std::string> stringTokens;
        split_regex(stringTokens, parameterPair.second, boost::regex(","));
        std::__1::vector<T> result;
        for (std::string token:stringTokens) {
            boost::trim(token);
            if (token == "") continue;
            result.push_back(convertToType(token));
        }
        return result;
    }
};

class StringListCommandBuilder : public ListCommandBuilder {
protected:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        const std::function<std::string(std::string)> &convertToString=[](std::string s)->std::string{ boost::trim(s); return s; };
        std::vector<std::string> result = toListValue<std::string>(parameterPair,convertToString);
        return Command(parameterPair.first, result);
    }
};

class IntegerListCommandBuilder : public ListCommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        const std::function<int(std::string)> &convertToInt=[](std::string s)->int{ return std::stoi(s); };
        std::vector<int> result = toListValue<int>(parameterPair,convertToInt);
        return Command(parameterPair.first, result);
    }
};
class BoolListCommandBuilder : public ListCommandBuilder {
public:
    Command buildCommand(const std::pair<std::string, std::string> &parameterPair) override {
        const std::function<bool(std::string)> &convertTobool=[](std::string s)->bool{
            if(s!="true"&&s!="false"){
                throw InvalidValueException("无效的布尔参数值");
            }
            return (s=="true")?true:false;
        };
        std::vector<bool> result = toListValue<bool>(parameterPair,convertTobool);
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

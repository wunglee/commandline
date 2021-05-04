#include "CommandParser.h"
#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace boost;

Command CommandParser::parse(std::string commandLine) {
    return toCommand(toParameterPair(commandLine));
}

pair<string, string> CommandParser::toParameterPair(string &commandLine) const {
    trim(commandLine);
    vector<string> commandsTokens;
    split_regex(commandsTokens, commandLine, regex("\\s+"));
    if (!regex_match(commandsTokens[0], regex("-\\w+"))) {
        throw CommandNotFoundException("没有查找到命令");
    }
    string flag = commandsTokens[0].substr(1);
    pair<string, string> parameterPair;
    if (commandsTokens.size() > 1) {
        parameterPair = pair<string, string>(flag, commandsTokens[1]);
    } else {
        parameterPair = pair<string, string>(flag, "");
    }
    return parameterPair;
}

Command CommandParser::toCommand(const pair<string, string> &parameterPair) {
    ValueType valueType = getType(parameterPair.first);
    CommandBuilder *commandBuilder = getCommandBuilder(valueType);
    if (commandBuilder == nullptr) {
        return Command(parameterPair.first, parameterPair.second);
    }
    Command command = commandBuilder->buildCommand(parameterPair);
    delete commandBuilder;
    return command;
}

CommandParser::ValueType CommandParser::getType(std::string flag) {
    if (commandConfig.find(flag) != commandConfig.end()) {
        return commandConfig.at(flag);
    } else {
        return CommandParser::StringType;
    }
}

void CommandParser::addCommandValueType(std::string flag, CommandParser::ValueType valueType) {
    commandConfig[flag] = valueType;
}

CommandBuilder *CommandParser::getCommandBuilder(CommandParser::ValueType valueType) {
    switch (valueType) {
        case StringType:
            return new StringCommandBuilder();
        case IntegerType:
            return new IntegerCommandBuilder();
        case BoolType:
            return new BoolCommandBuilder();
        default:
            return nullptr;
    }
}

Command IntegerCommandBuilder::buildCommand(const pair<std::string, std::string> &parameterPair) {
    if (parameterPair.second == "") {
        throw ValueNotFoundException("数值命令没有提供参数");
    }
    return Command(parameterPair.first, stoi(parameterPair.second));
}

Command StringCommandBuilder::buildCommand(const pair<std::string, std::string> &parameterPair) {
    if (parameterPair.second == "") {
        throw ValueNotFoundException("字符串命令没有提供参数");
    }
    return Command(parameterPair.first, parameterPair.second);
}

Command BoolCommandBuilder::buildCommand(const pair<std::string, std::string> &parameterPair) {
    if (parameterPair.second == "") {
        return Command(parameterPair.first, true);
    }
    if (parameterPair.second == "true" || parameterPair.second == "false") {
        return Command(parameterPair.first, parameterPair.second == "true" ? true : false);
    }
    throw InvalidValueException("无效的布尔参数值");
}

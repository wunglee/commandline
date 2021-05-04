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
    split_regex( commandsTokens, commandLine, regex("\\s+"));
    if(!regex_match(commandsTokens[0],regex("-\\w+"))){
        throw CommandNotFoundException("没有查找到命令");
    }
    string flag = commandsTokens[0].substr(1);
    pair<string,string> parameterPair(flag,commandsTokens[1]);
    return parameterPair;
}

Command CommandParser::toCommand(const pair<string, string> &parameterPair) {
    ValueType valueType= getType(parameterPair.first);
    switch (valueType) {
        case StringType:return Command(parameterPair.first,parameterPair.second);
        case IntegerType:return Command(parameterPair.first, stoi(parameterPair.second));
        default:
            return Command(parameterPair.first, parameterPair.second);
    }
}

CommandParser::ValueType CommandParser::getType(std::string flag) {
    return commandConfig.at(flag);
}

void CommandParser::addCommandValueType(std::string flag, CommandParser::ValueType valueType) {
    commandConfig[flag]=valueType;
}

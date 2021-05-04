#include "CommandParser.h"
#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace boost;
Command CommandParser::parse(std::string commandLine) {
    trim(commandLine);
    vector<string> commandsTokens;
    split_regex( commandsTokens, commandLine, regex("\\s+"));
    if(!regex_match(commandsTokens[0],regex("-\\w+"))){
        throw CommandNotFoundException("没有查找到命令");
    }
    string flag = commandsTokens[0].substr(1);
    ValueType valueType=getType(flag);
    switch (valueType) {
        case StringType:return Command(flag,commandsTokens[1]);
        case IntegerType:return Command(flag,std::stoi(commandsTokens[1]));
    }
}

CommandParser::ValueType CommandParser::getType(std::string flag) {
    map<string,ValueType> commandConfig;
    commandConfig["l"]=CommandParser::StringType;
    commandConfig["p"]=CommandParser::IntegerType;
    return commandConfig.at(flag);
}

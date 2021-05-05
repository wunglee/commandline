#include "CommandParser.h"
#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace boost;

Command CommandParser::parseOneCommand(std::string &commandLine) {
    return toCommand(toParameterPair(commandLine));
}
vector<Command> CommandParser::parse(std::string &commandLine) {
    vector<Command> commands;
    if (!regex_search(commandLine, regex("-\\w+"))) {
        throw CommandNotFoundException("没有查找到命令");
    }
    vector<string> commandsTokens;
    split_regex(commandsTokens, commandLine, regex("-"));
    for(string oneCommandLine:commandsTokens){
        trim(oneCommandLine);
        if(oneCommandLine==""){
            continue;
        }
        commands.push_back(parseOneCommand(oneCommandLine));
    }
    return commands;
}
pair<string, string> CommandParser::toParameterPair(string &oneCommandLine) const {
    int white_space_position = oneCommandLine.find(" ");
    string flag=oneCommandLine;
    string value="";
    if(white_space_position!=-1){
        flag=oneCommandLine.substr(0,white_space_position);
        value=oneCommandLine.substr(white_space_position+1);
    }
    trim(flag);
    trim(value);
    return pair<string, string>(flag, value);
}

Command CommandParser::toCommand(const pair<string, string> &parameterPair) {
    CommandBuilder::ValueType valueType = getType(parameterPair.first);
    CommandBuilder *commandBuilder = CommandBuilderFactory::getCommandBuilder(valueType);
    if (commandBuilder == nullptr) {
        return Command(parameterPair.first, parameterPair.second);
    }
    Command command = commandBuilder->buildCommand(parameterPair);
    delete commandBuilder;
    return command;
}

CommandBuilder::ValueType CommandParser::getType(const std::string &flag) {
    if (commandConfig.find(flag) != commandConfig.end()) {
        return commandConfig.at(flag);
    } else {
        return CommandBuilder::StringType;
    }
}

void CommandParser::addCommandValueType(const std::string &flag, const CommandBuilder::ValueType &valueType) {
    commandConfig[flag] = valueType;
}




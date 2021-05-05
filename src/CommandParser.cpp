#include "CommandParser.h"
#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace boost;

Command CommandParser::parse(std::string &commandLine) {
    return toCommand(toParameterPair(commandLine));
}
vector<Command> CommandParser::parseAll(std::string &commandLine) {
    vector<Command> v;
    v.push_back(Command("l",std::string("wer")));
    v.push_back(Command("s",std::string("rtt")));
    return v;
}
pair<string, string> CommandParser::toParameterPair(string &commandLine) const {
    trim(commandLine);
    vector<string> commandsTokens;
    split_regex(commandsTokens, commandLine, regex("\\s+"));
    if (!regex_match(commandsTokens[0], regex("-\\w+"))) {
        throw CommandNotFoundException("没有查找到命令");
    }
    string flag = commandsTokens[0].substr(1);
    if (commandsTokens.size() > 1) {
        return pair<string, string>(flag, commandsTokens[1]);
    } else {
        return pair<string, string>(flag, "");
    }
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




//
// Created by 王立 on 2021/5/4.
//

#include "CommandParser.h"
using namespace std;
using namespace boost;
Command CommandParser::parse(std::string commandLine) {
    vector<string> commandsTokens;
    boost::split_regex( commandsTokens, commandLine, regex(" "));
    string flag = commandsTokens[0].substr(1);
    string value = commandsTokens[1];
    return Command(flag,value);
}

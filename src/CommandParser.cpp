#include "CommandParser.h"
#include "Exceptions.h"
using namespace std;
using namespace boost;
Command CommandParser::parse(std::string commandLine) {
    if(commandLine.find("-", 0)!=0){
        throw InvalidCommandLineException("命令行没有以'-'开头");
    }
    vector<string> commandsTokens;
    boost::split_regex( commandsTokens, commandLine, regex(" "));
    string flag = commandsTokens[0].substr(1);
    string value = commandsTokens[1];
    return Command(flag,value);
}

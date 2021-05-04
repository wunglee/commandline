#include "CommandParser.h"
#include "Exceptions.h"
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>
using namespace std;
using namespace boost;
Command CommandParser::parse(std::string commandLine) {
    trim(commandLine);
    if(commandLine.find("-", 0)!=0){
        throw InvalidCommandLineException("命令行没有以'-'开头");
    }
    vector<string> commandsTokens;
    boost::split_regex( commandsTokens, commandLine, regex("\\s+"));
    string flag = commandsTokens[0].substr(1);
    return Command(flag,commandsTokens[1]);
}

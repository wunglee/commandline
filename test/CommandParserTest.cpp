#include "gtest/gtest.h"
#include "../src/CommandParser.h"
#include "../src/Exceptions.h"
void testStringValueCommand(const char *commandline, const char *flag, const char *value){
    CommandParser commandParser;
    Command result = commandParser.parse(commandline);
    ASSERT_EQ(result.flag_, flag);
    ASSERT_EQ(boost::any_cast<std::string>(result.value_), value);
}
TEST(单个命令,字符型命令){
    testStringValueCommand("-l local/usr", "l", "local/usr");
}
TEST(单个命令,字符型命令允许在flag和value之间存在多个空格){
    testStringValueCommand("-l   local/usr", "l", "local/usr");
}
TEST(单个命令,字符型命令允许在commandline前后存在多个空格){
    testStringValueCommand("   -l   local/usr   ", "l", "local/usr");
}
TEST(单个命令,字符型命令是否以横线开头){
    CommandParser commandParser;
    ASSERT_THROW(commandParser.parse("l local/usr"),InvalidCommandLineException);
    ASSERT_THROW(commandParser.parse("+l local/usr"),InvalidCommandLineException);
}
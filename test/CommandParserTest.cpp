#include "gtest/gtest.h"
#include "../src/CommandParser.h"
#include "../src/Exceptions.h"
template <typename T>
void testCommandValue(const char *commandline, const char *flag, const T value,CommandParser& commandParser){
    Command result = commandParser.parse(commandline);
    ASSERT_EQ(result.flag_, flag);
    ASSERT_EQ(boost::any_cast<T>(result.value_), value);
}
TEST(单个命令,字符型命令){
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandParser::StringType);
    testCommandValue<std::string>("-l local/usr", "l", "local/usr",commandParser);
}
TEST(单个命令,字符型命令允许在flag和value之间存在多个空格){
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandParser::StringType);
    testCommandValue<std::string>("-l   local/usr", "l", "local/usr",commandParser);
}
TEST(单个命令,字符型命令允许在commandline前后存在多个空格){
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandParser::StringType);
    testCommandValue<std::string>("   -l   local/usr   ", "l", "local/usr",commandParser);
}
template <typename E>
void testException(const char *commandline,CommandParser& commandParser) {
    ASSERT_THROW(commandParser.parse(commandline), E);
}
TEST(单个命令,字符型命令是否以横线开头){
    CommandParser commandParser;
    testException<CommandNotFoundException>("l local/usr",commandParser);
    testException<CommandNotFoundException>("+l local/usr",commandParser);
    testException<CommandNotFoundException>("   l     local/usr   ",commandParser);
    testException<CommandNotFoundException>("   ",commandParser);
    testException<CommandNotFoundException>(" - ",commandParser);
}
TEST(单个命令,整型命令){
    CommandParser commandParser;
    commandParser.addCommandValueType("p",CommandParser::IntegerType);
    testCommandValue<int>("-p 8080", "p", 8080,commandParser);
}
TEST(单个命令,布尔类型使用默认参数){
    CommandParser commandParser;
    commandParser.addCommandValueType("d",CommandParser::BoolType);
    testCommandValue<bool>("-d", "d", true,commandParser);
}
TEST(单个命令,布尔类型使用指定参数){
    CommandParser commandParser;
    commandParser.addCommandValueType("d",CommandParser::BoolType);
    testCommandValue<bool>("-d false", "d", false,commandParser);
    testCommandValue<bool>("-d true", "d", true,commandParser);
}
TEST(单个命令,布尔类型使用非指定参数){
    CommandParser commandParser;
    commandParser.addCommandValueType("d",CommandParser::BoolType);
    testException<InvalidValueException>(" -d ee ",commandParser);
}
TEST(单个命令,没有指定参数) {
    CommandParser commandParser;
    commandParser.addCommandValueType("l", CommandParser::StringType);
    testException<ValueNotFoundException>("-l", commandParser);
    commandParser.addCommandValueType("p", CommandParser::IntegerType);
    testException<ValueNotFoundException>("-p", commandParser);
}
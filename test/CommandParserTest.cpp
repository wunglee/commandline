#include "gtest/gtest.h"
#include "../src/CommandParser.h"
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
template <typename T>
void testCommandValue(std::string commandline,const std::string flag, const T value,CommandParser& commandParser){
    Command result = commandParser.parse(commandline);
    ASSERT_EQ(result.flag_, flag);
    ASSERT_EQ(boost::any_cast<T>(result.value_), value);
}
template <typename T>
boost::optional<T> findResult(std::string flag,std::vector<Command> &results) {
    for(Command command:results) {
        if (flag == command.flag_) {
            std::string s1= typeid(T).name();
            std::string s2= command.value_.type().name();
            if (typeid(T) == command.value_.type()) {
                return boost::any_cast<T>(command.value_);
            } else {
                throw AnytoTypeConvertException("any to type格式转换错误");
            }
        }
    }
    return boost::none;
}
TEST(单个命令,字符型命令){
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandBuilder::StringType);
    testCommandValue<std::string>("-l local/usr", "l", "local/usr",commandParser);
}
TEST(单个命令,字符型命令允许在flag和value之间存在多个空格){
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandBuilder::StringType);
    testCommandValue<std::string>("-l   local/usr", "l", "local/usr",commandParser);
}
TEST(单个命令,字符型命令允许在commandline前后存在多个空格){
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandBuilder::StringType);
    testCommandValue<std::string>("   -l   local/usr   ", "l", "local/usr",commandParser);
}
template <typename E>
void testException(std::string commandline,CommandParser& commandParser) {
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
    commandParser.addCommandValueType("p",CommandBuilder::IntegerType);
    testCommandValue<int>("-p 8080", "p", 8080,commandParser);
}
TEST(单个命令,布尔类型使用默认参数){
    CommandParser commandParser;
    commandParser.addCommandValueType("d",CommandBuilder::BoolType);
    testCommandValue<bool>("-d", "d", true,commandParser);
}
TEST(单个命令,布尔类型使用指定参数){
    CommandParser commandParser;
    commandParser.addCommandValueType("d",CommandBuilder::BoolType);
    testCommandValue<bool>("-d false", "d", false,commandParser);
    testCommandValue<bool>("-d true", "d", true,commandParser);
}
TEST(单个命令,布尔类型使用非指定参数){
    CommandParser commandParser;
    commandParser.addCommandValueType("d",CommandBuilder::BoolType);
    testCommandValue<std::string>("-l   local/usr", "l", "local/usr",commandParser);
}
TEST(单个命令,没有指定参数异常) {
    CommandParser commandParser;
    commandParser.addCommandValueType("l", CommandBuilder::StringType);
    testException<ValueNotFoundException>("-l", commandParser);
    commandParser.addCommandValueType("p", CommandBuilder::IntegerType);
    testException<ValueNotFoundException>("-p", commandParser);
}
TEST(多个命令,多个字符型命令) {
    CommandParser commandParser;
    commandParser.addCommandValueType("l",CommandBuilder::StringType);
    commandParser.addCommandValueType("s",CommandBuilder::StringType);
    std::string commandline="-l wer -s rtt";
    std::vector<Command> results = commandParser.parseAll(commandline);
    ASSERT_EQ(findResult<std::string>("l",results), std::string("wer"));
    ASSERT_EQ(findResult<std::string>("s",results), std::string("rtt"));
}
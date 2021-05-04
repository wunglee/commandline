#include "gtest/gtest.h"
#include "../src/CommandParser.h"
#include "../src/Exceptions.h"
template <typename T>
void testCommandValue(const char *commandline, const char *flag, const T value){
    Command result = CommandParser().parse(commandline);
    ASSERT_EQ(result.flag_, flag);
    ASSERT_EQ(boost::any_cast<T>(result.value_), value);
}
TEST(单个命令,字符型命令){
    testCommandValue<std::string>("-l local/usr", "l", "local/usr");
}
TEST(单个命令,字符型命令允许在flag和value之间存在多个空格){
    testCommandValue<std::string>("-l   local/usr", "l", "local/usr");
}
TEST(单个命令,字符型命令允许在commandline前后存在多个空格){
    testCommandValue<std::string>("   -l   local/usr   ", "l", "local/usr");
}
template <typename E>
void testException(const char *commandline) {
    ASSERT_THROW(CommandParser().parse(commandline), E);
}
TEST(单个命令,字符型命令是否以横线开头){
    testException<CommandNotFoundException>("l local/usr");
    testException<CommandNotFoundException>("+l local/usr");
    testException<CommandNotFoundException>("   l     local/usr   ");
    testException<CommandNotFoundException>("   ");
    testException<CommandNotFoundException>(" - ");
}
TEST(单个命令,整型命令){
    testCommandValue<int>("-p 8080", "p", 8080);
}

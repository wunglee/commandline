#include "gtest/gtest.h"
#include "../src/CommandParser.h"
#include "../src/Exceptions.h"
TEST(单个命令,字符型命令){
    CommandParser commandParser;
    Command result = commandParser.parse("-l local/usr");
    ASSERT_EQ(result.flag_,"l");
    ASSERT_EQ(boost::any_cast<std::string>(result.value_),"local/usr");
}
TEST(单个命令,字符型命令是否以横线开头){
    CommandParser commandParser;
    ASSERT_THROW(commandParser.parse("l local/usr"),InvalidCommandLineException);
    ASSERT_THROW(commandParser.parse("+l local/usr"),InvalidCommandLineException);
}
TEST(单个命令,字符型命令允许在flag和value之间存在多个空格){
    CommandParser commandParser;
    Command result = commandParser.parse("-l    local/usr");
    ASSERT_EQ(result.flag_,"l");
    ASSERT_EQ(boost::any_cast<std::string>(result.value_),"local/usr");
}
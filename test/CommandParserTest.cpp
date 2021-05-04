#include "gtest/gtest.h"
#include "../src/CommandParser.h"
TEST(单个命令,字符型命令){
    CommandParser commandParser;
    Command result = commandParser.parse("-l local/usr");
    ASSERT_EQ(result.flag,"l");
    ASSERT_EQ(boost::any_cast<const char*>(result.value),"local/usr");
}

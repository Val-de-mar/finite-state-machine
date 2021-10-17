
#include <iostream>
#include <gtest/gtest.h>

#include "suffix.h"

class LongestPartsTest : public ::testing::Test {
};

TEST(LongestPartsTest, getAlphabetSet) {
    ASSERT_TRUE((getAlphabetSet(std::string(".*ab"), std::string("*.de"), std::string("+ad")) == std::set<char>{'a', 'b', 'd', 'e'}));
}

TEST(LongestPartsTest, longestPrefix) {
    ASSERT_TRUE((longestPrefix(".+*abc", "aaabc") == 3));
    ASSERT_TRUE((longestPrefix(".+*abc", "bcc") == 2));
    ASSERT_TRUE((longestPrefix(".+*abc", "aaac") == 4));
}
TEST(LongestPartsTest, longestSuffix) {
    ASSERT_TRUE((longestSuffix(".+*abc", "aaabc") == 2));
    ASSERT_TRUE((longestSuffix(".+*abc", "abb") == 0));
    ASSERT_TRUE((longestSuffix(".+*abc", "aaac") == 4));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

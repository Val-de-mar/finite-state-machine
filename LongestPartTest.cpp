
#include <iostream>
#include <gtest/gtest.h>

#include "suffix.h"

class LongestPartsTest : public ::testing::Test {
};

TEST(LongestPartsTest, getAlphabetSet) {
    ASSERT_TRUE((getAlphabetSet(std::string(".*ab"), std::string("*.de"), std::string("+ad")) == std::set<char>{'a', 'b', 'd', 'e'}));
}

TEST(LongestPartsTest, longestPrefixPolish) {
    ASSERT_TRUE((longestPrefixPolish(".+*abc", "aaabc") == 3));
    ASSERT_TRUE((longestPrefixPolish(".+*abc", "bcc") == 2));
    ASSERT_TRUE((longestPrefixPolish(".+*abc", "aaac") == 4));
}
TEST(LongestPartsTest, longestSuffixPolish) {
    ASSERT_TRUE((longestSuffixPolish(".+*abc", "aaabc") == 2));
    ASSERT_TRUE((longestSuffixPolish(".+*abc", "abb") == 0));
    ASSERT_TRUE((longestSuffixPolish(".+*abc", "aaac") == 4));
}
TEST(LongestPartsTest, longestPrefixReversedPolish) {
    ASSERT_TRUE((longestPrefixReversedPolish("a*b+c.", "aaabc") == 3));
    ASSERT_TRUE((longestPrefixReversedPolish("a*b+c.", "bcc") == 2));
    ASSERT_TRUE((longestPrefixReversedPolish("a*b+c.", "aaac") == 4));
}
TEST(LongestPartsTest, longestSuffixReversedPolish) {
    ASSERT_TRUE((longestSuffixReversedPolish("a*b+c.", "aaabc") == 2));
    ASSERT_TRUE((longestSuffixReversedPolish("a*b+c.", "abb") == 0));
    ASSERT_TRUE((longestSuffixReversedPolish("a*b+c.", "aaac") == 4));
}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

//
// Created by val-de-mar on 20/9/21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "poland.h"

class QuickTest : public ::testing::Test {
};

bool func() {
    return true;
}

TEST(QuickTest, RidOfEpsilonAndEq)
{
    Machine<char> machine(5u);
    machine.add_trans(0, 1, 'a');
    machine.add_trans(0, 3, 'b');
    machine.add_trans(3, 1, 'a');
    machine.add_trans(3, 2, char(0));
    machine.add_trans(3, 4, char(0));
    machine.add_trans(1, 2, 'b');
    machine.add_trans(2, 4, 'a');
    machine.makeTerminal(4);
    auto res = machine.ridOfEpsilon();
    Machine<char> ans(5u);
    ans.add_trans(0, 1, 'a');
    ans.add_trans(0, 3, 'b');
    ans.add_trans(3, 1, 'a');
    ans.add_trans(3, 4, 'a');
    ans.add_trans(1, 2, 'b');
    ans.add_trans(2, 4, 'a');
    ans.makeTerminal(4);
    ans.makeTerminal(3);
    ASSERT_TRUE(ans == res);
    ans.add_cond();
    ASSERT_FALSE(ans == res);
}


TEST(QuickTest, DeterminationTest) {
    std::string c = "+.ab.ba", d = "+.aa.bb";
    std::string regex = ".*" + d + "*.." + c +"*" + d + "." + c + "*" + d;
    auto res = fromPoland(regex).determine();
    ASSERT_FALSE(res.check("baaababaaabbaabaabbbabbbabaa"));
    ASSERT_FALSE(res.check("ababbbbbabaabaaabba"));
    ASSERT_TRUE(res.check("aabbbbaaaaabaabababaababbaba"));
    ASSERT_TRUE(res.check("bbbabbabababbaababaaaaabbb"));
    ASSERT_FALSE(res.check("abbbaaabbbbbaabbbaabbbbbaabab"));
    ASSERT_FALSE(res.check("bbaabaababaabbaababaaababaaba"));
    ASSERT_FALSE(res.check("bbbabaabbbbbbbaaababaaa"));
    ASSERT_TRUE(res.check("aaabbbababaaaaab"));
    ASSERT_FALSE(res.check("bababbbbbbaaabbababbaabbbaa"));
    ASSERT_TRUE(res.check("baabbbababaababbbbbbba"));
    ASSERT_FALSE(res.check("abbbbaababbbbaaabbbbbbbbb"));
    ASSERT_FALSE(res.check("ababaaabbaabbaabbbbaaabbba"));
    ASSERT_FALSE(res.check("aabaaabaaaabaababbbababaaba"));
    ASSERT_FALSE(res.check("aabababaaaaabbbaababab"));
    ASSERT_TRUE(res.check("bbaababababbbbaabbabaaaa"));
    ASSERT_FALSE(res.check("abaababbaaaaaaba"));
    ASSERT_FALSE(res.check("baabbbbabaabbbabbaaaabbaa"));
    ASSERT_FALSE(res.check("bbaabbbbabbaaaabaaabbbaba"));
    ASSERT_FALSE(res.check("abaabbabbabbabaababaa"));
    ASSERT_FALSE(res.check("bbabbaabaaaaabaabababbaaaab"));
}

TEST(QuickTest, MinimiseTest)
{
    std::string c = "+.ab.ba", d = "+.aa.bb";
    std::string regex = ".*" + d + "*.." + c +"*" + d + "." + c + "*" + d;
    auto pre = fromPoland(regex).determine();
    auto res = pre.minimise();

    ASSERT_FALSE(pre == res);

    ASSERT_FALSE(res.check("baaababaaabbaabaabbbabbbabaa"));
    ASSERT_FALSE(res.check("ababbbbbabaabaaabba"));
    ASSERT_TRUE(res.check("aabbbbaaaaabaabababaababbaba"));
    ASSERT_TRUE(res.check("bbbabbabababbaababaaaaabbb"));
    ASSERT_FALSE(res.check("abbbaaabbbbbaabbbaabbbbbaabab"));
    ASSERT_FALSE(res.check("bbaabaababaabbaababaaababaaba"));
    ASSERT_FALSE(res.check("bbbabaabbbbbbbaaababaaa"));
    ASSERT_TRUE(res.check("aaabbbababaaaaab"));
    ASSERT_FALSE(res.check("bababbbbbbaaabbababbaabbbaa"));
    ASSERT_TRUE(res.check("baabbbababaababbbbbbba"));
    ASSERT_FALSE(res.check("abbbbaababbbbaaabbbbbbbbb"));
    ASSERT_FALSE(res.check("ababaaabbaabbaabbbbaaabbba"));
    ASSERT_FALSE(res.check("aabaaabaaaabaababbbababaaba"));
    ASSERT_FALSE(res.check("aabababaaaaabbbaababab"));
    ASSERT_TRUE(res.check("bbaababababbbbaabbabaaaa"));
    ASSERT_FALSE(res.check("abaababbaaaaaaba"));
    ASSERT_FALSE(res.check("baabbbbabaabbbabbaaaabbaa"));
    ASSERT_FALSE(res.check("bbaabbbbabbaaaabaaabbbaba"));
    ASSERT_FALSE(res.check("abaabbabbabbabaababaa"));
    ASSERT_FALSE(res.check("bbabbaabaaaaabaabababbaaaab"));
}

TEST(QuickTest, NonExistantEdgeTest) {
    auto res = fromPoland("*.+.+ababa").determine();
    ASSERT_FALSE(res.check("c"));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

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

TEST(QuickTest, EqualityTest) {
    DetMachine<char> machine1(4u);
    machine1.setTransition(0, 2, 'a');
    machine1.setTransition(0, 1, 'b');
    machine1.setTransition(1, 3, 'a');
    machine1.setTransition(1, 0, 'b');
    machine1.setTransition(2, 0, 'a');
    machine1.setTransition(2, 3, 'b');
    machine1.setTransition(3, 1, 'a');
    machine1.setTransition(3, 2, 'b');

    machine1.makeTerminal(0);

    DetMachine<char> machine2(4u);
    machine2.setTransition(0, 2, 'a');
    machine2.setTransition(0, 1, 'b');
    machine2.setTransition(1, 3, 'a');
    machine2.setTransition(1, 0, 'b');
    machine2.setTransition(2, 0, 'a');
    machine2.setTransition(2, 3, 'b');
    machine2.setTransition(3, 1, 'a');
    machine2.setTransition(3, 2, 'b');

    machine2.makeTerminal(0);

    ASSERT_TRUE(machine1 == machine2);

}


TEST(QuickTest, RidOfEpsilonAndEq)
{
    Machine<char> machine(5u);
    machine.addTransition(0, 1, 'a');
    machine.addTransition(0, 3, 'b');
    machine.addTransition(3, 1, 'a');
    machine.addTransition(3, 2, char(0));
    machine.addTransition(3, 4, char(0));
    machine.addTransition(1, 2, 'b');
    machine.addTransition(2, 4, 'a');
    machine.makeTerminal(4);
    auto res = machine.ridOfEpsilon();
    Machine<char> ans(5u);
    ans.addTransition(0, 1, 'a');
    ans.addTransition(0, 3, 'b');
    ans.addTransition(3, 1, 'a');
    ans.addTransition(3, 4, 'a');
    ans.addTransition(1, 2, 'b');
    ans.addTransition(2, 4, 'a');
    ans.makeTerminal(4);
    ans.makeTerminal(3);
    ASSERT_TRUE(ans == res);
    ans.addCondition();
    ASSERT_FALSE(ans == res);
}


TEST(QuickTest, DeterminationTest) {
    std::string regex = "+..abb..aba";
    auto res = fromPoland(regex).determine();

    DetMachine<char> machine(5u);
    machine.setTransition(0, 1, 'a');
    machine.setTransition(1, 2, 'b');
    machine.setTransition(2, 3, 'a');
    machine.setTransition(2, 4, 'b');

    machine.makeTerminal(3);
    machine.makeTerminal(4);

    ASSERT_TRUE(machine == res);
}

TEST(QuickTest, CheckTest) {
    DetMachine<char> machine(4u);
    machine.setTransition(0, 2, 'a');
    machine.setTransition(0, 1, 'b');
    machine.setTransition(1, 3, 'a');
    machine.setTransition(1, 0, 'b');
    machine.setTransition(2, 0, 'a');
    machine.setTransition(2, 3, 'b');
    machine.setTransition(3, 1, 'a');
    machine.setTransition(3, 2, 'b');

    machine.makeTerminal(0);

    ASSERT_FALSE(machine.check("bbbabaabbbbbbbaaababaaa"));
    ASSERT_TRUE(machine.check("aaabbbababaaaaab"));
    ASSERT_TRUE(machine.check("bbaababababbbbaabbabaaaa"));
    ASSERT_FALSE(machine.check("abaababbaaaaaaba"));
}

TEST(QuickTest, MinimiseTest)
{
    std::string c = "+.ab.ba", d = "+.aa.bb";
    std::string regex = ".*" + d + "*.." + c +"*" + d + "." + c + "*" + d;
    auto pre = fromPoland(regex).determine();
    auto res = pre.minimise();

    ASSERT_FALSE(pre == res);

    DetMachine<char> machine(4u);
    machine.setTransition(0, 2, 'a');
    machine.setTransition(0, 1, 'b');
    machine.setTransition(1, 3, 'a');
    machine.setTransition(1, 0, 'b');
    machine.setTransition(2, 0, 'a');
    machine.setTransition(2, 3, 'b');
    machine.setTransition(3, 1, 'a');
    machine.setTransition(3, 2, 'b');

    machine.makeTerminal(0);

    ASSERT_TRUE(res == machine);
}

TEST(QuickTest, NonExistantEdgeTest) {
    auto res = fromPoland("*.+.+ababa").determine();
    ASSERT_FALSE(res.check("c"));
}

TEST(QuickTest, MakeFullTest) {
    std::string c = "+.ab.ba", d = "+.aa.bb";
    std::string regex = ".*" + d + "*.." + c +"*" + d + "." + c + "*" + d;
    auto pre = fromPoland(regex).determine();
    auto res = pre.minimise().makeFull(std::vector<char>{'a', 'b', 'c'});

    DetMachine<char> machine(5u);
    machine.setTransition(0, 2, 'a');
    machine.setTransition(0, 1, 'b');
    machine.setTransition(1, 3, 'a');
    machine.setTransition(1, 0, 'b');
    machine.setTransition(2, 0, 'a');
    machine.setTransition(2, 3, 'b');
    machine.setTransition(3, 1, 'a');
    machine.setTransition(3, 2, 'b');

    machine.setTransition(0, 4, 'c');
    machine.setTransition(1, 4, 'c');
    machine.setTransition(2, 4, 'c');
    machine.setTransition(3, 4, 'c');
    machine.setTransition(4, 4, 'a');
    machine.setTransition(4, 4, 'b');
    machine.setTransition(4, 4, 'c');

    machine.makeTerminal(0);

    ASSERT_TRUE(machine == res);
    ASSERT_FALSE(pre == res);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

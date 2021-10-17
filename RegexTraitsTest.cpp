//
// Created by val-de-mar on 17/10/21.
//


#include <iostream>
#include <gtest/gtest.h>
#include "RegexTraits.h"

class RegexTraitsTest : public ::testing::Test {
};


TEST(RegexTraitsTest, RegexLetterTest) {
    RegexLetter letter('a');
    std::string a{'a'};
    ASSERT_TRUE(letter.regexPolish() == a);
    ASSERT_TRUE(letter.regexReversedPolish() == a);
    ASSERT_TRUE(letter.reversedRegexPolish() == a);
    ASSERT_TRUE(letter.reversedRegexReversedPolish() == a);
}

TEST(RegexTraitsTest, RegexBinaryOperationTest) {
    RegexLetter letter_left('a'), letter_right('b');
    RegexBinaryOperation operation(&letter_left, &letter_right, '.');
    ASSERT_TRUE(operation.regexPolish() == std::string(".ab"));
    ASSERT_TRUE(operation.regexReversedPolish() == std::string("ab."));
    ASSERT_TRUE(operation.reversedRegexPolish() == std::string(".ba"));
    ASSERT_TRUE(operation.reversedRegexReversedPolish() == std::string("ba."));
}

TEST(RegexTraitsTest, RegexUnaryOperationTest) {
    RegexLetter letter('a');
    RegexUnaryOperation operation(&letter, '*');
    ASSERT_TRUE(operation.regexPolish() == std::string("*a"));
    ASSERT_TRUE(operation.regexReversedPolish() == std::string("a*"));
    ASSERT_TRUE(operation.reversedRegexPolish() == std::string("*a"));
    ASSERT_TRUE(operation.reversedRegexReversedPolish() == std::string("a*"));
}

TEST(RegexTraitsTest, TreeFromPolishTest) {
    RegexTree tree(Notation<polish>{".*+abc"});
    try {
        RegexVertex *current_vertex = tree.root;
        auto casted_vertex1 = dynamic_cast<RegexBinaryOperation*>(current_vertex);
        ASSERT_TRUE(casted_vertex1->operation_sign_ == '.');
        ASSERT_TRUE(dynamic_cast<RegexLetter*>(casted_vertex1->right_)->letter_ == 'c');
        current_vertex = casted_vertex1->left_;
        auto casted_vertex2 = dynamic_cast<RegexUnaryOperation*>(current_vertex);
        ASSERT_TRUE(casted_vertex2->operation_sign_ == '*');
        current_vertex = casted_vertex2->operand_;
        auto casted_vertex3 = dynamic_cast<RegexBinaryOperation*>(current_vertex);
        ASSERT_TRUE(casted_vertex3->operation_sign_ == '+');
        ASSERT_TRUE(dynamic_cast<RegexLetter*>(casted_vertex3->left_)->letter_ == 'a');
        ASSERT_TRUE(dynamic_cast<RegexLetter*>(casted_vertex3->right_)->letter_ == 'b');
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(RegexTraitsTest, TreeFromReversedPolishTest) {
    RegexTree tree(Notation<reversed_polish>{"ab+*c."});
    try {
        RegexVertex *current_vertex = tree.root;
        auto casted_vertex1 = dynamic_cast<RegexBinaryOperation*>(current_vertex);
        ASSERT_TRUE(casted_vertex1->operation_sign_ == '.');
        ASSERT_TRUE(dynamic_cast<RegexLetter*>(casted_vertex1->right_)->letter_ == 'c');
        current_vertex = casted_vertex1->left_;
        auto casted_vertex2 = dynamic_cast<RegexUnaryOperation*>(current_vertex);
        ASSERT_TRUE(casted_vertex2->operation_sign_ == '*');
        current_vertex = casted_vertex2->operand_;
        auto casted_vertex3 = dynamic_cast<RegexBinaryOperation*>(current_vertex);
        ASSERT_TRUE(casted_vertex3->operation_sign_ == '+');
        ASSERT_TRUE(dynamic_cast<RegexLetter*>(casted_vertex3->left_)->letter_ == 'a');
        ASSERT_TRUE(dynamic_cast<RegexLetter*>(casted_vertex3->right_)->letter_ == 'b');
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(RegexTraitsTest, getReversedRegexPolish) {
    RegexTree tree(Notation<polish>{".*+abc"});
    ASSERT_TRUE(tree.getReversedRegexPolish() == ".c*+ba");
}
TEST(RegexTraitsTest, getReversedRegexReversedPolish) {
    RegexTree tree(Notation<polish>{".*+abc"});
    ASSERT_TRUE(tree.getReversedRegexReversedPolish() == "cba+*.");
}
TEST(RegexTraitsTest, getRegexPolish) {
    RegexTree tree(Notation<polish>{".*+abc"});
    ASSERT_TRUE(tree.getRegexPolish() == ".*+abc");
}
TEST(RegexTraitsTest, getRegexReversedPolish) {
    RegexTree tree(Notation<polish>{".*+abc"});
    ASSERT_TRUE(tree.getRegexReversedPolish() == "ab+*c.");
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

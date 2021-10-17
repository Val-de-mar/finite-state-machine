//
// Created by val-de-mar on 16/10/21.
//
#pragma once

#include <string>
#include <stack>
#include <vector>

#include "RegexLetter.h"
#include "RegexBinaryOperation.h"
#include "RegexUnaryOperation.h"



enum NotationType {
    polish = 0,
    reversed_polish = 1
};

template<int>
struct Notation {
    const std::string &regex;
};

struct RegexTree {
    RegexVertex *root = nullptr;
    std::vector<RegexVertex*> vertexes;


    explicit RegexTree(Notation<polish>);
    explicit RegexTree(Notation<reversed_polish>);



    [[nodiscard]] std::string getReversedRegexPolish() const;

    [[nodiscard]] std::string getReversedRegexReversedPolish() const;


    [[nodiscard]] std::string getRegexPolish() const;

    [[nodiscard]] std::string getRegexReversedPolish() const;

    ~RegexTree();
};




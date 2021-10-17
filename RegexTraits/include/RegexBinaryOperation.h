//
// Created by val-de-mar on 17/10/21.
//
#pragma once

#include "RegexOperation.h"

struct RegexBinaryOperation : public RegexOperation {
    RegexVertex *left_ = nullptr;
    RegexVertex *right_ = nullptr;
    char operation_sign_;

    RegexBinaryOperation(RegexVertex *left, RegexVertex *right, char operation_sign);
    explicit RegexBinaryOperation(char operation_sign);

    std::string regexPolish() override;
    std::string reversedRegexPolish() override;
    std::string regexReversedPolish() override;
    std::string reversedRegexReversedPolish() override;
    size_t valency() override;
    RegexVertex* &operator [] (size_t operand) override;
    ~RegexBinaryOperation() override = default;
};



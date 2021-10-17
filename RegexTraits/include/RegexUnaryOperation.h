//
// Created by val-de-mar on 17/10/21.
//
#pragma once

#include "RegexOperation.h"

struct RegexUnaryOperation : public RegexOperation {
    RegexVertex *operand_ = nullptr;
    char operation_sign_;

    RegexUnaryOperation(RegexVertex *operand, char operation_sign);
    explicit RegexUnaryOperation(char operation_sign);

    std::string regexPolish() override;
    std::string reversedRegexPolish() override;
    std::string regexReversedPolish() override;
    std::string reversedRegexReversedPolish() override;
    size_t valency() override;
    RegexVertex* &operator [] (size_t operand) override;
    ~RegexUnaryOperation() override = default;
};



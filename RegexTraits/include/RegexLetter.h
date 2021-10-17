//
// Created by val-de-mar on 17/10/21.
//
#pragma once


#include "RegexVertex.h"


struct RegexLetter : public RegexVertex {
    char letter_;

    explicit RegexLetter(char letter);

    std::string regexPolish() override;
    std::string reversedRegexPolish() override;
    std::string regexReversedPolish() override;
    std::string reversedRegexReversedPolish() override;
    ~RegexLetter() override = default;
};


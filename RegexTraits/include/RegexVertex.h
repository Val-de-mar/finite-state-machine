//
// Created by val-de-mar on 17/10/21.
//
#pragma once

#include <string>

struct RegexVertex {
    virtual std::string regexPolish() = 0;
    virtual std::string reversedRegexPolish() = 0;

    virtual std::string regexReversedPolish() = 0;
    virtual std::string reversedRegexReversedPolish() = 0;

    virtual ~RegexVertex() = default;
};


//
// Created by val-de-mar on 17/10/21.
//
#pragma once

#include "RegexVertex.h"

struct RegexOperation : public RegexVertex {
    virtual size_t valency() = 0;
    virtual RegexVertex* &operator [] (size_t operand) = 0;
    ~RegexOperation() override = default;
};



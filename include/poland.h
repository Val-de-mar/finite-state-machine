//
// Created by val-de-mar on 27/9/21.
//

#ifndef MACHINE_POLAND_H
#define MACHINE_POLAND_H

#include "machine.h"


std::pair<Machine<char>, uint> fromPolandH(const std::string &regex, uint l = 0) {
    switch (regex[l]) {
        case '.': {
            auto x = fromPolandH(regex, l + 1);
            auto ans = std::move(x.first);
            auto y = fromPolandH(regex, x.second);
            ans *= y.first;
            return std::make_pair(ans, y.second);
        }
        case '+': {
            auto x = fromPolandH(regex, l + 1);
            auto ans = std::move(x.first);
            auto y = fromPolandH(regex, x.second);
            ans += y.first;
            return std::make_pair(ans, y.second);
        }
        case '*': {
            auto x = fromPolandH(regex, l + 1);
            auto ans = std::move(x.first);
            ans.kleene();
            return std::make_pair(ans, x.second);
        }
        default: {
            return std::make_pair(Machine<char>(regex[l]), l + 1);
        }
    }
}

Machine<char> fromPoland(const std::string &regex) {
    return fromPolandH(regex, 0).first;
}

#endif //MACHINE_POLAND_H

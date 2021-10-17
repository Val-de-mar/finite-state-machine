//
// Created by val-de-mar on 16/10/21.
//

#include <iostream>
#include "suffix.h"

int main() {
    std::string regex;
    std::string word;
    std::cout << "enter notation(number):\n0)polish\n1)reversed_polish" << std::endl;
    int notation;
    std::cin >> notation;
    std::cout << "enter regex then word" << std::endl;
    std::cin >> regex >> word;
    for (auto &sign: regex) {
        sign = ((sign == '0')?'\0':sign);
    }
    switch (notation) {
        case 0:
            std::cout << "longest suffix: " << longestSuffixPolish(regex, word) << "\nlongest prefix: "
                      << longestPrefixPolish(regex, word) << "\n";
            break;
        case 1:
            std::cout << "longest suffix: " << longestSuffixReversedPolish(regex, word) << "\nlongest prefix: "
                      << longestPrefixReversedPolish(regex, word) << "\n";
            break;
        default:
            std::cout << "incorrect notation";
    }
    return 0;
}
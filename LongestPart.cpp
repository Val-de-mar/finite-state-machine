//
// Created by val-de-mar on 16/10/21.
//

#include <iostream>
#include "suffix.h"

int main() {
    std::string regex;
    std::string word;
    std::cin >> regex >> word;
    std::cout << longestSuffix(regex, word) << "\n" << longestPrefix(regex, word);
    return 0;
}
//
// Created by val-de-mar on 17/10/21.
//

#include "RegexLetter.h"

RegexLetter::RegexLetter(char letter) : letter_(letter) {}

std::string RegexLetter::regexPolish() {
    return std::string{letter_};
}

std::string RegexLetter::reversedRegexPolish() {
    return std::string{letter_};
}

std::string RegexLetter::regexReversedPolish() {
    return std::string{letter_};
}

std::string RegexLetter::reversedRegexReversedPolish() {
    return std::string{letter_};
}
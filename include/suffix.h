#pragma once

#include "DetMachine.h"
#include "poland.h"
#include "RegexTraits.h"

template<typename... StringT>
std::set<char> getAlphabetSet(const std::string &regex, const StringT &...str);


template<>
std::set<char> getAlphabetSet(const std::string &regex);


template<typename... StringT>
std::vector<char> getAlphabet(const StringT &... regexes);


size_t longestPrefix(const std::string &regex, const std::string &word);


size_t longestSuffix(const std::string &regex, const std::string &word);

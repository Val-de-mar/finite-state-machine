#pragma once

#include <set>
#include <vector>

template<typename... StringT>
std::set<char> getAlphabetSet(const std::string &regex, const StringT &... str) {
    std::set<char> ans;
    for (char sign: regex) {
        if (sign >= 'a' && sign <= 'z') {
            ans.insert(sign);
        }
    }
    ans.merge(getAlphabetSet(str...));
    return ans;
}

template<>
std::set<char> getAlphabetSet(const std::string &regex) {
    std::set<char> ans;
    for (char sign: regex) {
        if (sign >= 'a' && sign <= 'z') {
            ans.insert(sign);
        }
    }
    return ans;
}

template<typename... StringT>
std::vector<char> getAlphabet(const StringT &... regexes) {
    auto answer_set = getAlphabetSet(regexes...);
    std::vector<char> ans;
    ans.reserve(answer_set.size());
    for (char sign: answer_set) {
        ans.push_back(sign);
    }
    return ans;
}



size_t longestPrefixPolish(const std::string &regex, const std::string &word);
size_t longestPrefixReversedPolish(const std::string &regex, const std::string &word);


size_t longestSuffixPolish(const std::string &regex, const std::string &word);
size_t longestSuffixReversedPolish(const std::string &regex, const std::string &word);


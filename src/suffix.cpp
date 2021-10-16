//
// Created by val-de-mar on 16/10/21.
//

#include <suffix.h>

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

template<class Alphabet>
struct DetMachineReversedTree {

    std::vector<std::set<uint>> vertexes;
    std::vector<bool> is_terminal;

    explicit DetMachineReversedTree(const DetMachine<Alphabet> &machine) : vertexes(machine.size()),
                                                                           is_terminal(machine.size()) {
        for (int i = 0; i < machine.size(); ++i) {
            is_terminal[i] = machine.isTerminal(i);
            for (auto &edge: machine[i]) {
                vertexes[edge.second].insert(i);
            }
        }
    }

};

enum DfsColor {
    unvisited = 0,
    visited = 1
};

void dfsDeadlockSearch(const DetMachineReversedTree<char> &tree, std::vector<bool> &color, size_t current) {
    color[current] = DfsColor::visited;
    for (auto &edge: tree.vertexes[current]) {
        if (color[edge] == DfsColor::unvisited) {
            dfsDeadlockSearch(tree, color, edge);
        }
    }
}

std::vector<bool> nonDeadlockConditions(const DetMachine<char> &machine) {
    DetMachineReversedTree<char> tree(machine);
    std::vector<bool> color(tree.vertexes.size(), DfsColor::unvisited);
    for (int i = 0; i < tree.vertexes.size(); ++i) {
        if (tree.is_terminal[i] && color[i] == DfsColor::unvisited) {
            dfsDeadlockSearch(tree, color, i);
        }
    }
    return color;
}


size_t longestPrefix(const std::string &regex, const std::string &word) {
    auto alphabet = getAlphabet(regex);
    DetMachine<char> machine = Machine<char>(fromPoland(regex)).determine().makeFull(alphabet).minimise();
    auto non_deadlock = nonDeadlockConditions(machine);
    size_t i = 0;
    size_t current_condition = 0;
    for (; i < word.size(); ++i) {
        auto next = machine[current_condition].find(word[i]);
        if (next == machine[current_condition].end()) {
            break;
        }
        if (!non_deadlock[next->second]) {
            break;
        }
        current_condition = next->second;
    }
    return i;
}

size_t longestSuffix(const std::string &regex, const std::string &word) {
    RegexTree tree(Notation<polish>{regex});
    auto actual_regex = tree.getReversedRegexPolish();
    auto reversed_word = word;
    std::reverse(reversed_word.begin(), reversed_word.end());
    return longestPrefix(actual_regex, reversed_word);
}

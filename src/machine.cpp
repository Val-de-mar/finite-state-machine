//
// Created by val-de-mar on 20/9/21.
//

#include "machine.h"


template<typename Alphabet>
auto &Machine<Alphabet>::Condition::operator[](const Alphabet &sign) {
    return edges[sign];
}

template<typename Alphabet>
bool Machine<Alphabet>::Condition::operator==(const Machine::Condition &other) const {
    return edges == other.edges && is_terminal == other.is_terminal;
}

template<typename Alphabet>
bool Machine<Alphabet>::Condition::operator!=(const Machine::Condition &other) const {
    return !(edges == other.edges);
}

template<typename Alphabet>
bool Machine<Alphabet>::Condition::isTerminal() const {
    return is_terminal;
}

template<typename Alphabet>
auto &Machine<Alphabet>::VertexDfs::operator[](const Alphabet &sign) {
    return edges[sign];
}


template<typename Alphabet>
void Machine<Alphabet>::EpsilonDfs(std::vector<VertexDfs> &rev_null, uint cur) {
    rev_null[cur].is_grey = true;
    rev_null[cur].is_terminal = true;
    for (auto &i: rev_null[cur].edges) {
        EpsilonDfs(rev_null, i);
    }
}

template<typename Alphabet>
void Machine<Alphabet>::TokenDfs(std::vector<TokenVertex> &null_part, uint cur, uint token) {
    null_part[cur].last_token = token + 1;
    null_part[cur].tokens.push_back(token);
    for (auto &vert: null_part[cur].edges) {
        if (null_part[vert].last_token <= token) TokenDfs(null_part, vert, token);
    }
}

template<typename Alphabet>
void Machine<Alphabet>::stretchInitialCondition() {
    conditions.insert(conditions.begin(), Condition());
    addTransition(0, 1, Alphabet(0));
    for (int i = 1; i < conditions.size(); ++i) {
        for (auto &condition: conditions[i].edges) {
            std::set<uint> shifted_edges;
            for (auto &k: condition.second) {
                shifted_edges.insert(k + 1);
            }
            condition.second = std::move(shifted_edges);
        }
    }
}

template<typename Alphabet>
void Machine<Alphabet>::merge(const Machine &other) {
    size_t size = conditions.size();
    conditions.resize(size + other.conditions.size());
    for (int i = size; i < conditions.size(); ++i) {
        conditions[i] = other.conditions[i - size];
    }
    for (int i = size; i < conditions.size(); ++i) {
        for (auto &condition: conditions[i].edges) {
            std::set<uint> snew;
            for (auto &edge: condition.second) {
                snew.insert(edge + size);
            }
            condition.second = std::move(snew);
        }
    }
}

template<typename Alphabet>
void Machine<Alphabet>::uniqueExit(uint l, uint r, uint exit) {
    for (uint i = l; i < r; ++i) {
        if (conditions[i].is_terminal) {
            addTransition(i, exit, Alphabet(0));
            conditions[i].is_terminal = false;
        }
    }
}


template<typename Alphabet>
std::map<Alphabet, std::vector<bool>>
Machine<Alphabet>::detMachineConditionProcessing(std::map<std::vector<bool>, uint> &mask_to_set_number,
                                                 std::vector<std::vector<bool>> &set_number_to_mask, uint vert) {
    std::map<Alphabet, std::vector<bool>> next;
    std::vector<bool> &mask = set_number_to_mask[vert];
    for (int i = 0; i < conditions.size(); ++i) {
        if (!mask[i]) {
            continue;
        }
        for (auto &edge: conditions[i].edges) {
            for (auto &dest: edge.second) {
                next[edge.first].resize(conditions.size(), false);
                next[edge.first][dest] = true;
            }
        }

    }
    return next;
}

template<typename Alphabet>
DetMachine<Alphabet> Machine<Alphabet>::determineEpsilonFree() {
    DetMachine<Alphabet> ans;
    std::map<std::vector<bool>, uint> mask_to_set_number;
    std::vector<std::vector<bool>> set_number_to_mask;
    std::queue<uint> new_vertexes;
    new_vertexes.push(0);
    {
        auto mask = std::vector<bool>(conditions.size(), false);
        mask[0] = true;
        mask_to_set_number.insert(std::make_pair(mask, 0));
        set_number_to_mask.push_back(std::move(mask));
    }
    while (!new_vertexes.empty()) {
        auto vert = new_vertexes.front();
        new_vertexes.pop();
        auto next = detMachineConditionProcessing(mask_to_set_number, set_number_to_mask, vert);
        for (auto &i: next) {
            if (mask_to_set_number.find(i.second) == mask_to_set_number.end()) {
                mask_to_set_number.insert(std::make_pair(i.second, set_number_to_mask.size()));
                new_vertexes.push(set_number_to_mask.size());
                set_number_to_mask.push_back(i.second);
                ans.addCondition();
            }
            uint num = mask_to_set_number[i.second];
            ans.conditions[vert][i.first] = num;
        }
    }
    ans.is_terminal.resize(set_number_to_mask.size());
    for (int i = 0; i < ans.conditions.size(); ++i) {
        for (int j = 0; j < conditions.size(); ++j) {
            if (set_number_to_mask[i][j] && conditions[j].is_terminal) ans.is_terminal[i] = true;
        }
    }
    return ans;
}

template<typename Alphabet>
Machine<Alphabet>::Machine(uint size) : conditions(size ? size : 1) {

}

template<typename Alphabet>
Machine<Alphabet>::Machine(Alphabet sign) : conditions(2) {
    addTransition(0, 1, sign);
    makeTerminal(1);
}

template<typename Alphabet>
Machine<Alphabet> &Machine<Alphabet>::operator=(const Machine<Alphabet> &other) {
    conditions = other.conditions;
    return *this;
}

template<typename Alphabet>
bool Machine<Alphabet>::operator==(const Machine &other) const {
    return other.conditions.size() == conditions.size() && conditions == other.conditions;
}

template<typename Alphabet>
uint Machine<Alphabet>::addCondition() {
    conditions.emplace_back();
    return conditions.size() - 1;
}

template<typename Alphabet>
void Machine<Alphabet>::addTransition(uint from, uint to, Alphabet sign) {
    conditions[from][sign].insert(to);
}

template<typename Alphabet>
void Machine<Alphabet>::makeTerminal(uint cond) {
    conditions[cond].is_terminal = true;
}

template<typename Alphabet>
void Machine<Alphabet>::tokenPushThrough(TokenVertex &token_vertex, Condition &token_carrier,
                                         Machine<Alphabet> &editable_machine) {
    for (auto &token: token_vertex.tokens) {
        for (auto &edges: token_carrier.edges) {
            if (edges.first != Alphabet(0)) {
                for (auto &dest: edges.second) {
                    editable_machine.addTransition(token, dest, edges.first);
                }
            }
        }
    }
}

template<typename Alphabet>
Machine<Alphabet> Machine<Alphabet>::ridOfEpsilon() {
    Machine ans;
    ans.conditions.resize(conditions.size());
    {
        std::vector<VertexDfs> rev_null(conditions.size());
        std::vector<TokenVertex> null_part(conditions.size());
        for (int i = 0; i < conditions.size(); ++i) {
            rev_null[i].is_terminal = conditions[i].is_terminal;
            for (auto &condition: conditions[i].edges) {
                if (condition.first != Alphabet(0)) {
                    ans.conditions[i].edges.insert(condition);
                    continue;
                }
                for (auto k: condition.second) {
                    null_part[i].edges.push_back(k);
                    rev_null[k].edges.push_back(i);
                }
            }
        }
        for (int i = 0; i < rev_null.size(); ++i) {
            if (rev_null[i].is_terminal && !rev_null[i].is_grey) {
                EpsilonDfs(rev_null, i);
            }
        }
        for (int i = 0; i < rev_null.size(); ++i) {
            if (rev_null[i].is_terminal) ans.conditions[i].is_terminal = true;
        }
        for (int i = 0; i < null_part.size(); ++i) {
            TokenDfs(null_part, i, i);
        }
        for (int i = 0; i < null_part.size(); ++i) {
            tokenPushThrough(null_part[i], ans.conditions[i], ans);
        }
    }
    return ans;
}

template<typename Alphabet>
DetMachine<Alphabet> Machine<Alphabet>::determine() {
    auto ans = ridOfEpsilon().determineEpsilonFree();
    return ans;
}

template<typename Alphabet>
Machine<Alphabet> &Machine<Alphabet>::operator+=(const Machine<Alphabet> &other) {
    stretchInitialCondition();
    addTransition(0, conditions.size(), Alphabet(0));
    merge(other);
    uniqueExit(0, conditions.size(), conditions.size());
    conditions.emplace_back();
    conditions.back().is_terminal = true;
    return *this;
}

template<typename Alphabet>
Machine<Alphabet> &Machine<Alphabet>::operator*=(const Machine<Alphabet> &other) {
    uint size = conditions.size();
    merge(other);
    uniqueExit(0, size, size);
    return *this;
}

template<typename Alphabet>
Machine<Alphabet> &Machine<Alphabet>::kleene() {
    stretchInitialCondition();
    uniqueExit(1, conditions.size(), 0);
    conditions[0].is_terminal = true;
    return *this;
}

template<typename Alphabet>
Machine<Alphabet>::Machine(const DetMachine<Alphabet> &other) :  conditions(other.size()){
    for (int i = 0; i < conditions.size(); ++i) {
        conditions[i].is_terminal = other.isTerminal(i);
        for (auto edge: other[i]) {
            conditions[i].edges[edge.first].insert(edge.second);
        }
    }
}

template<typename Alphabet>
Machine<Alphabet> Machine<Alphabet>::reversed() {
    Machine<Alphabet> ans(uint(conditions.size() + 1));
    for (uint i = 0; i < conditions.size(); ++ i) {
        for (auto &edge: conditions[i].edges) {
            for (auto destination: edge.second) {
                ans.conditions[destination + 1].edges[edge.first].insert(i + 1);
            }
        }
    }
    for (int i = 0; i < conditions.size(); ++i) {
        if(conditions[i].isTerminal()) {
            ans.conditions[0].edges[Alphabet(0)].insert(i + 1);
        }
    }
    ans.conditions[0].is_terminal = false;
    ans.conditions[1].is_terminal = true;
    return ans;
}


template
class Machine<char>;


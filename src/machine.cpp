//
// Created by val-de-mar on 20/9/21.
//

#include "machine.h"


template<typename Sigma>
uint DetMachine<Sigma>::addCond() {
    all.emplace_back();
    is_terminal.push_back(false);
    return all.size() - 1;
}

template<typename Sigma>
DetMachine<Sigma>::DetMachine(uint size) : all(size ? size : 1), is_terminal(size ? size : 1, false) {

}

template<typename Sigma>
void DetMachine<Sigma>::setTrans(uint from, uint to, Sigma sign) {
    all[from][sign] = to;
}

template<typename Sigma>
void DetMachine<Sigma>::makeTerminal(uint vert) {
    is_terminal[vert] = true;
}

template<typename Sigma>
bool DetMachine<Sigma>::operator==(const DetMachine &other) const {
    return all == other.all && is_terminal == other.is_terminal;
}

template<typename Sigma>
DetMachine<Sigma> DetMachine<Sigma>::minimise() {
    std::vector<std::map<Sigma, uint>> eqclass(all.size());
    std::vector<uint> new_classes(all.size());
    for (int i = 0; i < all.size(); ++i) {
        new_classes[i] = eqclass[i][Sigma(0)] = is_terminal[i] ? 1 : 0;
    }
    bool flag = true;
    uint prev = 0;
    uint classname = 0;
    while (flag) {
        for (int i = 0; i < eqclass.size(); ++i) {
            for (auto &edge: all[i]) {
                eqclass[i].insert({edge.first, new_classes[edge.second]});
            }
        }
        std::vector<typename std::vector<std::map<Sigma, uint>>::iterator> sorter;
        for (auto it = eqclass.begin(); it != eqclass.end(); ++it) {
            sorter.push_back(it);
        }
        std::sort(sorter.begin(), sorter.end(), [](typename std::vector<std::map<Sigma, uint>>::iterator f1,
                                                   typename std::vector<std::map<Sigma, uint>>::iterator f2) {
            return *f1 < *f2;
        });
        prev = 0;
        classname = 0;
        for (int i = 0; i < sorter.size(); ++i) {
            auto help = sorter[i] - eqclass.begin();
            if (*sorter[prev] == *sorter[i]) {
                new_classes[sorter[i] - eqclass.begin()] = classname;
            } else {
                prev = i;
                ++classname;
                new_classes[sorter[i] - eqclass.begin()] = classname;
            }
        }
        flag = false;
        for (int i = 0; i < all.size(); ++i) {
            if (!flag && eqclass[i][Sigma(0)] != new_classes[i]) {
                flag = true;
            }
            eqclass[i].clear();
            eqclass[i][Sigma(0)] = new_classes[i];
        }
    }
    if (new_classes[0] != 0) {
        uint null_class = new_classes[0];
        for (unsigned int &new_class: new_classes) {
            if (new_class == 0) new_class = null_class;
            else if (new_class == null_class) new_class = 0;
        }
    }

    DetMachine<Sigma> ans(classname + 1);
    for (int i = 0; i < all.size(); ++i) {
        if (is_terminal[i]) {
            ans.is_terminal[new_classes[i]] = true;
        }
        for (auto[sign, dest]: all[i]) {
            ans.all[new_classes[i]][sign] = new_classes[dest];
        }
    }
    return ans;
}

template<typename Sigma>
bool DetMachine<Sigma>::check(const std::basic_string<Sigma> &str) {
    uint cond = 0;
    for (int i = 0; i < str.size(); ++i) {
        auto pl = all[cond].find(str[i]);
        if (pl == all[cond].end()) {
            return false;
        } else {
            cond = pl->second;
        }
    }
    return is_terminal[cond];
}

template<typename Sigma>
DetMachine<Sigma>& DetMachine<Sigma>::makeFull(const std::vector<Sigma> &alphabet) {
    bool flag = false;
    for (int i = 0; i < all.size(); ++i) {
        for (int j = 0; j < alphabet.size(); ++j) {
            auto pl = all[i].find(alphabet[j]);
            if (pl == all[i].end()) {
                all[i][alphabet[j]] = all.size();
                flag = true;
            }
        }
    }
    if (flag) {
        addCond();
        for(int j = 0; j < alphabet.size(); ++j) {
            all.back()[alphabet[j]]=all.size() - 1;
        }
    }
    return *this;
}



template<typename Sigmat>
std::ostream &operator<<(std::ostream &output, const DetMachine<Sigmat> &value) {
    output << std::string("size is ") << std::to_string(value.all.size()) << std::string("\n");
    output << std::string("from\tto\tsign\n");
    for (int i = 0; i < value.all.size(); ++i) {
        for (auto &j: value.all[i]) {
            bool t = value.is_terminal[i];
            output << std::to_string(i) << std::string("\t") << std::to_string(j.second)
                   << std::string("\t") << std::to_string(j.first) << std::string("\n");
        }
    }
    output << std::string("is terminal\n");
    for (int i = 0; i < value.all.size(); ++i) {
        output << std::to_string(i) << std::string(value.is_terminal[i] ? "\t+\n" : "\t \n");
    }
    return output;
}


template<typename Sigma>
auto &Machine<Sigma>::Condition::operator[](const Sigma &sign) {
    return data[sign];
}

template<typename Sigma>
bool Machine<Sigma>::Condition::operator==(const Machine::Condition &other) const {
    return data == other.data && is_terminal == other.is_terminal;
}

template<typename Sigma>
bool Machine<Sigma>::Condition::operator!=(const Machine::Condition &other) const {
    return !(data == other.data);
}

template<typename Sigma>
bool Machine<Sigma>::Condition::isTerminal() const {
    return is_terminal;
}

template<typename Sigma>
auto &Machine<Sigma>::VertexDfs::operator[](const Sigma &sign) {
    return edges[sign];
}


template<typename Sigma>
void Machine<Sigma>::EpsilonDfs(std::vector<VertexDfs> &rev_null, uint cur) {
    rev_null[cur].is_grey = true;
    rev_null[cur].is_terminal = true;
    for (auto &i: rev_null[cur].edges) {
        EpsilonDfs(rev_null, i);
    }
}

template<typename Sigma>
void Machine<Sigma>::TokenDfs(std::vector<TokenVertex> &null_part, uint cur, uint token) {
    null_part[cur].last_token = token + 1;
    null_part[cur].tokens.push_back(token);
    for (auto &vert: null_part[cur].edges) {
        if (null_part[vert].last_token <= token) TokenDfs(null_part, vert, token);
    }
}

template<typename Sigma>
void Machine<Sigma>::pushFront() {
    all.insert(all.begin(), Condition());
    addTrans(0, 1, Sigma(0));
    for (int i = 1; i < all.size(); ++i) {
        for (auto &j: all[i].data) {
            std::set<uint> snew;
            for (auto &k: j.second) {
                snew.insert(k + 1);
            }
            j.second = std::move(snew);
        }
    }
}

template<typename Sigma>
void Machine<Sigma>::merge(const Machine &other) {
    size_t size = all.size();
    all.resize(size + other.all.size());
    for (int i = size; i < all.size(); ++i) {
        all[i] = other.all[i - size];
    }
    for (int i = size; i < all.size(); ++i) {
        for (auto &j: all[i].data) {
            std::set<uint> snew;
            for (auto &k: j.second) {
                snew.insert(k + size);
            }
            j.second = std::move(snew);
        }
    }
}

template<typename Sigma>
void Machine<Sigma>::uniqueExit(uint l, uint r, uint exit) {
    for (uint i = l; i < r; ++i) {
        if (all[i].is_terminal) {
            addTrans(i, exit, Sigma(0));
            all[i].is_terminal = false;
        }
    }
}

template<typename Sigma>
DetMachine<Sigma> Machine<Sigma>::determineEpsilonFree() {
    DetMachine<Sigma> ans;
    std::map<std::vector<bool>, uint> translate;
    std::vector<std::vector<bool>> rtranslate;
    std::queue<uint> new_vertexes;
    new_vertexes.push(0);
    {
        auto mask = std::vector<bool>(all.size(), false);
        mask[0] = true;
        translate.insert(std::make_pair(mask, 0));
        rtranslate.push_back(std::move(mask));
    }
//        ans.addCond();
    while (!new_vertexes.empty()) {
        auto vert = new_vertexes.front();
        new_vertexes.pop();
        std::map<Sigma, std::vector<bool>> next;
        std::vector<bool> &mask = rtranslate[vert];
        for (int i = 0; i < all.size(); ++i) {
            if (mask[i]) {
                for (auto &edge: all[i].data) {
                    for (auto &dest: edge.second) {
                        if (next[edge.first].empty()) {
                            next[edge.first] = std::vector<bool>(all.size(), false);
                        }
                        next[edge.first][dest] = true;
                    }
                }
            }
        }
        for (auto &i: next) {
            if (translate.find(i.second) == translate.end()) {
                translate.insert(std::make_pair(i.second, rtranslate.size()));
                new_vertexes.push(rtranslate.size());
                rtranslate.push_back(i.second);
                ans.addCond();
            }
            uint num = translate[i.second];
            ans.all[vert][i.first] = num;
        }
    }
    ans.is_terminal.resize(rtranslate.size());
    for (int i = 0; i < ans.all.size(); ++i) {
        for (int j = 0; j < all.size(); ++j) {
            if (rtranslate[i][j] && all[j].is_terminal) ans.is_terminal[i] = true;
        }
    }
    return ans;
}

template<typename Sigma>
Machine<Sigma>::Machine(uint size) : all(size ? size : 1) {

}

template<typename Sigma>
Machine<Sigma>::Machine(Sigma sign) : all(2) {
    addTrans(0, 1, sign);
    makeTerminal(1);
}

template<typename Sigma>
Machine<Sigma> &Machine<Sigma>::operator=(const Machine<Sigma> &other) {
    all = other.all;
    return *this;
}

template<typename Sigma>
bool Machine<Sigma>::operator==(const Machine &other) const {
    if (other.all.size() != all.size()) {
        return false;
    }
    for (int i = 0; i < all.size(); ++i) {
        if (all[i] != other.all[i]) return false;
    }
    return true;
}

template<typename Sigma>
uint Machine<Sigma>::addCond() {
    all.emplace_back();
    return all.size() - 1;
}

template<typename Sigma>
void Machine<Sigma>::addTrans(uint from, uint to, Sigma sign) {
    all[from][sign].insert(to);
}

template<typename Sigma>
void Machine<Sigma>::makeTerminal(uint cond) {
    all[cond].is_terminal = true;
}

template<typename Sigma>
Machine<Sigma> Machine<Sigma>::ridOfEpsilon() {
    Machine ans;
    ans.all.resize(all.size());
    {
        std::vector<VertexDfs> rev_null(all.size());
        std::vector<TokenVertex> null_part(all.size());
        for (int i = 0; i < all.size(); ++i) {
            rev_null[i].is_terminal = all[i].is_terminal;
            for (auto &j: all[i].data) {
                if (j.first != Sigma(0)) ans.all[i].data.insert(j);
                else {
                    for (auto k: j.second) {
                        null_part[i].edges.push_back(k);
                        rev_null[k].edges.push_back(i);
                    }
                }
            }
        }
        for (int i = 0; i < rev_null.size(); ++i) {
            if (rev_null[i].is_terminal && !rev_null[i].is_grey) {
                EpsilonDfs(rev_null, i);
            }
        }
        for (int i = 0; i < rev_null.size(); ++i) {
            if (rev_null[i].is_terminal) ans.all[i].is_terminal = true;
        }
        for (int i = 0; i < null_part.size(); ++i) {
            TokenDfs(null_part, i, i);
        }
        for (int i = 0; i < null_part.size(); ++i) {
            for (auto &token: null_part[i].tokens) {
                for (auto &edges: ans.all[i].data) {
                    if (edges.first != Sigma(0)) {
                        for (auto &dest: edges.second) {
                            ans.addTrans(token, dest, edges.first);
                        }
                    }
                }
            }
        }
    }
    return ans;
}

template<typename Sigma>
DetMachine<Sigma> Machine<Sigma>::determine() {
    auto ans = ridOfEpsilon().determineEpsilonFree();
    return ans;
}

template<typename Sigma>
Machine<Sigma> &Machine<Sigma>::operator+=(const Machine<Sigma> &other) {
    pushFront();
    addTrans(0, all.size(), Sigma(0));
    merge(other);
    uniqueExit(0, all.size(), all.size());
//        for (uint i = 0; i < all.size(); ++i) {
//            if(all[i].is_terminal) {
//                addTrans(i, all.size(), Sigma(0));
//                all[i].is_terminal = false;
//            }
//        }
    all.emplace_back();
    all.back().is_terminal = true;
    return *this;
}

template<typename Sigma>
Machine<Sigma> &Machine<Sigma>::operator*=(const Machine<Sigma> &other) {
    uint size = all.size();
    merge(other);
    uniqueExit(0, size, size);
//        for (uint i = 0; i < size; ++i) {
//            if(all[i].is_terminal) {
//                addTrans(i, size, Sigma(0));
//                all[i].is_terminal = false;
//            }
//        }
    return *this;
}

template<typename Sigma>
Machine<Sigma> &Machine<Sigma>::kleene() {
    pushFront();
    uniqueExit(1, all.size(), 0);
    all[0].is_terminal = true;
    return *this;
}

template
class Machine<char>;

template
class DetMachine<char>;

template
std::ostream &operator<<(std::ostream &output, const DetMachine<char> &value);

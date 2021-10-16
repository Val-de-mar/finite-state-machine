//
// Created by val-de-mar on 4/10/21.
//

#include "DetMachine.h"
template<typename Alphabet>
uint DetMachine<Alphabet>::addCondition() {
    conditions.emplace_back();
    is_terminal.push_back(false);
    return conditions.size() - 1;
}

template<typename Alphabet>
DetMachine<Alphabet>::DetMachine(uint size) : conditions(size ? size : 1), is_terminal(size ? size : 1, false) {

}

template<typename Alphabet>
void DetMachine<Alphabet>::setTransition(uint from, uint to, Alphabet sign) {
    conditions[from][sign] = to;
}

template<typename Alphabet>
void DetMachine<Alphabet>::makeTerminal(uint vert) {
    is_terminal[vert] = true;
}

template<typename Alphabet>
bool DetMachine<Alphabet>::operator==(const DetMachine &other) const {
    return conditions == other.conditions && is_terminal == other.is_terminal;
}

template<typename Alphabet>
bool DetMachine<Alphabet>::classTransitionsIteration(std::vector<uint>& new_classes) {
    std::vector<std::map<Alphabet, uint>> class_transitions(conditions.size());
    for (int i = 0; i < class_transitions.size(); ++i) {
        class_transitions[i][Alphabet(0)] = new_classes[i];
        for (auto &edge: conditions[i]) {
            class_transitions[i].insert({edge.first, new_classes[edge.second]});
        }
    }
    std::vector<typename std::vector<std::map<Alphabet, uint>>::iterator> sorter;
    for (auto it = class_transitions.begin(); it != class_transitions.end(); ++it) {
        sorter.push_back(it);
    }
    std::sort(sorter.begin(), sorter.end(), [](typename std::vector<std::map<Alphabet, uint>>::iterator f1,
                                               typename std::vector<std::map<Alphabet, uint>>::iterator f2) {
        return *f1 < *f2;
    });
    uint prev = 0;
    uint classname = 0;
    for (int i = 0; i < sorter.size(); ++i) {
        auto help = sorter[i] - class_transitions.begin();
        if (*sorter[prev] == *sorter[i]) {
            new_classes[sorter[i] - class_transitions.begin()] = classname;
        } else {
            prev = i;
            ++classname;
            new_classes[sorter[i] - class_transitions.begin()] = classname;
        }
    }
    bool flag = false;
    for (int i = 0; i < conditions.size(); ++i) {
        if (!flag && class_transitions[i][Alphabet(0)] != new_classes[i]) {
            flag = true;
        }
    }
    return flag;
}

template<typename Alphabet>
DetMachine<Alphabet> DetMachine<Alphabet>::minimise() {
    std::vector<std::map<Alphabet, uint>> class_transitions(conditions.size());
    std::vector<uint> new_classes(conditions.size());
    for (int i = 0; i < conditions.size(); ++i) {
        new_classes[i] = class_transitions[i][Alphabet(0)] = is_terminal[i] ? 1 : 0;
    }
    bool flag = true;
    while (flag) {
        flag = classTransitionsIteration(new_classes);
    }
    if (new_classes[0] != 0) {
        uint null_class = new_classes[0];
        for (unsigned int &new_class: new_classes) {
            if (new_class == 0) new_class = null_class;
            else if (new_class == null_class) new_class = 0;
        }
    }

    uint det_machine_size = *std::max_element(new_classes.begin(), new_classes.end()) + 1;

    DetMachine<Alphabet> ans(det_machine_size);
    for (int i = 0; i < conditions.size(); ++i) {
        if (is_terminal[i]) {
            ans.is_terminal[new_classes[i]] = true;
        }
        for (auto[sign, dest]: conditions[i]) {
            ans.conditions[new_classes[i]][sign] = new_classes[dest];
        }
    }
    return ans;
}

template<typename Alphabet>
bool DetMachine<Alphabet>::check(const std::basic_string<Alphabet> &str) {
    uint cond = 0;
    for (int i = 0; i < str.size(); ++i) {
        auto pl = conditions[cond].find(str[i]);
        if (pl == conditions[cond].end()) {
            return false;
        } else {
            cond = pl->second;
        }
    }
    return is_terminal[cond];
}

template<typename Alphabet>
DetMachine<Alphabet> &DetMachine<Alphabet>::makeFull(const std::vector<Alphabet> &alphabet) {
    bool flag = false;
    for (int i = 0; i < conditions.size(); ++i) {
        for (int j = 0; j < alphabet.size(); ++j) {
            auto pl = conditions[i].find(alphabet[j]);
            if (pl == conditions[i].end()) {
                conditions[i][alphabet[j]] = conditions.size();
                flag = true;
            }
        }
    }
    if (flag) {
        addCondition();
        for (int j = 0; j < alphabet.size(); ++j) {
            conditions.back()[alphabet[j]] = conditions.size() - 1;
        }
    }
    return *this;
}


template<typename AlphabetT>
std::ostream &operator<<(std::ostream &output, const DetMachine<AlphabetT> &value) {
    output << std::string("size is ") << std::to_string(value.conditions.size()) << std::string("\n");
    output << std::string("from\tto\tsign\n");
    for (int i = 0; i < value.conditions.size(); ++i) {
        for (auto &condition: value.conditions[i]) {
            bool t = value.is_terminal[i];
            output << std::to_string(i) << std::string("\t") << std::to_string(condition.second)
                   << std::string("\t") << std::string(1, condition.first) << std::string("\n");
        }
    }
    output << std::string("is terminal\n");
    for (int i = 0; i < value.conditions.size(); ++i) {
        output << std::to_string(i) << std::string(value.is_terminal[i] ? "\t+\n" : "\t \n");
    }
    return output;
}

template<typename Alphabet>
size_t DetMachine<Alphabet>::size() const {
    return conditions.size();
}

template<typename Alphabet>
const std::map<Alphabet, uint> &DetMachine<Alphabet>::operator[](uint condition) const {
    return conditions[condition];
}

template<typename Alphabet>
bool DetMachine<Alphabet>::isTerminal(uint condition) const {
    return is_terminal[condition];
}


template
class DetMachine<char>;

template
std::ostream &operator<<(std::ostream &output, const DetMachine<char> &value);
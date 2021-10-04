//
// Created by val-de-mar on 4/10/21.
//

#ifndef MACHINE_DETMACHINE_H
#define MACHINE_DETMACHINE_H

#include <map>
#include <vector>
#include <algorithm>

using uint = unsigned int;

template<typename Alphabet>
class Machine;

template<typename Alphabet>
class DetMachine {
    std::vector<std::map<Alphabet, uint>> all;
    std::vector<bool> is_terminal;

    friend class Machine<Alphabet>;

    bool classTransitionsIteration(std::vector<uint> &new_classes);

public:
    DetMachine(uint size = 1);

    uint addCondition();

    void setTransition(uint from, uint to, Alphabet sign);

    void makeTerminal(uint vert);

    bool operator==(const DetMachine &other) const;

    DetMachine minimise();

    bool check(const std::basic_string<Alphabet> &str);

    DetMachine &makeFull(const std::vector<Alphabet> &alphabet);

    template<class AlphabetT>
    friend std::ostream &operator<<(std::ostream &output, const DetMachine<AlphabetT> &value);
};


#endif //MACHINE_DETMACHINE_H

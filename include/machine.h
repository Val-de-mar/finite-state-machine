//
// Created by val-de-mar on 20/9/21.
//

#ifndef MACHINE_MACHINE_H
#define MACHINE_MACHINE_H

#include <vector>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>

#include "DetMachine.h"

using uint = unsigned int;


template<typename Alphabet>
class Machine {

    class Condition {
        std::map<Alphabet, std::set<uint>> conditions;
        bool is_terminal = false;
    public:
        auto &operator[](const Alphabet &sign);

        bool operator==(const Condition &other) const;

        bool operator!=(const Condition &other) const;

        Condition() : conditions() {}

        [[nodiscard]] bool isTerminal() const;

        friend class Machine<Alphabet>;
    };

    struct TokenVertex {
        std::vector<uint> edges;
        std::vector<uint> tokens;
        uint last_token = 0;
    };

    struct VertexDfs {
        std::vector<uint> edges;
        bool is_grey = false;
        bool is_terminal = false;

        auto &operator[](const Alphabet &sign);
    };

    void EpsilonDfs(std::vector<VertexDfs> &rev_null, uint cur);

    void TokenDfs(std::vector<TokenVertex> &null_part, uint cur, uint token);

    std::vector<Condition> all;

    void stretchInitialCondition();

    void merge(const Machine &other);

    void uniqueExit(uint l, uint r, uint exit);

    std::map<Alphabet, std::vector<bool>>
    detMachineConditionProcessing(std::map<std::vector<bool>, uint> &mask_to_set_number,
                                  std::vector<std::vector<bool>> &set_number_to_mask, uint vert);

    DetMachine<Alphabet> determineEpsilonFree();

    void tokenPushThrough(TokenVertex& token_vertex, Condition& token_carrier, Machine<Alphabet>& editable_machine);

public:
    Machine(uint size = 1);

    Machine(Alphabet sign);

    Machine(const Machine<Alphabet> &other) = default;

    Machine(Machine<Alphabet> &&other) = default;

    Machine &operator=(const Machine<Alphabet> &other);

    bool operator==(const Machine &other) const;

    uint addCond();

    void addTrans(uint from, uint to, Alphabet sign);

    void makeTerminal(uint cond);

    Machine ridOfEpsilon();

    DetMachine<Alphabet> determine();

    Machine &operator+=(const Machine<Alphabet> &other);

    Machine &operator*=(const Machine<Alphabet> &other);

    Machine &kleene();


};


#endif //MACHINE_MACHINE_H

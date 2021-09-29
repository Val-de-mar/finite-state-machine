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

using uint = unsigned int;

template<typename Sigma>
class Machine;

template<typename Sigma>
class DetMachine {
    std::vector<std::map<Sigma, uint>> all;
    std::vector<bool> is_terminal;

    friend class Machine<Sigma>;

public:
    DetMachine(uint size = 1);

    uint addCond();

    void setTrans(uint from, uint to, Sigma sign);

    bool operator==(const DetMachine &other) const;

    DetMachine minimise();

    bool check(const std::basic_string<Sigma> &str);

    template<class Sigmat>
    friend std::ostream &operator<<(std::ostream &output, const DetMachine<Sigmat> &value);
};

template<typename Sigma>
class Machine {

    class Condition {
        std::map<Sigma, std::set<uint>> data;
        bool is_terminal = false;
    public:
        auto &operator[](const Sigma &sign);

        bool operator==(const Condition &other) const;

        bool operator!=(const Condition &other) const;

        Condition() : data() {}

        [[nodiscard]] bool isTerminal() const;

        friend class Machine<Sigma>;
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

        auto &operator[](const Sigma &sign);
    };

    void EpsilonDfs(std::vector<VertexDfs> &rev_null, uint cur);

    void TokenDfs(std::vector<TokenVertex> &null_part, uint cur, uint token);

    std::vector<Condition> all;

    void pushFront();

    void merge(const Machine &other);

    void uniqueExit(uint l, uint r, uint exit);

    DetMachine<Sigma> determineEpsilonFree();

public:
    Machine(uint size = 1);

    Machine(Sigma sign);

    Machine(const Machine<Sigma> &other) = default;

    Machine(Machine<Sigma> &&other) = default;

    Machine &operator=(const Machine<Sigma> &other);

    bool operator==(const Machine &other) const;

    uint add_cond();

    void add_trans(uint from, uint to, Sigma sign);

    void makeTerminal(uint cond);

    Machine ridOfEpsilon();

    DetMachine<Sigma> determine();

    Machine &operator+=(const Machine<Sigma> &other);

    Machine &operator*=(const Machine<Sigma> &other);

    Machine &kleene();


};



#endif //MACHINE_MACHINE_H

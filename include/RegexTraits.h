//
// Created by val-de-mar on 16/10/21.
//

#ifndef MACHINE_REGEXTRAITS_H
#define MACHINE_REGEXTRAITS_H


#include <string>
#include <stack>
#include <vector>

struct RegexVertex {
    virtual std::string regexPolish() = 0;
    virtual std::string reversedRegexPolish() = 0;

    virtual std::string regexReversedPolish() = 0;
    virtual std::string reversedRegexReversedPolish() = 0;

    virtual ~RegexVertex() = default;
};

struct RegexOperation : public RegexVertex {
    virtual size_t valency() = 0;
    virtual RegexVertex* &operator [] (size_t operand) = 0;
    ~RegexOperation() override = default;
};

struct RegexBinaryOperation : public RegexOperation {
    RegexVertex *left_ = nullptr;
    RegexVertex *right_ = nullptr;
    char operation_sign_;

    RegexBinaryOperation(RegexVertex *left, RegexVertex *right, char operation_sign);
    explicit RegexBinaryOperation(char operation_sign);

    std::string regexPolish() override;
    std::string reversedRegexPolish() override;
    std::string regexReversedPolish() override;
    std::string reversedRegexReversedPolish() override;
    size_t valency() override;
    RegexVertex* &operator [] (size_t operand) override;
    ~RegexBinaryOperation() override = default;
};

struct RegexUnaryOperation : public RegexOperation {
    RegexVertex *operand_ = nullptr;
    char operation_sign_;

    RegexUnaryOperation(RegexVertex *operand, char operation_sign);
    explicit RegexUnaryOperation(char operation_sign);

    std::string regexPolish() override;
    std::string reversedRegexPolish() override;
    std::string regexReversedPolish() override;
    std::string reversedRegexReversedPolish() override;
    size_t valency() override;
    RegexVertex* &operator [] (size_t operand) override;
    ~RegexUnaryOperation() override = default;
};

struct RegexLetter : public RegexVertex {
    char letter_;

    explicit RegexLetter(char letter);

    std::string regexPolish() override;
    std::string reversedRegexPolish() override;
    std::string regexReversedPolish() override;
    std::string reversedRegexReversedPolish() override;
    ~RegexLetter() override = default;
};

enum NotationType {
    polish = 0,
    reversed_polish = 1
};

template<int>
struct Notation {
    const std::string &regex;
};

struct RegexTree {
    RegexVertex *root = nullptr;
    std::vector<RegexVertex*> vertexes;


    explicit RegexTree(Notation<polish>);
    explicit RegexTree(Notation<reversed_polish>);



    [[nodiscard]] std::string getReversedRegexPolish() const;

    [[nodiscard]] std::string getReversedRegexReversedPolish() const;


    [[nodiscard]] std::string getRegexPolish() const;

    [[nodiscard]] std::string getRegexReversedPolish() const;

    ~RegexTree();
};



#endif //MACHINE_REGEXTRAITS_H

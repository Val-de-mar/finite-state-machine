//
// Created by val-de-mar on 16/10/21.
//
#include <RegexTraits.h>
#include <cassert>





RegexBinaryOperation::RegexBinaryOperation(RegexVertex *left, RegexVertex *right, char operation_sign) : left_(left), right_(right),
                                                                                                         operation_sign_(
                                                                                                                 operation_sign) {}

std::string RegexBinaryOperation::regexReversedPolish()  {
    return left_->regexReversedPolish() + right_->regexReversedPolish() + operation_sign_;
}

std::string RegexBinaryOperation::reversedRegexReversedPolish(){
    return right_->reversedRegexReversedPolish() + left_->reversedRegexReversedPolish() + operation_sign_;
}

RegexBinaryOperation::RegexBinaryOperation(char operation_sign) : operation_sign_(operation_sign){

}

size_t RegexBinaryOperation::valency() {
    return 2;
}

RegexVertex *&RegexBinaryOperation::operator[](size_t operand) {
    switch (operand) {
        case 0:
            return left_;
        case 1:
            return right_;
        default:
            assert(false);
    }
}

std::string RegexBinaryOperation::regexPolish() {
    return operation_sign_ + left_->regexPolish() + right_->regexPolish();
}

std::string RegexBinaryOperation::reversedRegexPolish() {
    return operation_sign_ + right_->reversedRegexPolish() + left_->reversedRegexPolish();
}

RegexUnaryOperation::RegexUnaryOperation(RegexVertex *operand, char operation_sign) : operand_(operand),
                                                                                      operation_sign_(operation_sign) {

}



std::string RegexUnaryOperation::regexReversedPolish() {
    return operand_->regexReversedPolish() + operation_sign_;
}

std::string RegexUnaryOperation::reversedRegexReversedPolish() {
    return operand_->reversedRegexReversedPolish() + operation_sign_;
}

RegexUnaryOperation::RegexUnaryOperation(char operation_sign): operation_sign_(operation_sign) {

}

size_t RegexUnaryOperation::valency() {
    return 1;
}

RegexVertex *&RegexUnaryOperation::operator[](size_t operand) {
    switch (operand) {
        case 0:
            return operand_;
        default:
            assert(false);
    }
}

std::string RegexUnaryOperation::regexPolish() {
    return operation_sign_ + operand_->regexPolish();
}
std::string RegexUnaryOperation::reversedRegexPolish() {
    return operation_sign_ + operand_->reversedRegexPolish();
}

RegexLetter::RegexLetter(char letter) : letter_(letter) {}

std::string RegexLetter::regexPolish() {
    return std::string{letter_};
}

std::string RegexLetter::reversedRegexPolish() {
    return std::string{letter_};
}

std::string RegexLetter::regexReversedPolish() {
    return std::string{letter_};
}

std::string RegexLetter::reversedRegexReversedPolish() {
    return std::string{letter_};
}

 RegexTree::RegexTree(Notation<reversed_polish> notation) {
    const std::string &regex = notation.regex;
    std::stack<RegexVertex *> buffer;
    for (char sign: regex) {
        if (sign >= 'a' && sign <= 'z') {
            vertexes.push_back(new RegexLetter(sign));
            buffer.push(vertexes.back());
        } else if (sign == '*') {
            vertexes.push_back(new RegexUnaryOperation(buffer.top(), sign));
            root = vertexes.back();
            buffer.pop();
        } else {
            auto &right = buffer.top();
            buffer.pop();
            auto &left = buffer.top();
            buffer.pop();
            vertexes.push_back(new RegexBinaryOperation(left, right, sign));
            root = vertexes.back();
        }
    }
}

size_t operation_valency(char operation) {
    if (operation == '*') {
        return 1;
    } else {
        return 2;
    }
}

RegexTree::RegexTree(Notation<polish> notation) {
    const std::string &regex = notation.regex;
    std::stack<RegexOperation*> operators_buffer;
    std::stack<size_t> fullness;
    RegexLetter* free_letter;
    for (char sign: regex) {
        if (sign >= 'a' && sign <= 'z') {
            vertexes.push_back(new RegexLetter(sign));
            (*operators_buffer.top())[fullness.top()] = vertexes.back();
            ++fullness.top();
            while(fullness.top() >= operators_buffer.top()->valency()) {
                auto vertex = operators_buffer.top();
                operators_buffer.pop();
                if (operators_buffer.empty()) {
                    root = vertex;
                    break;
                }
                fullness.pop();
                (*operators_buffer.top())[fullness.top()] = vertex;
                ++fullness.top();
            }
        } else if (sign == '*') {
            RegexOperation *new_vertex = new RegexUnaryOperation(sign);
            vertexes.push_back(new_vertex);
            operators_buffer.push(new_vertex);
            fullness.push(0);
        } else {
            RegexOperation *new_vertex = new RegexBinaryOperation(sign);
            vertexes.push_back(new_vertex);
            operators_buffer.push(new_vertex);
            fullness.push(0);
        }
    }
}


std::string RegexTree::getReversedRegexPolish() const {
    return root->reversedRegexPolish();
}

std::string RegexTree::getReversedRegexReversedPolish() const {
    return root->reversedRegexReversedPolish();
}

RegexTree::~RegexTree() {
    for (auto ptr: vertexes) {
        delete ptr;
    }
}

std::string RegexTree::getRegexPolish() const {
    return root->regexPolish();
}


std::string RegexTree::getRegexReversedPolish() const {
    return root->regexReversedPolish();
}


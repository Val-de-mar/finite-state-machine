//
// Created by val-de-mar on 16/10/21.
//
#include "RegexTraits.h"


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
            buffer.top() = root;
        } else {
            auto &right = buffer.top();
            buffer.pop();
            auto &left = buffer.top();
            buffer.pop();
            vertexes.push_back(new RegexBinaryOperation(left, right, sign));
            root = vertexes.back();
            buffer.push(root);
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
    std::stack<RegexOperation *> operators_buffer;
    std::stack<size_t> fullness;
    RegexLetter *free_letter;
    for (char sign: regex) {
        if (sign >= 'a' && sign <= 'z') {
            vertexes.push_back(new RegexLetter(sign));
            (*operators_buffer.top())[fullness.top()] = vertexes.back();
            ++fullness.top();
            while (fullness.top() >= operators_buffer.top()->valency()) {
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


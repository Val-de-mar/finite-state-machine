//
// Created by val-de-mar on 17/10/21.
//

#include "RegexBinaryOperation.h"
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

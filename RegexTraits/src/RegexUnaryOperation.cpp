//
// Created by val-de-mar on 17/10/21.
//

#include "RegexUnaryOperation.h"
#include <cassert>

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

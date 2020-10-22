//
// Created by tyler on 9/14/2020.
//

#ifndef LAB1_236_UNDEFINEDAUTOMATON_H
#define LAB1_236_UNDEFINEDAUTOMATON_H
#include "Automaton.h"

class UndefinedAutomaton : public Automaton {
private:
    TokenType tokenType;
    int Read(const std::string& input) {
        return 0;
    }
public:
    UndefinedAutomaton(TokenType tokenType) : Automaton(tokenType) {
        this->tokenType = tokenType;
    }
};


#endif //LAB1_236_UNDEFINEDAUTOMATON_H

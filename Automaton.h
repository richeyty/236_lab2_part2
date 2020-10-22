//
// Created by tyler on 9/11/2020.
//

#ifndef LAB1_236_AUTOMATON_H
#define LAB1_236_AUTOMATON_H
#include <iostream>
#include "Token.h"

using namespace std;


class Automaton {
protected:
    int newLines = 0;
    enum TokenType type;

public:
    Automaton(TokenType type) { this->type = type; }



    virtual int Read(const std::string& input) = 0;

    virtual Token* CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }

    virtual int NewLinesRead() const {

        return newLines;
    }


};


#endif //LAB1_236_AUTOMATON_H

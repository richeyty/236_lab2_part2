//
// Created by tyler on 9/13/2020.
//

#ifndef LAB1_236_STRINGAUTOMATON_H
#define LAB1_236_STRINGAUTOMATON_H
#include "Automaton.h"
#include <iostream>

using namespace std;
class StringAutomaton : public Automaton {
private:
    string toMatch = "''";
    TokenType tokenType;
public:
    StringAutomaton(TokenType tokenType) : Automaton(tokenType) {
        this->tokenType = tokenType;
    }
    int Read(const std::string& input) {
        newLines = 0;
        unsigned int i = 0;
        if (input[i] != '\'') {
            tokenType = UNDEFINED;
            return i;
        }
        bool finished = false;
        if (input[0] == '\'') {                        // beginning apostraphe
            i = 1;
            while (i < input.size() && !finished) {           // run through the rest
                if (input[i] == '\n') {
                    newLines++;
                }
                else if (input[i] == '\'') {              // first apostraphe(possible close)
                    if (i + 1 < input.size() && input[i + 1] == '\'') {
                        i++;
                    }
                    else {
                        finished = true;
                    }


                }
                i++;
            }
            if (!finished) {

                type = UNDEFINED;
            }



            return i;
        }
        return 0;

    }
};




#endif //LAB1_236_STRINGAUTOMATON_H

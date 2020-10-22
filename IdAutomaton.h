//
// Created by tyler on 9/15/2020.
//

#ifndef LAB1_236_IDAUTOMATON_H
#define LAB1_236_IDAUTOMATON_H
#include "Automaton.h"

class IdAutomaton : public Automaton {
private:
    TokenType tokenType;
public:
    IdAutomaton(TokenType tokenType) : Automaton(tokenType) {
        this->tokenType = tokenType;
    }
    int Read(const string& input) {

        int charsRead = 0;
        if (isalpha(input[0])) {
            for (unsigned int i = 0; i < input.size(); ++i)
            {
                if (isalpha(input[i])) {
                    ++charsRead;
                }
                else if (isdigit(input[i])) {
                    ++charsRead;
                }
                else {
                    break;
                }
            }

            return charsRead;
        }
        else {
            return 0;
        }

    }
};


#endif //LAB1_236_IDAUTOMATON_H

//
// Created by tyler on 9/13/2020.
//

#ifndef LAB1_236_MATCHERAUTOMATON_H
#define LAB1_236_MATCHERAUTOMATON_H
#include "Automaton.h"

using namespace std;

class MatcherAutomaton : public Automaton {
private:
    string toMatch;
    TokenType tokenType;
public:
    MatcherAutomaton(string toMatch, TokenType tokenType) : Automaton(tokenType) {
        this->toMatch = toMatch;
        this->tokenType = tokenType;
    }
    int Read(const string& input) {
        bool isMatch = true;
        int inputRead = 0;
        int i = 0;
        string newLine = "\n";
        newLines = 0;
        for (i = 0; i < (int)toMatch.size() && isMatch; i++) {


            if (input[i] != toMatch[i]) {
                isMatch = false;
            }

        }

        if (isMatch) {

            inputRead = i;

        }
        return inputRead;
    }

};






#endif //LAB1_236_MATCHERAUTOMATON_H

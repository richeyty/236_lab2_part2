#ifndef LAB1_236_EOFAUTOMATON_H
#define LAB1_236_EOFAUTOMATON_H
#include "Automaton.h"

using namespace std;

class EofAutomaton : public Automaton {
private:
    TokenType tokenType;
public:
    EofAutomaton(TokenType tokenType) : Automaton(tokenType) {
        this->tokenType = tokenType;
    }
    int Read(const string& input) {
        if (input == "") {
            return 1;
        }
        else {
            return 0;
        }
    }

};






#endif //LAB1_236_EOFAUTOMATON_H

//
// Created by tyler on 9/13/2020.
//

#ifndef LAB1_236_COMMENTAUTOMATON_H
#define LAB1_236_COMMENTAUTOMATON_H
#include "Automaton.h"


class CommentAutomaton : public Automaton {
private:

    TokenType tokenType;
public:
    CommentAutomaton(TokenType tokenType) : Automaton(tokenType) {
        this->tokenType = tokenType;
    }
    int Read(const std::string& input) {
        newLines = 0;
        unsigned int i = 0;
        bool finished = false;
        if (input[0] == '#') { // starts with a #

            if (i + 1 < input.size() && input[i + 1] == '|') {                     // comment block started - we got a |
                while (i < input.size() && !finished) {
                    if (input[i] == '\n') {
                        newLines++;
                    }
                    if (input[i] == '|') {
                        if (i + 1 < input.size() && input[i + 1] == '#') {
                            i++;
                            finished = true;
                        }


                    }
                    i++;

                }
                if (!finished) {

                    type = UNDEFINED;
                }
            }
            else {                                          // just a normal comment
                for (i = 0; i < input.size(); ++i) {

                    if (input[i] == '\n') {              // we found a newline

                        break;
                    }
                    else if (input[i] == EOF) {
                        break;
                    }

                }
            }

            return i;
        }
        else {
            return 0;
        }

    }
};


#endif //LAB1_236_COMMENTAUTOMATON_H

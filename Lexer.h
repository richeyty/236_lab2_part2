//
// Created by tyler on 9/13/2020.
//

#ifndef LAB1_236_LEXER_H
#define LAB1_236_LEXER_H
#include <iostream>
#include <string>
#include "MatcherAutomaton.h"
#include "Token.h"
#include <vector>
#include "StringAutomaton.h"
#include "IdAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EofAutomaton.h"
#include "CommentAutomaton.h"


using namespace std;

class Lexer {
private:
    int lineNumber;
    int maxRead;
    int inputRead;
    int maxNewLines;
    Token* newToken;
    MatcherAutomaton comma = MatcherAutomaton(",", COMMA);
    MatcherAutomaton period = MatcherAutomaton(".", PERIOD);
    MatcherAutomaton qMark = MatcherAutomaton("?", Q_MARK);
    MatcherAutomaton leftParen = MatcherAutomaton("(", LEFT_PAREN);
    MatcherAutomaton rightParen = MatcherAutomaton(")", RIGHT_PAREN);
    MatcherAutomaton colon = MatcherAutomaton(":", COLON);
    MatcherAutomaton colonDash = MatcherAutomaton(":-", COLON_DASH);
    MatcherAutomaton multiply = MatcherAutomaton("*", MULTIPLY);
    MatcherAutomaton add = MatcherAutomaton("+", ADD);
    MatcherAutomaton schemes = MatcherAutomaton("Schemes", SCHEMES);
    MatcherAutomaton facts = MatcherAutomaton("Facts", FACTS);
    MatcherAutomaton rules = MatcherAutomaton("Rules", RULES);
    MatcherAutomaton queries = MatcherAutomaton("Queries", QUERIES);
    StringAutomaton sa = StringAutomaton(STRING);
    UndefinedAutomaton ua = UndefinedAutomaton(UNDEFINED);
    IdAutomaton id = IdAutomaton(ID);
    CommentAutomaton ca = CommentAutomaton(COMMENT);
    EofAutomaton eofa = EofAutomaton(ENDFILE);
    Automaton* machineList[18] = { &ua, &comma, &period, &qMark, &leftParen, &rightParen, &colon, &colonDash, &multiply, &add,
                                                 &schemes, &facts, &rules, &queries, &sa, &ca, &id, &eofa };
    Automaton* maxMachine;
protected:
    vector<Token*> tokens;

    
public:
    vector<Token*> runLexer(string input) {
        lineNumber = 1;
        while (input[0] == '\n') {

            ++lineNumber;
            input.erase(0, 1);
        }
        while (input.size() > 0) {

            if (isspace(input[0])) {

                input.erase(0, 1);
            }
            if (input[0] == '\n') {

                ++lineNumber;
                input.erase(0, 1);
            }
            maxRead = 0;
            // set macMachine to the first item in machines
            maxMachine = machineList[0];
            for (int i = 0; i < 18; ++i) {

                inputRead = machineList[i]->Read(input);

                if (inputRead > maxRead) {

                    maxRead = inputRead;

                    maxMachine = machineList[i];

                    maxNewLines = machineList[i]->NewLinesRead();
                }

            }

            if (maxRead > 0) {
                if (maxMachine != machineList[15]) {

                    newToken = maxMachine->CreateToken(input.substr(0, maxRead), lineNumber);
                    lineNumber = lineNumber + maxNewLines;
                    tokens.push_back(newToken);
                }
                
            }
            else {
                // This is going to handle the one character undefined tokens
                maxRead = 1;
                maxMachine = machineList[0];
                newToken = maxMachine->CreateToken(input.substr(0, maxRead), lineNumber);
                tokens.push_back(newToken);

            }

            input.erase(0, maxRead);



            while (input[0] == '\n') {

                ++lineNumber;
                input.erase(0, 1);
            }
            while (isspace(input[0])) {
                if (input[0] == '\n') {
                    ++lineNumber;
                    input.erase(0, 1);
                }
                else {
                    input.erase(0, 1);
                }
            }

        }

        maxMachine = machineList[17];
        newToken = maxMachine->CreateToken(input.substr(0, maxRead), lineNumber);
        tokens.push_back(newToken);


        /*for (unsigned int i = 0; i < tokens.size(); ++i) {

            cout << tokens[i]->toString() << endl;
        }

        
        cout << "Total Tokens = " << tokens.size() + 1;*/

        return tokens;
    }


};


#endif //LAB1_236_LEXER_H

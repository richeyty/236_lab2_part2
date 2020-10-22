//
// Created by tyler on 9/13/2020.
//

#ifndef LAB1_236_TOKEN_H
#define LAB1_236_TOKEN_H
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, ENDFILE, UNDEFINED
}; 

class Token {
private:
    string inputString;
    int lineNum;
    enum TokenType tokenType;
    string tokenString;
public:
    Token(TokenType type, string input, int lineNumber) {
        tokenType = type;
        lineNum = lineNumber;
        inputString = input;
    }

    string getTokenType() {
        toString();
        return tokenString;
    }

    string getTokenInput() {
        return inputString;
    }

    string toString() {

        if (tokenType == 0) {
            tokenString = "COMMA";
        }
        else if (tokenType == 1) {
            tokenString = "PERIOD";
        }
        else if (tokenType == 2) {
            tokenString = "Q_MARK";
        }
        else if (tokenType == 3) {
            tokenString = "LEFT_PAREN";
        }
        else if (tokenType == 4) {
            tokenString = "RIGHT_PAREN";
        }
        else if (tokenType == 5) {
            tokenString = "COLON";
        }
        else if (tokenType == 6) {
            tokenString = "COLON_DASH";
        }
        else if (tokenType == 7) {
            tokenString = "MULTIPLY";
        }
        else if (tokenType == 8) {
            tokenString = "ADD";
        }
        else if (tokenType == 9) {
            tokenString = "SCHEMES";
        }
        else if (tokenType == 10) {
            tokenString = "FACTS";
        }
        else if (tokenType == 11) {
            tokenString = "RULES";
        }
        else if (tokenType == 12) {
            tokenString = "QUERIES";
        }
        else if (tokenType == 13) {
            tokenString = "ID";
        }
        else if (tokenType == 14) {

            tokenString = "STRING";
        }
        else if (tokenType == 15) {
            tokenString = "COMMENT";
        }
        else if (tokenType == 16) {

            tokenString = "EOF";
        }
        else {
            tokenString = "UNDEFINED";
        }

        stringstream ss;
        ss << "(" << tokenString << "," << "\"" << inputString << "\"," << to_string(lineNum) << ")";

        return ss.str();
    }
};


#endif //LAB1_236_TOKEN_H

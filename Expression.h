#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "Parameter.h"
#include <string>
class Expression : public Parameter {
private:
	string expressionString;
public:
	Expression(string inputString) {
		this->expressionString = inputString;
	}
	
	string toString() {
		return "( " + expressionString + " )";
	}
};

#endif // EXPRESSION_H


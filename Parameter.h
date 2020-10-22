#ifndef LAB1_236_PARAMETER_H
#define LAB1_236_PARAMETER_H
#include <string>

using namespace std;

class Parameter {
protected:
	string input;
	bool isConstant;
	int index;
public:
	Parameter() {}
	Parameter(string inputString) {
		this->input = inputString;
		if (inputString.at(0) == '\'') {
			isConstant = true;
		}
		else {
			isConstant = false;
		}
	}
	bool getIsConstant() {
		return isConstant;
	}
	string toString() {
		return input;
	}
	void setIndex(int index) {
		this->index = index;
	}
	int getIndex() {
		return index;
	}
};

#endif //LAB1_236_PARAMETER_H

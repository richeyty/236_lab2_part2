#ifndef LAB1_236_PREDICATE_H
#define LAB1_236_PREDICATE_H
#include "Parameter.h"
#include <vector>
class Predicate
{
private:
	vector<Parameter> parameterList;
	string id;
public:
	Predicate() {}
	Predicate(string id, vector<Parameter> parameterList) {
		this->id = id;
		this->parameterList = parameterList;
	}
	string toString() {
		string vectorString;
		for (unsigned int i = 0; i < parameterList.size(); ++i) {
			vectorString = vectorString + parameterList.at(i).toString() + ",";
		}
		vectorString.pop_back();
		return id + "(" + vectorString + ")";
	}
	vector<Parameter> getParameterList() {
		return parameterList;
	}
	string getHeaderName() {
		return id;
	}
};

#endif // PREDICATE_H

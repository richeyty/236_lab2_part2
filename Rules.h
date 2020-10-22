#ifndef LAB1_236_RULES_H
#define LAB1_236_RULES_H
#include <vector>
#include "Predicate.h"
class Rules
{
private:
	Predicate headPredicate;
	vector<Predicate> predicateList;
public:
	Rules(Predicate headPredicate, vector<Predicate> predicateList) {
		this->headPredicate = headPredicate;
		this->predicateList = predicateList;
	}
	string toString() {
		string vectorString;
		for (unsigned int i = 0; i < predicateList.size(); ++i) {
			vectorString = vectorString + predicateList.at(i).toString() + ",";
		}
		vectorString.pop_back();
		return headPredicate.toString() + " :- " + vectorString + ".";
	}
};

#endif // RULES_H


#ifndef LAB1_236_TUPLE_H
#define LAB1_236_TUPLE_H
#include <vector>
#include <string>
using namespace std;
class Tuple
{
private:
	vector<string> tupleValues;
	
public:
	Tuple() {}
	Tuple(vector<string> values) {
		for (unsigned int i = 0; i < values.size(); ++i) {
			tupleValues.push_back(values.at(i));
		}
	}
	bool operator< (const Tuple& other) const {
		for (unsigned int i = 0; i < tupleValues.size(); ++i) {
			if (tupleValues.at(i) < other.tupleValues.at(i)) {
				return true;
			}
			else if (tupleValues.at(i) > other.tupleValues.at(i)) {
				return false;
			}
		}
		return false;
	}
	vector<string> toString() {
		return tupleValues;
	}
};

#endif //LAB1_236_TUPLE_H


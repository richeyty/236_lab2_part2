#ifndef LAB1_236_RELATION_H
#define LAB1_236_RELATION_H
#include <vector>
#include <string>
#include "Header.h"
#include <set>
#include "Tuple.h"
#include <iostream>
using namespace std;

class Relation
{
private:
	string headerName;
	Header header;
	set<Tuple> tupleSet;
	bool hasVariables = false;
public:
	Relation() {}
	Relation(Header header, string headerName) {
		this->header = header;
		this->headerName = headerName;
	}

	void addTuple(Tuple tupleObject) {
		tupleSet.insert(tupleObject);
	}

	Relation select(int index, string value) {
		Relation relationObject(header, headerName);
		for (Tuple t : tupleSet) {
			vector<string> tupleValues = t.toString();
			if (tupleValues.at(index) == value) {
				relationObject.addTuple(t);
			}
		}
		return relationObject;
	}

	Relation select(int index, int index2) {
		Relation relationObject(header, headerName);
		for (Tuple t : tupleSet) {
			vector<string> tupleValues = t.toString();
			if (tupleValues.at(index) == tupleValues.at(index2)) {
				relationObject.addTuple(t);
			}
		}
		return relationObject;
	}

	Relation project(vector<int> indices) {
		vector<string> headerAttributes = header.toString();
		vector<string> keepAttributes;
		for (unsigned int i = 0; i < indices.size(); ++i) {
			
			keepAttributes.push_back(headerAttributes.at(indices.at(i)));
		}
		Header newHeader(keepAttributes);
		Relation relationObject(newHeader, headerName);
		for (Tuple t : tupleSet) {
			vector<string> tupleValues = t.toString();
			vector<string> newTupleVals;
			for (unsigned int i = 0; i < indices.size(); ++i) {
				newTupleVals.push_back(tupleValues.at(indices.at(i)));
				
			}
			Tuple newTuple(newTupleVals); // NEW
			relationObject.addTuple(newTuple); // CHANGED
		}
		return relationObject;
	}

	Relation rename(vector<string> names) {
		Header newHeader(names);
		Relation relationObject(newHeader, headerName);
		for (Tuple t : tupleSet) {
			relationObject.addTuple(t);
		}
		return relationObject;
	}

	string toString() {
		string returnString;
		vector<string> attributes = header.toString();
		for (Tuple t : tupleSet) {
			vector<string> tupleValues = t.toString();
			returnString = returnString + " ";
			for (unsigned int j = 0; j < attributes.size(); ++j) {
				returnString = returnString + " " + attributes.at(j) + "=";  // CHANGED
				returnString = returnString + tupleValues.at(j) + ",";
			}
			returnString.pop_back();
			returnString = returnString + "\n";
		}
		returnString.pop_back(); // CHANGED - Requires other changes to work.
		return returnString;
	}

	string getHeaderName() {
		return headerName;
	}

	int getTuplesSize() {
		return tupleSet.size();
	}

	void setHasVariables() {
		hasVariables = true;
	}

	bool getHasVariables() {
		return hasVariables;
	}
};
#endif // RELATION_H


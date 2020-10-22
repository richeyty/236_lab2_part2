#ifndef LAB1_236_DATABASE_H
#define LAB1_236_DATABASE_H
#include <map>
#include <vector>
#include "Predicate.h"
#include "Relation.h"
using namespace std;
class Database
{
private:
	Relation relationObject;
	map<string, Relation> Map;
public:
	Database() {}
	void insertRelation(Relation relationObject) {
		Map.insert(make_pair(relationObject.getHeaderName(), relationObject));
	}
	void insertTuple(Tuple tupleObject, string headerName) {
		Map[headerName].addTuple(tupleObject);
	}
	Relation getRelation(string headerName) {
		return Map[headerName];
	}
};
#endif // DATABASE_H


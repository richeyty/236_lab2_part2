#ifndef LAB1_236_INTERPETER_H
#define LAB1_236_INTERPRETER_H
#include "Datalog.h"
#include "Database.h"
using namespace std;
class Interpreter
{
private:
	Datalog datalogObject;
	Database databaseObject;
public:
	Interpreter() {}
	Interpreter(Datalog datalogObject) {
		this->datalogObject = datalogObject;
		vector<Predicate> schemeList = datalogObject.getSchemes();
		vector<Predicate> factList = datalogObject.getFacts();
		string headerName;
		
		for (unsigned int i = 0; i < schemeList.size(); ++i) {
			headerName = schemeList.at(i).getHeaderName();
			vector<Parameter> parameterList = schemeList.at(i).getParameterList();
			vector<string> attributes;
			for (unsigned int j = 0; j < parameterList.size(); ++j) {
				attributes.push_back(parameterList.at(j).toString());
			}
			Header headerObject(attributes);
			Relation relationObject(headerObject, headerName);
			databaseObject.insertRelation(relationObject);
		}

		for (unsigned int i = 0; i < factList.size(); ++i) {
			headerName = factList.at(i).getHeaderName();
			vector<Parameter> parameterList = factList.at(i).getParameterList();
			vector<string> tupleStrings;
			for (unsigned int j = 0; j < parameterList.size(); ++j) {
				tupleStrings.push_back(parameterList.at(j).toString());
			}
			Tuple tupleObject(tupleStrings);
			databaseObject.insertTuple(tupleObject, headerName);
		}
	}

	Relation evaluatePredicate(Predicate p) {
		string headerName = p.getHeaderName();
		Relation queryRelation = databaseObject.getRelation(headerName);
		vector<Parameter> queryParameters = p.getParameterList();
		vector<Parameter> seenBefore;
		vector<int> indices;
		vector<string> names;
		bool isMatch = false;
		int index;
		for (unsigned int i = 0; i < queryParameters.size(); ++i) {
			if (queryParameters.at(i).getIsConstant() == true) {
				queryRelation = queryRelation.select(i, queryParameters.at(i).toString());
			}
			if (queryParameters.at(i).getIsConstant() == false) {
				for (unsigned int j = 0; j < seenBefore.size(); ++j) {
					if (seenBefore.at(j).toString() == queryParameters.at(i).toString()) {
						isMatch = true;
						index = j; // NEW
					}
				}
				if (isMatch == false) {
					seenBefore.push_back(queryParameters.at(i));
					indices.push_back(i); // NEW
					names.push_back(queryParameters.at(i).toString()); // NEW
				}
				else {
					queryRelation = queryRelation.select(i, index);
				}
				isMatch = false;
				
			}
		}
		if (seenBefore.size() != 0) {
			queryRelation = queryRelation.project(indices);
			queryRelation = queryRelation.rename(names);
		}
		
		if (seenBefore.size() > 0) {
			queryRelation.setHasVariables();
		}
		
		return queryRelation;
	}
	
	void interpretQueries() {
		vector<Predicate> queryList = datalogObject.getQueries();
		vector<Relation> relations;
		for (unsigned int i = 0; i < queryList.size(); ++i) {
			cout << queryList.at(i).toString() << "? ";
			relations.push_back(evaluatePredicate(queryList.at(i)));
			if (relations.at(i).getTuplesSize() > 0) {
				cout << "Yes(" << relations.at(i).getTuplesSize() << ")" << endl;
				if (relations.at(i).getHasVariables() == true) {
					cout << relations.at(i).toString() << endl; // MOVED
				}
				
			}
			else {
				cout << "No" << endl;
			}
			
		}
		for (unsigned int i = 0; i < relations.size(); ++i) {
			
			
		}
	}
};

#endif // INTERPRETER_H


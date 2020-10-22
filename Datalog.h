#ifndef LAB1_DATALOG_H
#define LAB1_DATALOG_H
#include "Predicate.h"
#include "Parameter.h"
#include "Rules.h"
#include <vector>
#include <sstream>
#include <set>
#include <iostream>
#include <string>

using namespace std;

class Datalog {
private:
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rules> rules;
	set<string> factsSet;
	std::set<string>::iterator it;
public:
	Datalog() {}
	Datalog(vector<Predicate> schemes, vector<Predicate> facts, vector<Predicate> queries, vector<Rules> rules) {
		this->schemes = schemes;
		this->facts = facts;
		this->queries = queries;
		this->rules = rules;
	}
	vector<Predicate> getSchemes() {
		return schemes;
	}
	vector<Predicate> getFacts() {
		return facts;
	}
	vector<Predicate> getQueries() {
		return queries;
	}
	string toString() {
		stringstream ss;
		ss << "Schemes(" << schemes.size() << "):\n";
		for (unsigned int i = 0; i < schemes.size(); ++i) {
			ss << "  " << schemes.at(i).toString() << "\n";
		}
		ss << "Facts(" << facts.size() << "):\n";
		for (unsigned int i = 0; i < facts.size(); ++i) {
			ss << "  " << facts.at(i).toString() << ".\n";
		}
		ss << "Rules(" << rules.size() << "):\n";
		for (unsigned int i = 0; i < rules.size(); ++i) {
			ss << "  " << rules.at(i).toString() << "\n";
		}
		ss << "Queries(" << queries.size() << "):\n";
		for (unsigned int i = 0; i < queries.size(); ++i) {
			ss << "  " << queries.at(i).toString() << "?\n";
		}
		// DO DOMAIN HERE
		for (unsigned int i = 0; i < facts.size(); ++i) {
			vector<Parameter> parameters;
			parameters = facts.at(i).getParameterList();
			
			for (unsigned int j = 0; j < parameters.size(); ++j) {
				
				Parameter parameterToInsert = parameters.at(j);
				factsSet.insert(parameterToInsert.toString());
			}
		}
		
		ss << "Domain(" << factsSet.size() << "):\n";
		for (it = factsSet.begin(); it != factsSet.end(); ++it) {
			
			ss << "  " << *it << "\n";
			
		}

		return ss.str();
		
	}
};


#endif //LAB1_DATALOG_H


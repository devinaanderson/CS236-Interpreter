#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"

using namespace std;


class Interpreter
{
private:
	DatalogProgram datalog;
	Database database;

public:
	Interpreter(DatalogProgram d) {
		datalog = d;
	};

	~Interpreter() {};

	Relation* EvalPredicate(const Predicate p) {		Relation *r = NULL;		r = new Relation;		r->name = p.name;		Header h(p.params);		r->header = h;		r->ToString();		return r;	};	void EvalSchemes() {		for (Predicate p : datalog.schemes) {			database.AddRelation(EvalPredicate(p));		}	};	void EvalFacts() {		for (Predicate p : datalog.facts) {			Tuple t(p.params);			database.map[p.name]->tuples.insert(t);		//database.ADD TUPLE TO RELATION WITH SAME NAME AS FACT		}	};	void EvalQueries() {		for (Predicate p : datalog.queries) {			Relation *r = database.map[p.name];			//r->Select			/*select for each constant in the query ‘q’
			select for each pair of matching variables in ‘q’
			project using the positions of the variables in ‘q’
			rename to match the names of variables in ‘q’
			print the resulting relation*/		}	};
};


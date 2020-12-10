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

	Relation* EvalPredicate(const Predicate p) {
			select for each pair of matching variables in �q�
			project using the positions of the variables in �q�
			rename to match the names of variables in �q�
			print the resulting relation*/
};

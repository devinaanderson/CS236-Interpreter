#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Relation.h"

using namespace std;


class Database
{
public:
	map<string, Relation*> map;
public:
	Database();
	~Database();
	void AddRelation(Relation *r) {
		map.insert(pair<string, Relation*>(r->name, r));
	};
};



Database::Database()
{
}


Database::~Database()
{
}

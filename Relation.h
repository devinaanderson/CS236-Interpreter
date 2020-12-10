#pragma once
#include <iostream>
#include <set>
#include "Tuple.h"
#include "Header.h"

using namespace std;


class Relation
{
private:
	
public:
	string name;
	Header header;
	set<Tuple> tuples;

	Relation();
	~Relation();
	Relation Select(int index, string val) {};
	Relation Select(int index1, int index2) {};
	Relation Project(vector<int> columns) {};
	Relation Rename(vector<string> attributes) {};

	void ToString() {
		cout << "Name: " << name << endl;
		cout << "Header: ";
		header.ToString();
		cout << endl;
	}
};



Relation::Relation()
{
}


Relation::~Relation()
{
}

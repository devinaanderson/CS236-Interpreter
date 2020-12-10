#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Tuple
{
private:
	vector<string> values;
public:
	Tuple(vector<Parameter>);
	~Tuple();

	bool operator<(const Tuple& tuple) const {
		return this->values < tuple.values;
	}
};

Tuple::Tuple(vector<Parameter> params)
{
	for (Parameter p : params) {
		values.push_back(p.ToString());
	}
}


Tuple::~Tuple()
{
}


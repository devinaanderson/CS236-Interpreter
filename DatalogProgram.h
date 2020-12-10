#pragma once
//#include "Parser.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

class Parameter
{
private:
	string value;

public:
	Parameter(string paramVal) {
		value = paramVal;
	};
	string ToString() {
		return value;
	};
};


class Predicate
{
private:

public:
	string name;

	vector<Parameter> params;

	Predicate(string predName) {
		name = predName;
	};

	Predicate() {
	};

	void AddParam(string value) {
		Parameter param(value);
		params.push_back(param);
	};

	string ToString() {
		stringstream ss;
		ss << name << "(";
		for (unsigned int i = 0; i < params.size(); i++) {
			ss << params[i].ToString();
			if (i != params.size() - 1) ss << ",";
		}
		ss << ")";
		return ss.str();
	};

	const string GetName() {
		return name;
	}
};


class Rule
{
private:
	Predicate headPred;
	vector<Predicate> bodyPreds;

public:

	Rule(Predicate head) {
		headPred = head;
	};
	
	void AddBodyPred(Predicate pred) {
		bodyPreds.push_back(pred);
	};

	string ToString() {
		stringstream ss;
		ss << headPred.ToString() << " :- ";
		for (unsigned int i = 0; i < bodyPreds.size(); i++) {
			ss << bodyPreds[i].ToString();
			if (i != bodyPreds.size() - 1) ss << ",";
		}
		return ss.str();
	};

};



class DatalogProgram
{
public:
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rule> rules;
	set<string> domain;

	DatalogProgram();

	void FillDomain();
	void ToString();

};

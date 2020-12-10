#pragma once
#include <iostream>
#include "Token.h"
#include "DatalogProgram.h"
#include <vector>
#include <string>


using namespace std;

class Parser
{
private:
	vector<Token> tokenList;

	void ParseSchemeList();
	void ParseFactList();
	void ParseRuleList();
	void ParseQueryList();

	void ParseScheme();
	void ParseFact();
	void ParseRule();
	void ParseQuery();

	Predicate ParseHeadPredicate();
	Predicate ParsePredicate();

	void ParsePredicatelist();
	void ParsePredicatelist(Rule &rule);
	void ParseParameterlist(Predicate &pred);
	void ParseStringlist(Predicate &pred);
	void ParseIDlist(Predicate &p);

	string ParseParameter();
	string ParseExpression();
	string ParseOperator();


public:
	DatalogProgram datalog;
	int index = 0;
	Parser(vector<Token> tokenList);
	void Parse();
	void Compare(string type);
	void ParseDatalogProgram();
	DatalogProgram GetDatalog();
};
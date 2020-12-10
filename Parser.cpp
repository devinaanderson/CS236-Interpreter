#include "Parser.h"
#include <sstream>



Parser::Parser(vector<Token> lexerTokens)
{
	tokenList = lexerTokens;

	Parse();
}


void Parser::Parse()
{
	try
	{
		ParseDatalogProgram();
		//cout << "Success!" << endl;
		//datalog.ToString();
	}
	catch (Token error)
	{
		cout << "Failure!" << endl;
		cout << "  " << error.ToString() << endl;
	}
}

void Parser::Compare(string type) {
	if (tokenList.at(index).typeAsString() == type) {
		index++;
	}
	else {
		throw(tokenList.at(index));
	}
}

void Parser::ParseDatalogProgram()
{
	//SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
	Compare("SCHEMES");
	Compare("COLON");
	ParseScheme();
	ParseSchemeList();
	Compare("FACTS");
	Compare("COLON");
	ParseFactList();
	Compare("RULES");
	Compare("COLON");
	ParseRuleList();
	Compare("QUERIES");
	Compare("COLON");
	ParseQueryList();
	Compare("EOF");
}

DatalogProgram Parser::GetDatalog()
{
	return datalog;
}

void Parser::ParseSchemeList()		//schemeList	->	scheme schemeList | lambda
{
	if (tokenList.at(index).typeAsString() == "ID") {
		ParseScheme();
		ParseSchemeList();
	}
}

void Parser::ParseScheme()		//scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
{
	Compare("ID");
	Predicate scheme(tokenList.at(index - 1).GetVal());

	Compare("LEFT_PAREN");
	Compare("ID");
	scheme.AddParam(tokenList.at(index - 1).GetVal());

	ParseIDlist(scheme);
	Compare("RIGHT_PAREN");
	datalog.schemes.push_back(scheme);
}

void Parser::ParseFactList()		//factList	->	fact factList | lambda
{
	if (tokenList.at(index).typeAsString() == "ID") {
		ParseFact();
		ParseFactList();
	}
}

void Parser::ParseFact()		//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
{
	Compare("ID");
	Predicate fact(tokenList.at(index - 1).GetVal());

	Compare("LEFT_PAREN");
	Compare("STRING");
	fact.AddParam(tokenList.at(index - 1).GetVal());

	ParseStringlist(fact);
	Compare("RIGHT_PAREN");
	Compare("PERIOD");
	datalog.facts.push_back(fact);
}


void Parser::ParseRuleList()		//ruleList	->	rule ruleList | lambda
{
	if (tokenList.at(index).typeAsString() == "ID") {
		ParseRule();
		ParseRuleList();
		return;
	}
}

void Parser::ParseRule()		//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
{
	Rule currRule(ParseHeadPredicate());
	Compare("COLON_DASH");
	currRule.AddBodyPred(ParsePredicate());
	ParsePredicatelist(currRule);
	Compare("PERIOD");
	datalog.rules.push_back(currRule);
}

void Parser::ParseQueryList()		//queryList	->	query queryList | lambda
{
	if (tokenList.at(index).typeAsString() == "ID") {
		ParseQuery();
		ParseQueryList();
	}
}

void Parser::ParseQuery()		//query	        ->      predicate Q_MARK
{
	Predicate query = ParsePredicate();
	Compare("Q_MARK");
	datalog.queries.push_back(query);
}

Predicate Parser::ParseHeadPredicate()		//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
{
	Compare("ID");
	Predicate pred(tokenList.at(index - 1).GetVal());

	Compare("LEFT_PAREN");
	Compare("ID");
	pred.AddParam(tokenList.at(index - 1).GetVal());
	ParseIDlist(pred);
	Compare("RIGHT_PAREN");

	return pred;
}

Predicate Parser::ParsePredicate()			//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
{
	Compare("ID");
	Predicate pred(tokenList.at(index - 1).GetVal());
	Compare("LEFT_PAREN");
	pred.AddParam(ParseParameter());
	ParseParameterlist(pred);
	Compare("RIGHT_PAREN");

	return pred;
}

void Parser::ParsePredicatelist()		//predicateList	->	COMMA predicate predicateList | lambda
{
	if (tokenList.at(index).typeAsString() == "COMMA") {
		Compare("COMMA");
		ParsePredicate();
		ParsePredicatelist();
	}
}

void Parser::ParsePredicatelist(Rule& rule)		//predicateList	->	COMMA predicate predicateList | lambda
{
	if (tokenList.at(index).typeAsString() == "COMMA") {
		Compare("COMMA");
		rule.AddBodyPred(ParsePredicate());
		ParsePredicatelist(rule);
	}
}

void Parser::ParseParameterlist(Predicate& pred)		//parameterList	-> 	COMMA parameter parameterList | lambda
{
	if (tokenList.at(index).typeAsString() == "COMMA") {
		Compare("COMMA");
		pred.AddParam(ParseParameter());
		ParseParameterlist(pred);
	}
}

void Parser::ParseStringlist(Predicate& pred)			//stringList	-> 	COMMA STRING stringList | lambda
{
	if (tokenList.at(index).typeAsString() == "COMMA") {
		Compare("COMMA");
		Compare("STRING");

		pred.AddParam(tokenList.at(index - 1).GetVal());


		ParseStringlist(pred);
	}
}

void Parser::ParseIDlist(Predicate& pred)			 	//idList  	-> 	COMMA ID idList | lambda
{
	if (tokenList.at(index).typeAsString() == "COMMA") {
		Compare("COMMA");
		Compare("ID");
		pred.AddParam(tokenList.at(index - 1).GetVal());

		ParseIDlist(pred);
	}
}

string Parser::ParseParameter()		//parameter	->	STRING | ID | expression
{
	if (tokenList.at(index).typeAsString() == "STRING") {
		Compare("STRING");
		return tokenList.at(index - 1).GetVal();
	}
	else if (tokenList.at(index).typeAsString() == "ID") {
		Compare("ID");
		return tokenList.at(index - 1).GetVal();
	}
	else if (tokenList.at(index).typeAsString() == "LEFT_PAREN") {
		return ParseExpression();
	}
	else {
		throw(tokenList.at(index));
	}
}

string Parser::ParseExpression()		//expression	->	LEFT_PAREN parameter operator parameter RIGHT_PAREN
{
	stringstream ss;
	Compare("LEFT_PAREN");
	ss << tokenList.at(index - 1).GetVal();
	ss << ParseParameter();
	ss << ParseOperator();
	ss << ParseParameter();
	Compare("RIGHT_PAREN");
	ss << tokenList.at(index - 1).GetVal();
	
	return ss.str();
}

string Parser::ParseOperator()		//operator	->	ADD | MULTIPLY
{
	if (tokenList.at(index).typeAsString() == "ADD") {
		Compare("ADD");
		return tokenList.at(index - 1).GetVal();
	}
	else if (tokenList.at(index).typeAsString() == "MULTIPLY") {
		Compare("MULTIPLY");
		return tokenList.at(index - 1).GetVal();
	}
	else {
		throw(tokenList.at(index));
	}
}
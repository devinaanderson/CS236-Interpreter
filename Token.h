#pragma once

#include <string>

using namespace std;

enum TokenType
{
	QUERIES,
	SCHEMES, 
	FACTS,
	RULES,
	ID,
	STRING,
	COMMENT,
	LEFT_PAREN,
	RIGHT_PAREN,
	COMMA,
	PERIOD,
	Q_MARK,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	EOF_TOKEN,
	UNDEFINED
};

class Token
{
private:
	string val;			// The actual value
	int lineNum;
	TokenType type;

public:
	Token(string value, int lineNumber, TokenType thisTokenType);
	~Token();

	string GetVal();
	string ToString();
	string typeAsString();





};


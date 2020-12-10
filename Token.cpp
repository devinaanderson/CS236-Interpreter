#include "Token.h"



Token::Token(string value, int lineNumber, TokenType thisTokenType)
{
	val = value;
	lineNum = lineNumber;
	type = thisTokenType;


}

Token::~Token()
{
}

string Token::GetVal()
{
	return val;
}

string Token::typeAsString() 
{
	switch (type)
	{
	case QUERIES: return "QUERIES"; break; //Needs to return (QUERIES, "Query", 6)
	case SCHEMES: return "SCHEMES"; break;
	case FACTS: return "FACTS"; break;
	case RULES: return "RULES"; break;
	case ID: return "ID"; break;
	case STRING: return "STRING"; break;
	case COMMENT: return "COMMENT"; break;
	case COLON: return "COLON"; break;
	case COLON_DASH: return "COLON_DASH"; break;
	case LEFT_PAREN: return "LEFT_PAREN"; break;
	case RIGHT_PAREN: return "RIGHT_PAREN"; break;
	case COMMA: return "COMMA"; break;
	case PERIOD: return "PERIOD"; break;
	case Q_MARK: return "Q_MARK"; break;
	case MULTIPLY: return "MULTIPLY"; break;
	case ADD: return "ADD"; break;
	case EOF_TOKEN: return "EOF"; break;
	case UNDEFINED: return "UNDEFINED"; break;
	}
	return "ERROR";
}

string Token::ToString()
{
	string stringified = "(" + typeAsString() + ",\"" + val + "\"," + to_string(lineNum) + ")";
	return stringified;
}

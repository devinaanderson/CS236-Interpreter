#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Token.h"
using namespace std;

class Lexer
{
private: 
	void ReadFile(string fileName);
	void GetNextToken(ifstream &input);
	Token Tokenize(string value);
	Token Tokenize(TokenType tokenType);
	void PushPeekedChar(char & next, string & str, ifstream & input);
	vector<Token> tokensList;
	int lineNum;

public:
	Lexer(string fileName);
	~Lexer();
	void PrintOutput();

	vector<Token> GetTokensList();

};



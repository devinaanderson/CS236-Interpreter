#include "Lexer.h"


Lexer::Lexer(string fileName)
{
	lineNum = 1;
	ReadFile(fileName);
}


Lexer::~Lexer()
{
}


void Lexer::ReadFile(string fileName)
{
	ifstream input;


	input.open(fileName.data());
	if (!input) {
		cerr << "File cannot be read";
		exit(1);
	}

	while (input.peek() != EOF) {
		GetNextToken(input);
	}
	tokensList.push_back(Tokenize(EOF_TOKEN));
}


void Lexer::GetNextToken(ifstream &input)
{
	char next = input.peek();
	
	if (isspace(next)) {										//skip through whitespace
		if (next == '\n') {
			lineNum++;
		}
		input.get(next);
		return;
	}
	string str = "";


	if (next == '#') {											//Comments
		PushPeekedChar(next, str, input);
		next = input.peek();
		if (next == '|') {												//Block Comment
			int newLinesInBlock = 0;
			input.get(next);
			str += next;
			next = input.peek();	
			while (next != EOF) {
				if (next == '|') {
					PushPeekedChar(next, str, input);
					next = input.peek();
					if (next == '#') {
						PushPeekedChar(next, str, input);
						break;
					}
					else {
						continue;
					}
				}
				if (next == '\n') {
					newLinesInBlock++;
				}
				PushPeekedChar(next, str, input);
				next = input.peek();
			}
			//tokensList.push_back(Tokenize(str));						Don't add comments to vector
			lineNum += newLinesInBlock;
			return;
		}

		else {															//Line Comment
			while (next != EOF) {
				if (next == '\n') {
					break;
				}
				input.get(next);
				str += next;
				next = input.peek();
			}
			//tokensList.push_back(Tokenize(str));						Don't add comments to vector
			return;
		}
	}

	else if (next == '\'') {					//String
		
		char quoteType = '\'';
		int newLinesInBlock = 0;
		PushPeekedChar(next, str, input);
		next = input.peek();


		while (next != EOF) {
			if (next == quoteType) {
				PushPeekedChar(next, str, input);
				next = input.peek();
				if (next == quoteType) {
					PushPeekedChar(next, str, input);
					next = input.peek();
					continue;
				}
				else {
					tokensList.push_back(Tokenize(str));
					lineNum += newLinesInBlock;
					newLinesInBlock = 0;
					return;
				}
			}
			if (next == '\n') { 
				newLinesInBlock++;
			}
			PushPeekedChar(next, str, input);
			next = input.peek();
		}

		tokensList.push_back(Tokenize(str));
		lineNum += newLinesInBlock;
		newLinesInBlock = 0;
		return;
	}

	else if (isalpha(next)) {									//Keyword or ID
		do {
			PushPeekedChar(next, str, input);
			next = input.peek();
		}	while (isalnum(next));

		tokensList.push_back(Tokenize(str));
		return;
	}

	else if (next == ':') {										//Colon or Colon dash
		PushPeekedChar(next, str, input);
		next = input.peek();
		if (next == '-') {
			PushPeekedChar(next, str, input);
		}
		tokensList.push_back(Tokenize(str));
		return;
	}

	else {														//All other symbols and numbers, single character token values
		PushPeekedChar(next, str, input);
		tokensList.push_back(Tokenize(str));
		return;
	}
		
	cout << "SOMETHING'S WRONG" << endl;
	return;	
}


Token Lexer::Tokenize(string value)
{
	TokenType type;
	if (value == "(") {
		type = LEFT_PAREN;
	}
	else if (value == ")") {
		type = RIGHT_PAREN;
	}
	else if (value == "?") {
		type = Q_MARK;
	}
	else if (value == ".") {
		type = PERIOD;
	}
	else if (value == ",") {
		type = COMMA;
	}
	else if (value == "*") {
		type = MULTIPLY;
	}
	else if (value == "+") {
		type = ADD;
	}
	else if (value == ":") {
		type = COLON;
	}
	else if (value == ":-") {
		type = COLON_DASH;
	}
	else if (value == "Queries") {
		type = QUERIES;
	}
	else if (value == "Schemes") {
		type = SCHEMES;
	}
	else if (value == "Facts") {
		type = FACTS;
	}
	else if (value == "Rules") {
		type = RULES;
	}
	else if (value == "END OF FILE") {
		type = EOF_TOKEN;
	}
	else if (isalpha(value.front())) {
		type = ID;
	}
	else if (value.front() == '\'' && value.back() == '\'') {
		type = STRING;
	}
	else if (value.compare(0, 2, "#|") == 0 && value.compare(value.length() - 2, 2, "|#") == 0) {
		type = COMMENT;
	}
	else if (value.front() == '#' && value.find('\n') == string::npos) {
		type = COMMENT;
	}
	else {
		type = UNDEFINED;
	}

	return Token(value, lineNum, type);
}


Token Lexer::Tokenize(TokenType tokenType) {
	return Token("", lineNum, tokenType);
}


void Lexer::PushPeekedChar(char &next, string &str, ifstream &input) {
	input.get(next);
	str += next;
}


void Lexer::PrintOutput() 
{
	for (unsigned int i = 0; i < tokensList.size(); i++) {
		cout << tokensList.at(i).ToString() << endl;
	}
	cout << "Total Tokens = " << tokensList.size() << endl;
}

vector<Token> Lexer::GetTokensList()
{
	return tokensList;
}
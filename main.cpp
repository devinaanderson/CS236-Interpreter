#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[1]) {

	string fileName = argv[1];
	Lexer Lexer(fileName);

	Parser Parser(Lexer.GetTokensList());

	Interpreter Interpreter(Parser.GetDatalog());

	Interpreter.EvalSchemes();

	

	return 0;
}
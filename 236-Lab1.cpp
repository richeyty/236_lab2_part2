#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Datalog.h"
#include "Interpreter.h"
using namespace std;
int main(int argc, char* argv[]) {
    ifstream in(argv[1]);

    if (!in.is_open()) {
        cerr << "Unable to open " << argv[1] << " for input" << endl;
        return 2;
    }

    ostringstream sstr;
    sstr << in.rdbuf();
    string lexerInput = sstr.str();


    Lexer lexerObject;
    Parser parserObject;
    Datalog datalogObject;
    
    
    datalogObject = parserObject.parse(lexerObject.runLexer(lexerInput));
    Interpreter interpreterObject(datalogObject);
    interpreterObject.interpretQueries();

    return 0;
}
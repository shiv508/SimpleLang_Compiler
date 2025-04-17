#include <iostream>
#include <fstream>
#include <memory>
#include "lexer.h"
#include "parser.h"

using namespace std;

void printTokens(vector<Token> &tokens)
{
    for (Token t : tokens)
    {
        cout << "Token Value" << t.value << "token number" << static_cast<int>(t.type) << endl;
    }
}

int main()
{
    ifstream inputFile("input.txt");
    ofstream outFile("output.asm");

    if (!outFile.is_open())
    {
        cout << "output file not open" << endl;
    }
    string sourceCode((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();
    Lexer lexer(sourceCode);
    vector<Token> tokens = lexer.tokenize();

    printTokens(tokens);
    cout << "token going to parse" << endl;
    Parser parser(tokens);
    cout << "token parsed" << endl;
    shared_ptr<ASTNode> ast = parser.parse();

    if (ast)
    {
        cout << "going to parsing" << endl;
        outFile << ".txt" << endl;
        ast->generateCode(outFile);
    }
    else
    {
        cerr << "parsing faild" << endl;
    }
    outFile << "hit" << endl;
    outFile.close();
    return 0;
}
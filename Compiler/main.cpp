/* 
 * File:   main.cpp
 * Author: Jordan Ross
 *
 * Created on January 22, 2014, 9:56 PM
 */

#include <cstdlib>
#include <iostream>
#include "Scanner.h"
#include "Types.h"
#include "SymbolTable.h"

using namespace std;

/// Global variable for the symbol table.
SymbolTable* symbolTable = new SymbolTable();

/*
 * 
 */
int main(int argc, char** argv) {
    // Uncomment this line when we release
    //char* fileName = argv[1];
    const char* fileName = "B:\\Documents\\GitHub\\CompilerProject\\CompilerProject\\test_program.txt";
    
    // Keep track of the current line number
    int curLineCount = 0;
    
    // Print message to let user know the compiler  is starting
    cout << "Starting compilation of " << fileName << " ..." << endl;
    
    // Open up the file
    FILE *pFile;
    //pFile = fopen("B:/Documents/GitHub/CompilerProject/ComplierProject/test_program.txt", "r");
    pFile = fopen("D:\\GitRepo\\Compiler_Project\\ComplierProject\\Compiler\\test_program.txt", "r");
    if (!pFile)
    {
        cout << "Could not open specified file!" << endl;
        return 0;
    }
    
    // Instantiate a scanner object
    Scanner *scanner = new Scanner(pFile);
    
    // Initialize the scanner
    scanner->Initialize();
    
    //TEST: Remove the following lines when we have a parser.
    Token allTokens[30];
    int curToken = 0;
    
    // Create a token structure to pass and fill.
    Token token;
    
    // Process one token at a time
    scanner->ScanOneToken(&token);
    
    // Continue scanning tokens one at at time until we reach the end of the
    // file.
    while (token.name != T_EOF) // Replace -8762 with the EOF constant
    {
        if (token.name != 0)
        {
            // Process the token
            
            // TEST: We are just going to save them off for now.
            allTokens[curToken] = token;
            curToken++;
            
        }
        // Get the next token
        scanner->ScanOneToken(&token);
    }
    
    
    fclose(pFile);
    
    // Report any Scanner Errors
    // TODO: Change this hard coded 20
    std::string scannerErrorMessages[20];
    scanner->GetErrorMessages(scannerErrorMessages);
    for (int i = 0 ; i < 20; i++)
    {
        cout << scannerErrorMessages[i] << endl;
    }
    
    return 0;
}


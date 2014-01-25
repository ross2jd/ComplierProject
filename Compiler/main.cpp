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

using namespace std;

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
    pFile = fopen("B:/Documents/GitHub/CompilerProject/ComplierProject/test_program.txt", "r");
    
    // Instantiate a scanner object
    Scanner *scanner = new Scanner(pFile);
    
    // Initialize the scanner
    
    //TEST: Remove the following lines when we have a parser.
    Token allTokens[15];
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
    
    return 0;
}


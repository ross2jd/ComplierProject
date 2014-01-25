/* 
 * File:   Scanner.h
 * Author: Jordan Ross
 *
 * Created on January 25, 2014, 7:43 AM
 */

#ifndef SCANNER_H
#define	SCANNER_H

#include <stdio.h>
#include "Types.h"
#include "ScannerStates.h"


class Scanner {
public:
    //----------------------- PUBLIC METHODS-------------------------//
    
    // Method to initialize the scanner
    void Initialize();
    
    // Method to scan one token from the file
    void ScanOneToken(Token *token);
    
    // Method to unset all values of the token structure
    void ClearToken(Token *token);
    
    // Constructor
    Scanner(FILE *fp);
    
    // Copy constructor
    Scanner(const Scanner& orig);
    
    // Default destructor
    virtual ~Scanner();
private:
    //----------------------- PRIVATE MEMBERS ------------------------//
    
    /// Holds the pointer to the input file handle
    FILE *pFile;
    
    /// Holds the current token that is being built
    Token curToken;
    
    //----------------------- PRIVATE METHODS ------------------------//
    
    /// Process the start state
    ScannerStateType ProcessStartState(char &curChar);
    
    /// Process the comment state
    ScannerStateType ProcessCommentState();
    
    /// Process the identifier/reserved word state
    ScannerStateType ProcessIdentifierState(char curChar);
};

#endif	/* SCANNER_H */


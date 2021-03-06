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
#include "Error.h"
#include "ReservedTable.h"

///////////////////////////////////////////////////////////////////////////////
/// @class Scanner
/// @brief Class for encapsulating the functionality for the scanner 
/// implementation for compiler
///
/// <h1>Design</h1>
/// This will contain the design for the Scanner class.
///
/// @author Jordan Ross
///////////////////////////////////////////////////////////////////////////////
class Scanner {
public:
    //----------------------- PUBLIC METHODS-------------------------//
    
    // Method to initialize the scanner
    void Initialize();
    
    // Method to scan one token from the file
    void ScanOneToken(Token *token);
    
    // Method to unset all values of the token structure
    void ClearToken(Token *token);
    
    // Method to get all scanner Error messages
    void GetErrorMessages(std::string messages[]);
    
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
    
    /// Holds the current line number in the file being scanned
    int curLineNumber;
    
    /// Holds the current column number in the file being scanned
    int curColNumber;
    
    /// Holds the object for the Error class.
    Error* error;
    
    /// Holds the object for the ReservedTable class.
    ReservedTable* reservedTable;
    
    //----------------------- PRIVATE METHODS ------------------------//
    
    /// Process the start state
    ScannerStateType ProcessStartState(char &curChar);
    
    /// Process the comment state
    ScannerStateType ProcessCommentState();
    
    /// Process the identifier/reserved word state
    ScannerStateType ProcessIdentifierState(char curChar);
    
    /// Process the number state
    ScannerStateType ProcessNumberState(char curDigit);
    
    /// Process the string state
    ScannerStateType ProcessStringState(char curChar);
    
    /// Process any operator state
    ScannerStateType ProcessOperatorState(char curChar, ScannerStateType state);
    
    /// Process relative operators among misc tokens
    ScannerStateType ProcessOtherTokenState(char curChar, ScannerStateType state);
};

#endif	/* SCANNER_H */


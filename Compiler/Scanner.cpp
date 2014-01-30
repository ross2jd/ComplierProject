/* 
 * File:   Scanner.cpp
 * Author: Jordan Ross
 * 
 * Created on January 25, 2014, 7:43 AM
 */

#include "Scanner.h"
#include <cstring>
#include <cctype>

// ------------------- PUBLIC METHOD DEFINITIONS ----------------------------//

///////////////////////////////////////////////////////////////////////////////
/// @method Initialize
///
/// @details Initializes the scanner by reseting all counters and inserts all
/// of the reserved words into the the ReservedTable object.
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void Scanner::Initialize()
{
    // Reset the line number and column numbers
    this->curLineNumber = 1;
    this->curColNumber = 1;
    
    // Setup the reserved table
    this->reservedTable->InsertEntry("string", T_STRING);
    this->reservedTable->InsertEntry("int", T_INT);
    this->reservedTable->InsertEntry("bool", T_BOOL);
    this->reservedTable->InsertEntry("float", T_FLOAT);
    this->reservedTable->InsertEntry("global", T_GLOBAL);
    this->reservedTable->InsertEntry("in", T_IN);
    this->reservedTable->InsertEntry("out", T_OUT);
    this->reservedTable->InsertEntry("if", T_IF);
    this->reservedTable->InsertEntry("then", T_THEN);
    this->reservedTable->InsertEntry("else", T_ELSE);
    this->reservedTable->InsertEntry("case", T_CASE);
    this->reservedTable->InsertEntry("for", T_FOR);
    this->reservedTable->InsertEntry("and", T_AND);
    this->reservedTable->InsertEntry("or", T_OR);
    this->reservedTable->InsertEntry("not", T_NOT);
    this->reservedTable->InsertEntry("program", T_PROGRAM);
    this->reservedTable->InsertEntry("procedure", T_PROCEDURE);
    this->reservedTable->InsertEntry("begin", T_BEGIN);
    this->reservedTable->InsertEntry("return", T_RETURN);
    this->reservedTable->InsertEntry("end", T_END);
}

///////////////////////////////////////////////////////////////////////////////
/// @method ScanOneToken
///
/// @details Scans the inputted file and searches for the next token. It then
/// stores the token into the passed by reference token.
///
/// @param *token       The token produced by the scan.
/// @return void
///////////////////////////////////////////////////////////////////////////////
void Scanner::ScanOneToken(Token *token)
{
    ScannerState curState = start, nextState = start;
    char curChar;
    
    this->ClearToken(&this->curToken);
    
    // Continue looping through the states until with get the state to be "done"
    while (nextState != done)
    {
        curState = nextState;
        switch (curState)
        {
            case start:
                nextState = this->ProcessStartState(curChar);
                break;
            case comment:
                nextState = this->ProcessCommentState();
                break;
            case identifier:
                nextState = this->ProcessIdentifierState(curChar);
                break;
            case number:
                nextState = this->ProcessNumberState(curChar);
                break;
            case string:
                nextState = this->ProcessStringState(curChar);
                break;
            case plus: case minus: case astrix: case divide: case equal:
                nextState = this->ProcessOperatorState(curChar, curState);
                break;
            case lessThan: lessThanEq: case greatThan: case greatThanEq:
                nextState = this->ProcessOtherTokenState(curChar, curState);
                break;
            case colon: case colonEq: case semicolon: case comma: case leftParen:
                nextState = this->ProcessOtherTokenState(curChar, curState);
                break;
            case rightParen: case leftBracket: case rightBracket: case invalidNot:
                nextState = this->ProcessOtherTokenState(curChar, curState);
                break;
            case illegalChar:
                // We have an error here.
                this->error->ReportErrorMessage("Illegal character found", this->curLineNumber, this->curColNumber);
                nextState = done;
                break;
            default:
                nextState = done;
                break;
        }
    }
    *token = this->curToken;
}

///////////////////////////////////////////////////////////////////////////////
/// @method ClearToken
///
/// @details Clears out the token values to be all 0.
/// @param *token       The token to clear.
/// @return void
///////////////////////////////////////////////////////////////////////////////
void Scanner::ClearToken(Token *token)
{
    token->name = 0;
    token->attribute.doubleValue = 0;
    memset(token->attribute.stringValue, '\0', sizeof(token->attribute.stringValue));
    token->attribute.intValue = 0;
    token->attribute.opValue = 0;
}

void Scanner::GetErrorMessages(std::string messages[])
{
    this->error->GetErrorMessages(messages);
}

Scanner::Scanner(FILE *fp) {
    this->pFile = fp;
    // Create and instance of the Error object for holding the Scanner errors
    this->error = new Error();
    
    // Create an instance of the ReservedTable object for holding the reserved
    // words.
    this->reservedTable = new ReservedTable();
}

Scanner::Scanner(const Scanner& orig) {
}

Scanner::~Scanner() {
}


// ------------------- PRIVATE METHOD DEFINITIONS ----------------------------//

///////////////////////////////////////////////////////////////////////////////
/// @method ProcessStartState()
/// @details This method will be called when the state is the start state in the
/// finite automata. It will get the character from the file and determine the 
/// next state of the finite automata.
///
/// @param char                 The current character that was read.
/// @return ScannerStateType    The next state of the finite automata.
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessStartState(char &curChar)
{
    char nextChar, idChar, curDigit;
    
    curChar = getc(this->pFile);
    
    if (isalpha(curChar))
    {
        idChar = curChar;
        curChar = 'L';
    }
    else if (isdigit(curChar))
    {
        curDigit = curChar;
        curChar = 'N';
    }
    
    switch (curChar)
    {
        case '/':
            // We must check to see if this is a comment or a divide operation
            nextChar = getc(this->pFile);
            if (nextChar == '/')
            {
                // We have a comment. We should continue to a newline character
                // and return nothing.
                return comment;
            }
            else
            {
                // We have a divide operation. We need to back out the last
                // character we read.
                ungetc(nextChar, this->pFile);
                return divide;
            }
        case 'L':
            curChar = idChar;
            return identifier;
        case 'N':
            curChar = curDigit;
            return number;
        case '"':
            return string;
        case '<':
            return lessThan;
        case '>':
            return greatThan;
        case '!':
            return invalidNot;
        case ':':
            return colon;
        case ';':
            return semicolon;
        case ',':
            return comma;   
        case '(':
            return leftParen;
        case ')':
            return rightParen;
        case '{':
            return leftBracket;
        case '}':
            return rightBracket;
        case '+':
            return plus;
        case '-':
            return minus;
        case '*':
            return astrix;
        case '=':
            return equal;
        // Skip white spaces
        case ' ':
            return start;
        // Increment the current line number
        case '\n':
            this->curLineNumber++;
            return start;
        case EOF:
            this->curToken.name = T_EOF;
            return done;
        default:
            return illegalChar;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @method ProcessCommentState()
/// @details This method will be called when the state is the comment state in 
/// the finite automata. It will continue reading characters from the file
/// until it reaches a new line. It will return "done" as its state in order
/// to get the next token.
///
/// @return ScannerStateType    The next tsate of the finite automata.
/// @retval ScannerState::done
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessCommentState()
{  
    // We have a comment so just read the characters until we read a new line.
    char curChar = getc(this->pFile);
    while (curChar != '\n')
    {
        curChar = getc(this->pFile);
    }
    ungetc(curChar, this->pFile);
    return done;
}


///////////////////////////////////////////////////////////////////////////////
/// @method ProcessIdentifierState()
/// @details This method will be called when the state is the identifier state in 
/// the finite automata. It will continue reading characters from the file
/// until it reaches a non alpha or underscore character. It will write the 
/// characters to the token structure. Once all characters are read in it will 
/// check to see if the string of characters is a reserved word and will update
/// the token name appropriately. It will return "done" as its state in order 
/// to get the next token.
///
/// @return ScannerStateType    The next state of the finite automata.
/// @retval ScannerState::done
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessIdentifierState(char curChar)
{
    int curPos = 0;
    this->curToken.attribute.stringValue[curPos] = curChar;
    curPos++;
    
    curChar = getc(this->pFile);
    // Continue getting characters until we don't get a character or underscore
    while (isalpha(curChar) || curChar == '_')
    {
        this->curToken.attribute.stringValue[curPos] = curChar;
        curPos++;
        curChar = getc(this->pFile);
    }
    ungetc(curChar, this->pFile);
    
    // Check to see if the token is a reserved word
    this->curToken.name = this->reservedTable->LookupEntry(std::string(this->curToken.attribute.stringValue));
    if (this->curToken.name == 0)
    {
        // The string value was not a reserved word.
        this->curToken.name = T_IDENTIFIER;
    }
    
    return done;
}


///////////////////////////////////////////////////////////////////////////////
/// @method ProcessNumberState()
/// @details This method will be called when the state is the number state in 
/// the finite automata. It will continue reading characters from the file
/// until it reaches a non digit character. It will write the value of the digits
/// to the token structure and will update the token name appropriately. 
/// It will return "done" as its state in order to get the next token.
///
/// @return ScannerStateType    The next state of the finite automata.
/// @retval ScannerState::done
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessNumberState(char curDigit)
{
    this->curToken.attribute.intValue = curDigit - '0';
    while(isdigit(curDigit = getc(this->pFile)))
        this->curToken.attribute.intValue = this->curToken.attribute.intValue*10 + curDigit - '0';
    ungetc(curDigit, this->pFile);
    // Assume integer type
    this->curToken.name = T_INTEGER;
    
    return done;
}


///////////////////////////////////////////////////////////////////////////////
/// @method ProcessStringState()
/// @details This method will be called when the state is the string state in 
/// the finite automata. It will continue reading characters from the file
/// until it reaches a new line or a matching double quote. It will write 
/// the value of the digits characters to the token structure and will set the
/// token name appropriately. It will return "done" as its state in order to 
/// get the next token.
///
/// @return ScannerStateType    The next state of the finite automata.
/// @retval ScannerState::done
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessStringState(char curChar)
{
    int curPos = 0;
    this->curToken.attribute.stringValue[curPos] = curChar;
    curPos++;
    
    curChar = getc(this->pFile);
    // Continue getting characters until we don't get a character or underscore
    while (isalpha(curChar) || isdigit(curChar) || curChar == '_' || 
            curChar == ',' || curChar == ';' || curChar == ':' || curChar == '.'
            || curChar == ' ')
    {
        this->curToken.attribute.stringValue[curPos] = curChar;
        curPos++;
        curChar = getc(this->pFile);
    }
    if (curChar == '"')
    {
        // TEST Assuming identifiers right now!
        this->curToken.name = T_STRING;
        this->curToken.attribute.stringValue[curPos] = curChar;
    }
    else
    {
        ungetc(curChar,this->pFile);
        // We have an error here!
        this->error->ReportErrorMessage("Invalid String", this->curLineNumber, this->curColNumber);
    }
    
    return done;
}

///////////////////////////////////////////////////////////////////////////////
/// @method ProcessOperatorState()
/// @details This method will be called when the state is one of the operator
/// states in the finite automata. It will look at the current character and 
/// the passed in state and will create a token for the operator.
///
/// @return ScannerStateType    The next state of the finite automata.
/// @retval ScannerState::done
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessOperatorState(char curChar, ScannerStateType state)
{
    switch (state)
    {
        case plus:
            this->curToken.name = T_PLUS;
            this->curToken.attribute.stringValue[0] = curChar;
            break;
        case minus:
            this->curToken.name = T_MINUS;
            this->curToken.attribute.stringValue[0] = curChar;
            break;
        case astrix:
            this->curToken.name = T_MUL;
            this->curToken.attribute.stringValue[0] = curChar;
            break;
        case divide:
            this->curToken.name = T_DIV;
            this->curToken.attribute.stringValue[0] = curChar;
            break;
        case equal:
            this->curToken.name = T_EQUAL;
            this->curToken.attribute.stringValue[0] = curChar;
            break;
        default:
            // Throw an exception here. This is not a compiler error but a
            // programming one.
            return done;
    }
    return done;
}


///////////////////////////////////////////////////////////////////////////////
/// @method ProcessOtherTokenState()
/// @details This method will be called when the state is one of the other
/// token states in the finite automata. It will look at the current character
/// and the state that was passed in and create the correct token.
///
/// @return ScannerStateType    The next state of the finite automata.
/// @retval ScannerState::done
///////////////////////////////////////////////////////////////////////////////
ScannerStateType Scanner::ProcessOtherTokenState(char curChar, ScannerStateType state)
{
    char nextChar;
    switch(curChar)
    {
        case '<':
            nextChar = getc(this->pFile);
            if (nextChar == '=')
            {
                this->curToken.name = T_LTHANEQ;
                this->curToken.attribute.stringValue[1] = '=';
            }
            else
            {
                ungetc(nextChar, this->pFile);
                this->curToken.name = T_LTHAN;
            }
            this->curToken.attribute.stringValue[0] = '<';
            break;
        case '>':
            nextChar = getc(this->pFile);
            if (nextChar == '=')
            {
                this->curToken.name = T_GTHANEQ;
                this->curToken.attribute.stringValue[1] = '=';
            }
            else
            {
                ungetc(nextChar, this->pFile);
                this->curToken.name = T_GTHAN;
            }
            this->curToken.attribute.stringValue[0] = '>';
            break;
        case ':':
            nextChar = getc(this->pFile);
            if (nextChar == '=')
            {
                this->curToken.name = T_COLONEQ;
                this->curToken.attribute.stringValue[1] = '=';
            }
            else
            {
                ungetc(nextChar, this->pFile);
                this->curToken.name = T_COLON;
            }
            this->curToken.attribute.stringValue[0] = ':';
            break;
        case '!':
            nextChar = getc(this->pFile);
            if (nextChar == '=')
            {
                this->curToken.name = T_NOTEQ;
                this->curToken.attribute.stringValue[0] = '!';
                this->curToken.attribute.stringValue[1] = '=';
            }
            else
            {
                // We have an error for an illegal character
                ungetc(nextChar, this->pFile);
                this->error->ReportErrorMessage("Illegal character '!'", this->curLineNumber, this->curColNumber);
                return done;
            }
            break;
        case '(':
            this->curToken.name = T_LPAREN;
            this->curToken.attribute.stringValue[0] = '(';
            break;
        case ')':
            this->curToken.name = T_RPAREN;
            this->curToken.attribute.stringValue[0] = ')';
            break;
        case '{':
            this->curToken.name = T_LBRACKET;
            this->curToken.attribute.stringValue[0] = '{';
            break;
        case '}':
            this->curToken.name = T_RBRACKET;
            this->curToken.attribute.stringValue[0] = '}';
            break;
        case ';':
            this->curToken.name = T_SEMI;
            this->curToken.attribute.stringValue[0] = ';';
            break;
        case ',':
            this->curToken.name = T_COMMA;
            this->curToken.attribute.stringValue[0] = ',';
            break;
        default:
            // Throw an exception here. This is not a compiler error but a
            // programming one.
            return done;           
    }
    return done;
}

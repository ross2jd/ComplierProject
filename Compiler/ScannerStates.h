/* 
 * File:   ScannerStates.h
 * Author: Jordan Ross
 *
 * Created on January 25, 2014, 10:27 AM
 */

#ifndef SCANNERSTATES_H
#define	SCANNERSTATES_H

typedef enum ScannerState {
    start,
    identifier,
    invalidString,
    string,
    number,
    lessThan,
    lessThanEq,
    greatThan,
    greatThanEq,
    colon,
    colonEq,
    semicolon,
    comma,
    plus,
    minus,
    astrix,
    leftParen,
    rightParen,
    equal,
    leftBracket,
    rightBracker,
    invalidNot,
    notEqaul,
    divide,
    comment,
    done
}ScannerStateType;


#endif	/* SCANNERSTATES_H */


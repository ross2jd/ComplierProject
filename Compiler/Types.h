/* 
 * File:   Types.h
 * Author: Jordan Ross
 *
 * Created on January 25, 2014, 8:36 AM
 */

#ifndef TYPES_H
#define	TYPES_H

// Define the string size for the identifiers
static int const STRING_SIZE = 256;

// Token type codes for the recognized reserved words
// Note that these numbers must not change as they are the indecies into the
// the reserved word table. If more reserved words are added the must follow
// sequentially.
#define T_STRING        1
#define T_INT           2
#define T_BOOL          3
#define T_FLOAT         4
#define T_GLOBAL        5
#define T_IN            6
#define T_OUT           7
#define T_IF            8
#define T_THEN          9
#define T_ELSE          10
#define T_CASE          11
#define T_FOR           12
#define T_AND           13
#define T_OR            14
#define T_NOT           15
#define T_PROGRAM       16
#define T_PROCEDURE     17
#define T_BEGIN         18
#define T_RETURN        19
#define T_END           20

// This number should be equal to the last reserved word token type code + 1
static int const NUM_RESERVED_WORDS = 21;

// Other Token Types
#define T_EOF           21
#define T_IDENTIFIER    22
#define T_INTEGER       23



///////////////////////////////////////////////////////////////////////////////
/// @struct Token
/// @brief This structure holds the data for a single token.
///
/// Code adapted from "Lexical Analysis" handout by Maggie Johnson and Julie
/// Zelenski
///////////////////////////////////////////////////////////////////////////////
struct Token
{
    /// Holds the token type code.
    int name;
    
    /// @union value
    union {
        /// holds lexeme value if operation
        int opValue;
        /// holds lexeme value if string/identifier
        char stringValue[STRING_SIZE];
        /// holds lexeme value if integer
        int intValue;
        /// hold lexeme value if double
        double doubleValue;
    } attribute;
};

#endif	/* TYPES_H */


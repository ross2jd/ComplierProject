/* 
 * File:   ReservedTable.cpp
 * Author: Jordan Ross
 * 
 * Created on January 28, 2014, 9:36 AM
 */

#include <string>

#include "ReservedTable.h"

///////////////////////////////////////////////////////////////////////////////
/// @method InsertEntry()
/// @details This method will insert a new entry into the symbol table. The
/// table is set up by having the index of the array reservedWords be the token
/// type code. Then the entry at that index is the standard string representation
/// for the word.
///
/// @param stringValue          Reserved word to insert into the table.
/// @param tokenTypeCode        The code associated with the reserved word. See
///                             Types.h
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void ReservedTable::InsertEntry(std::string stringValue, int tokenTypeCode)
{
    this->reservedWords[tokenTypeCode] = stringValue;
}
    
///////////////////////////////////////////////////////////////////////////////
/// @method LookupEntry()
/// @details This method will look through the reserved table and if it finds
/// the word in the table then it will return the token type code. Otherwise
/// it will return 0.
///
/// @param stringValue   Reserved word to look up in the table.
///
/// @return int
///     @retval 0       Entry not found
///     @retval Other   Token type code for entry
///////////////////////////////////////////////////////////////////////////////
int ReservedTable::LookupEntry(std::string stringValue)
{
    for (int tokenTypeCode = 1; tokenTypeCode < NUM_RESERVED_WORDS; tokenTypeCode++)
    {
        if (stringValue.compare(this->reservedWords[tokenTypeCode]) == 0)
        {
            // We have a match.
            return tokenTypeCode;
        }
    }
    return 0;
}

ReservedTable::ReservedTable() {
    for (int i = 0; i < NUM_RESERVED_WORDS; i++)
    {
        this->reservedWords[i] = "";
    }
}

ReservedTable::ReservedTable(const ReservedTable& orig) {
}

ReservedTable::~ReservedTable() {
}


/* 
 * File:   ReservedTable.h
 * Author: Jordan Ross
 *
 * Created on January 28, 2014, 9:36 AM
 */

#ifndef RESERVEDTABLE_H
#define	RESERVEDTABLE_H

#include "Types.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// @class ReservedTable
/// @brief Class for holding the reserved table and its functions.
///
/// <h1>Design</h1>
/// This will contain the design for the ReservedTable class.
///
/// @author Jordan Ross
///////////////////////////////////////////////////////////////////////////////
class ReservedTable {
public:
    //----------------------- PUBLIC METHODS-------------------------//
    
    /// Method to insert a new entry into the reserved table
    void InsertEntry(std::string stringValue, int tokenTypeCode);
    
    /// Method for looking up if an entry is in the table
    int LookupEntry(std::string stringValue);
    
    /// Default constructor
    ReservedTable();
    
    /// Default copy constructor
    ReservedTable(const ReservedTable& orig);
    
    /// Default destructor
    virtual ~ReservedTable();
private:
    //----------------------- PRIVATE MEMBERS--------------------------//
    
    /// This member holds all reserved words that have been inserted.
    std::string reservedWords[NUM_RESERVED_WORDS];
    
};

#endif	/* RESERVEDTABLE_H */


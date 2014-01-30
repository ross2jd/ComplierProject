/* 
 * File:   SymbolTable.h
 * Author: Jordan Ross
 *
 * Created on January 30, 2014, 5:23 PM
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

#include "Types.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// @class Scanner
/// @brief Class for encapsulating the functionality for the SymbolTable 
/// implementation for compiler
///
/// <h1>Design</h1>
/// This will contain the design for the SymbolTable class.
///
/// @author Jordan Ross
///////////////////////////////////////////////////////////////////////////////
class SymbolTable {
public:
    //----------------------- PUBLIC MEMBERS-------------------------//
    
    /////////////////////////////////////////////////////////////////
    /// @struct SymbolEntry
    /// @details The structure for an entry in the symbol table
    /////////////////////////////////////////////////////////////////
    struct SymbolEntry
    {
        /// The string representation of the symbol
        std::string symbol;
        /// A placeholder for value right now -- WILL CHANGE
        int value;
    };
    
    //----------------------- PUBLIC METHODS-------------------------//
    
    /// Insert entry into Symbol table if it does not already exist.
    void InsertSymbol(std::string symbol);
    
    /// Default Constructor
    SymbolTable();
    
    /// Default Copy Constructor
    SymbolTable(const SymbolTable& orig);
    
    /// Default Destructor
    virtual ~SymbolTable();
private:
    //----------------------- PRIVATE MEMBERS--------------------------//
    
    /// Member to hold the maximum number of symbols in the symbol table.
    static int const MAX_NUMBER_SYMBOLS = 50;
    
    /// This member holds the symbols in the symbol table
    SymbolTable::SymbolEntry symbols[MAX_NUMBER_SYMBOLS];
    
    /// Member to keep track of the next available position in the symbol table.
    int lastSymbol;
    
    //----------------------- PRIVATE METHODS--------------------------//
    
    /// Method to check if a symbol is in the table
    bool IsSymbolInTable(std::string symbol);
};

#endif	/* SYMBOLTABLE_H */


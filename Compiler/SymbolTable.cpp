/* 
 * File:   SymbolTable.cpp
 * Author: Jordan Ross
 * 
 * Created on January 30, 2014, 5:23 PM
 */

#include <string>

#include "SymbolTable.h"

// ------------------- PUBLIC METHOD DEFINITIONS ----------------------------//

///////////////////////////////////////////////////////////////////////////////
/// @method InsertSymbol()
/// @details This method will add a new symbol to the symbol table if it is not
/// already in the table.
///
/// @param symbol       The symbol to attempt to add to the table.
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void SymbolTable::InsertSymbol(std::string symbol)
{
    if (!IsSymbolInTable(symbol))
    {
        this->symbols[this->lastSymbol].symbol = symbol;
        this->lastSymbol++;
    }
}

SymbolTable::SymbolTable() {
    this->lastSymbol = 0;
    for (int i = 0; i < this->MAX_NUMBER_SYMBOLS; i++)
    {
        this->symbols[i].symbol = "";
    }
}

SymbolTable::SymbolTable(const SymbolTable& orig) {
}

SymbolTable::~SymbolTable() {
}


// ------------------- PRIVATE METHOD DEFINITIONS ----------------------------//

///////////////////////////////////////////////////////////////////////////////
/// @method InsertSymbol()
/// @details This method will check to see if the specified symbol is in the
/// symbol table.
///
/// @param symbol       The symbol to check.
///
/// @return bool
///     @retval true    Symbol is in table.
///     @retval false   Symbol is not in table
///////////////////////////////////////////////////////////////////////////////
bool SymbolTable::IsSymbolInTable(std::string symbol)
{
    for (int i = 0; i < this->MAX_NUMBER_SYMBOLS; i++)
    {
        if (symbol.compare(this->symbols[i].symbol) == 0)
            return true;
    }
    return false;
}
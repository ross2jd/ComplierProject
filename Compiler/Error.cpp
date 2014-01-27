/* 
 * File:   Error.cpp
 * Author: Jordan Ross
 * 
 * Created on January 27, 2014, 1:49 PM
 */

#include "Error.h"

///////////////////////////////////////////////////////////////////////////////
/// @method reportErrorMessage()
/// @details This method will add another error message to the array of error
/// messages in this class. It will incorporate the line number and column
/// number.
///
/// @param message      Error message to store
/// @param lineNum      Line number the error occurred on.
/// @param colNum       Column number the error occurred in.
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void Error::ReportErrorMessage(std::string message, int lineNum, int colNum)
{
    std::string errMsg = message + " line: " + std::to_string(lineNum);
    errMsg += " col: " + std::to_string(colNum);
    this->errorMessages[this->curErrorMessage] = errMsg;
    this->curErrorMessage++;
}


///////////////////////////////////////////////////////////////////////////////
/// @method getErrorMessages()
/// @details This method will get all of the error messages that are stored in
/// the errorMessages[] array member and will store them in the array passed to
/// the functions.
///
/// @note The user MUST pass an array of size equal to the constant member
/// MAX_NUM_ERROR_MESSAGES.
///
/// @param messages[]   Reference array to store the errorMessages.
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void Error::GetErrorMessages(std::string messages[])
{
    for (int i = 0; i < this->MAX_NUM_ERROR_MESSAGES; i++)
    {
        messages[i] = this->errorMessages[i];
    }
}


Error::Error() {
    // Reset all members
    this->curErrorMessage = 0;
    for (int i = 0; i < this->MAX_NUM_ERROR_MESSAGES; i++)
    {
        this->errorMessages[i] = "";
    }
}

Error::Error(const Error& orig) {
}

Error::~Error() {
}


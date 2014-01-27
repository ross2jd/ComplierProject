/* 
 * File:   Error.h
 * Author: Jordan Ross
 *
 * Created on January 27, 2014, 1:49 PM
 */

#ifndef ERROR_H
#define	ERROR_H

#include <string>

///////////////////////////////////////////////////////////////////////////////
/// @class Error
/// @brief Class for handling the reporting of errors back to the user.
///
/// <h1>Design</h1>
/// This will contain the design for the Error class.
///
/// @author Jordan Ross
///////////////////////////////////////////////////////////////////////////////
class Error {
public:
    //----------------------- PUBLIC MEMBERS-------------------------//
    
    /// The maximum number of error messages allowed
    static const int MAX_NUM_ERROR_MESSAGES = 20;
    
    //----------------------- PUBLIC METHODS-------------------------//
    
    /// Method to report another error message
    void ReportErrorMessage(std::string message, int lineNum, int colNum);
    
    /// Method for returning all error messages that have been reported
    void GetErrorMessages(std::string messages[]);
    
    /// Default constructor
    Error();
    
    /// Default copy-constructor
    Error(const Error& orig);
    
    /// Default destructor
    virtual ~Error();
private:
    //----------------------- PRIVATE MEMBERS ------------------------//
    
    /// A static array of fixed size to hold the error messages to report
    std::string errorMessages[MAX_NUM_ERROR_MESSAGES];
    
    /// Holds the current position in the array errorMessages
    int curErrorMessage;
    
    //----------------------- PRIVATE METHODS ------------------------//

};

#endif	/* ERROR_H */


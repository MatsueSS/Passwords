#ifndef _ERRORVALUES_H_
#define _ERRORVALUES_H_

#include <iostream>

using std::string;

class ErrorValues : public std::exception {
protected:
    string msg;

public:
    ErrorValues(string msg) noexcept;
    ErrorValues(const ErrorValues& obj) noexcept;

    virtual ~ErrorValues();
    const char* what() const noexcept override;

};

#endif
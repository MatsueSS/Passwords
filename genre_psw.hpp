#ifndef _COURSE_HPP_
#define _COURSE_HPP_

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using std::string;

//not recommended edit this value
enum { fault_num = 5 };

class ErrorValue : public std::exception {
protected:
    string msg;
public:
    ErrorValue(string msg) noexcept;
    ErrorValue(const ErrorValue& obj) noexcept;

    virtual ~ErrorValue();
    virtual const char* what() const noexcept override;
};

class Encryption {
    string msg;
public:
    Encryption(string msg);

    operator std::string();
    void _decryption();
    void _encryption();
};

class Password {
    string chars, password = "";
    Encryption obj();
    int min_l {20}, max_l {21};
    bool flag_crypt = 0;

    void _make_encryption();
    void _make_decryption();
public:
    Password(string chars);

    void operator()();
    string print_password();
    void write(std::ofstream& os, string name);
    void read(std::ifstream& is, string* array, int capacity);
};

#endif //_COURSE_HPP_

#ifndef _COURSE_HPP_
#define _COURSE_HPP_

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using std::string;

//not recommended edit this value
enum { fault_num = 5 };

class ErrorValues : public std::exception {
protected:
    string msg;
public:
    ErrorValues(string msg) noexcept;
    ErrorValues(const ErrorValues& obj) noexcept;

    virtual ~ErrorValues();
    const char* what() const noexcept override;
};

class Encrypt {
    string msg;
    bool flag_crypt = 0;

    void _decryption();
    void _encryption();
public:
    Encrypt(string msg = "");

    operator string();
    void set_msg(string msg, bool flag = 0);
};

class Password {
    Encrypt _password;
    string chars;   
    int min_l, max_l;

    // void _make_encryption();
    // void _make_decryption();
public:
    Password(int min_l = 20, int max_l = 21, string chars = "qwertuiopasdfghjklxcvbnm0123456789@$%&*!ABCDEFGHIJKLMNOPQRSTUVMXYZ");

    void operator()();
    string print_password();
    void write(std::ofstream& os, string name);
    void read(std::ifstream& is, string* array, int capacity);
};

#endif //_COURSE_HPP_

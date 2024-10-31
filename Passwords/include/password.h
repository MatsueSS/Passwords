#ifndef _PASSWORD_H_
#define _PASSWORD_H_

#include "encrypt.h"

#include <iostream>

using std::string;

class Password {
    string name; // name of password
    Encrypt password; // password
    string chars = "qwertuiopasdfghjklxcvbnm0123456789@$%&*!ABCDEFGHIJKLMNOPQRSTUVMXYZ"; // chars for generate password  
    int min_l = 20, max_l = 21; // length password

public:
    Password(string name, int min_l = 20, int max_l = 21, string chars = "qwertuiopasdfghjklxcvbnm0123456789@$%&*!ABCDEFGHIJKLMNOPQRSTUVMXYZ");
    Password(Encrypt msg);

    const string& getName();
    void setName(const string& name);

    void generatePassword();

    const string& getPassword(); // get encrypt password
    void setPassword(const string& psw); // set encrypt password
    const string printPassword(); // print decrypt password

    void read(const string& fileName);
    void write(const string& fileName);
};

#endif
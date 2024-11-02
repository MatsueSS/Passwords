#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#include <iostream>

enum { fault_num = 5 };

using std::string;

class Encrypt {
    string msg; // message for encrypt
    bool flag_crypt = 0;

    void _decryption(); // make decryption
    void _encryption(); // make encryption

public:
    Encrypt(string msg);
    Encrypt(const Encrypt& obj);

    const string getDecryptMsg();
    void setDecryptMsg(const string& msg);

    const string& getEncryptMsg();
    void setEncryptMsg(const string& msg);

};

#endif
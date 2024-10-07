#ifndef _PASSWORDS_H_
#define _PASSWORDS_H_

#include <string>
#include <map>

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

class File {
public:
    virtual void read(const string& filename) = 0;
    virtual void write(const string& filename) = 0;
};

class Encrypt {
    string msg; // message for encrypt
    bool flag_crypt = 0;

    void _decryption(); // make decryption
    void _encryption(); // make encryption

public:
    Encrypt(string msg = "");
    Encrypt(const Encrypt& obj);

    const string getDecryptMsg();
    void setDecryptMsg(const string& msg);

    const string& getEncryptMsg();
    void setEncryptMsg(const string& msg);

};

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

class PasswordFileManager : public File {
    Password* password;
public:
    PasswordFileManager(Password* psw);

    virtual void write(const string& filename) override;
    virtual void read(const string& filename) override;
};

class LibPasswords {
    std::map<string, Password> libPsw;

    enum sort { _quick_sort = 0, _choice_sort = 1, _bubble_sort = 2, _pyramid_sort = 3, _insert_sort = 4 };

public:
    LibPasswords();

    void removePassword(string name);
    void addPassword(string name, Password psw);
    void sortPasswords(sort type);
    Password findPassword(const string& name);

    std::map<string, Password>& getLib();
    
    string operator[](int size);

    void read(const string& fileName);
    void write(const string& fileName);

    friend void QuickSort(LibPasswords& lib, int low, int high, bool(*func)(string, string));
};

class LibPasswordsFileManager : public File {
    LibPasswords* lib;
public:
    LibPasswordsFileManager(LibPasswords* lib);

    virtual void write(const string& filename) override;
    virtual void read(const string& filename) override;
};

#endif //_PASSWORDS_H_

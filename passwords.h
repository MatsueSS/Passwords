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
    virtual void read(string fileName) = 0;
    virtual void write(string fileName) = 0;
};

class Encrypt {
    string msg; // message for encrypt
    bool flag_crypt = 0;

    void _decryption(); // make decryption
    void _encryption(); // make encryption

public:
    Encrypt(string msg = "");
    Encrypt(const Encrypt& obj);

    void getMsg(string& msg);
    void setMsg(string newMsg);
    string showMsg() const;
};

class Password : public File {
    string name; // name of password
    Encrypt password; // password
    string chars; // chars for generate password  
    int min_l, max_l; // length password

public:
    Password(int min_l = 20, int max_l = 21, string chars = "qwertuiopasdfghjklxcvbnm0123456789@$%&*!ABCDEFGHIJKLMNOPQRSTUVMXYZ");
    Password(Encrypt msg);

    void generatePassword();
    Encrypt showPassword() const;
    string printPassword();

    virtual void read(string fileName) override;
    virtual void write(string fileName) override;
};

class LibPasswords : public File {
    std::map<string, Password> libPsw;

    enum sort { _quick_sort = 0, _choice_sort = 1, _bubble_sort = 2, _pyramid_sort = 3, _insert_sort = 4 };

public:
    LibPasswords();

    void removePassword(string name);
    void addPassword(string name, Password psw);
    void sortPasswords(sort type, bool(*func)(string, string));
    
    string operator[](int size);

    virtual void read(string fileName) override;
    virtual void write(string fileName) override;

    friend void QuickSort(LibPasswords& lib, int low, int high, bool(*func)(string, string));
    friend void ChoiceSort(LibPasswords& lib, int n, bool(*func)(string, string));
    
};

#endif //_PASSWORDS_H_

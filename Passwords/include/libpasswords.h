#ifndef _LIB_PASSWORDS_H_
#define _LIB_PASSWORDS_H

#include "password.h"

#include <map>

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

#endif
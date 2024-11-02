#ifndef _LIB_PASSWORDS_FILE_MANAGER_H_
#define _LIB_PASSWORDS_FILE_MANAGER_H_

#include "file.h"

class LibPasswords;

class LibPasswordsFileManager : public File {
    LibPasswords* lib;
public:
    LibPasswordsFileManager(LibPasswords* lib);

    virtual void write(const string& filename) override;
    virtual void read(const string& filename) override;
};

#endif
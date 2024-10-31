#ifndef _PASSWORD_FILE_MANAGER_H_
#define _PASSWORD_FILE_MANAGER_H_

#include "file.h"

class Password;

class PasswordFileManager : public File {
    Password* password;
public:
    PasswordFileManager(Password* psw);

    virtual void write(const string& filename) override;
    virtual void read(const string& filename) override;
};

#endif
#include "passwordfilemanager.h"
#include "password.h"

Password::Password(string name, int min_l, int max_l, string chars) : name(name), min_l(min_l), max_l(max_l), chars(chars), password("") { srand(time(nullptr)); }

void Password::generatePassword(){
    string psw = "";
    int length = rand()%(max_l-min_l)+min_l;
    for(int i = 0; i < length; i++){
        psw += chars[rand()%chars.size()];
    }
    password.setDecryptMsg(psw);
}

Password::Password(Encrypt msg) : password(msg) {}

const string Password::printPassword() { return password.getDecryptMsg(); }

void Password::setPassword(const string& psw) { password.setEncryptMsg(psw); }

const string& Password::getPassword() { return password.getEncryptMsg(); }

const string& Password::getName() { return name; }

void Password::setName(const string &name) { this->name = name; }

void Password::read(const string& filename){
    PasswordFileManager user(this);
    user.read(filename);
}
void Password::write(const string& filename){
    PasswordFileManager user(this);
    user.write(filename);
}
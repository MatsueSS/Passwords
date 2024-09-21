#include "passwords.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

ErrorValues::ErrorValues(string msg) noexcept : msg(msg) {}
ErrorValues::ErrorValues(const ErrorValues& obj) noexcept : msg(obj.msg) {}
ErrorValues::~ErrorValues() {}
const char* ErrorValues::what() const noexcept { return msg.c_str(); }

Encrypt::Encrypt(string msg) : msg(msg) { _encryption(); }
void Encrypt::_encryption(){
    for(int i = 0; i < msg.size(); i++){
        msg[i] += fault_num;
        if(msg[i] > 126) msg[i] = 32 + (msg[i] - 127);
    }
    flag_crypt = 1;
}
Encrypt::Encrypt(const Encrypt& obj) : msg(obj.msg), flag_crypt(obj.flag_crypt) {}
void Encrypt::_decryption(){
    for(int i = 0; i < msg.size(); i++){
        msg[i] -= fault_num;
        if(msg[i] < 32) msg[i] = 127 - (32 - msg[i]);
    }
    flag_crypt = 0;
}
void Encrypt::getMsg(string& msg) { _decryption(); msg = this->msg; _encryption(); }
void Encrypt::setMsg(string newMsg) { msg = newMsg; _encryption(); }
string Encrypt::showMsg() const { return msg; }

Password::Password(int min_l, int max_l, string chars) : min_l(min_l), max_l(max_l), chars(chars) { srand(time(nullptr)); }
void Password::generatePassword(){
    string psw = "";
    int length = rand()%(max_l-min_l)+min_l;
    for(int i = 0; i < length; i++){
        psw += chars[rand()%chars.size()];
    }
    password.setMsg(psw);
}
Password::Password(Encrypt msg) : password(msg) {}
string Password::printPassword() { string psw; password.getMsg(psw); return psw; }
Encrypt Password::showPassword() const { return password; }
/*virtual*/void Password::read(string fileName){
    std::ifstream file(fileName);
    if(file.is_open()){
        string psw = "";
        while(!file.eof()){
            string line;
            std::getline(file, line);
            for(int i = 0, flag = 0; i < line.size(); i++){
                if(flag == 1) psw += line[i];
                if(line[i] == ' ') flag = 1;
                if(flag == 0) name += line[i];
            }
        }
        password.setMsg(psw);
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}
/*virtual*/void Password::write(string fileName){
    std::ofstream file(fileName);
    if(file.is_open()){
        file << name << " " << password.showMsg() << "\n";
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}

LibPasswords::LibPasswords() {}
void LibPasswords::addPassword(string name, Password psw){
    libPsw.insert(libPsw.end(), {name, psw});
}
void LibPasswords::removePassword(string name){
    libPsw.erase(libPsw.find(name));
}
/*virtual*/void LibPasswords::read(string fileName){
    std::ifstream file(fileName);
    if(file.is_open()){
        while(!file.eof()){
            string line, name = "", psw = "";
            std::getline(file, line);
            for(int i = 0, flag = 0; i < line.size(); i++){
                if(flag == 1) psw += line[i];
                if(line[i] == ' ') flag = 1;
                if(flag == 0) name += line[i];
            }
            addPassword(name, Password(Encrypt(psw)));
        }
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}
/*virtual*/void LibPasswords::write(string fileName){
    std::ofstream file(fileName);
    if(file.is_open()){
        std::map<string, Password>::iterator it = libPsw.begin();
        while(it != libPsw.end()){
            file << (*it).first << " " << (*it).second.showPassword().showMsg() << "\n";
            it++;
        }
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}
string LibPasswords::operator[](int size){
    if(size >= libPsw.size()) throw ErrorValues("Size must be less than size map");
    std::map<string, Password>::iterator it = libPsw.begin();
    for(int i = 0; i < libPsw.size() && i != size; i++) it++;
    return (*it).first;
}
template <typename T>
bool increase(T a, T b) { return a > b; }

template<typename T>
bool decrease(T a, T b) { return a < b; }

void LibPasswords::sortPasswords(sort type, bool(*func)(string, string)){
    switch (type){
    case _quick_sort:
        QuickSort(*this, 0, libPsw.size(), func);
        break;
    case _choice_sort:
        ChoiceSort(*this, libPsw.size(), func);
        break;
    }
}
void swap(std::map<string, Password>::iterator a, std::map<string, Password>::iterator b){
    std::map<string, Password>::iterator temp = a;
    a = b;
    b = temp;
}
void QuickSort(LibPasswords& lib, int low, int high, bool(*func)(string, string)){
    if(low > high) return;
    string p = lib[(low+high)/2];
    int i = low, j = high;
    while(i <= j){
        while(func(p, lib[i])) i++;
        while(func(lib[j], p)) j--;
        if(i <= j){
            swap(lib.libPsw.find(lib[i++]), lib.libPsw.find(lib[j--]));
        }
    }
    QuickSort(lib, low, j, func);
    QuickSort(lib, i, high, func);
}
void ChoiceSort(LibPasswords& lib, int n, bool(*func)(string, string)){
    for(int i = 0; i < lib.libPsw.size()-1; i++){
        string temp = lib[i];
        int flagJ;
        for(int j = i+1; j < lib.libPsw.size(); j++){
            if(func(temp, lib[j])) { temp = lib[j]; flagJ = j; }
        }
        if(temp != lib[i]){
            swap(lib.libPsw.find(lib[i]), lib.libPsw.find(lib[flagJ]));
        }
    }
}

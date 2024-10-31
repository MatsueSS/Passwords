#include "libpasswordsfilemanager.h"
#include "libpasswords.h"
#include "errorvalues.h"

#include <algorithm>

LibPasswords::LibPasswords() {}
void LibPasswords::addPassword(string name, Password psw){
    libPsw.insert(libPsw.end(), {name, psw});
}
void LibPasswords::removePassword(string name){
    libPsw.erase(libPsw.find(name));
}
Password LibPasswords::findPassword(const string& name){
    if(libPsw.find(name) != libPsw.end()) return libPsw.find(name)->second;
    throw ErrorValues("Password is not find");
}

std::map<string, Password>& LibPasswords::getLib(){
    return libPsw;
}

void LibPasswords::read(const string& filename){
    LibPasswordsFileManager user(this);
    user.read(filename);
}
void LibPasswords::write(const string& filename){
    LibPasswordsFileManager user(this);
    user.write(filename);
}
string LibPasswords::operator[](int size){
    if(size >= libPsw.size()) throw ErrorValues("Size must be less than size map");
    std::map<string, Password>::iterator it = libPsw.begin();
    for(int i = 0; i < libPsw.size() && i != size; i++) it++;
    return (*it).first;
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
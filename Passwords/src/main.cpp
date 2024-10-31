#include "libpasswords.h"

#include <iostream>

int main(void){
    Password psw1("Michael");
    Password psw2("MatsueSS");
    Password psw3("Elize");
    psw1.generatePassword();
    psw2.generatePassword();
    psw3.generatePassword();

    LibPasswords lib;
    lib.addPassword(psw1.getName(), psw1);
    lib.addPassword(psw2.getName(), psw2);
    lib.addPassword(psw3.getName(), psw3);

    for(int i = 0; i < 3; i++) std::cout << lib[i] << "\n";
    
    return 0;
}
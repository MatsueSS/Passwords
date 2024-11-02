#include "libpasswords.h"
#include "errorvalues.h"

#include <iostream>

int main(void){
    for(;;){
        int n1, n2;
        std::cout << "Введите номер функции:\n1.Добавить пароль\n2.Вывести пароль\n3.Выход\n";
        std::cin >> n1;
        if(n1 == 1){
            Password psw("");
            string name = "";
            std::cout << "Введите имя: ";
            std::cin >> name;
            psw.setName(name);
            std::cout << "1.Свой пароль\n2.Сгенерировать пароль\n";
            std::cin >> n2;
            if(n2 == 1) {
                string encr;
                std::cout << "Введите пароль: ";
                std::cin >> encr;
                Encrypt msg(encr);
                psw.setPassword(msg.getEncryptMsg());
            }
            else if(n2 == 2){
                psw.generatePassword();
            }
            else throw ErrorValues("Out of index in main.cpp\n");
            psw.write("../resources/psw.txt");
        }
        else if(n1 == 2){
            LibPasswords lib;
            lib.read("../resources/psw.txt");
            string name;
            std::cout << "Введите имя обладателя пароля для его вывода: ";
            std::cin >> name;
            std::cout << lib.findPassword(name).printPassword() << std::endl;
        }
        else if(n1 == 3) break;
        else throw ErrorValues("Out of index in main.cpp\n");
    }

    return 0;
}
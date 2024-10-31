#include "passwordfilemanager.h"
#include "errorvalues.h"
#include "password.h"

#include <fstream>

PasswordFileManager::PasswordFileManager(Password* password) : password(password) {}

/*virtual*/void PasswordFileManager::read(const string& filename)
{
    std::ifstream file(filename);
    if(file.is_open()){
        string psw = "";
        string name = "";
        while(!file.eof()){
            string line = "";
            std::getline(file, line);
            if(line.size() < 3) break;
            name = "";
            psw = "";
            for(int i = 0, flag = 0; i < line.size(); i++){
                if(flag == 1) psw += line[i];
                if(line[i] == ' ') flag = 1;
                if(flag == 0) name += line[i];
            }
        }
        password->setName(name);
        password->setPassword(psw);
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}

/*virtual*/void PasswordFileManager::write(const string& filename)
{
    std::ofstream file(filename, std::ios::app);
    if(file.is_open()){
        file << password->getName() << " " << password->getPassword() << "\n";
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}
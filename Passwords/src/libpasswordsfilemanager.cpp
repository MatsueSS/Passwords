#include "libpasswordsfilemanager.h"
#include "errorvalues.h"
#include "libpasswords.h"

#include <fstream>

LibPasswordsFileManager::LibPasswordsFileManager(LibPasswords* lib) : lib(lib) {}

/*virtual*/void LibPasswordsFileManager::read(const string& filename){
    std::ifstream file(filename);
    if(file.is_open()){
        while(!file.eof()){
            string line, name = "", psw = "";
            std::getline(file, line);
            if(line.size() < 3) break;
            for(int i = 0, flag = 0; i < line.size(); i++){
                if(flag == 1) psw += line[i];
                if(line[i] == ' ') flag = 1;
                if(flag == 0) name += line[i];
            }
            Encrypt obj("");
            obj.setEncryptMsg(psw);
            lib->addPassword(name, Password(obj));
        }
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}
/*virtual*/void LibPasswordsFileManager::write(const string& filename){
    std::ofstream file(filename);
    if(file.is_open()){
        std::map<string, Password>::iterator it = lib->getLib().begin();
        while(it != lib->getLib().end()){
            file << (*it).first << " " << (*it).second.getPassword() << "\n";
            it++;
        }
    }
    else throw ErrorValues("File cannot be opened");
    file.close();
}
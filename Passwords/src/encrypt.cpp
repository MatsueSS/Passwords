#include "encrypt.h"

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

const string Encrypt::getDecryptMsg() {
    _decryption();
    string temp = msg;
    _encryption();
    return temp;
}

void Encrypt::setDecryptMsg(const string& msg) {
    _decryption();
    this->msg = msg;
    _encryption();
}

const string& Encrypt::getEncryptMsg() {
    return msg;
}

void Encrypt::setEncryptMsg(const string& msg){
    this->msg = msg;
}
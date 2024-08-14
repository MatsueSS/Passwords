#include "genre_psw.hpp"

Password::Password(int min_l, int max_l, string chars) : min_l(min_l), max_l(max_l), chars(chars)
{ 
    srand(time(nullptr)); 
}

void Password::operator()()
{
    string psw = "";
    int roll = rand()%(max_l-min_l)+min_l;
    for(int i = 0; i < roll; i++)
    {
        psw += chars[rand()%chars.size()];
    }
    this->_password.set_msg(psw);
}

string Password::print_password()
{
    return _password;
}

void Password::write(std::ofstream& os, string name)
{
    if(os.is_open()){ os << name << " " << string(_password) << '\n'; }
    else throw ErrorValues("Error with write your file or created");
}

void Password::read(std::ifstream& is, string* array, int capacity = 100)
{
    if(is.is_open())
    {
        int size = 0;
        while(!is.eof())
        {
            if(size == capacity) break;
            string psw = "";
            std::getline(is, array[size]);
            for(int i = 0, flag = 0; i < array[size].size(); i++)
            {
                if(flag == 1) psw+=array[size][i];
                if(array[size][i] == ' ') flag = 1;
            }
            _password.set_msg(psw, true);
            array[size++] = _password;
        }
    }
    else throw ErrorValues("Error with read your file");
}

ErrorValues::ErrorValues(string msg) noexcept : msg(msg) { }
ErrorValues::ErrorValues(const ErrorValues& obj) noexcept : msg(obj.msg) { }
ErrorValues::~ErrorValues() { }

const char* ErrorValues::what() const noexcept { return msg.c_str(); }

Encrypt::Encrypt(string msg) : msg(msg) { _encryption(); }

Encrypt::operator string() { _decryption(); string new_msg = msg; _encryption(); return new_msg; }

void Encrypt::_encryption() 
{
    for(int i = 0; i < msg.size(); i++) {
        msg[i] += fault_num; 
        if(msg[i] > 126) msg[i] = 32 + (msg[i] - 127);
    }
    flag_crypt = 1;
}

void Encrypt::_decryption()
{
    for(int i = 0; i < msg.size(); i++){
        msg[i] -= fault_num; 
        if(msg[i] < 32) msg[i] = 127 - (32 - msg[i]);
    }
    flag_crypt = 0;
}

void Encrypt::set_msg(string msg, bool flag) 
{ 
    if(flag == 0) { this->msg = msg; _encryption(); }
    else { this->msg = msg; }
}

int main(void)
{
    string array[100];
    Password obj;
    std::ofstream file1("course111.txt", std::ios::app);

    obj();
    std::cout << obj.print_password() << std::endl;
    obj.write(file1, "yandex");
    obj();
    std::cout << obj.print_password() << std::endl;
    obj.write(file1, "google");
    obj();
    std::cout << obj.print_password() << std::endl;
    obj.write(file1, "VK");
    file1.close();

    std::ifstream file2("course111.txt", std::ios::in);
    obj.read(file2, array);
    for(int i = 0; i < 3; i++) std::cout << array[i] << std::endl;
    file2.close();

    return 0;
}

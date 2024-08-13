#include "course.hpp"

Password::Password(string chars = "qwertuiopasdfghjklxcvbnm0123456789@$%&*!ABCDEFGHIJKLMNOPQRSTUVMXYZ") : chars(chars) 
{ 
    srand(time(nullptr)); 
}

void Password::_make_encryption() 
{ 
    for(int i = 0; i < password.size(); i++) {
        password[i] += fault_num; 
        if(password[i] > 126) password[i] = 32 + (password[i] - 127);
    }
    flag_crypt = 1; 
}

/*
void Password::_make_encryption()
{

}
*/

void Password::_make_decryption() 
{ 
    for(int i = 0; i < password.size(); i++){
        password[i] -= fault_num; 
        if(password[i] < 32) password[i] = 127 - (32 - password[i]);
    }
    flag_crypt = 0; 
}

void Password::write(std::ofstream& os, string name = "") 
{ 
    if(flag_crypt == 0) _make_encryption();
    if(os.is_open()) os << name << " " << password << '\n';
    else throw ErrorValue("File cannot be opened");
}

void Password::read(std::ifstream& is, string* array, int capacity = 100)
{ 
    if(is.is_open())
    {
        int size = 0;
        while(!is.eof())
        {
            string psw = "";
            std::getline(is, array[size]);
            for(int i = 0, flag = 0; i < array[size].size(); i++)
            {
                if(flag == 1) psw+=array[size][i];
                if(array[size][i] == ' ') flag = 1;
            }
            this->password = psw;
            _make_decryption();
            array[size++] = password;
        }
    }
    else throw ErrorValue("File cannot be opened");
}

string Password::print_password() 
{ 
    _make_decryption(); 
    return password;
}

void Password::operator()() 
{
    password = "";
    int roll = rand()%(max_l-min_l)+min_l;
    for(int i = 0; i < roll; i++)
    {
        password += chars[rand()%chars.size()];
    }
    _make_encryption();
}

ErrorValue::ErrorValue(string msg) : msg(msg) { }
ErrorValue::ErrorValue(const ErrorValue& obj) : msg(obj.msg) { }
ErrorValue::~ErrorValue() { }

const char* ErrorValue::what() const { return msg.c_str(); }

Encryption::Encryption(string msg = "") : msg(msg) { }

Encryption::operator std::string() { return msg; }

void Encryption::_encryption() 
{
    for(int i = 0; i < msg.size(); i++) {
        msg[i] += fault_num; 
        if(msg[i] > 126) msg[i] = 32 + (msg[i] - 127);
    }
}

void Encryption::_decryption()
{
    for(int i = 0; i < msg.size(); i++){
        msg[i] -= fault_num; 
        if(msg[i] < 32) msg[i] = 127 - (32 - msg[i]);
    }
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

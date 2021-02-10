#include "pasman.h"

int main(){
    pasman p;
    p.init_file();
    std::cout << p.get_password(0) << '\n';
    /*std::fstream file("pass");
    std::vector<std::string> vec;
    std::string mess;
    while(!file.eof()) {
    getline(file, mess);
    vec.push_back(mess);
    }
    std::cout << vec.at(1) << '\n' << vec.at(0) << '\n';
    */
    return 0;
}
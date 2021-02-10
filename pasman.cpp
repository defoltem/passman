#include "pasman.h"

void pasman::init_file(){
    std::string file_name;
    std::cout << "Write the file that contain passwords (press enter for file by default) ? ";
    getline(std::cin, file_name);
    if (file_name == "") file.open(deflt);
    else file.open(file_name);
    if(file) std::cout << "file's open properly\n";
    else std::cout << "there isn't any file like that\n";
}

std::string pasman::get_password(int ord){
    return passwords.at(ord);
}

std::string pasman::get_description(int ord){
    return descriptions.at(ord);
}


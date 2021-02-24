#include "pasman.h"

void pasman::init_file(){
    std::string file_name;
    std::cout << "Write the file that contain passwords (press enter for the file by default) ? ";
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

void pasman::read_file(){
    std::string per = "";
    while(!file.eof()){
        getline(file, per);
        lines.push_back(per);
    }
}

std::string pasman::get_line(int ord){
    return lines.at(ord);
}

void pasman::split_lines() {
    for(const std::string s:lines) {
        int pos1 = 0;
        int pos2 = s.find(";");
        descriptions.push_back(s.substr(pos1, pos2));
        pos1 = s.size();
        passwords.push_back(s.substr(pos2+1, pos1));
    }
}

void pasman::descr_list() {
    for(const std::string s:descriptions){
        std::cout << s << '\n';
    }
}
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
        show_pas.push_back(false);
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

void pasman::print_descr(std::string s){
    for(const char c:s) addch(c | A_STANDOUT);
    printw(" - ");
}

void pasman::descr_list() {
    keypad(stdscr, true);
    initscr();
    curs_set(0);
    while(1) {
        clear();
        for(size_t i = 0; i < descriptions.size(); i++) {
            if (choice == i) print_descr(get_description(i));
            else printw("%s - ", get_description(i).c_str());
            if(show_pas.at(i) == true) printw("%s\n", get_password(i).c_str());
            else addch('\n');
        }
        switch(getch()) {
            case 107:
                if(choice) choice--;
            break;
            case 106:
                if(choice < descriptions.size()) choice++;
            break;
            case 10:
                if (!show_pas.at(choice)) show_pas.at(choice) = true;
                else show_pas.at(choice) = false;
            break;
        }
    }
}
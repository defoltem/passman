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

void pasman::delete_record(int ord) {
    size_t lenght = lines.size();
    for (size_t i = ord; i < lenght-1; i++){
        lines.at(i) = lines.at(i+1);
        passwords.at(i) = passwords.at(i+1);
        descriptions.at(i) = descriptions.at(i+1);
        show_pas.at(i) = show_pas.at(i+1);
    }   
}

void pasman::descr_list() {
    keypad(stdscr, true);
    initscr();
    curs_set(0);
    while(1) {
        clear();
        printw("press 'd' to activate the delete mode\nuse 'j' (down) and 'k' (up) keys to move\npress 'enter' to choose\n");
        if (delete_mod) printw("delete mod is active!\n");
        for(size_t i = 0; i < descriptions.size(); i++) {
            if (choice == i) { 
                printw("%d ", i);
                print_descr(get_description(i));
            }
            else printw("%d %s - ", i,get_description(i).c_str());
            if(show_pas.at(i) == true) printw("%s\n", get_password(i).c_str());
            else addch('\n');
        }
        switch(getch()) {
            case 'k':
                if(choice) choice--;
            break;
            case 'j':
                if(choice < descriptions.size()) choice++;
            break;
            case 10:
                if(delete_mod) {
                    delete_record(choice);
                } else {
                if (!show_pas.at(choice)) show_pas.at(choice) = true;
                else show_pas.at(choice) = false;
                }
            break;
            case 'd':
                if (delete_mod == true) delete_mod = false;
                else delete_mod = true;
            break;
        }
    }
}
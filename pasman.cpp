#include "pasman.h"

void pasman::init_file(){
    std::string file_name;
    std::cout << "Write the file that contain passwords (press enter for the file by default) ? ";
    getline(std::cin, file_name);
    if (file_name == "") file.open(deflt);
    else file.open(file_name);
    if(file) std::cout << "file's open properly\n";
    else { 
        std::cout << "there isn't any file like that\n";
        exit(0);
    }
    std::cout << "write a key (it have to be 16 symbols or remaining field will fill by zeros) ? ";
    getline(std::cin, key_string);
    if (key_string.size() < 16) {
        for (size_t i = key_string.size(); i < 16; i++){
            key_string += "0";
        }
    }
    iv = SecByteBlock((const byte*)key_string.data(), key_string.size());
    key = SecByteBlock((const byte*)key_string.data(), key_string.size()); // convert to SecByteBlock
}

std::string pasman::get_password(int ord){
    return passwords.at(ord);
}

std::string pasman::get_description(int ord){
    return descriptions.at(ord);
}

void pasman::read_file(){
    try {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);
        std::string per = "";
        std::string recovered = "";
        while(!file.eof()){
            getline(file, per);
            if(per == "") break;
            StringSource ss(per, true, new HexDecoder(new StreamTransformationFilter(d, new StringSink(recovered))));
            lines.push_back(recovered);
        }
    } catch(const CryptoPP::Exception &e) {
        std::cout << "wrong password\n";
        exit(0);
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
        show_pas.push_back(false);
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

void pasman::write_file(){
    //SecByteBlock iv = SecByteBlock((const byte*)key_string.data(), key_string.size());
    //SecByteBlock key((const byte*)key_string.data(), key_string.size());// convert to SecByteBlock
    std::string cipher, encoded;
    file.close();
    CBC_Mode< AES >::Encryption e;
    e.SetKeyWithIV( key, key.size(), iv );
    std::ofstream fout;
    fout.open("pass");
    size_t lenght = lines.size();
    for (size_t i = 0; i < lenght; i++){
        StringSource ss1(lines.at(i), true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(cipher)));
        StringSource ss2(cipher, true, new CryptoPP::HexEncoder( new CryptoPP::StringSink(encoded)));
        fout << encoded << '\n';
    }
    printw("the file was rewritten\n");
}

void pasman::add_new_record(){
    endwin();
    system("clear");
    std::string pas, descr, cmplt;
    std::cout << "Write a description for your password ? ";
    getline(std::cin, descr);
    std::cout << "Write the password ? ";
    getline(std::cin, pas);
    cmplt = descr + ';' + pas;
    std::cout << cmplt << '\n';
    lines.push_back(cmplt);
    int pos1 = 0;
    int pos2 = cmplt.find(";");
    descriptions.push_back(cmplt.substr(pos1, pos2));
    pos1 = cmplt.size();
    passwords.push_back(cmplt.substr(pos2+1, pos1));
    show_pas.push_back(false);
    system("clear");
}

void pasman::descr_list() {
    keypad(stdscr, true);
    initscr();
    curs_set(0);
    while(1) {
        clear();
        printw("Use 'j' (down) and 'k' (up) keys to move\nPress 'd' to activate the delete mode\nPress 'enter' to choose\nPress 'a' to add a new record\nPress 's' to save changes\nPress 'e' to exit the programm\n");
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
            case 'a':
                add_new_record();
            break;
            case 's':
                write_file();
            break;
            case 'e':
                endwin();
                system("clear");
                exit(0);
            break;
        }
    }
}

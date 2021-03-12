#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ncurses.h>

class pasman {
    size_t choice = 0;
    bool delete_mod = false;
    std::string deflt = "pass";
    std::vector<std::string> lines;
    std::vector<std::string> passwords;
    std::vector<std::string> descriptions;
    std::vector<bool> show_pas;
    std::ifstream file;
public:
    void init_file(); // file's init
    void read_file(); // read the file's information
    void split_lines(); // split lines to passwords and descriptions
    void descr_list(); // show the list of descriptions
    void delete_record(int ord);
    void add_new_record(); // add new record to the lines vector
    void print_descr(std::string s); // write the highlated line
    void write_file(); 
    std::string get_description(int ord); // return a description
    std::string get_password(int ord); // return a password
    std::string get_line(int ord); // return a line (uses for debug)
};
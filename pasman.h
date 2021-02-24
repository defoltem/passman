#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class pasman {
    std::string description, password, deflt = "pass";
    std::vector<std::string> lines;
    std::vector<std::string> passwords;
    std::vector<std::string> descriptions;
    std::fstream file;
public:
    void init_file(); // file's init
    void read_file(); // read the file's information
    void split_lines(); // split lines to passwords and descriptions
    void descr_list(); // show the list of descriptions
    void add_new_record(); // add new record to the lines vector
    std::string get_description(int ord); // return a description
    std::string get_password(int ord); // return a password
    std::string get_line(int ord); // return a line (uses for debug)
};
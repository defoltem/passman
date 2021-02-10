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
    void init_file();
    void read_file();
    void add_new_record();
    std::string get_description(int ord);
    std::string get_password(int ord);
};
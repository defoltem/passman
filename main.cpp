#include "pasman.h"

int main(){
    pasman p;
    p.init_file();
    p.read_file();
    p.split_lines();
    p.descr_list();
    return 0;
}
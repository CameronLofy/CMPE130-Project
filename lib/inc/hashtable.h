//
// Created by camer on 5/3/2019.
//

#ifndef CMPE_130_HASHTABLE_H
#define CMPE_130_HASHTABLE_H

#include "contact_node.h"
#include <string>
using namespace std;
namespace lib{
    class hashtable{

        unsigned int size = 8963;
    public:
        contact_node **hash_table;
        hashtable();
        ~hashtable();
        int hash_func(std::string name);
        void insert(string name, string num);
        void delete_entry(string name, string num);
        contact_node* get(string name);
        void list_all();
        string num_parse(string num);
        string name_parse(string name);
        string format_name(string name);
        string format_num(string num);
        bool is_num(char n);
        bool is_letter(char l);


    };
}

#endif //CMPE_130_HASHTABLE_H

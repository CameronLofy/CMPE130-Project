//
// Created by camer on 5/4/2019.
//


#include "hashtable.h"
#include "contact_node.h"
#include <string>
#include <iostream>

using namespace std;  //Not sure why this is getting errors
namespace lib{
    class contact_node {     // Node used to store each name added to hashtable
    public:
        info_node *num_node;    // String for phone number
        string name;            // String for name (basically the key)
        contact_node *next;        // Node for chaining

        //initializing the contact_node
        contact_node(string name, string num) {
            this->num_node = new info_node(num); //Stores numbers associated to the name.
            this->name = name;
            this->next = nullptr;
        };

        static void print_all();
    };

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
    

    void contact_node::print_all(){
        hashtable hashtable;
        contact_node *entry = this;
        info_node *info = entry->num_node;
        while(info != nullptr)
        {
            cout<< hashtable.format_name(name) << ", "<< info->num << endl;
            info = info->next_num;
        }
    }
}